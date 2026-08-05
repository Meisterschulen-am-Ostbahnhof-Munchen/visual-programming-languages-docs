# AS_MUX_3
![AS_MUX_3](./AS_MUX_3.svg)

* * * * * * * * * *
## Introduction
The **AS_MUX_3** is a generic multiplexer IC according to IEC 61499-2. It allows one of three input signals to be forwarded to a common output via a unidirectional **AS** adapter. The active input is selected using an integer index `K` (UINT). The IC is particularly suitable for flexible switching between different signal sources in automation systems, such as those found in agricultural technology.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-------|----------------------------------|

| REQ | Event | Sets the index K and triggers the forwarding |

### **Event Outputs**

| Name | Type | Comment |

|------|-------|---------------------------------------------------|

| CNF | Event | Confirms successful acquisition of index K |

### **Data Inputs**

| Name | Type | Comment |

|------|------|-----------------------------|

| K | UINT | Selection index (0, 1, or 2) |

### **Data Outputs**

No direct data outputs are available. Output is exclusively via the **OUT** adapter.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----------------------------------|----------------------------------------|

| Plug | OUT | adapter::types::unidirectional::AS | Output for the selected input |

Socket | IN1 | adapter::types::unidirectional::AS | First input (K=0) |

Socket | IN2 | adapter::types::unidirectional::AS | Second input (K=1) |

Socket | IN3 | adapter::types::unidirectional::AS | Third input (K=2) |

## Functionality

This function block operates in an event-driven manner. Upon a **REQ** event, the current value of the data input `K` (0, 1, or 2) is read. The corresponding adapter connection from the socket (`IN1`, `IN2`, or `IN3`) is then switched to the **OUT** plug, and the incoming signals are passed through. After a successful switchover, the **CNF** event is output.

- If `K = 0` → OUT receives the signals from IN1.
- If `K = 1` → OUT receives the signals from IN2.
- If `K = 2` → OUT receives the signals from IN3.
- Values outside the range 0-2 are undefined and result in undefined behavior.

## Technical Features
- **Adapter-based**: The function block uses the unidirectional `adapter::types::unidirectional::AS` adapter. This allows for flexible coupling with other function blocks of the same adapter type without fixed data paths.
- **Generic design**: The **AS_MUX_3** is declared as a generic function block (attribute `eclipse4diac::core::GenericClassName = 'GEN_AS_MUX'`). This allows it to be customized in various configurations (e.g., different numbers of inputs) using the IDE.
- **Easy Extensibility**: The concept can be extended to any number of inputs (e.g., AS_MUX_4, AS_MUX_5, etc.) without changing its fundamental functionality.

## State Overview

The function block does not have an explicit state machine in the XML. Its behavior can be described as an **event-driven function block** with the following implicit states:

1. **Waiting**: No REQ event is pending → Output OUT remains unchanged.

2. **Selection**: REQ is received → Index K is checked, and the corresponding adapter socket is switched to the plug.

3. **Acknowledgement**: After successful switching, CNF is sent, followed by a return to the waiting state.

## Application Scenarios
- **Signal Switching** in Field Control: Selection between different sensors (e.g., temperature, humidity, pressure) for control purposes.
- **Data Stream Multiplexing** in a higher-level control logic where multiple sources need to be queried sequentially.
- **Test and Diagnostic Systems**: Switching between normal operation and test signals.

## Comparison with Similar Function Blocks

| Function Block | Inputs | Output | Special Feature |

|-------------|----------|------------------------|------------------------------------------|

| AS_MUX_2 | 2 | 1 (unidirectional) | Simpler Multiplexer |

| **AS_MUX_3**| 3 | 1 | This Function Block |

| AS_MUX_4 | 4 | 1 | Extended Selection Options |

| SEL (Standard 61499) | 2 Data Inputs | 1 Data Output | Operates on simple data types, not adapters |

The **AS_MUX_3** distinguishes itself from classic SEL devices, which only process simple variables, through its adapter interface. Adapters enable the exchange of complex data types and provide a type-safe connection.

## Conclusion

The **AS_MUX_3** is a compact and efficient multiplexer device for three unidirectional **AS** signals. Its clear event control and generic design make it a valuable tool in IEC 61499-based automation solutions, especially in agricultural technology, where flexible signal switching is required. By foregoing data outputs in favor of an adapter plug, a clean separation of data and event paths is ensured.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
