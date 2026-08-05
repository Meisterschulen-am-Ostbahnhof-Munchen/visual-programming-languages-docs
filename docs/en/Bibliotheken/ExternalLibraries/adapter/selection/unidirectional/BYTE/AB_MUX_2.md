# AB_MUX_2
---
## Introduction
![AB_MUX_2](./AB_MUX_2.svg)
The function block **AB_MUX_2** is a generic multiplexer that selects two values (IN1, IN2) present at adapter interfaces via an index `K` and forwards them to the output `OUT`. The block operates in an event-driven manner and is suitable for use in industrial control applications with standardized adapters of type `AB`.
## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Starts the switching process: The index `K` is evaluated, and the corresponding input signal is passed to `OUT`. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirms successful execution of the switching process. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| `K` | UINT | Selection index: 0 → IN1, 1 → IN2 (other values are undefined or remain unchanged). |

### **Data Outputs**

No direct data outputs – output is exclusively via the `OUT` adapter.

### **Adapters**

| Type | Name | Description |

|-----|------|--------------|

| **Plug** | `OUT` | Adapter type `adapter::types::unidirectional::AB` – provides the selected signal. |

| **Socket** | `IN1` | Adapter type `adapter::types::unidirectional::AB` – first input source. |

| **Socket** | `IN2` | Adapter type `adapter::types::unidirectional::AB` – second input source. |

## Functionality

1. The module waits in idle mode for a `REQ` event.

2. Upon arrival of `REQ`, the value of the data input `K` is read.

- If `K = 0` is present, the signal from adapter `IN1` is switched to output adapter `OUT`.
- If `K = 1` is present, the signal from adapter `IN2` is switched to output adapter `OUT`.

3. After a successful switchover, the event `CNF` is output.

Values are transmitted via standardized AB adapters, making the function block usable regardless of specific data formats.

## Technical Features
- **Generic Structure**: The function block is declared as a generic FB (`GEN_AB_MUX`) and can be reused in different contexts.
- **Adapter-Based**: Inputs and outputs use the adapter type `unidirectional::AB`, which provides a uniform interface for value-based connections.
- **No State Machine**: The function block does not have an explicit ECC state machine – the simple logic is executed directly upon receiving `REQ`.

## State Overview

Since the function block does not define a state machine (ECC is missing), only the implicit **Idle** state exists. For each `REQ`, the switchover is performed immediately, and `CNF` is returned. No delayed or multi-stage processes can be observed.

## Application Scenarios
- **Signal Switching** in field devices: Selection between two sensors (e.g., temperature, pressure) under index control.
- **Redundancy Switching**: Switching between primary and secondary measured values.
- **Operating Mode Selection**: Selection of different control parameters or commands depending on the operating mode.

## Comparison with Similar Function Blocks

| Function Block | Property |

|----------|-------------|

| **AB_MUX_2** | Adapter-based, two inputs, event-driven, generic. |

| Standard MUX function blocks (e.g., MUX2) | It typically works with direct data inputs (BOOL, INT) and has its own data outputs. |

**Advantage AB_MUX_2** | Uniform adapter interface, easy interchangeability of data source and sink. |

## Conclusion

The function block **AB_MUX_2** provides a flexible and standardized solution for selecting between two signal sources. The use of adapters facilitates integration into complex 4diac projects and ensures a clean separation of control logic and data flows. Thanks to its generic declaration, the block is reusable and suitable for a wide range of industrial applications.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]