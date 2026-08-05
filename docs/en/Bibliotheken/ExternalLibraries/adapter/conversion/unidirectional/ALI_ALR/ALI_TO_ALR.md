# ALI_TO_ALR
![ALI_TO_ALR](./ALI_TO_ALR.svg)
*(Image not available)*

* * * * * * * * * *
## Introduction
The function block **ALI_TO_ALR** is a composite function block that converts an **ALI adapter** (LINT data type) to an **ALR adapter** (LREAL data type). It acts as a bridge between different adapter interfaces and enables seamless data conversion from 64-bit integers to 64-bit floating-point numbers.

## Interface Structure

### **Event Inputs**

The function block does not have separate event inputs. Event-driven processing is handled via the **socket** `ALI_IN`, whose event `E1` triggers the conversion.

### **Event Outputs**

There are no standalone event outputs. The result event is output via the **plug** `ALR_OUT` to its event `E1`.

### **Data Inputs**

The FB has no direct data inputs. The LINT data to be converted is provided via the **socket** `ALI_IN` (data point `D1`).

### **Data Outputs**

Similarly, there are no separate data outputs. The converted LREAL value is output via the **plug** `ALR_OUT` (data point `D1`).

### **Adapters**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| **Socket** | `ALI_IN` | Input | Adapter type `adapter::types::unidirectional::ALI` (LINT) |
| **Plug** | `ALR_OUT` | Output | Adapter type `adapter::types::unidirectional::ALR` (LREAL) |

## Functionality

The function block operates as a simple forwarder and converter:

1. An event at **Socket** `ALI_IN.E1` triggers the internal function block `Convert` (type `F_LINT_TO_LREAL`).

2. Simultaneously, the LINT value from `ALI_IN.D1` is passed to input `Convert.IN`.

3. The conversion block `Convert` converts the value into an LREAL value according to IEC 61131 conversion logic.

4. After the conversion is complete, `Convert` generates the event `CNF`, which is forwarded to the **plug** `ALR_OUT.E1`.

5. At the same time, the converted LREAL value from `Convert.OUT` is passed to `ALR_OUT.D1`.

The entire process is event-driven and does not use its own state logic.

...
## Technical Features

- **Composite Block**: The logic is implemented exclusively through the interconnection of the standardized conversion block `F_LINT_TO_LREAL` – no proprietary algorithm.
- **Adapter-Oriented Interface**: The function block (FB) completely encapsulates the conversion within the adapter interfaces, allowing it to be used in environments with uniform adapter types (unidirectional).
- **No State Machine**: Due to its pure data flow structure, there is no internal state machine.

## State Overview

The FB does not have its own state machine. Execution follows the event chain of the internal network exclusively:

- Idle → Event sent to `ALI_IN.E1` → Conversion in progress → Result event sent to `ALR_OUT.E1` → Returns to Idle.

## Application Scenarios
- Integration of components that provide LINT values (e.g., counters, position sensors) into systems that expect LREAL (e.g., control algorithms with floating-point calculations).
- Conversion from integer-based to floating-point-based adapter interfaces without changing the higher-level architecture.
- Intermediate layer in modular control projects where different data types need to be connected.

## Comparison with Similar Components

The library contains analogous converters for other data types (e.g., `LINT_TO_REAL`, `DINT_TO_REAL`). `ALI_TO_ALR` is the adapter-specific variant that integrates the conversion into the standardized unidirectional adapters `ALI` and `ALR`. It allows for easy exchange between different adapter types without the calling environment needing to know the details of the conversion.

## Conclusion

The FB `ALI_TO_ALR` offers a clean, maintainable, and standards-compliant solution for converting a LINT adapter to an LREAL adapter. By using a proven IEC 61131 conversion block, the implementation remains reliable and efficient. It is particularly suitable for modular control architectures where data type and adapter compatibility is required.
