# AX_ATM_FB_TOF

![AX_ATM_FB_TOF](AX_ATM_FB_TOF.svg)

* * * * * * * * * *

## Introduction

`AX_ATM_FB_TOF` is the adapter-based variant of [AX_FB_TOF](AX_FB_TOF.md): the same IEC 61131-3
off-delay timer (`iec61131::timers::FB_TOF`), but with `PT` (preset time) as a socket and `ET`
(elapsed time) as a plug — both of type [ATM](../../types/unidirectional/TIME/ATM.md) — instead
of plain `TIME` data variables. Like [AX_ATM_FB_TON](AX_ATM_FB_TON.md), this lets the block be
wired directly into adapter-based chains without drawing separate data connections for `PT`/`ET`
at every call site.

## Interface Structure

### **Event Inputs**

- **REQ** (event, non-triggering): normal execution request. The application typically attaches
  an `E_CYCLE` here so `ET` keeps updating while the timer is running.

### **Event Outputs**

None of its own; events flow exclusively through the `Q` and `ET` adapter plugs.

### **Data Inputs**

None of its own. All data is carried through the adapter sockets.

### **Data Outputs**

None of its own. All data is carried through the adapter plugs.

### **Adapters**

| Direction | Name | Type | Description |
|-----------|------|------|--------------|
| Socket (input) | `IN` | `adapter::types::unidirectional::AX` | Start signal |
| Socket (input) | `PT` | `adapter::types::unidirectional::ATM` | Preset time |
| Plug (output) | `Q` | `adapter::types::unidirectional::AX` | Output, stays TRUE for `PT` after `IN` falls |
| Plug (output) | `ET` | `adapter::types::unidirectional::ATM` | Elapsed time, event only on value change |

## Functionality

Internally the same standard `FB_TOF` block used by `AX_FB_TOF` is wired up, with two added
`E_D_FF`/`E_D_FF_ANY` buffers:

1. `IN.E1`, the block's own `REQ` event, and `PT.E1` all trigger `FB_TOF.REQ` together.
2. `FB_TOF.Q` runs through an `E_D_FF` (change detection) onto `Q.D1`/`Q.E1`.
3. `FB_TOF.ET` runs through an `E_D_FF_ANY` (generic change detection) onto `ET.D1`/`ET.E1` —
   only on an actual value change, not on every `REQ` cycle.

Unlike the on-delay timer, `IN = TRUE` sets output `Q` to TRUE immediately; only once `IN` falls
back to FALSE does the `PT` countdown run before `Q` drops back to FALSE.

## Technical Details

- **`REQ` deliberately stays a plain event, not an adapter connection**, as in
  [AX_ATM_FB_TON](AX_ATM_FB_TON.md) — the application controls `ET`'s update rate itself via an
  externally attached `E_CYCLE`.
- **`ET` events only fire on a value change**, the same principle used by
  [ASSEMBLE_AB_FROM_AX](../../assembling/ASSEMBLE_AB_FROM_AX.md).
- **`PT.E1` also re-triggers**, so a preset time changed at runtime is picked up immediately.

## State Overview

1. **Idle**: `IN` is FALSE, `Q` is FALSE, `ET` is 0.
2. **`IN` becomes TRUE**: `Q` becomes TRUE immediately, `ET` stays 0.
3. **`IN` falls to FALSE**: the timer starts, `ET` climbs up to `PT`, `Q` stays TRUE.
4. **Elapsed**: `ET` has reached `PT`, `Q` becomes FALSE.

## Application Scenarios

- Run-on/coast-down times where an output needs to stay active for a defined period after an
  input switches off, with visible remaining time via `ET`.
- Anywhere `AX_FB_TOF` is already used but `PT`/`ET` should flow through adapter-based chains.

## ⚖️ Comparison with Similar Blocks

- **[AX_FB_TOF](AX_FB_TOF.md)**: identical timing behavior, but `PT`/`ET` as plain `TIME` data
  variables rather than adapters.
- **[AX_TOF](../../events/unidirectional/BOOL/timers/AX_TOF.md)**: the `events` variant with no
  `ET` output.
- **[AX_ATM_FB_TON](AX_ATM_FB_TON.md) / [AX_ATM_FB_TP](AX_ATM_FB_TP.md)**: the same adapter
  extension for on-delay and pulse timing instead of off-delay.

## Conclusion

`AX_ATM_FB_TOF` carries `AX_FB_TOF`'s proven timing behavior into a fully adapter-based
interface, with change detection on the `ET` output to avoid unnecessary events.
