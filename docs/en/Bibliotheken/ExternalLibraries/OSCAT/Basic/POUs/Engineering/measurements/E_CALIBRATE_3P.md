# E_CALIBRATE_3P

![E_CALIBRATE_3P_ecc](./E_CALIBRATE_3P_ecc.svg)

![E_CALIBRATE_3P](E_CALIBRATE_3P.svg)

* * * * * * * * * *
## Introduction

`E_CALIBRATE_3P` is the event-driven counterpart to [CALIBRATE_3P](CALIBRATE_3P.md): the three-point calibration with piecewise linear interpolation (Min/Mid/Max) is triggered by its own events `EI_MIN`/`EI_MID`/`EI_MAX`, each with its own confirmation event.

## Interface Structure

### **Event Inputs**

- **REQ**: normal execution request -- computes `Y`. Carries `X`, `MIN_REF`, `MID_REF`, `MAX_REF`, `X_MIN`, `X_MID`, `X_MAX`.
- **EI_MIN**: calibrates the minimum point (`X_MIN := X`). Carries `X`.
- **EI_MID**: calibrates the mid point (`X_MID := X`). Carries `X`.
- **EI_MAX**: calibrates the maximum point (`X_MAX := X`). Carries `X`.

### **Event Outputs**

- **CNF**: confirms `REQ`, carries `Y`.
- **EO_MIN**: confirms minimum-point calibration, carries `X_MIN`.
- **EO_MID**: confirms mid-point calibration, carries `X_MID`.
- **EO_MAX**: confirms maximum-point calibration, carries `X_MAX`.

### **Data Inputs**

- **X** (REAL): raw input value.
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

`E_CALIBRATE_3P` has a start state `START` and four action states directly reachable from it:

- **REQ**: interpolates `Y` piecewise linearly between the stored points (as in [CALIBRATE_3P](CALIBRATE_3P.md)) and fires `CNF`.
- **C_MIN**/**C_MID**/**C_MAX**: store the current raw value `X` in the corresponding `X_MIN`/`X_MID`/`X_MAX` and fire the matching confirmation event (`EO_MIN`/`EO_MID`/`EO_MAX`).

Each of these four states returns immediately to `START`, from which all four events are again equally reachable -- so the calibration points can be visited in any order and repeated individually as often as needed.

**Example** (joystick with center drift, raw range `0..1000`, desired output range `-100..0..100`):

| Step | Action | Result |
|---|---|---|
| 1 | Move joystick to **minimum**, fire `EI_MIN` | `X_MIN = 50` (drift from ideal `0`) |
| 2 | Move joystick to **center**, fire `EI_MID` | `X_MID = 520` (drift from ideal `500`) |
| 3 | Move joystick to **maximum**, fire `EI_MAX` | `X_MAX = 980` (drift from ideal `1000`) |

Result: `Y` is interpolated and clipped between `MIN_REF=-100`, `MID_REF=0` and `MAX_REF=100`.

## Technical Details

- **Four equal actions from a shared start state**: unlike [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md), there is no dependency between the calibration steps -- each point can be re-set independently and in any order.
- **Output always clipped**: `Y` is clipped to `MIN_REF..MAX_REF` after interpolation.
- **Degenerate calibration points**: as with `CALIBRATE_3P`, an interpolation with `X_MID <= X_MIN` or `X_MAX <= X_MID` returns a constant `MIN_REF` or `MID_REF` instead of dividing by zero.

## State Overview

```
START --REQ-----> REQ    --1--> START   (normal operation)
START --EI_MIN--> C_MIN  --1--> START   (calibrate minimum)
START --EI_MID--> C_MID  --1--> START   (calibrate mid)
START --EI_MAX--> C_MAX  --1--> START   (calibrate maximum)
```

All four calibration events are independently reachable from `START` -- no enforced order.

## Application Scenarios

- Three-point calibration of joysticks in systems that already provide the calibration trigger as an event
- Applications where each calibration point needs its own, immediate confirmation (e.g. for UI feedback "point X calibrated")
- Readjusting individual points (e.g. only `EI_MID` after drift) without needing to recalibrate the other two

## ⚖️ Comparison with Similar Blocks

Compare with [CALIBRATE_3P](CALIBRATE_3P.md), which applies the same three-point logic Boolean-triggered rather than event-driven, and with [E_CALIBRATE](E_CALIBRATE.md)/[E_CALIBRATE_SQ](E_CALIBRATE_SQ.md), which perform a linear two-point rather than three-point calibration.

## Conclusion

`E_CALIBRATE_3P` provides event-driven three-point calibration with independently triggerable, individually confirmed calibration points, and fits especially well for joysticks and similar controls with a center position.
