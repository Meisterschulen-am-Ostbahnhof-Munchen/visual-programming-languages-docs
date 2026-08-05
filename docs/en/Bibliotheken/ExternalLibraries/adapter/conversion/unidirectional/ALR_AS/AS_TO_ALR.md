# AS_TO_ALR
![AS_TO_ALR](./AS_TO_ALR.svg)
*No image available.*

* * * * * * * * * *
## Introduction
The function block **AS_TO_ALR** is a composite function block (FB) that converts an **AS adapter** (data type SINT) into an **ALR adapter** (data type LREAL). It serves as a simple interface conversion between these two unidirectional adapter types and is located in the package `adapter::conversion::unidirectional`.

## Interface Structure

### **Event Inputs**

| Name | Comment |
|-------|------------------------------------|
| E1 | Event from AS adapter (Socket AS_IN) |

### **Event Outputs**

| Name | Comment |
|-------|--------------------------------------|
| E1 | Event for the ALR adapter (Plug ALR_OUT) |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|---------------------------------|
| D1 | SINT | Data value from the AS adapter (Socket AS_IN) |

### **Data Outputs**

| Name | Data Type | Comment |
|------|----------|-----------------------------------|
| D1 | LREAL | Data value for the ALR adapter (Plug ALR_OUT) |

### **Adapters**

| Direction | Name | Type | Comment |
|----------|--------|---------------------------------------|----------------------------|
| Socket | AS_IN | `adapter::types::unidirectional::AS` | Input Adapter (SINT) |
| Plug | ALR_OUT| `adapter::types::unidirectional::ALR` | Output Adapter (LREAL) |

## Functionality

The **AS_TO_ALR** block forwards incoming events and data values directly to the output side without further processing.

- The event **E1** at socket `AS_IN` is passed to plug `ALR_OUT` without delay.
- The data value **D1** of type SINT is forwarded to the output of the same name. The conversion from SINT to LREAL is performed implicitly by the runtime environment – the function block itself does not execute any arithmetic operations.

The function block has no state machine (ECC) and no internal algorithms; its entire functionality is implemented through the included connections.

## Technical Features
- **Composite Structure**: The function block consists exclusively of an internal network (FBNetwork) with direct event and data connections between the adapters.
- **Implicit Type Conversion**: Data conversion from SINT to LREAL is handled by the IEC 61499 runtime environment. Explicit type conversion is not required.
- **Packaging**: The function block is organized in the package `adapter::conversion::unidirectional`, providing a clean separation between adapter and converter logic.

## State Overview

The **AS_TO_ALR** function block does not have its own state machine (no ECC diagram). Its behavior is defined solely by the direct connection of its inputs and outputs. There is no defined start or end state.

## Application Scenarios
- **Sensor Connection**: A sensor provides data in SINT format (e.g., an 8-bit counter) that needs to be integrated into an environment with an LREAL interface (e.g., an analog adapter) via an AS adapter.
- **Protocol Conversion**: In heterogeneous automation systems where different components expect adapters of various types, **AS_TO_ALR** serves as a simple converter.
- **Interface Migration**: When switching from SINT-based to LREAL-based adapters, this function block can be used as a temporary bridge.

## Comparison with Similar Components
- **AS_TO_AR**: Converts an AS adapter (SINT) to an AR adapter (REAL) – similar structure, but with a smaller value range (REAL instead of LREAL).
- **ALR_TO_AS**: The inverse conversion (LREAL → SINT), which may require explicit range checking or rounding.
- **AS_TO_ALR** is characterized by the larger value range of its output (LREAL), enabling lossless transmission of SINT values.

## Conclusion

The **AS_TO_ALR** is a minimal yet useful converter component for easily connecting AS adapters to ALR adapters. Its composite architecture and implicit type conversion make it easy to understand and efficient to use.
