# E_TLIM

* * * * * * * * * *

## Introduction

`E_TLIM` (time-limiting) limits how long `Q` can stay `TRUE` at most: as soon as `IN` switches to `TRUE`, `Q` also becomes `TRUE`; if `IN` stays `TRUE` longer than `PT`, `Q` automatically switches to `FALSE` once `PT` elapses (timeout). If `IN` already falls back to `FALSE` before `PT` elapses, `Q` follows immediately.

![E_TLIM](E_TLIM.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Trigger, carries `IN` and `PT`.

### **Event Outputs**

- **CNF**: Confirmation, carries `Q`.

### **Data Inputs**

- **IN** (BOOL): The input state being monitored.
- **PT** (TIME): Maximum time `Q` may stay `TRUE` after a rising edge of `IN`.

### **Data Outputs**

- **Q** (BOOL): `TRUE` while `IN` is `TRUE` and `PT` has not yet elapsed.

## Functionality

`E_RF_TRIG` detects edge transitions of `IN`: a rising edge (`ER`) starts `E_DELAY` (with `PT`) and sets `E_SR.S` (→ `Q := TRUE`). A falling edge (`EF`) immediately stops `E_DELAY` and sets `E_SR.R` (→ `Q := FALSE`) — so `IN` always wins over the timeout. If `E_DELAY` instead runs to completion (because `IN` stayed `TRUE` longer than `PT`), this also triggers `E_SR.R`, causing `Q` to fall back to `FALSE` even without a falling edge of `IN` (the timeout case).

## Technical Features

- **Two paths to `Q := FALSE`**: either a falling edge of `IN` (regular case) or `PT` elapsing (timeout case) — both go through `E_SR.R`.
- **Composed of three standard blocks**: `E_RF_TRIG` (edge detection) + `E_DELAY` (timeout timer) + `E_SR` (state storage), no ECC of its own.

## State Overview

| State (implicit via `E_SR`/`E_DELAY`) | Meaning |
| --- | --- |
| Q = FALSE, timer inactive | Idle, `IN = FALSE` |
| Q = TRUE, timer running | `IN` is `TRUE`, `PT` not yet elapsed |
| Q = FALSE (timeout) | `IN` was `TRUE` longer than `PT`, automatically reset |

## Application Scenarios

- **Monitoring maximum durations**: A signal may be active for at most `PT` (e.g. a maximum on-time for an actuator as a safety limit); if `IN` stays active longer, `Q` is automatically reset.
- **Timeout monitoring of process steps**: `IN` marks the running step, `Q` indicates whether the step is still within the allowed time `PT`.

## Comparison with similar function blocks

- **`E_TON`/`E_TOF`** (standard IEC 61131-3 timers): delay the *turning on* or *turning off* of `Q` relative to `IN`, but do not limit its maximum on-time.
- **[E_PULSE_RETRIG](E_PULSE_RETRIG.md) / [E_TP_RETRIG](E_TP_RETRIG.md)**: generate a pulse of fixed duration, regardless of how long `IN`/`REQ` actually stays active.
- **`E_RF_TRIG`**: the internally used edge detection.

## Conclusion

`E_TLIM` limits the maximum on-time of a `BOOL` signal and is a simple timeout guard for actuators or process steps where staying too long in the `TRUE` state should be ended automatically.
