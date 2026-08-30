# AX_ATM_FB_TP

![AX_ATM_FB_TP](AX_ATM_FB_TP.svg)

* * * * * * * * * *

## Introduction

`AX_ATM_FB_TP` is the adapter-based variant of [AX_FB_TP](AX_FB_TP.md): the same IEC 61131-3
pulse timer (`iec61131::timers::FB_TP`), but with `PT` (pulse time) as a socket and `ET` (elapsed
time) as a plug — both of type [ATM](../../types/unidirectional/TIME/ATM.md) — instead of plain
`TIME` data variables. Like [AX_ATM_FB_TON](AX_ATM_FB_TON.md), this lets the block be wired
directly into adapter-based chains without drawing separate data connections for `PT`/`ET` at
every call site.

## Interface Structure

### **Event Inputs**

- **REQ** (event, non-triggering): normal execution request. The application typically attaches
  an `E_CYCLE` here so `ET` keeps updating while the pulse is running.

### **Event Outputs**

None of its own; events flow exclusively through the `Q` and `ET` adapter plugs.

### **Data Inputs**

None of its own. All data is carried through the adapter sockets.

### **Data Outputs**

None of its own. All data is carried through the adapter plugs.

### **Adapters**

| Direction | Name | Type | Description |
| ----------- | ------ | ------ | -------------- |
| Socket (input) | `IN` | `adapter::types::unidirectional::AX` | Start signal |
| Socket (input) | `PT` | `adapter::types::unidirectional::ATM` | Pulse time |
| Plug (output) | `Q` | `adapter::types::unidirectional::AX` | Output, TRUE for duration `PT` after a rising edge on `IN` |
| Plug (output) | `ET` | `adapter::types::unidirectional::ATM` | Elapsed time, event only on value change |

## Functionality

Internally the same standard `FB_TP` block used by `AX_FB_TP` is wired up, with two added
`E_D_FF`/`E_D_FF_ANY` buffers:

1. `IN.E1`, the block's own `REQ` event, and `PT.E1` all trigger `FB_TP.REQ` together.
2. `FB_TP.Q` runs through an `E_D_FF` (change detection) onto `Q.D1`/`Q.E1`.
3. `FB_TP.ET` runs through an `E_D_FF_ANY` (generic change detection) onto `ET.D1`/`ET.E1` —
   only on an actual value change, not on every `REQ` cycle.

A rising edge on `IN` immediately sets `Q` to TRUE and starts the countdown; `Q` stays TRUE for
the full duration `PT` regardless of whether `IN` falls back to FALSE in the meantime (a true
pulse, not retriggerable).

## Technical Details

- **`REQ` deliberately stays a plain event, not an adapter connection**, as in
  [AX_ATM_FB_TON](AX_ATM_FB_TON.md) — the application controls `ET`'s update rate itself via an
  externally attached `E_CYCLE`.
- **`ET` events only fire on a value change**, the same principle used by
  [ASSEMBLE_AB_FROM_AX](../../assembling/ASSEMBLE_AB_FROM_AX.md).
- **`PT` is live, not latched — `IN.E1`, `PT.E1`, and `REQ` are equivalent triggers for
  `FB_TP`**, exactly as in [AX_ATM_FB_TON](AX_ATM_FB_TON.md). `PT.D1` sits as a plain data
  connection permanently wired to `FB_TP.PT`, no buffering/debouncing in the adapter:
  - **`PT = 0`**: the pulse is already considered elapsed at the next evaluation — from an
    observer's point of view, `Q` may have effectively no visible TRUE phase.
  - **`PT` is decreased while a pulse is running**, such that the already-elapsed `ET` exceeds
    the new preset time: `Q` becomes FALSE immediately.
  - **`PT` is increased while a pulse is running**: `Q` correspondingly stays TRUE longer.
  - **Rapid consecutive `PT.E1` events** each trigger their own evaluation, no coalescing.
  - **Before the very first `PT.E1`**, `FB_TP.PT` reads `TIME`'s default value `T#0s`.
- **Identical behavior in [AX_ATM_FB_TON](AX_ATM_FB_TON.md) and
  [AX_ATM_FB_TOF](AX_ATM_FB_TOF.md)** — all three are structurally wired identically, only the
  internally wrapped standard block differs.

## State Overview

1. **Idle**: `IN` is FALSE, `Q` is FALSE, `ET` is 0.
2. **Rising edge on `IN`**: `Q` becomes TRUE immediately, `ET` starts running.
3. **Pulse active**: `ET` climbs up to `PT`, `Q` stays TRUE — regardless of `IN`'s further
   behavior.
4. **Elapsed**: `ET` has reached `PT`, `Q` becomes FALSE.

## Application Scenarios

- Fixed, non-retriggerable pulse lengths (e.g. a valve's minimum on-time) with visible time
  progress via `ET`.
- Anywhere `AX_FB_TP` is already used but `PT`/`ET` should flow through adapter-based chains.

## ⚖️ Comparison with Similar Blocks

- **[AX_FB_TP](AX_FB_TP.md)**: identical timing behavior, but `PT`/`ET` as plain `TIME` data
  variables rather than adapters.
- **[AX_TP](../../events/unidirectional/BOOL/timers/AX_TP.md)**: the `events` variant with no
  `ET` output.
- **[AX_ATM_FB_TON](AX_ATM_FB_TON.md) / [AX_ATM_FB_TOF](AX_ATM_FB_TOF.md)**: the same adapter
  extension for on-delay and off-delay timing instead of a pulse.

## Conclusion

`AX_ATM_FB_TP` carries `AX_FB_TP`'s proven timing behavior into a fully adapter-based interface,
with change detection on the `ET` output to avoid unnecessary events.
