# AR_CALIBRATE

![AR_CALIBRATE](./AR_CALIBRATE.svg)

* * * * * * * * * *
## Introduction

The function block `AR_CALIBRATE` is used for offset and scale calibration of an analog input signal provided via an adapter. It enables two-stage calibration: First, the offset is determined by comparison with a reference value during active calibration (CO), and then the scale is determined using a second reference (CS). The calibrated output signal is calculated continuously.
## Interface Structure

### **Event Inputs**

| Event | Type | With | Description |
|----------|-----|-----|--------------|
| `SET` | `EInit` | `Y_Offset`, `Y_Scale` | Sets the reference values for offset and scale calibration |

### **Event Outputs**

This function block does not have its own event outputs. However, events are sent via the connected adapters (e.g., `Y.E1`, `OFFSET.EO1`, `SCALE.EO1`).

### **Data Inputs**

| Name | Type | Description |
|------|-----|---------------|
| `Y_Offset` | `REAL` | Reference value for offset calibration |
| `Y_Scale` | `REAL` | Reference value for scale calibration |

### **Data Outputs**

The FB has no direct data outputs. The calculated values are provided via the adapters `Y`, `OFFSET`, and `SCALE`.

### **Adapters**

**Plugs (providing interfaces):**

| Adapter | Type | Description |
|---------|-----|--------------|
| `Y` | `adapter::types::unidirectional::AR` | Calibrated output (data + event) |
| `OFFSET` | `adapter::types::bidirectional::AR2` | Returns the calculated offset value (bidirectional) |
| `SCALE` | `adapter::types::bidirectional::AR2` | Returns the calculated scale factor (bidirectional) |

**Sockets (user interfaces):**

| Adapter | Type | Description |
|---------|-----|--------------|
| `X` | `adapter::types::unidirectional::AR` | Analog input value (unidirectional) |
| `CO` | `adapter::types::unidirectional::AX` | Trigger for offset calibration (event + data) |
| `CS` | `adapter::types::unidirectional::AX` | Trigger for Scale Calibration (Event + Data) |

## Functionality

The function block operates with three basic algorithms, which are executed in the states `REQ`, `CO`, and `CS`:

- **REQ** (Normal Operation):

Y.D1 := (X.D1 + OFFSET.DI1) * SCALE.DI1`
The output value is calculated from the input, the current offset, and the scale factor.

- **CO** (Offset Calibration):

OFFSET.DO1 := Y_Offset - X.D1`
The offset is determined as the difference between the reference value `Y_Offset` and the current input value.

- * **CS** (Scale Calibration):

SCALE.DO1 := Y_Scale / (X.D1 + OFFSET.DI1)`

The scale factor is calculated by dividing the reference value `Y_Scale` by the input value corrected by the offset.

**Calibration Procedure:**

1. In state `REQ`, the function block (FB) is transitioned to state `CO` by an event on adapter `CO` (containing data). There, the offset is calculated and output via adapter `OFFSET`. The FB then immediately returns to state `REQ`.

2. Scale calibration is performed analogously via the adapter `CS` and the state `CS`.

3. The event `SET` updates the reference values `Y_Offset` and `Y_Scale` without exiting the calibration state.
4. Repeated measurements (via `X.E1`) update the output `Y` with the current calibration parameters.

The transitions between the states are defined as follows:

- `REQ` → `REQ`: at `X.E1`, `SET`, `OFFSET.EI1`, or `SCALE.EI1`
- `REQ` → `CO`: when `CO.E1` occurs and the associated data (`CO.D1`) is valid
- `REQ` → `CS`: when `CS.E1` occurs and the associated data (`CO.D1`) is valid (`CS.D1`) is valid
- `CO` → `REQ`: always (condition `1`)
- `CS` → `REQ`: always (condition `1`)

## Technical Features

- **Adapter-based communication**: All inputs and outputs (except reference values) are implemented via adapters. This allows for flexible coupling with various analog input modules.
- **Bidirectional calibration adapters**: The adapters `OFFSET` and `SCALE` are bidirectional, meaning they can be written to by the calibration function block and read by external modules.
- **Two-Stage Calibration**: Offset and scaling are calibrated sequentially. The scaling factor already uses the determined offset to ensure correct linear correction.
- **No Own Event Output**: The function block does not generate its own events but triggers them via the adapter events (e.g., `Y.E1` after each calculation).

## State Overview

| State | Description | Action |
|---------|--------------|--------|
| **REQ** | Normal Operation – Calculation of the Calibrated Output | Executes algorithm `REQ`, sends event to `Y.E1` |
| **CO** | Offset Calibration | Executes algorithm `CO`, sends event to `OFFSET.EO1` |
| **CS** | Scale Calibration | Executes algorithm `CS`, sends event to `SCALE.EO1` |

## Application Scenarios

- **Industrial Data Processing**: Calibration of pressure sensors, temperature sensors, or other analog encoders where offset and gain need to be readjusted.
- **Measuring Chain Alignment**: After connecting a sensor, the entire chain can be linearized by applying a known zero point (offset) and a known measured value (scaling).
- **Automatic Recalibration**: Drift effects can be compensated for by cyclically triggering the calibration adapters.
*
## Comparison with Similar Function Blocks

Simple scaling function blocks (e.g., `SCALE`) offer only fixed multiplication and addition, without automatic calibration. In contrast, `AR_CALIBRATE` integrates the entire calibration logic – including reference setting and event-driven activation – and is therefore suitable for dynamic environments where parameters need to be adjusted during operation.

## Conclusion

The `AR_CALIBRATE` function block provides a robust solution for offset and scale calibration of analog signals. Thanks to its adapter-based interfaces and clear state machine, it can be easily integrated into existing automation solutions and enables precise, repeatable measurement correction.
