# E_TP_RETRIG

* * * * * * * * * *

## Introduction

`E_TP_RETRIG` is the retriggerable variant of the standard timer `E_TP`: on every rising edge of `IN`, it generates a `TRUE` pulse of duration `PT` on `Q` — unlike `E_TP`, however, a new rising edge during a running pulse restarts it instead of being ignored.

![E_TP_RETRIG](E_TP_RETRIG.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Checks `IN` for a rising edge, carries `IN` and `PT`.
- **R**: Immediately aborts the running pulse.

### **Event Outputs**

- **CNF**: Confirmation, carries `Q`.

### **Data Inputs**

- **IN** (BOOL): The input to check for rising edges.
- **PT** (TIME): Duration of the pulse.

### **Data Outputs**

- **Q** (BOOL): `TRUE` during the pulse duration.

## Functionality

`E_R_TRIG` detects rising edges of `IN` on every `REQ`. Every detected edge sets `E_SR.S` (→ `Q := TRUE`) and simultaneously restarts `E_DELAY` (with `PT`) — a new rising edge during a running pulse thus extends it instead of being ignored. When `E_DELAY` elapses, it sets `E_SR.R` (→ `Q := FALSE`). An `R` event stops the timer immediately and resets `Q` directly.

## Technical Features

- **Retriggerable via an `IN` edge rather than `REQ` alone**: Unlike [E_PULSE_RETRIG](E_PULSE_RETRIG.md), which retriggers on *every* `REQ` event, `E_TP_RETRIG` only reacts to actual rising edges of `IN` — repeated `REQ` events while `IN` is already held `TRUE` without a new edge do not trigger a new pulse.
- **Composed of three standard blocks**: `E_R_TRIG` + `E_DELAY` + `E_SR`, no ECC of its own.

## State Overview

Stateless wiring logic: `E_SR` holds the `Q` state, `E_DELAY` restarts on every detected rising edge of `IN`.

## Application Scenarios

- **Extendable pulses triggered by edge transitions**: e.g. motion-sensor-controlled lighting, where every new motion (rising edge of `IN`) restarts the on-duration.
- **Debounced but extendable response to a digital input**, where only genuine edge transitions — not mere `REQ` repetitions — should trigger a new pulse run.

## Comparison with similar function blocks

- **`E_TP`**: the same base functionality, but not retriggerable.
- **[E_PULSE_RETRIG](E_PULSE_RETRIG.md)**: retriggerable pulse, triggered by *every* `REQ` event instead of an `IN` edge.
- **[E_TLIM](E_TLIM.md)**: limits the on-time of `IN` itself, instead of generating a fixed pulse.

## Conclusion

`E_TP_RETRIG` provides an edge-triggered, extendable pulse of fixed duration and is suitable for applications where repeated genuine edge transitions — not mere `REQ` repetitions — should keep the pulse alive.
