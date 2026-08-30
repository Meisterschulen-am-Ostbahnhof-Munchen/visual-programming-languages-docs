# ScrollFS

![ScrollFS](ScrollFS.svg)

* * * * * * * * * *

## Introduction

`ScrollFS` is the pure position engine of a scrollable VT list: it holds the current row
position (0…`i32PosMax`), reacts to navigation events (line/page up/down, first/last, absolute
position) and writes the matching Y offset for both the list content and the scrollbar thumb via
two `Q_ChildPosition` calls (ISO 11783-6 F.16, "Change Child Location") to the VT. It reads
**no** physical buttons or input fields — that's what [ScrollFS_PHYS](ScrollFS_PHYS.md) and
[ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.md) are for, which wrap `ScrollFS` internally. See
`Workspace_Scroll/SCROLL_KONZEPT.md` in the `4diac_training1` project for the full derivation.

## Interface Structure

### **Event Inputs**

- `INIT`: Snapshots the configuration (`stObj`).
- `FIRST`: Jumps to the first row (position 0).
- `PAGE_UP`: Page up (fast, by `stObj.i32Step` rows).
- `LINE_UP`: One row up.
- `LINE_DOWN`: One row down.
- `PAGE_DOWN`: Page down (fast, by `stObj.i32Step` rows).
- `LAST`: Jumps to the last row (position `stObj.i32PosMax`).
- `GOTO`: Jumps to an absolute row position (`SET_POS`), clamped to `0…stObj.i32PosMax`.

### **Event Outputs**

- `CNF`: Confirms a position change, delivers `OUT`, `qAtFirst` and `qAtLast`.

### **Data Inputs**

- `stObj` (`isobus::utils::scroll::ScrollObjectPool_S`): list/bar geometry (container IDs, row
  height, bar offsets, `i32PosMax`, `i32Step`) — snapshotted once at `INIT`.
- `SET_POS` (DINT): Target position for `GOTO`.

### **Data Outputs**

- `OUT` (DINT): Current scroll position (0…`stObj.i32PosMax`, in rows).
- `qAtFirst` (BOOL): `TRUE` if `OUT` is at row 0 (start of the list reached).
- `qAtLast` (BOOL): `TRUE` if `OUT` is at `stObj.i32PosMax` (end of the list reached).

### **Adapters**

No adapters available.

## Functionality

`ScrollFS` wires four blocks together into a complete position engine:

1. **`Snap`** (`F_MOVE`, `DataType = ScrollObjectPool_S`): snapshots `stObj` once at `INIT`,
   after which all nine geometry fields are permanently available as `Snap.OUT.<field>`.
2. **`Ramp`** (`RampLimitFS`, package `eclipse4diac::signalprocessing`): the actual position
   state machine, reused directly (no separate state machine needed). The eight `ScrollFS`
   events map 1:1 to `RampLimitFS` events:

   | `ScrollFS` event | `RampLimitFS` event | Effect on `OUT` |
   | --- | --- | --- |
   | `FIRST` | `ZERO` | `OUT := 0` |
   | `PAGE_UP` | `DOWN_FAST` | `OUT -= stObj.i32Step` (clamped at 0) |
   | `LINE_UP` | `DOWN_SLOW` | `OUT -= 1` (clamped at 0) |
   | `LINE_DOWN` | `UP_SLOW` | `OUT += 1` (clamped at `i32PosMax`) |
   | `PAGE_DOWN` | `UP_FAST` | `OUT += stObj.i32Step` (clamped at `i32PosMax`) |
   | `LAST` | `FULL` | `OUT := stObj.i32PosMax` |
   | `GOTO` | `LOAD` (with `PV := SET_POS`) | `OUT := SET_POS`, clamped to `0…i32PosMax` |

   `VAL_ZERO := 0`, `VAL_FULL := Snap.OUT.i32PosMax`, `SLOW := 1`, `FAST := Snap.OUT.i32Step`.
3. **`ListY`** (`F_ScrollListY`) and **`BarY`** (`F_ScrollBarY`): on every `Ramp.CNF`, compute the
   Y offset for the list and the scrollbar from `Ramp.OUT`.
4. **`MoveList`** and **`MoveBar`** (each a `Q_ChildPosition`): write the computed Y values to the
   VT — `MoveList` moves `Container_Scrolling_Content` within `Container_Scrolling_Parent`,
   `MoveBar` moves `Container_Scrollbar_Content` within `Container_Scrollbar_Parent`. Both have a
   fixed `s16Xposition := 0` (vertical scrolling only).

`Ramp.qAtZero`/`Ramp.qAtFull` are passed through unchanged as `qAtFirst`/`qAtLast`.

## Technical Details

- **`F_MOVE` snapshot for struct access**: `Snap.IN`/`.OUT` are generically `ANY`-typed; an `ANY`
  connection (here: the concretely-typed `stObj` into the generic `Snap.IN`) in 4diac always
  needs a `MOVE` block in between, never directly. Every individual struct field addressed via
  `Snap.OUT.<field>` needs its own `Parameter Name="OUT.<field>"` entry with
  `Attribute Name="Visible" Value="true"` on the `Snap` instance - without it, the network won't
  compile.
- **Init chain is serial, not parallel**: `Snap.CNF` triggers `Ramp.INIT`; only after
  `Ramp.INITO` do `MoveList.INIT` and `MoveBar.INIT` fire - guaranteeing
  `VAL_ZERO`/`VAL_FULL`/`SLOW`/`FAST` are set in `Ramp` before any position value is written to
  the VT.
- **`ListY`/`BarY` are concretely typed** (`DINT`/`INT`, see [F_ScrollListY](helpers/F_ScrollListY.md),
  [F_ScrollBarY](helpers/F_ScrollBarY.md)) - so no extra `MOVE` anchor is needed between them and
  `Ramp.OUT`, even though `Ramp.OUT` itself comes from a generic `RampLimitFS` instance.

## State Overview

The only state lives in `Ramp` (`RampLimitFS`): `OUT` persists between events, each navigation
event changes it incrementally or jumps directly. `qAtFirst`/`qAtLast` are recomputed on every
change, never maintained separately.

## Application Scenarios

- Never used directly — always wrapped by [ScrollFS_PHYS](ScrollFS_PHYS.md) (softkeys) or
  [ScrollFS_PHYS_Button](ScrollFS_PHYS_Button.md) (on-screen buttons), which derive the eight
  navigation events from physical button presses.

## ⚖️ Comparison with Similar Blocks

- **Versus `RampLimitFS`**: `ScrollFS` is at its core a `RampLimitFS` with VT wiring - the
  position math itself (clamping, limit flags) lives entirely in `RampLimitFS`; `ScrollFS` only
  adds struct configuration, row/bar conversion, and writing to the VT.

## 🛠️ Related Exercises

- No standalone exercise example — see `Workspace_Scroll/SCROLL_KONZEPT.md` (project
  `4diac_training1`) for the full derivation against a real pool.

## Conclusion

`ScrollFS` bundles the position state, limit detection, and VT write access of a scrollable list
into a single, reusable composite block — independent of whether it's later operated via
softkeys or on-screen buttons.
