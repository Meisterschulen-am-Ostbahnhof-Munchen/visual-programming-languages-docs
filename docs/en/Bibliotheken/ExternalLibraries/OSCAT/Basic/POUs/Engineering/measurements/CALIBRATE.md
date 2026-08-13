# CALIBRATE

![CALIBRATE](CALIBRATE.svg)

* * * * * * * * * *
## Introduction

`CALIBRATE` performs a two-point calibration (offset & scale) of an analog input signal: `Y = (X + OFFSET) * SCALE`. Calibration is not triggered by dedicated events but by the Boolean inputs `CO`/`CS`, which are checked on every `REQ`. For an event-driven variant see [E_CALIBRATE](E_CALIBRATE.md); for a variant with enforced ordering see [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).

## Interface Structure

### **Event Inputs**

- **REQ**: normal execution request, carries `X`, `CO`, `CS`, `Y_Offset`, `Y_Scale`, `OFFSET`, `SCALE`. Recomputes `Y` on every call and, where applicable, performs a calibration step (see Functionality).

### **Event Outputs**

- **CNF**: confirms execution, carries `Y`, `OFFSET` and `SCALE`.

### **Data Inputs**

- **X** (REAL): raw input value.
- **CO** (BOOL): when `TRUE`, triggers offset calibration.
- **CS** (BOOL): when `TRUE`, triggers scale calibration (only meaningful once `CO` has run first).
- **Y_Offset** (REAL): target value for `Y` at the low reference point (offset calibration).
- **Y_Scale** (REAL): target value for `Y` at the high reference point (scale calibration).

### **Data Outputs**

- **Y** (REAL): calibrated output value.

### **In/Out Variables**

- **OFFSET** (REAL, initial `0.0`): stored offset value -- recalculated on `CO`, otherwise held persistently by the caller.
- **SCALE** (REAL, initial `1.0`): stored scale factor -- recalculated on `CS`, otherwise held persistently by the caller.

## Functionality

On every `REQ`, `CALIBRATE` first checks `CO` and `CS` (as an `ELSIF` chain, so at most one calibration step per call):

- If `CO = TRUE`: `OFFSET := Y_Offset - X` -- shifts `X` so that `Y = Y_Offset` at the current reference (only correct when `SCALE = 1`).
- Else if `CS = TRUE`: `SCALE := Y_Scale / (X + OFFSET)` -- scales so that `Y = Y_Scale` at the current reference. Requires `OFFSET` to already have been determined via `CO`.

`Y := (X + OFFSET) * SCALE` is then computed either way and output via `CNF`.

**Two-point calibration procedure:**

1. Apply the low reference, set `Y_Offset` to the desired output, set `CO = TRUE` -- yields `OFFSET`.
2. Apply the high reference, set `Y_Scale` to the desired output, set `CS = TRUE` -- yields `SCALE`.

**Example** (4-20 mA pressure sensor via logiBUS, normalized to `0.0..1.0`, desired output range `0.0..500.0`):

| Step | Action | Result |
|---|---|---|
| 1 | Apply 4 mA (`X=0.0`), `Y_Offset=0.0`, `CO=TRUE` | `OFFSET = 0` |
| 2 | Apply 20 mA (`X=1.0`), `Y_Scale=500.0`, `CS=TRUE` | `SCALE = 500` |

Result: `Y = (X + 0) * 500 = X * 500 = 0..500`.

## Technical Details

- **Order not enforced**: `CO` must run before `CS`, since `CS` uses the `OFFSET` already determined. As a `SimpleFB` with a single `ECState`, `CALIBRATE` cannot enforce this order itself -- that is the caller's responsibility. For an ECC-enforced variant see [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).
- **Y after CO only correct when SCALE = 1**: the formula `OFFSET := Y_Offset - X` only yields exactly `Y = Y_Offset` after offset calibration if `SCALE` still has its initial value `1.0`. `E_CALIBRATE_SQ` instead uses `OFFSET := Y_Offset / SCALE - X`, which is correct regardless of `SCALE`.
- **Triggered via BOOL, not events**: unlike the `E_CALIBRATE*` variants, calibration here runs through the data inputs `CO`/`CS`, re-evaluated on every `REQ` -- no dedicated calibration event needed, but also no separate confirmation event per calibration step.

## State Overview

`CALIBRATE` is a `SimpleFB` with a single `ECState` (`REQ`): every call immediately runs the `REQ` algorithm and fires `CNF`. There are no state transitions and no real ECC -- the "calibration phase" results purely from the value of `CO`/`CS` at call time.

## Application Scenarios

- Scaling analog sensors (pressure, temperature, level) with two-point reference calibration
- Systems where the calibration trigger is already available as a Boolean signal (e.g. a button/switch rather than a dedicated event source)
- Simple applications where an accidental wrong order (`CS` before `CO`) poses no risk

## ⚖️ Comparison with Similar Blocks

Compare with [E_CALIBRATE](E_CALIBRATE.md), which performs the same two-point calibration but event-driven (`EICO`/`EICS` instead of `CO`/`CS`), and with [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md), which additionally enforces offset-before-scale ordering via its ECC and always computes `Y` correctly after offset calibration regardless of `SCALE`. For a three-point calibration (e.g. joysticks with a center position) see [CALIBRATE_3P](CALIBRATE_3P.md).

## Conclusion

`CALIBRATE` provides simple, Boolean-triggered two-point calibration for analog signals, and fits applications where the caller ensures the correct order of offset and scale calibration.
