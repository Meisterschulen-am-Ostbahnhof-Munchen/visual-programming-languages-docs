# NumericValue_PHYS

(Image not available)
![NumericValue_PHYS](./NumericValue_PHYS.svg)

* * * * * * * * * *
## Introduction

The function block **NumericValue_PHYS** is an input service interface block according to ISO 11783-6. It returns a physical REAL value by reading a raw digital value (DWORD) from the ISOBUS object pool and converting it into a physical value, taking into account a predefined scaling and offset. The conversion is performed entirely in software (within the function block).
## Interface Structure

### **Event Inputs**

| Event | Type | With Variables | Comment |
|----------|-----|----------------|-----------|
| INIT | EInit | QI, PARAMS, stObj | Initialize the block |
| REQ | Event | QI | Request a new physical value |

### **Event Outputs**

| Event | Type | With variables | Comment |
|----------|-----|---------------|------------|
| INITO | EInit | QO, STATUS | Confirm initialization |
| IND | Event | QO, STATUS, rPhys | Output the calculated physical value |

### **Data Inputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| QI | BOOL | Input qualifier (enables processing) |
| PARAMS | STRING | Service parameter (e.g., configuration string) |
| stObj | logiBUS::utils::conversion::phys::NumericObjectPool_S | Object pool properties: Object ID (16 bits), scaling, offset, decimal places |

### **Data Outputs**

| Variable | Type | Comment |
|----------|-----|-----------|
| QO | BOOL | Output qualifier (processing status) |
| STATUS | STRING | Status message (error or success message) |
| rPhys | REAL | Physical value after applying scaling/offset |

### **Adapters**

No adapters available.

## Functionality

The internal process is controlled via the INIT and REQ events and utilizes four sub-function blocks:

1. **INIT**
- The passed structure parameter `stObj` is copied via the sub-function block `F_MOVE` (of type `iec61131::selection::F_MOVE`).
- The copied value (`stObj.u16ObjId`) is forwarded to the sub-function block `NumericValue_ID`, which is thereby initialized (`NumericValue_ID.INIT`).
2. **REQ** (or re-output after INIT)
- The sub-function block `NumericValue_ID` is triggered by `REQ`. It outputs a raw DWORD value from the ISOBUS object pool via its output `IN`.

This DWORD value is converted into an unsigned 32-bit integer (`UDINT`) via `F_DWORD_TO_UDINT`.

The sub-module `F_RAW_TO_PHYS` receives the integer value and the original structure `stObj` (scaling, offset, decimal places) and calculates the physical REAL value from it (`rPhys`).

Finally, the output `IND` is activated, and the calculated value is output at the data output `rPhys`.
...``

The chaining ensures that the current raw value is read from the object pool and calculated for each REQ.

## Technical Features

- **Standard Compliance**: The function block complies with the ISO 11783-6 standard (ISOBUS).
- **Software Scaling**: Unlike purely hardware interfaces, the conversion (scaling/offset) is performed within the function block, allowing for flexible adaptation without changing the peripherals.
- **Reusable Sub-Function Blocks**: The sub-function blocks used (`NumericValue_ID`, `F_DWORD_TO_UDINT`, `F_RAW_TO_PHYS`, `F_MOVE`) are standardized logiBUS or IEC 61131 function blocks and can be used in other contexts.
- **Object Pool Structure**: The input structure `stObj` contains all necessary parameters (object ID, scale, offset, decimal places) and can be managed centrally.

## State Overview

The function block does not have an explicit state machine but reacts purely event-driven. The process is divided into two main phases:

- **Initialization Phase** (Event `INIT` → `INITO`):

Acceptance and storage of the configuration (`stObj`), initialization of `NumericValue_ID`.

- **Operation Phase** (Event `REQ` → `IND`):

Reading the raw value, conversion, and output of the physical value.

After successful initialization, `REQ` can be executed any number of times.

## Application Scenarios

- **ISOBUS Vehicle Control**: Reading sensor data (e.g., speed, pressure, temperature) from the ISOBUS object pool and converting it into physical units.
- **Agricultural Automation**: Processing measured values from ISOBUS-compatible devices (tractors, implements) for further control or visualization.
- **Test and Simulation Environments**: Replacing real hardware components with software emulation using defined scaling.

## Comparison with Similar Components

- **NumericValue_ID**: Returns only the raw DWORD value without scaling/offset. `NumericValue_PHYS` extends this value with the physical conversion.

**NumericValue_ID**: Returns only the raw DWORD value without scaling/offset. - **Analog input blocks** (e.g., `AI_SCALED`) in PLC systems: These often scale directly in the hardware driver. `NumericValue_PHYS`, on the other hand, operates purely in software and is therefore more flexible with regard to parameterization.

- **logiBUS blocks such as `F_RAW_TO_PHYS`**: These are used internally by `NumericValue_PHYS`; this function block encapsulates the entire chain from ID query to final output.

## Conclusion

The function block `NumericValue_PHYS` offers a clean and standards-compliant way to convert ISOBUS objects into physical values with integrated scaling and offset correction. By using modular sub-components and parameterization via a structure variable, it is easy to maintain and reusable. It is particularly suitable for applications requiring software-controlled conversions without affecting the hardware configuration.
