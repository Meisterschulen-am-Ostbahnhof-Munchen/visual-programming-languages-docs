# E_PULSE_RETRIG

* * * * * * * * * *
## Introduction

`E_PULSE_RETRIG` is the retriggerable variant of `E_PULSE`: it generates a `TRUE` pulse of duration `PT` on `Q`, but restarts the pulse from the beginning on every new `REQ` event instead of ignoring a running interval.

![E_PULSE_RETRIG](E_PULSE_RETRIG.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts (or retriggers) the pulse, carries `PT`.
- **R**: Immediately aborts the running pulse.

### **Event Outputs**

- **CNF**: Confirmation, carries `Q`.

### **Data Inputs**

- **PT** (TIME): Duration of the pulse.

### **Data Outputs**

- **Q** (BOOL): `TRUE` during the pulse duration, otherwise `FALSE`.

## Functionality

Every `REQ` event simultaneously sets `E_SR.S` (→ `Q := TRUE`) and restarts `E_DELAY` with time `PT` — a new `REQ` during a running pulse thus restarts the `E_DELAY` timer from scratch instead of waiting for the original pulse to elapse. When `E_DELAY` elapses, `E_SR.R` is triggered (`Q := FALSE`). An `R` event stops the timer immediately and resets `Q` to `FALSE` directly.

## Technical Features

- **Retriggerable**: The key difference to `E_PULSE` (not retriggerable) is that every `REQ` restarts the `E_DELAY` timer — a pulse can thus be extended indefinitely through repeated `REQ` events.
- **Composed of `E_DELAY` + `E_SR`**: pure wiring, no ECC of its own.

## State Overview

Stateless wiring logic: `E_SR` holds the current `Q` state, `E_DELAY` restarts on every `REQ`.

## Application Scenarios

- **Dead-time/watchdog logic**: `Q` should remain `TRUE` as long as `REQ` events keep arriving regularly (e.g. a sensor heartbeat), and only become `FALSE` once `PT` has elapsed since the last `REQ` without a further one.
- **Extendable pulses**, e.g. a light that restarts its on-duration on every new motion detection (`REQ`) instead of timing out.

## Comparison with similar function blocks

- **`E_PULSE`**: the same base functionality, but not retriggerable (`REQ` during a running pulse has no effect).
- **[E_TP_RETRIG](E_TP_RETRIG.md)**: retriggerable pulse, triggered by a rising edge of `IN` instead of a separate `REQ` event.

## Conclusion

`E_PULSE_RETRIG` provides an extendable `TRUE` pulse whose duration restarts on every `REQ` event, suiting watchdog and dead-time applications where a running pulse should be kept alive by repeated requests.
