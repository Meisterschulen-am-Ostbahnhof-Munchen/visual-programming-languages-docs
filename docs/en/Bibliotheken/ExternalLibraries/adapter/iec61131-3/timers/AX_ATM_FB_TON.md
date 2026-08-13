# AX_ATM_FB_TON

![AX_ATM_FB_TON](AX_ATM_FB_TON.svg)

* * * * * * * * * *

## Introduction

`AX_ATM_FB_TON` is the adapter-based variant of [AX_FB_TON](AX_FB_TON.md): the same IEC 61131-3
on-delay timer (`iec61131::timers::FB_TON`), but with `PT` (preset time) as a socket and `ET`
(elapsed time) as a plug — both of type [ATM](../../types/unidirectional/TIME/ATM.md) — instead
of plain `TIME` data variables. This lets the block be wired directly into adapter-based chains
(e.g. behind an `AR_SUBSCRIBE_1` delivering a REAL seconds value written via OPC-UA, converted to
`TIME`) without drawing separate data connections for `PT`/`ET` at every call site.

## Interface Structure

### **Event Inputs**

- **REQ** (event, non-triggering): normal execution request. The application typically attaches
  an `E_CYCLE` here so `ET` keeps updating while the timer is running — without an external
  `E_CYCLE`, `ET` would stay frozen between `IN`/`PT` events.

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
| Plug (output) | `Q` | `adapter::types::unidirectional::AX` | Output, TRUE once `IN` has been present for `PT` |
| Plug (output) | `ET` | `adapter::types::unidirectional::ATM` | Elapsed time, event only on value change |

## Functionality

Internally the same standard `FB_TON` block used by `AX_FB_TON` is wired up, with two added
`E_D_FF`/`E_D_FF_ANY` buffers:

1. `IN.E1`, the block's own `REQ` event, and `PT.E1` all trigger `FB_TON.REQ` together — each of
   the three sources (input changes, preset time changes, or an external cyclic nudge) should
   recompute the current time base.
2. `FB_TON.Q` runs through an `E_D_FF` (change detection) onto `Q.D1`/`Q.E1` — the `Q` plug only
   fires its event when the boolean output actually changes.
3. `FB_TON.ET` runs through an `E_D_FF_ANY` (generic change detection) onto `ET.D1`/`ET.E1` —
   likewise only on an actual value change, not on every `REQ` cycle.

## Technical Details

- **`REQ` deliberately stays a plain event, not an adapter connection.** This lets the application
  decide the update rate for `ET` itself (e.g. via `E_CYCLE`), instead of the block imposing a
  fixed refresh rate.
- **`ET` events only fire on a value change**, the same principle used by
  [ASSEMBLE_AB_FROM_AX](../../assembling/ASSEMBLE_AB_FROM_AX.md) and
  [AB_AX_SEL_AB](../selection/adapter/AB_AX_SEL_AB.md) — prevents event flooding on every
  `E_CYCLE` tick when the time value (depending on resolution) hasn't actually changed.
- **`PT` is live, not latched — `IN.E1`, `PT.E1`, and `REQ` are equivalent triggers for
  `FB_TON`.** `PT.D1` sits as a plain data connection permanently wired to `FB_TON.PT`; the
  adapter does not buffer or debounce `PT`. `FB_TON` itself doesn't distinguish which of the
  three events (`IN.E1`, `PT.E1`, `REQ`) triggered the re-evaluation — it always evaluates the
  *current* `PT` against the *current* `ET`. A preset time changed at runtime is therefore not
  frozen at `IN`'s rising edge; it takes effect immediately at the next evaluation:
  - **`PT = 0`**: `Q` becomes TRUE immediately at the next evaluation, since `ET` (≥ 0) has
    already reached/exceeded the preset time.
  - **`PT` is decreased while timing is in progress**, such that the already-elapsed `ET` now
    exceeds the new, smaller preset time: `Q` becomes TRUE immediately at the next evaluation,
    instead of waiting for the originally larger preset time.
  - **`PT` is increased while timing is in progress**: `Q` correspondingly stays FALSE longer.
  - **Rapid consecutive `PT.E1` events are not coalesced** — each individual event triggers its
    own `FB_TON.REQ` evaluation; there is no debounce logic in the adapter.
  - **Before the very first `PT.E1`**, `FB_TON.PT` reads `TIME`'s default value `T#0s`, not a
    project-specific default — equivalent to the `PT = 0` case above if `IN` becomes TRUE before
    that.
- **Identical behavior in [AX_ATM_FB_TOF](AX_ATM_FB_TOF.md) and
  [AX_ATM_FB_TP](AX_ATM_FB_TP.md).** All three blocks are structurally wired identically (the
  same `IN.E1`/`PT.E1`/`REQ` → `REQ` pattern, the same `E_D_FF`/`E_D_FF_ANY` change-detection
  pattern for `Q`/`ET`) — only the internally wrapped standard block (`FB_TON`/`FB_TOF`/`FB_TP`)
  differs. The `PT` behavior described above applies equally to all three; see their respective
  pages for the timer-specific `PT = 0` edge cases.
- **The `adapter::events::unidirectional::timers` family (`AX_TON` etc.) has no `ET` output at
  all.** If the remaining/elapsed time is needed (e.g. for a countdown in the Visu), this
  `iec61131-3` family is required, not the simpler `events` family.

## State Overview

Like `AX_FB_TON`: no ECC of its own, a pure composite wiring pattern around the standard
`FB_TON`.

1. **Idle**: `IN` is FALSE, `Q` is FALSE, `ET` is 0.
2. **Timing**: `IN` is TRUE, the timer runs, `ET` climbs up to `PT`, `Q` stays FALSE.
3. **Triggered**: `ET` has reached `PT`, `Q` becomes TRUE.
4. **Reset**: `IN` goes FALSE, `Q` becomes FALSE, `ET` becomes 0.

## Application Scenarios

- **Countdown display via OPC-UA**: feed `PT` from a subscribed REAL seconds value (e.g.
  `Override.Dauer`), forward `ET` (or `PT - ET` for the remaining time) to the Visu via a publish
  block.
- Anywhere `AX_FB_TON` is already used but `PT`/`ET` should flow through adapter-based chains
  instead of individual data connections.

## ⚖️ Comparison with Similar Blocks

- **[AX_FB_TON](AX_FB_TON.md)**: identical timing behavior, but `PT`/`ET` as plain `TIME` data
  variables rather than adapters.
- **[AX_TON](../../events/unidirectional/BOOL/timers/AX_TON.md)**: the `events` variant with no
  `ET` output at all — suitable when only the timing result (`Q`) is needed, not the elapsed
  time.
- **[AX_ATM_FB_TOF](AX_ATM_FB_TOF.md) / [AX_ATM_FB_TP](AX_ATM_FB_TP.md)**: the same adapter
  extension for off-delay and pulse timing instead of on-delay.

## Conclusion

`AX_ATM_FB_TON` carries `AX_FB_TON`'s proven timing behavior into a fully adapter-based
interface, so both the preset time and the elapsed time can flow through adapter-based networks
without extra data connections — including change detection on the `ET` output to avoid
unnecessary events.
