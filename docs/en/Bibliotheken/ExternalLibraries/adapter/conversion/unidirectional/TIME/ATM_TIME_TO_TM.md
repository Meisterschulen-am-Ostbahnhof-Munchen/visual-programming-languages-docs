# ATM_TIME_TO_TM

![ATM_TIME_TO_TM](ATM_TIME_TO_TM.svg)

* * * * * * * * * *
## Introduction

`ATM_TIME_TO_TM` is a composite function block that converts a plain `TIME` data value into the
[ATM](../../../types/unidirectional/TIME/ATM.md) adapter format. It follows exactly the same
pattern as [ADI_DINT_TO_DI](../DINT/ADI_DINT_TO_DI.md) (DINT→ADI) and
[AUI_UINT_TO_UI](../UINT/AUI_UINT_TO_UI.md) (UINT→AUI): a single data connection and a single
event connection, passed straight through to the plug — no conversion logic of its own.

## Interface Structure

### **Event Inputs**

- **REQ**: request event that triggers the conversion; carries the value of `OUT` (`With Var="OUT"`).

### **Event Outputs**

None of its own; the event flows exclusively through the `ATM_OUT` adapter plug.

### **Data Inputs**

- **OUT** (TIME): the time value to convert.

### **Data Outputs**

None of its own; the value is provided exclusively through the `ATM_OUT` adapter plug.

### **Adapters**

- **ATM_OUT** (plug, type `adapter::types::unidirectional::ATM`): emits the value of `OUT` via
  its `E1`/`D1` adapter event on `REQ`.

## Functionality

When the `REQ` event arrives, it is forwarded directly to `ATM_OUT.E1`, while the current value of
`OUT` is simultaneously placed onto `ATM_OUT.D1`. The `ATM_OUT` plug thus fires its adapter event
carrying the supplied time value — no buffering, no change detection, freshly on every `REQ`.

## Technical Details

- **Pure wiring logic**, no ECC of its own, no ST algorithms — a composite FB that establishes
  exactly one data and one event connection.
- **No `REAL_TO_TIME` exists in the standard libraries.** This block does not convert a numeric
  value into `TIME` — it accepts an already-finished `TIME` value and merely forwards it as an
  adapter. The actual conversion (e.g. from REAL seconds) happens beforehand, typically via
  `iec61131::arithmetic::F_MULTIME` (`T#1s * REAL#seconds`) — see the `Override_Timer` block
  (`adapter::OverrideK`) for a concrete usage example.
- **No event is suppressed for an unchanged value** — unlike, say,
  [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)'s `ET` output, there is no
  `E_D_FF`/`E_D_FF_ANY` buffering here; every `REQ` produces a fresh adapter event.

## State Overview

The block is stateless: every `REQ` event immediately outputs the current `OUT` value via
`ATM_OUT`.

## Application Scenarios

- **Feeding sockets that expect an `ATM` adapter instead of a plain `TIME` variable**, e.g. `PT`
  on [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)/
  [AX_ATM_FB_TOF](../../../iec61131-3/timers/AX_ATM_FB_TOF.md)/
  [AX_ATM_FB_TP](../../../iec61131-3/timers/AX_ATM_FB_TP.md).
- The final step in a conversion chain from REAL seconds to an adapter-based time value
  (`F_MULTIME` → `ATM_TIME_TO_TM`), as used in the `Override_Timer` block
  (`adapter::OverrideK`).

## ⚖️ Comparison with Similar Blocks

- **[ATM_TM_TO_TIME](ATM_TM_TO_TIME.md)**: the reverse direction — accepts an `ATM` adapter
  socket and exposes the value as a plain `TIME` data variable.
- **[ADI_DINT_TO_DI](../DINT/ADI_DINT_TO_DI.md) / [AUI_UINT_TO_UI](../UINT/AUI_UINT_TO_UI.md) /
  [AR_REAL_TO_R](../REAL/AR_REAL_TO_R.md)**: the same "data value → adapter plug" pattern for
  DINT, UINT, and REAL instead of TIME.

## Conclusion

`ATM_TIME_TO_TM` is the simplest way to expose a `TIME` data value as an `ATM` adapter plug,
bridging the gap between numeric time calculations (e.g. via `F_MULTIME`) and adapter-based time
sockets such as `PT` on `AX_ATM_FB_TON`/`TOF`/`TP`.
