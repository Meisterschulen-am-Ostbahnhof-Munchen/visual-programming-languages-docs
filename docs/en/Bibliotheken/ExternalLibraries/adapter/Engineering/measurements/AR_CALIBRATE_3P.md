# AR_CALIBRATE_3P

![AR_CALIBRATE_3P](./AR_CALIBRATE_3P.svg)

* * * * * * * * * *

## Introduction

The **AR_CALIBRATE_3P** function block enables 3-point calibration of an analog input signal using adapters. It is specifically designed for joysticks that exhibit center drift and corrects this drift by linearizing between three reference points: minimum, mean, and maximum. The calibration points are saved and can be reset as needed.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| SET | Event | Sets the reference values (MIN_REF, MID_REF, MAX_REF) for the calibration curve. Does not trigger a calculation, but only sets the target output values. |

### **Event Outputs**

No explicit event outputs are available. Output is exclusively via the **Y** adapter.

### **Data Inputs**

| Name | Data Type | Default Value | Comment |
| ------ | ---------- | ------------- | ----------- |
| MIN_REF | REAL | 0.0 | Target value for the smallest input value (Min). |
| MID_REF | REAL | 50.0 | Target value for the middle value (Mid). |
| MAX_REF | REAL | 100.0 | Target value for the largest input value (Max). |

### **Data Outputs**

No direct data outputs – all outputs are provided via **plugs** (output adapters).

### **Adapters**

| Direction | Name | Adapter Type | Comment |
| ---------- | ------ | ------------ | ----------- |
| **Plug** (Output) | Y | `adapter::types::unidirectional::AR` | Calibrated output value (analog value plus event). |
| **Plug** (Output) | X_MIN | `adapter::types::bidirectional::AR2` | Stored minimum value (from the raw value). |
| **Plug** (Output) | X_MID | `adapter::types::bidirectional::AR2` | Stored average value (from the raw value). |
| **Plug** (Output) | X_MAX | `adapter::types::bidirectional::AR2` | Stored maximum value (from the raw value). |
| **Socket** (Input) | X | `adapter::types::unidirectional::AR` | Raw value from the sensor (analog value plus event). |
| **Socket** (Input) | C_MIN | `adapter::types::unidirectional::AX` | Event for calibrating the minimum point (reads the current raw value). |
| **Socket** (Input) | C_MID | `adapter::types::unidirectional::AX` | Event for calibrating the midpoint. |
| **Socket** (Input) | C_MAX | `adapter::types::unidirectional::AX` | Event for calibrating the maximum point. |

## Functionality

The calibration is based on piecewise linear interpolation between three stored raw values (`X_MIN`, `X_MID`, `X_MAX`) and the corresponding reference values (`MIN_REF`, `MID_REF`, `MAX_REF`).

1. **Calibration of the Points:**

An event at one of the calibration inputs (`C_MIN.E1`, `C_MID.E1`, `C_MAX.E1`) saves the currently applied raw value (`X.D1`) to the corresponding stored value (`X_MIN.DO1`, `X_MID.DO1`, `X_MAX.DO1`). This requires that the supplied data signal (`C_MIN.D1`, etc.) is true.

1. **Calculation of the Calibrated Value:**

As soon as an event arrives from the raw value adapter (`X.E1`), the function block becomes active and executes the **REQ** algorithm. The raw value `X.D1` is then linearly mapped:

- If the raw value is below the stored mean `X_MID.DI1`, the lower branch of the characteristic curve is used:

Y.D1 = MIN_REF + (X.D1 – X_MIN.DI1) * (MID_REF – MIN_REF) / (X_MID.DI1 – X_MIN.DI1)`

If the intervals are invalid (division by zero or negative range), `MIN_REF` is used.

... - If the raw value is above or equal to `X_MID.DI1`, the upper branch is calculated:

Y.D1 = MID_REF + (X.D1 – X_MID.DI1) * (MAX_REF – MID_REF) / (X_MAX.DI1 – X_MID.DI1)`

Here too, invalid intervals result in `MID_REF` being output.

1. **Clipping:**

The calculated output value is clipped to the interval `[MIN_REF, MAX_REF]` to ensure physically meaningful results.

1. **Output:**

The calibrated value is output via the adapter `Y` (event `Y.E1` and data `Y.D1`).

## Technical Features

- **Bidirectional Adapters for Calibration Points:** The stored raw values (`X_MIN`, `X_MID`, `X_MAX`) are bidirectional adapters of type `AR2`. They can be both written to (during calibration) and read from (during calculation). This ensures that the calibration points are permanently retained as long as the connection to the parent resource exists.
- **Event-Driven Calibration:** The calibration of the three points is not automatic but is triggered by specific events (`C_MIN`, `C_MID`, `C_MAX`). This allows for the time-separated acquisition of the reference points.
- **Protection against invalid intervals:** The algorithms check whether the ranges of the stored raw values are positive. If not (e.g., if the system is not yet calibrated), safe default values are output.
- **No self-calibration:** The function block does not store a history – the system must explicitly set the calibration points.

## State overview

| State | Description |
| --------- | -------------- |
| **IDLE** | Waiting – no event pending. Transitions: For `SET` → IDLE (only set reference values); for `X_MIN.EI1`, `X_MID.EI1`, `X_MAX.EI1` → IDLE (no action); for `C_MIN.E1[C_MIN.D1]` → CAL_MIN; at `C_MID.E1[C_MID.D1]` → CAL_MID; at `C_MAX.E1[C_MAX.D1]` → CAL_MAX; at `X.E1` → REQ. |
| **REQ** | Calculates the calibrated output value. Returns to IDLE immediately after execution. |
| **CAL_MIN** | Stores the current raw value as the minimum (`X_MIN.DO1 := X.D1`). Returns to IDLE automatically. |
| **CAL_MID** | Stores the current raw value as the average. Returns to IDLE automatically. |
| **CAL_MAX** | Stores the current raw value as the maximum. Returns to IDLE automatically. |

**Transition Conditions:**

- `X.E1` → Start of calculation
- `C_MIN.E1[C_MIN.D1]` → Calibration of the minimum point (only if the data signal is true)
- `C_MID.E1[C_MID.D1]` → Calibration of the midpoint
- `C_MAX.E1[C_MAX.D1]` → Calibration of the maximum point
- `SET`, `X_MIN.EI1`, `X_MID.EI1`, `X_MAX.EI1` → No change of state (remains in IDLE)

## Application Scenarios

- **Joystick Calibration:** A joystick with an analog output (e.g., 0-10V) exhibits component-related deviations in the center and at the End stops. The operator moves the joystick to the three positions (Min, Center, Max) and triggers the calibration events via pushbuttons. Afterwards, `Y` delivers a linearized value normalized to the desired target values.
- **Analog Potentiometer:** A sliding potentiometer showing signs of wear can be corrected by 3-point calibration.
- **Sensors with Offset and Scaling Error:** For example, a pressure sensor with non-linear behavior between 0%, 50%, and 100% of its range.

## Comparison with Similar Function Blocks

| Function Block | Property |
| ---------- | ------------- |
| **AR_SCALE** | Simple linear scaling (2-point) – without correction of center nonlinearities. |
| **AR_CALIBRATE_2P** | Two-point calibration (Min, Max) – cannot address center drift. |
| **AR_CALIBRATE_3P** (this block) | Three-point calibration with separate center calibration – ideal for joysticks with center drift. |
| **Table-based correction** | More complex, requires many reference points; AR_CALIBRATE_3P is simpler and faster. |

The key advantage lies in the explicit handling of the center point, which is neglected in many simple scaling methods.

## Conclusion

AR_CALIBRATE_3P` is a practical function block for the precise correction of analog sensors with three distinct reference points. Thanks to its adapter-based interface, it integrates seamlessly into IEC-61499 systems and enables a flexible and reusable calibration solution, especially for joysticks and similar input devices.
