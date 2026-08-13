# F_ScrollBarY

![F_ScrollBarY](F_ScrollBarY.svg)

* * * * * * * * * *
## Introduction

The `F_ScrollBarY` function computes, from the current scroll position (in rows), the Y offset
for the scrollbar content container (`Container_Scrollbar_Content.Top`), so the bar "thumb"
proportionally reflects the list position. It's the scrollbar counterpart to
[F_ScrollListY](F_ScrollListY.md) and is used internally by the `ScrollFS` scroll block (package
`isobus::UT::Q`).

## Interface Structure

### **Event Inputs**

- `REQ`: Calculation request, reads `i32Pos`, `i32BarTravel`, `i32PosMax` and
  `i32BarBaseOffset`.

### **Event Outputs**

- `CNF`: Confirms the calculation and delivers the return value (unnamed `OutputVar`, addressed
  via `<InstanceName>.` with a trailing dot).

### **Data Inputs**

- `i32Pos` (DINT): Current scroll position in rows (0…`i32PosMax`).
- `i32BarTravel` (DINT): Available travel distance of the thumb (viewport height − thumb height).
- `i32PosMax` (DINT): Maximum scroll position (last valid row).
- `i32BarBaseOffset` (DINT): `Top` value of `Container_Scrollbar_Content` at position 0 — must
  match the thumb's fixed internal `Top` position in magnitude, with the opposite sign, so the
  thumb lands at net Y = 0 when `i32Pos = 0`.

### **Data Outputs**

- *(unnamed)* (INT): `Container_Scrollbar_Content.Top` value (`s16Yposition` for
  `Q_ChildPosition`).

### **Adapters**

No adapters available.

## Functionality

The calculation is a single formula:

```
OUT := DINT_TO_INT(i32BarBaseOffset + (i32Pos * i32BarTravel) / i32PosMax)
```

At `i32Pos = 0`, `OUT = i32BarBaseOffset` (thumb at the start of the list); at
`i32Pos = i32PosMax`, `OUT = i32BarBaseOffset + i32BarTravel` (thumb at the end of the list).
Everything in between is linearly interpolated.

## Technical Details

- **`DINT_TO_INT` cast**: same as `F_ScrollListY` — the calculation runs in `DINT`, the result is
  only converted to `INT` at the end (`Q_ChildPosition.s16Yposition`).
- **Integer division**: `(i32Pos * i32BarTravel) / i32PosMax` rounds down (integer division) —
  with a small `i32BarTravel` relative to `i32PosMax`, the thumb can stay put for several
  position steps before visibly moving. Unnoticeable in practice, since `i32BarTravel` is
  typically much larger than `i32PosMax`.
- **Concretely typed, no `ANY`**: like `F_ScrollListY` — fixed `DINT`/`INT` typing, no `MOVE`
  anchor needed when wiring it up.

## State Overview

Stateless — every `REQ` recomputes the result immediately from the current input values.

## Application Scenarios

- Used exclusively inside `ScrollFS` to recompute `Container_Scrollbar_Content.Top` on every
  position change — running in parallel with `F_ScrollListY` for the list itself, sharing the
  same `i32Pos` value as its source.

## ⚖️ Comparison with Similar Blocks

- **Versus `F_ScrollListY`**: same basic idea (row position to pixel offset), but scaled to the
  (smaller) scrollbar span instead of a direct multiplication by the row height, plus a base
  offset. See [F_ScrollListY](F_ScrollListY.md).

## Conclusion

The scrollbar counterpart to `F_ScrollListY` — the same row position drives both the list and the
scrollbar through two separate, concretely typed formulas, each with its own scaling.
