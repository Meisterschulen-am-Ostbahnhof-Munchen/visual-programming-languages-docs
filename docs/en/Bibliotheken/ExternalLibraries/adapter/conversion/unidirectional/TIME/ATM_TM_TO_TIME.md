# ATM_TM_TO_TIME

![ATM_TM_TO_TIME](ATM_TM_TO_TIME.svg)

* * * * * * * * * *

## Introduction

`ATM_TM_TO_TIME` is the reverse of [ATM_TIME_TO_TM](ATM_TIME_TO_TM.md): a composite function
block that accepts an [ATM](../../../types/unidirectional/TIME/ATM.md) adapter socket and exposes
its value as a plain `TIME` data variable. It follows exactly the same pattern as
[AUI_UI_TO_UINT](../UINT/AUI_UI_TO_UINT.md) (AUI→UINT): a single data connection and a single
event connection, read straight off the socket — no conversion logic of its own.

## Interface Structure

### **Event Inputs**

None of its own; the event arrives exclusively through the `ATM_IN` adapter socket.

### **Event Outputs**

- **CNF**: confirmation event, fires when the `ATM_IN` adapter socket fires its event; carries the
  value of `IN` (`With Var="IN"`).

### **Data Inputs**

None of its own; the value arrives exclusively through the `ATM_IN` adapter socket.

### **Data Outputs**

- **IN** (TIME): the time value received from the adapter.

### **Adapters**

- **ATM_IN** (socket, type `adapter::types::unidirectional::ATM`): receives the time value from
  the connected plug.

## Functionality

As soon as the connected plug fires an event on `ATM_IN`, `ATM_IN.E1` is forwarded directly to
`CNF`, while `ATM_IN.D1` is simultaneously placed onto the data output variable `IN`. The block
thus makes the value of an incoming `ATM` adapter usable by downstream blocks that expect a plain
`TIME` variable rather than an adapter socket (e.g. `OSCAT::Basic::POUs::conversion::TIME_TO_REAL`,
whose `TM` input is a plain data variable).

## Technical Details

- **Pure wiring logic**, no ECC of its own, no ST algorithms — a composite FB that establishes
  exactly one data and one event connection.
- **Necessary because plugs cannot feed a plain data variable directly.** An adapter plug (e.g.
  the `ET` output of [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)) can only
  connect to a socket, never directly to a function's plain `InputVar`. `ATM_TM_TO_TIME` closes
  that gap.
- **No event is suppressed for an unchanged value** — the block itself buffers nothing; whether an
  event actually only arrives on a value change depends on the upstream plug (e.g.
  `AX_ATM_FB_TON.ET` already has its own `E_D_FF_ANY` change detection).

## State Overview

The block is stateless: every event on the `ATM_IN` socket immediately outputs the current value
via `IN`/`CNF`.

## Application Scenarios

- **Making an adapter plug readable for functions with plain data variables**, e.g. forwarding the
  `ET` output of [AX_ATM_FB_TON](../../../iec61131-3/timers/AX_ATM_FB_TON.md)/
  [AX_ATM_FB_TOF](../../../iec61131-3/timers/AX_ATM_FB_TOF.md)/
  [AX_ATM_FB_TP](../../../iec61131-3/timers/AX_ATM_FB_TP.md) into
  `OSCAT::Basic::POUs::conversion::TIME_TO_REAL`.
- The first step in a conversion chain from an adapter-based time value back to REAL seconds
  (`ATM_TM_TO_TIME` → `TIME_TO_REAL` → `F_DIV`), as used in the `Override_Timer` SubApp
  (`FBs::sys`, Getreideannahme application code, not part of this library's documentation).

## ⚖️ Comparison with Similar Blocks

- **[ATM_TIME_TO_TM](ATM_TIME_TO_TM.md)**: the reverse direction — accepts a plain `TIME` data
  variable and exposes it as an `ATM` adapter plug.
- **[AUI_UI_TO_UINT](../UINT/AUI_UI_TO_UINT.md) / [ADI_DI_TO_DINT](../DINT/ADI_DI_TO_DINT.md)**:
  the same "adapter socket → data value" pattern for UINT and DINT instead of TIME.

## Conclusion

`ATM_TM_TO_TIME` is the simplest way to make an `ATM` adapter plug's value usable as a plain
`TIME` variable, bridging the gap between adapter-based time plugs (e.g. `ET` on
`AX_ATM_FB_TON`/`TOF`/`TP`) and functions that only accept plain data variables.
