# CALIBRATE_3P

![CALIBRATE_3P](CALIBRATE_3P.svg)

* * * * * * * * * *
## Introduction

`CALIBRATE_3P` is a three-point calibration for raw inputs with a center position, as typically found on joysticks. Instead of a single linear scale like [CALIBRATE](CALIBRATE.md), it interpolates piecewise linearly between three stored reference points (Min, Mid, Max), which also compensates for a center position that doesn't sit exactly in the middle of the raw range.

## Interface Structure

### **Event Inputs**

- **REQ**: normal execution request, carries `X`, `C_MIN`, `C_MID`, `C_MAX`, `MIN_REF`, `MID_REF`, `MAX_REF`, `X_MIN`, `X_MID`, `X_MAX`. Recomputes `Y` on every call and, where applicable, performs a calibration step.

### **Event Outputs**

- **CNF**: confirms execution, carries `Y`, `X_MIN`, `X_MID`, `X_MAX`.

### **Data Inputs**

- **X** (REAL): raw input value.
- **C_MIN** (BOOL): when `TRUE`, triggers calibration of the minimum point.
- **C_MID** (BOOL): when `TRUE`, triggers calibration of the mid point.
- **C_MAX** (BOOL): when `TRUE`, triggers calibration of the maximum point.
- **MIN_REF** (REAL, initial `0.0`): target output value for the minimum point.
- **MID_REF** (REAL, initial `50.0`): target output value for the mid point.
- **MAX_REF** (REAL, initial `100.0`): target output value for the maximum point.

### **Data Outputs**

- **Y** (REAL): calibrated, interpolated output value, clipped to `MIN_REF..MAX_REF`.

### **In/Out Variables**

- **X_MIN** (REAL, initial `0.0`): stored raw value at the minimum point.
- **X_MID** (REAL, initial `50.0`): stored raw value at the mid point.
- **X_MAX** (REAL, initial `100.0`): stored raw value at the maximum point.

## Functionality

On every `REQ`, `CALIBRATE_3P` first checks `C_MIN`, `C_MID` and `C_MAX` (as an `ELSIF` chain, at most one calibration point per call) and, if the corresponding flag is set, stores the current raw value `X` in `X_MIN`/`X_MID`/`X_MAX`.

`Y` is then interpolated piecewise linearly:

- For `X < X_MID`: interpolation between `(X_MIN, MIN_REF)` and `(X_MID, MID_REF)`.
- For `X >= X_MID`: interpolation between `(X_MID, MID_REF)` and `(X_MAX, MAX_REF)`.
- The result is clipped to the range `MIN_REF..MAX_REF`.

The three calibration points can be calibrated in **any order** and repeated individually as often as needed -- but at most one is updated per `REQ` call.

**Example** (joystick with center drift, raw range `0..1000`, desired output range `-100..0..100`):

| Step | Action | Result |
|---|---|---|
| 1 | Move joystick to **minimum**, `C_MIN=TRUE` | `X_MIN = 50` (drift from ideal `0`) |
| 2 | Move joystick to **center**, `C_MID=TRUE` | `X_MID = 520` (drift from ideal `500`) |
| 3 | Move joystick to **maximum**, `C_MAX=TRUE` | `X_MAX = 980` (drift from ideal `1000`) |

Result: `Y` is interpolated and clipped between `MIN_REF=-100`, `MID_REF=0` and `MAX_REF=100` -- the joystick's actual (drifted) center position now yields exactly `Y=0`.

## Technical Details

- **Center-position compensation**: unlike a plain two-point calibration (see [CALIBRATE](CALIBRATE.md)), the center position is captured explicitly -- important for joysticks whose mechanical rest position doesn't sit exactly in the middle of the electrical raw range.
- **Output always clipped**: `Y` is clipped to `MIN_REF..MAX_REF` after interpolation, even if `X` lies outside the calibrated raw values.
- **Degenerate calibration points**: if `X_MID` is not above `X_MIN` (or `X_MAX` not above `X_MID`), the affected interpolation returns a constant `MIN_REF` or `MID_REF` instead of dividing by zero.
- **Order not enforced**: as with `CALIBRATE`, being a `SimpleFB` means it's the caller's responsibility to supply sensible calibration values. For an event-driven variant see [E_CALIBRATE_3P](E_CALIBRATE_3P.md).

## State Overview

`CALIBRATE_3P` is a `SimpleFB` with a single `ECState` (`REQ`): every call immediately runs the `REQ` algorithm and fires `CNF`. There are no state transitions -- which calibration point (if any) gets updated is determined purely by `C_MIN`/`C_MID`/`C_MAX` at call time.

## Application Scenarios

- Calibrating joysticks and similar controls with a mechanical center position
- Raw inputs with nonlinear or asymmetric behavior around the zero point
- Applications where individual calibration points need to be readjusted independently without affecting the others

## ⚖️ Comparison with Similar Blocks

Compare with [CALIBRATE](CALIBRATE.md), which uses the same Boolean-triggered approach but only offers a linear two-point calibration without a center position, and with [E_CALIBRATE_3P](E_CALIBRATE_3P.md), which provides the same three-point logic event-driven (`EI_MIN`/`EI_MID`/`EI_MAX`) with its own confirmation event per point.

## Conclusion

`CALIBRATE_3P` fits anywhere a simple two-point calibration falls short because the raw value range isn't symmetric around a (possibly shifted) center point -- most notably for joysticks and similar controls.
