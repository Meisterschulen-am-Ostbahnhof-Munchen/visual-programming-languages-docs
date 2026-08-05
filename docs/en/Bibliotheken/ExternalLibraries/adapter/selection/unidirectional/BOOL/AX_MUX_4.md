# AX_MUX_4
![AX_MUX_4](./AX_MUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **AX_MUX_4** is a generic multiplexer for adapters of type `adapter::types::unidirectional::AX`. It allows one of four adapter inputs (IN1 … IN4) to be switched to an output (OUT). The active input is selected via the index **K**, which is evaluated upon an event at the **REQ** input.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-------|------------------------------------|

| REQ | Event | Triggers the switch to the input defined by K. |

### **Event Outputs**

| Name | Type | Description |

|------|-------|-------------------------------------------------|

| CNF | Event | Confirmation that the switchover has occurred. |

### **Data Inputs**

| Name | Type | Description |

|------|------|----------------------------------|

| K | UINT | Index of the desired input (0 … 3). |

### **Data Outputs**
None.

### **Adapters**

| Type | Direction | Name | Description |

|------------------------------------------|----------|------|-----------------------------------------------------------------------------|

| `adapter::types::unidirectional::AX` | Plug | OUT | Output: provides the data of the input selected by K. |

| `adapter::types::unidirectional::AX` | Socket | IN1 | First input (K = 0). |

| `adapter::types::unidirectional::AX` | Socket | IN2 | Second input (K = 1). |

| `adapter::types::unidirectional::AX` | Socket | IN3 | Third input (K = 2). |

| `adapter::types::unidirectional::AX` | Socket | IN4 | Fourth input (K = 3). |

## Functionality
The function block waits for an event at the **REQ** input. Upon arrival, the value of the data input **K** (0 … 3) is evaluated. The corresponding socket adapter (**IN1** for K=0, **IN2** for K=1, **IN3** for K=2, **IN4** for K=3) is connected to the plug adapter **OUT**. The **CNF** event is then output to signal successful completion.

The switching occurs instantly – there are no internal states or delays. The function block operates purely event-driven.

## Technical Features
- **Generic Type:** The function block is designed as a generic function block (`GEN_AX_MUX`). It can therefore be reused in various contexts, as long as the adapters used correspond to the `AX` type.
- **License:** The function block is licensed under the **Eclipse Public License 2.0** (EPL-2.0). Copyright © 2026 HR Agrartechnik GmbH.
- **Type Hash:** A type hash (`TypeHash`) is used for identification, which is automatically calculated during integration into the 4diac IDE.

## State Overview
The **AX_MUX_4** has no states of its own. The switching occurs causally with each **REQ** event. An internal state machine is not required.

## Application Scenarios
- **Signal Selection:** Selection of one of four analog or discrete AX signals, e.g., in controllers for agricultural machinery.
- **Mode Switching:** Switching between different sensor or actuator values connected via AX adapters.
- **Redundancy:** Switching to backup signals in case of a failure (e.g., IN1 primary, IN2 backup).

## Comparison with Similar Components
Unlike classic multiplexers that operate on simple data types (INT, BOOL, etc.), the **AX_MUX_4** operates at the **adapter level**. This enables the routing of complex, composite data structures defined by the `AX` adapter. Advantage: The interface remains clearly structured in the graphical 4diac environment without the need to manually connect individual data lines.

## Conclusion

The **AX_MUX_4** is a simple yet flexible multiplexer for AX adapters. It is suitable for all applications that require switching between multiple adapter sources at runtime. Due to its generic nature and clear event handling, it can be integrated into many automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]