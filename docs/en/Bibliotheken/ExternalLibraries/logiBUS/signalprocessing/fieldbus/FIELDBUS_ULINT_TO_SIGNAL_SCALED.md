# FIELDBUS_ULINT_TO_SIGNAL_SCALED

![FIELDBUS_ULINT_TO_SIGNAL_SCALED](./FIELDBUS_ULINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Introduction

The function block **FIELDBUS_ULINT_TO_SIGNAL_SCALED** is used to convert a raw ULINT value (e.g., from a fieldbus) into a scaled LREAL value. The validity of the input signal is checked against a constant threshold (`VALID_SIGNAL_LW`). If the input is valid, linear scaling is performed (multiplication by a factor and addition of an offset); otherwise, the output is set to 0,0 and the validity is negated.

## Interface Structure

### **Event Inputs**

| Event | Type | Description | With Variables |
| ---------- | ----- | -------------- | --------------- |
| **INIT** | EInit | Initialization Request | SCALE, OFFSET |
| **REQ** | Event | Normal Execution Request | IN |

### **Event Outputs**

| Event | Type | Description | With Variables |
| ---------- | ----- | --------------- | --------------- |
| **INITO** | EInit | Initialization Acknowledgement | – |
| **CNF** | Event | Execution Acknowledgement | OUT, VALID |

### **Data Inputs**

| Variable | Type | Initial Value | Description |
| ---------- | ----- | ------------- | -------------- |
| **IN** | ULINT | `LWORD_TO_ULINT(NOT_AVAILABLE_LWM)` | Raw value from the fieldbus |
| **SCALE** | LREAL | `1.0` | Scaling factor |
| **OFFSET** | DINT | `0` | Offset added after scaling |

### **Data Outputs**

| Variable | Type | Initial value | Description |
| ---------- | ----- | -------------- | -------------- |
| **OUT** | LREAL | `0.0` | Scaled output value (valid only if VALID = TRUE) |
| **VALID** | BOOL | `FALSE` | Validation signal: TRUE if IN ≤ `VALID_SIGNAL_LW`, otherwise FALSE |

### **Adapters**

No adapters available.

## Functionality

The function block has two operating states, which are activated by the **INIT** and **REQ** events:

1. **INIT State**

When the INIT event arrives, the algorithm `INIT` is executed (currently empty). The **INITO** event is then sent.

The **SCALE** and **OFFSET** parameters can be set via the inputs connected to INIT.

1. **REQ State**

When a REQ event occurs, the algorithm `REQ` is executed:

- Check: `IN ≤ LWORD_TO_ULINT(VALID_SIGNAL_LW)`
- **Valid** (condition met):

OUT := ULINT_TO_LREAL(IN) * SCALE + DINT_TO_LREAL(OFFSET)`

VALID := TRUE`

- **Invalid** (condition not met):

OUT := 0.0`

VALID := FALSE`

- Subsequently, the **CNF** event is output with the new values of **OUT** and **VALID**.

The constants `NOT_AVAILABLE_LWM` and `VALID_SIGNAL_LW` are taken from the imported package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` and define the threshold for validation.

## Technical Features

- The function block is implemented as a **SimpleFB** with two states, making it deterministic and eliminating the need for complex state machines.
- Validation is performed by comparing the result with the imported `VALID_SIGNAL_LW`. This allows for application-specific configuration of the valid value range.
- In the event of an invalid signal, the output **OUT** is reset to 0,0 – a defined error handling mechanism.
- Scaling and offset are passed as LREAL and DINT, respectively. The offset is internally converted to LREAL, enabling negative values.
- The initial value of **IN** (`NOT_AVAILABLE_LWM`) is chosen so that it is recognized as invalid on the first pass if no valid fieldbus value is present.

## State Overview

| State | Description | Trigger | Output Event |
| --------- | -------------- | ---------- | ----------------- |
| **INIT** | Initialization (no action) | INIT | INITO |
| **REQ** | Input signal processing (scaling or error handling) | REQ | CNF |

## Application Scenarios

- **Fieldbus Sensors**: A 64-bit ULINT value from a pressure sensor is converted to bar using a factor (e.g., 0.001), and a zero-point offset is added. Validation prevents the processing of communication errors.
- **Error Handling**: If the value exceeds `VALID_SIGNAL_LW` (e.g., due to sensor failure), **VALID** is set to FALSE, preventing the higher-level controller from accepting the value.
- **Initialization**: During system startup, the scaling and offset can be loaded from a parameter set via INIT.

## Comparison with Similar Function Blocks

- **FIELDBUS_SINT_TO_SIGNAL_SCALED** – same logic, but for signed 8-bit values (SINT). This block processes 64-bit unsigned values.
- **FIELDBUS_ULINT_TO_SIGNAL (without scaling)** – simple type conversion without scaling and without integrated validation.
- **GENERIC_SCALER** – a general scaling block where the validity check must be implemented externally.

## Conclusion

The **FIELDBUS_ULINT_TO_SIGNAL_SCALED** function block offers a compact, configurable solution for the reliable conversion of raw fieldbus data into physical values. By combining validity checking, scaling, and offset, it is ideally suited for industrial automation tasks where data integrity and easy calibration are required.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
