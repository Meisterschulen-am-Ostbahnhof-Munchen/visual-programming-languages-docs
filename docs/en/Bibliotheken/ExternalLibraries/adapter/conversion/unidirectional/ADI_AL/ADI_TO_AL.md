# ADI_TO_AL
![ADI_TO_AL](./ADI_TO_AL.svg)

* * * * * * * * * *
## Introduction
The function block `ADI_TO_AL` serves as a composite block for converting an ADI adapter (DINT) to an AL adapter (LWORD). It encapsulates a type conversion from a 32-bit integer value to a 64-bit word and provides the connection via unidirectional adapters. The block is ideal for systems where different data type representations between components need to be bridged.
## Interface Structure
The block has no direct event or data inputs/outputs. All communication takes place via two adapter interfaces:

### **Event Inputs**
- **No direct event inputs**

The event is received via the ADI adapter `ADI_IN.E1`.

### **Event Outputs**
- **No direct event outputs**

The outgoing event is sent via the AL adapter `AL_OUT.E1`.

### **Data Inputs**
- **No direct data inputs**

The input data is provided via the ADI adapter `ADI_IN.D1` (data type: DINT).

### **Data Outputs**
- **No direct data outputs**

The output data is provided via the AL adapter `AL_OUT.D1` (data type: LWORD).

### **Adapter**

| Name | Type | Direction | Comment |
|-------------|-----|----------|-----------|
| `ADI_IN` | `adapter::types::unidirectional::ADI` | Socket (Input) | Returns a DINT value and controls processing via event `E1`. |
| `AL_OUT` | `adapter::types::unidirectional::AL` | Plug (Output) | Outputs the converted LWORD value and acknowledges it via event `E1`. |

## Functionality

The function block implements a simple type conversion chain:

1. An event received via the ADI adapter `ADI_IN` (`E1`) starts the conversion.

2. The internal function block `F_DINT_TO_LWORD` converts the incoming DINT value (`ADI_IN.D1`) into an LWORD value.

3. After successful conversion, the result is output as an LWORD via the AL adapter (`AL_OUT.D1`), and an event (`E1`) is sent.

Communication between the adapters and the conversion function block is asynchronous, using event and data connections within the composite block's network.

## Technical Features
- **Unidirectional Adapters** – The block uses exclusively unidirectional adapters (socket for input, plug for output), which define a clear data flow direction.
- **Internal Conversion** – The actual type conversion is handled by the standard block `F_DINT_TO_LWORD` from the IEC 61131 library, eliminating the need for a custom implementation.
- **License** – The block is licensed under the Eclipse Public License 2.0 (EPL-2.0) and can be freely used, modified, and distributed.
- **No States** – The composite block has no state logic of its own; all control is achieved through event chaining.

## State Overview

The block does not have its own state machine. Its behavior is purely reactive: An incoming event at the ADI adapter is immediately reflected in the output of the AL adapter. Internal delays are undefined.

## Application Scenarios
- **Data Bridge Between Different Bus Systems** – When a sensor or controller delivers a DINT value, but a subsequent component expects an LWORD value (e.g., with 64-bit actuators or fieldbus interfaces).
- **Middleware Adaptation** – Use in heterogeneous automation systems to harmonize adapter types without modifying the original components.
- **Test and Simulation Environments** – Easy conversion of data types for debugging or backup connections.

## Comparison with Similar Function Blocks
- **Single Conversion Function Blocks** – Function blocks like `DINT_TO_LWORD` (direct conversion without an adapter) offer a more compact interface but require their own event and data lines.

**Middleware Adaptation** – Use in heterogeneous automation systems to harmonize adapter types without modifying the original components. - **Universal Adapter Converters** – Generic converters exist that can convert any data type via adapters. `ADI_TO_AL` is specifically optimized for the DINT→LWORD combination and is therefore easier to understand and maintain.

- **Bidirectional Adapters** – Unlike bidirectional variants, this module is limited to one data flow direction, which reduces the potential for errors.

## Conclusion
The `ADI_TO_AL` module offers a clean, streamlined solution for converting DINT to LWORD using unidirectional adapters. It can be easily integrated into existing 4diac projects, requires no custom state modeling, and benefits from the reusability of the internal standard conversion module. This makes it ideal for all applications where fast and reliable data conversion between different adapter types is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
