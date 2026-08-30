# AX_ATM_FB_TON_REST

![AX_ATM_FB_TON_REST](AX_ATM_FB_TON_REST.svg)

* * * * * * * * * *

## Introduction

`AX_ATM_FB_TON_REST` wraps [AX_ATM_FB_TON](AX_ATM_FB_TON.md) with a third adapter plug, `REST`,
carrying the remaining time (`PT - ET`) as a REAL seconds value. Several applications need not
just "has the timer elapsed" (`Q`) or "how much time has passed" (`ET`), but "how much time is
left" for a countdown display — computing that from `PT`/`ET` externally means repeating the same
adapter chain (`ATM_SUB` → `ATM_IN_S_TO_ALR` → `ALR_TO_AR`) at every call site. This block
does it once, internally, so the caller gets `REST` as a single ready-to-publish adapter plug.

## Interface Structure

### **Event Inputs**

- **REQ** (event, non-triggering): same role as on `AX_ATM_FB_TON` — the application typically
  attaches an `E_CYCLE` here so `ET`/`REST` keep updating while the timer is running.

### **Event Outputs**

None of its own; events flow exclusively through the `Q`, `ET`, and `REST` adapter plugs.

### **Data Inputs**

None of its own. All data is carried through the adapter sockets.

### **Data Outputs**

None of its own. All data is carried through the adapter plugs.

### **Adapters**

| Direction | Name | Type | Description |
|-----------|------|------|--------------|
| Socket (input) | `IN` | `adapter::types::unidirectional::AX` | Start signal |
| Socket (input) | `PT` | `adapter::types::unidirectional::ATM` | Preset time |
| Plug (output) | `Q` | `adapter::types::unidirectional::AX` | Output, TRUE once `IN` has been present for `PT` |
| Plug (output) | `ET` | `adapter::types::unidirectional::ATM` | Elapsed time, event only on value change |
| Plug (output) | `REST` | `adapter::types::unidirectional::AR` | Remaining time `PT - ET` in seconds, no sentinel value |

## Functionality

Internally, a plain `AX_ATM_FB_TON` instance does the actual timing. Around it:

1. `PT` is split (`ATM_SPLIT_2`) so its value reaches both the wrapped timer's own `PT` and an
   `ATM_SUB` computing `PT - ET`.
2. The wrapped timer's `ET` is likewise split so it reaches both this block's own `ET` plug and
   the same `ATM_SUB` as the subtrahend.
3. `ATM_SUB.OUT` (an `ATM`, i.e. `TIME`) is converted to seconds via `ATM_IN_S_TO_ALR` →
   `ALR_TO_AR`, producing the `REST` value.
4. `Q` is passed straight through from the wrapped timer.

**Why plain Socket/Plug forwarding doesn't work here, and what the block does instead:** a
Socket can only be *fed by* a Plug, and a Plug can only *feed* a Socket — a bare
`<Connection Source="IN" Destination="InnerTimer.IN"/>` between this block's own `IN` Socket and
the wrapped timer's `IN` Socket (both Sockets) is not a legal adapter connection, and the
symmetric problem exists for `Q` (both Plugs). Because `AX_ATM_FB_TON_REST` is itself a `FBType`
(not a `SubAppType`), reading a Socket's current value via `IN.D1`/`IN.E1` dot-access **is**
legal here — the fix is therefore to bridge through the plain-variable pair at each boundary:
[AX_BOOL_TO_X](../../conversion/unidirectional/BOOL/AX_BOOL_TO_X.md) reads `IN.D1`/`IN.E1` and
re-emits it as a Plug feeding the wrapped timer's `IN` Socket; symmetrically,
[AX_X_TO_BOOL](../../conversion/unidirectional/BOOL/AX_X_TO_BOOL.md) reads the wrapped timer's
`Q` Plug and re-emits it onto this block's own `Q` Plug. The same pattern applies to `PT`/`ET`
(`ATM_TIME_TO_TM`/`ATM_TM_TO_TIME`), each pair bridging one direction in and one direction out
because the wrapped timer's socket and plug both need a bound value. `REST` only needs the
outbound half of that pattern — it is computed purely internally and never fed from outside — so
just [AR_R_TO_REAL](../../conversion/unidirectional/REAL/AR_R_TO_REAL.md) is used: it reads the
internally computed `AR` (via its own `AR_IN` Socket, fed by `ALR_TO_R`'s Plug) and re-emits the
plain `REAL` onto `REST`'s own Plug pins. The same Socket-can-only-be-fed-by-a-Plug rule this
works around applies to any adapter type, not just `AX`/`ATM`/`AR`.

## Technical Details

- **`REST` carries no sentinel convention (no "-1 = inactive").** A caller that needs one (e.g.
  "-1 while the timer isn't running") gates `REST` itself with an
  [AR_AX_SEL_AR](../selection/adapter/AR_AX_SEL_AR.md) downstream, selecting between `REST`
  and a constant based on its own "active" condition — this block only ever reports the raw
  `PT - ET` difference.
- **`REST` updates on the same resolution as `ET`**, i.e. only on an actual value change
  (inherited from `AX_ATM_FB_TON`'s `E_D_FF_ANY` on `ET`), not on every `REQ`/`E_CYCLE` tick.
- **All of `AX_ATM_FB_TON`'s `PT` semantics apply unchanged** — `PT` is live, not latched;
  `PT = 0` makes `Q` (and thus a `REST` of 0) become true/reached at the very next evaluation. See
  [AX_ATM_FB_TON](AX_ATM_FB_TON.md#technical-details) for the full breakdown of these edge cases.

## State Overview

Same four states as `AX_ATM_FB_TON`, with `REST` following `PT - ET` throughout:
1. **Idle**: `IN` is FALSE, `Q` is FALSE, `ET` is 0, `REST` equals `PT` converted to seconds.
3. **Triggered**: `ET` has reached `PT`, `REST` reaches 0, `Q` becomes TRUE.
4. **Reset**: `IN` goes FALSE, `Q` becomes FALSE, `ET` becomes 0, `REST` returns to `PT`.

## Application Scenarios

- **Countdown display via OPC-UA**: feed `PT` from a subscribed REAL seconds value, publish
  `REST` directly to the Visu — no external `ATM_SUB`/`ATM_IN_S_TO_ALR`/`ALR_TO_AR` chain needed
  at the call site.
- Any place that today wires `AX_ATM_FB_TON` alongside its own copy of the
  `ATM_SUB`/`ATM_IN_S_TO_ALR`/`ALR_TO_AR` chain to get a remaining-time value — this block
  replaces all four blocks with one.

## ⚖️ Comparison with Similar Blocks

- **[AX_ATM_FB_TON](AX_ATM_FB_TON.md)**: identical timing behavior and interface, minus the
  `REST` plug — use it when only `Q`/`ET` are needed.
- **[AR_AX_SEL_AR](../selection/adapter/AR_AX_SEL_AR.md)**: not a replacement, but the
  companion block for adding a sentinel value (e.g. "-1 = inactive") on top of this block's raw
  `REST` output.

## Conclusion

`AX_ATM_FB_TON_REST` folds the recurring "on-delay timer with a remaining-time readout" pattern —
previously four separately-wired blocks per call site — into a single adapter-based block,
trading a slightly more complex internal wiring (Socket/Plug bridging at every boundary) for a
much simpler call site.
