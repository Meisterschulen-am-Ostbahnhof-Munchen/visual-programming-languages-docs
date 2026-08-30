# ADI_TO_ALR

![ADI_TO_ALR](./ADI_TO_ALR.svg)

* * * * * * * * * *
## Introduction

The function block **ADI_TO_ALR** is a composite function block (FB) that converts an ADI adapter (data type DINT) into an ALR adapter (data type LREAL). It serves as a unidirectional converter between two standardized adapter interfaces and enables the seamless integration of integer values into systems that require floating-point numbers.
## Interface Structure

### **Event Inputs**

- No dedicated event inputs are available.

Event forwarding is handled via the **ADI_IN** adapter (see Adapter section).

### **Event Outputs**

- No dedicated event outputs are available.

The event is output via the **ALR_OUT** adapter (see Adapter section).

### **Data Inputs**

- No dedicated data inputs are available.

The value to be converted is provided via the **ADI_IN** adapter (see Adapter section).

### **Data Outputs**

- No dedicated data outputs are available.

The converted value is output via the **ALR_OUT** adapter (see Adapter section).

#### **Adapters**

| Name | Type | Direction | Description |
|-------------|--------------------------------------------|----------|------------------------------------|
| **ADI_IN** | `adapter::types::unidirectional::ADI` | Socket | Input: DINT value and event |
| **ALR_OUT** | `adapter::types::unidirectional::ALR` | Plug | Output: LREAL Value and Event |

*Note:* The adapters each imply an event and a data signal (`E1` and `D1`).

## Functionality

The module performs direct internal routing:

- **Event:** The incoming event `ADI_IN.E1` is transmitted to the output `ALR_OUT.E1` without delay.
- **Data:** The integer value `ADI_IN.D1` (data type DINT) is converted to the LREAL data type without scaling or conversion and output as `ALR_OUT.D1`. Type conversion is performed implicitly by the runtime environment of the IEC 61499 system.

No further processing (filtering, limiting, delaying) takes place.

## Technical Features

- **Composite Block:** The conversion is implemented via a simple wire-through in the FB network – no state machine, no proprietary algorithms.
- **Implicit Type Conversion:** DINT → LREAL is a lossless conversion (LREAL offers 64-bit accuracy).
- **Unidirectional:** Data flows exclusively from the socket to the plug.
- **Reusability:** Encapsulated as an adapter converter, the block can be used in any system that relies on the corresponding adapter interfaces.

## State Overview

The block has **no state machine**. It is purely combinatorial (event-driven) and executes the pass-through immediately upon receiving an event.

## Application Scenarios

- **Counter Values as Floating-Point Numbers:** An integer counter (e.g., quantities, pulses) is to be processed as an LREAL value in a controller.
- **Interface Adaptation:** System components that already work with ADI adapters can be seamlessly connected to components that expect ALR adapters.
- **Prototypical Development:** Simple conversion without additional logic to quickly link different adapter protocols.

## Comparison with Similar Function Blocks

| Function Block | Type Conversion | Event Behavior |
|------------------------|----------------------|-----------------------------------------------------|
| **ADI_TO_ALR** | DINT → LREAL | Direct Pass-Through without Delay |
| `INT_TO_REAL` (4diac) | INT → REAL | Standalone function block with its own event interface |
| Individual converters | Any number of | Often with state machines or parameterization |

This function block is characterized by its **simple, adapter-oriented structure**, which enables direct coupling in adapter networks without having to define separate data and event channels.

## Conclusion

**ADI_TO_ALR** is a minimal yet useful converter for the unidirectional transfer of DINT values to the LREAL format. It is robust, fast, and requires no configuration. Thanks to its composite structure, it can be easily integrated into existing applications based on adapter interfaces.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
