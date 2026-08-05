# AUDI_TO_ALR
![AUDI_TO_ALR](./AUDI_TO_ALR.svg)
* * * * * * * * * *
## Introduction
The **AUDI_TO_ALR** function block is a composite module that converts a unidirectional adapter of type **AUDI** (data type `UDINT`) into an adapter of type **ALR** (data type `LREAL`). It serves as a simple link between two different adapter interfaces, thus enabling the integration of components based on different data formats.
## Interface Structure

### **Event Inputs**

| Name | Comment |

|------|-----------|

| `AUDI_IN.E1` | Event input of the AUDI adapter (passed through to the ALR output) |

### **Event Outputs**

| Name | Comment |

|------|-----------|

| `ALR_OUT.E1` | Event output of the ALR adapter (inherited from the AUDI input) |

### **Data Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `AUDI_IN.D1` | `UDINT` | Data input of the AUDI adapter (passed directly as LREAL) |

### **Data Outputs**

| Name | Data Type | Comment |

|------|----------|-----------|
| `ALR_OUT.D1` | `LREAL` | Data output of the ALR adapter (value from the AUDI input, type-converted) |

### **Adapter**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Socket (Input) | `AUDI_IN` | `adapter::types::unidirectional::AUDI` | Receives the UDINT data and the associated event |

| Plug (Output) | `ALR_OUT` | `adapter::types::unidirectional::ALR` | Provides the converted LREAL data and the event |

## Functionality

The function block forwards the incoming event `E1` from socket `AUDI_IN` directly to plug `ALR_OUT`. Simultaneously, the data value `D1` (type `UDINT`) is transferred unchanged to the output data channel `D1` (type `LREAL`). The actual type conversion from `UDINT` to `LREAL` takes place within the adapter interfaces used; the composite block itself does not perform any arithmetic or logical transformation, but merely serves as a wiring aid.

...
## Technical Features

- **Pure Adapter Passthrough:** The module contains no logic or state machines of its own – it simply connects the corresponding channels of the two adapters.
- **Unidirectional Communication:** Both the AUDI and ALR adapters support only one direction of data flow, which simplifies their use in simple sensor/actuator interfaces or when coupling different protocols.
- **No Type Conversion in the Module:** The conversion from `UDINT` to `LREAL` is handled by the adapter infrastructure. The developer must ensure that the adapter implementations used provide the necessary conversion.

## State Overview

As a composite module, `AUDI_TO_ALR` does not have its own state machine. Its behavior is purely combinatorial: An incoming event is immediately passed on to the output – without delay or condition.

## Application Scenarios
- **Integration of UDINT-based sensors** (e.g., rotary encoders with 32-bit counters) into an LREAL-processing control system.
- **Adapter bridge** between different libraries or components based on different data types but using uniform adapter interfaces.
- **Prototype development** and rapid wiring of adapters without having to create separate conversion logic.

## Comparison with Similar Function Blocks

In the 4diac ecosystem, simple conversion function blocks such as `INT_TO_REAL` or `UDINT_TO_LREAL` exist, which are usually implemented as Basic or Service FBs. The present Composite FB differs in that it does not convert the data value itself, but rather connects two complete adapters. It is therefore specifically designed for environments that rely on adapter interfaces and not for simple data flow conversion.

## Conclusion

AUDI_TO_ALR` is a minimal yet useful composite block for connecting two unidirectional adapters with different data types. It reduces wiring complexity and makes the type conversion explicitly visible. This block should always be used when a clean separation between adapter types and simple event and data transmission are required.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
