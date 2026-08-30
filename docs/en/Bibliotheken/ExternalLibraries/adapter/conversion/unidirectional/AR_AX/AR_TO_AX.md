# AR_TO_AX

![AR_TO_AX](./AR_TO_AX.svg)

* * * * * * * * * *
## Introduction

The AR_TO_AX function block converts a REAL value received via an AR adapter into a BOOL value and outputs it via an AX adapter. The conversion is performed by comparing the REAL value with 0.0. If the value is not zero, TRUE is output; otherwise, FALSE. The block serves as a bridge between analog and digital adapter interfaces.
## Interface Structure

### **Event Inputs**

No direct event inputs at the FB level. The event input is contained in the AR adapter (`AR_IN.E1`).

### **Event Outputs**

No direct event outputs at the FB level. The event output is included in the AX adapter (`AX_OUT.E1`).

### **Data Inputs**

No direct data inputs at the FB level. The data input is included in the AR adapter (`AR_IN.D1`).

### **Data Outputs**

No direct data outputs at the FB level. The data output is included in the AX adapter (`AX_OUT.D1`).

### **Adapters**

- **AR_IN** (Socket) – Adapter of type `adapter::types::unidirectional::AR`. Accepts a REAL value and an event to start processing.
- **AX_OUT** (Plug) – Adapter of type `adapter::types::unidirectional::AX`. Provides the BOOL result value and an event to confirm processing.

## Functionality

The function block processes incoming REAL values as follows:

1. An event at `AR_IN.E1` triggers the internal comparison function block `F_NE` (not equal).
2. The REAL value received via `AR_IN.D1` is compared to the constant value 0.0.
3. The result of the comparison (BOOL) is forwarded via `F_NE.OUT` to `AX_OUT.D1`.
4. An event at output `F_NE.CNF` is sent to `AX_OUT.E1` to signal the availability of the BOOL value.

The internal function block `F_NE` is an IEC 61131-3 compliant comparator block and outputs TRUE if the input `IN1` is not equal to `IN2` (here 0,0).

## Technical Features

- Uses a composite function block approach, where the logic consists of a single comparator block and adapter connections.
- All inputs and outputs are implemented via standardized unidirectional adapters (`AR`, `AX`), enabling a modular and interchangeable interface definition.
- The comparator value (0,0) is fixed in the function block and cannot be changed at runtime.
- Execution is event-driven: A conversion is only performed when an event occurs at `AR_IN.E1`.

## State Overview

Since the function block (FB) is implemented as a composition (network of basic building blocks), it does not have its own state machine. Its function is determined by the sequential processing of event and data flows in the internal network:

- **Waiting State**: No event at `AR_IN.E1`. The output value remains unchanged.
- **Processing State**: An event at `AR_IN.E1` triggers the comparison and generates an event at `AX_OUT.E1` as soon as the BOOL value is available.

## Application Scenarios

- **Threshold Switch**: An analog sensor (e.g., a pressure sensor) provides REAL values. The FB outputs TRUE as soon as the value deviates from 0.0 (e.g., when a threshold is exceeded, if the zero point is calibrated).
- **Digitization of Analog Signals**: For connecting analog adapters to digital logic in control engineering.
- **Simple Plausibility Check**: Checks whether a REAL value is non-zero (e.g., a valid measured value).

## Comparison with Similar Function Blocks

Unlike a generic `AR_TO_BOOL` function block, which uses direct data without an adapter, AR_TO_AX is specifically designed for use with adapter interfaces. A comparison block with an adjustable threshold (e.g., `F_GT`, `F_LT`) would offer more flexibility but would also require additional configuration effort. This function block provides a simple, fixed conversion: non-zero → TRUE.

## Conclusion

The AR_TO_AX function block offers a compact solution for converting a REAL adapter value to a BOOL adapter value using zero comparison. Thanks to the use of adapters and a standardized comparison module, it can be easily integrated into existing 4diac projects and is well-suited for fast, unidirectional signal conversions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
