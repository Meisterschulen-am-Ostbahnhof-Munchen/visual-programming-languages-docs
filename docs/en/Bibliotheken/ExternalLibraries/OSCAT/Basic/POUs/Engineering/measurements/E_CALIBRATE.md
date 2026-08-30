# E_CALIBRATE

![E_CALIBRATE_ecc](./E_CALIBRATE_ecc.svg)

![E_CALIBRATE](E_CALIBRATE.svg)

* * * * * * * * * *

## Introduction

`E_CALIBRATE` is the event-driven counterpart to [CALIBRATE](CALIBRATE.md): the two-point calibration (`Y = (X + OFFSET) * SCALE`) is triggered not by Boolean data values but by its own events `EICO`/`EICS`, each with its own confirmation event. Ordering (offset before scale) is still not enforced here -- for that, see [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).

## Interface Structure

### **Event Inputs**

- **REQ**: normal execution request -- computes `Y`. Carries `X`, `Y_Offset`, `Y_Scale`, `OFFSET`, `SCALE`.
- **EICO**: calibrates the offset (`OFFSET := Y_Offset - X`). Carries `X`, `Y_Offset`.
- **EICS**: calibrates the scale (`SCALE := Y_Scale / (X + OFFSET)`). Carries `X`, `Y_Scale`, `OFFSET`.

### **Event Outputs**

- **CNF**: confirms `REQ`, carries `Y`.
- **EOCO**: confirms offset calibration, carries `OFFSET`.
- **EOCS**: confirms scale calibration, carries `SCALE`.

### **Data Inputs**

- **X** (REAL): raw input value.
- **Y_Offset** (REAL): target output value at the low reference point.
- **Y_Scale** (REAL): target output value at the high reference point.

### **Data Outputs**

- **Y** (REAL): calibrated output value.

### **In/Out Variables**

- **OFFSET** (REAL, initial `0.0`): stored offset value.
- **SCALE** (REAL, initial `1.0`): stored scale factor.

## Functionality

`E_CALIBRATE` has three ECC states, all directly reachable from state `REQ`:

- **REQ** (start state): on the `REQ` event, `Y := (X + OFFSET) * SCALE` is computed and `CNF` fires; the block stays in `REQ`.
- **CO**: on `EICO`, the block transitions to `CO`, runs `OFFSET := Y_Offset - X`, fires `EOCO` and immediately returns to `REQ`.
- **CS**: on `EICS`, the block transitions to `CS`, runs `SCALE := Y_Scale / (X + OFFSET)` (only if `X + OFFSET <> 0`), fires `EOCS` and immediately returns to `REQ`.

Since both `EICO` and `EICS` are reachable from `REQ` at any time, the ECC does not enforce ordering -- `EICS` can also be fired before `EICO`, but then yields an inconsistent result since `SCALE` would be based on an as-yet-uncalibrated `OFFSET`.

**Example** (4-20 mA pressure sensor via logiBUS, normalized to `0.0..1.0`, desired output range `0.0..500.0`):

| Step | Action | Result |
| --- | --- | --- |
| 1 | Apply 4 mA (`X=0.0`), `Y_Offset=0.0`, fire `EICO` | `OFFSET = 0` |
| 2 | Apply 20 mA (`X=1.0`), `Y_Scale=500.0`, fire `EICS` | `SCALE = 500` |

Result: `Y = (X + 0) * 500 = X * 500 = 0..500`.

## Technical Details

- **Y after CO only correct when SCALE = 1**: as with `CALIBRATE`, `OFFSET := Y_Offset - X` only yields exactly `Y = Y_Offset` after offset calibration if `SCALE` is still `1.0`. `E_CALIBRATE_SQ` resolves this using `OFFSET := Y_Offset / SCALE - X`.
- **No order enforcement**: `EICO` and `EICS` are both directly reachable from `REQ` -- the ECC does not track whether calibration has already happened. For enforced ordering, see [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md).
- **REQ stays available at all times**: normal operation (`REQ`) is possible regardless of calibration status, even between `EICO` and `EICS`.

## State Overview

```
REQ --EICO--> CO --1--> REQ     (offset calibration)
REQ --EICS--> CS --1--> REQ     (scale calibration)
REQ --REQ---> REQ --1--> REQ    (normal operation)
```

All three states are pass-through states: the block returns to `REQ` immediately after each action.

## Application Scenarios

- Two-point calibration of analog sensors in systems that already provide the calibration trigger as an event (e.g. a button-press event rather than a data value)
- Applications where offset and scale calibration each need their own, immediate confirmation (`EOCO`/`EOCS`)
- Systems with occasional offset re-calibration without redetermining the scale

## ⚖️ Comparison with Similar Blocks

Compare with [CALIBRATE](CALIBRATE.md), which applies the same formula Boolean-triggered rather than event-driven, and with [E_CALIBRATE_SQ](E_CALIBRATE_SQ.md), which uses the same event interface but enforces offset-before-scale ordering via its ECC and always computes `Y` correctly after offset calibration regardless of `SCALE`.

## Conclusion

`E_CALIBRATE` provides event-driven two-point calibration with its own confirmation event per calibration step, but still leaves the correct order (offset before scale) to the caller.
