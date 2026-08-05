# AD_MUX_2
![AD_MUX_2](./AD_MUX_2.svg)
* * * * * * * * * *
## Introduction
The function block **AD_MUX_2** implements a generic multiplexer for adapter interfaces of type `adapter::types::unidirectional::AD`. It selects between two input adapters (IN1, IN2) based on an integer index K and forwards the selected adapter signal to the output adapter OUT. The selection is initiated by an event pulse at the REQ input; after successful switching, the block acknowledges this with an event at the CNF output.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (0 = IN1, 1 = IN2) |

### **Data Outputs**

No dedicated data outputs. Output is provided via the adapter plug OUT.

### **Adapter**

| Type | Name | Type | Comment |

|----------|------|------------------------------------------|------------------------------------|

| Plug | OUT | adapter::types::unidirectional::AD | Output: contains IN1 for K=0, IN2 for K=1 |

Socket | IN1 | adapter::types::unidirectional::AD | First Input |

Socket | IN2 | adapter::types::unidirectional::AD | Second Input |

## Functionality

The function block operates according to a simple selection principle:

1. An event at the **REQ** input activates the evaluation of the data input **K**.

2. The value of K determines which of the two adapter sockets is connected to the adapter plug **OUT**:

- **K = 0** → OUT receives the data/signals from IN1.
- **K = 1** → OUT receives the data/signals from IN2.

3. After the switchover, an acknowledgment event is output at the **CNF** output.

The function block itself does not contain an internal state machine; it operates strictly event-driven.

## Technical Features
- **Generic Function Block (FB)**: The function block is declared as a generic function block. The adapter types are identified by the attributes `GenericClassName` and `TypeHash`, enabling reuse with different but structurally identical adapter definitions.
- **Adapter-Based**: Input and output are handled exclusively via adapter interfaces. This allows complex data structures or signal bundles to be efficiently passed on without the need to declare individual variables.
- **Event-Driven Selection**: Switching occurs only upon an explicit REQ event; changes to K without an event have no immediate effect.

## State Overview

The function block does not have a programmed execution state. It can be considered an **event-driven transmitter**:

- **Idle state**: No event is pending, OUT is set to the last selected adapter.
- **Selection phase**: After REQ, K is read and the corresponding adapter is switched.
- **Acknowledgement phase**: CNF is output, after which the module returns to idle state.

## Application scenarios
- **Switching between two sensors/actuators**: When two different devices (e.g., different transducers) are to be connected to a controller via the same communication adapter.
- **Redundancy switching**: Switching between the primary and secondary signal paths, controlled by an error or control index.
- **Test/normal operation**: Selection between a normal operating adapter and a test/simulation adapter.

## Comparison with Similar Components
- **MUX_2 (Standard Data Type Multiplexer)**: Unlike a classic multiplexer that selects elementary data types (e.g., INT, BOOL), AD_MUX_2 operates at the adapter level. Its advantage lies in the bundling of multiple signals and the typed interface.
- **AD_MUX_N (N-Way Multiplexer)**: An extended component with more than two inputs (e.g., AD_MUX_4) would require multiple sockets and a larger index range. AD_MUX_2 represents the simplest form.
- **Adapter Selector with Priority**: Alternatively, a component with priority logic (e.g., "only valid signal wins") could be implemented; AD_MUX_2, on the other hand, follows a strict index logic.

## Conclusion

The **AD_MUX_2** is a compact, generic function block for adapter selection in 4diac environments. Its clear event interface and adapter-based operation make it ideal for applications where signal paths need to be switched flexibly. Thanks to its generic declaration, it can be easily integrated into various projects or adapted to specific adapter types.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]