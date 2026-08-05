# AUDI_SPLIT_8
![AUDI_SPLIT_8](./AUDI_SPLIT_8.svg)
* * * * * * * * * *
## Introduction
The function block **AUDI_SPLIT_8** is used to distribute an incoming unidirectional **AUDI** adapter signal to eight parallel outputs.
It is implemented as a generic function block (FB) and allows for the simple forwarding of an adapter signal to up to eight receivers.
## Interface Structure
### **Event Inputs**
None.

### **Event Outputs**
None.

### **Data Inputs**
None.

### **Data Outputs**
None.

### **Adapter**

| Type | Direction | Name | Description |

|-----|----------|------|--------------|

adapter::types::unidirectional::AUDI` | Socket (Input) | `IN` | Input adapter that receives the signal to be distributed. |

adapter::types::unidirectional::AUDI` | Plug (Output) | `OUT1` .. `OUT8` | Eight output adapters, each providing the identical signal of the input. |

## Functionality
The module forwards the **AUDI** adapter signal present at socket `IN` unchanged to all eight plugs (`OUT1` to `OUT8`).

No processing, filtering, or buffering takes place – distribution is completely passive at the adapter level.

By using a generic type (see Technical Specifications), the function block can be flexibly used for various specific AUDI adapter implementations.

## Technical Specifications
- **Generic Function Block**: The function block is declared as a generic type (`eclipse4diac::core::GenericClassName = 'GEN_AUDI_SPLIT'`).

This allows reuse for any AUDI adapter specialization without having to modify the function block itself.

- **No State Logic**: Since only adapters are used, the function block has neither events nor its own state machine.
- **Space Saving**: By combining eight outputs into a single function block, the network diagram becomes clearer than when using several simple split blocks.

## State Overview

The function block has no internal state machine (no ECC).

The functionality is purely combinational: The signal at the input is permanently passed through to all outputs.

## Application Scenarios
- **Signal broadcast** in control applications where a single AUDI adapter signal needs to be distributed to multiple independent receiver modules (e.g., smart sensors, actuators, or bus couplers).
- **Expanding the number of participants** in an existing AUDI wiring system without affecting the original signal.
- **Structured automation solutions** in agricultural machinery where adapters according to IEC 61499 are used for communication between components (e.g., in HR Agrartechnik GmbH systems).

## Comparison with Similar Modules
- **Simple Split FB (e.g., SPLIT_2)**: Distributes a signal to two outputs – AUDI_SPLIT_8 offers eight outputs in a single module.
- **Data Distribution FB**: Some libraries provide generic distributors for data ports; this FB is specifically optimized for the AUDI adapter type and requires no additional data structure configuration.
- **Manual Parallel Connection**: Multiple AUDI socket-to-plug connections could achieve the same result, but are less organized and more prone to errors.

## Conclusion

**AUDI_SPLIT_8** is a compact, generic, specialized module for signal distribution at the adapter level.

It reduces modeling effort, improves the readability of control programs, and, due to its generic nature, can be flexibly deployed in various AUDI-based environments.

For applications requiring a 1:8 split of a unidirectional audio adapter, it represents an ideal and clean solution.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 Total resistance in series & parallel circuits on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)

