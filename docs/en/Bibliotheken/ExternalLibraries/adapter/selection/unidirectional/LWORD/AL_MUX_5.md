# AL_MUX_5
![AL_MUX_5](./AL_MUX_5.svg)

* * * * * * * * * *
## Introduction
The **AL_MUX_5** is a generic multiplexer function block that allows one of five analog or logic adapter inputs (IN1 to IN5) to be switched to a common output (OUT). The active channel is selected via the index parameter K. The block is designed for use in industrial control systems and is based on the IEC 61499-2 standard.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|--------|-------------------------------|

| `REQ` | Event | Set Index K – takes the current value of K and switches the corresponding input. |

### **Event Outputs**

| Name | Type | Comment |

|-------|--------|-----------------------------------------|

| `CNF` | Event | Confirmation of successful channel switching. |

### **Data Inputs**

| Name | Type | Comment |

|------|--------|---------------------------------------|

| `K` | UINT | Index of the input to be activated (0..4). |

### **Data Outputs**

No data outputs available. Signal transmission is handled via the adapter.

### **Adapter**

| Name | Type | Comment |

|-------|------------------------------------|---------------------------------------------------------------------------|

| `OUT` | `adapter::types::unidirectional::AL` (Plug) | Output – forwards the data of the input selected by K. |

| `IN1` | `adapter::types::unidirectional::AL` (Socket) | Input value 1 (becomes active when K=0). |

| `IN2` | `adapter::types::unidirectional::AL` (Socket) | Input value 2 (becomes active when K=1). |

| `IN3` | `adapter::types::unidirectional::AL` (Socket) | Input value 3 (becomes active when K=2). |

| `IN4` | `adapter::types::unidirectional::AL` (Socket) | Input value 4 (becomes active when K=3). |

| `IN5` | `adapter::types::unidirectional::AL` (Socket) | Input value 5 (becomes active when K=4). |

## Functionality

When an event arrives at the **REQ** input, the function block reads the current value of the data input **K** (data type UINT). The socket input corresponding to the index (IN1 for K=0, IN2 for K=1, …, IN5 for K=4) is then switched to the plug output **OUT**. The function block then outputs an acknowledgment event on **CNF**. If K is greater than 4, no input is activated (no defined response). The switching occurs asynchronously to the data flow and must be triggered by the REQ event.

```
## Technical Features

- **Generic Function Block**: The AL_MUX_5 is declared as a generic function block (GenericClassName `GEN_AL_MUX`). It can be reused and configured in different projects.
- **Adapter-Based Interface**: Both inputs and output use the unidirectional adapter type `AL`, which enables a standardized connection for analog or logic signals.
- **No State Machine**: The function block does not have an explicit ECC (Execution Control Chart). Functionality is implemented purely event-driven – each REQ operation leads directly to channel switching and acknowledgment.

## State Overview

The function block is stateless (combinatory). There is no internal state machine. Channel selection is strictly event-driven and without memory of past states.

## Application Scenarios
- **Signal Selection**: Selection of a sensor signal from multiple sources in a higher-level controller.
- **Data Routing**: Forwarding of different data streams to a common processing node.
- **Test and Diagnostic Systems**: Switching between different test signals to an analysis unit.
- **Redundancy Switching**: Taking over a substitute signal upon fault detection by changing the index K.

## Comparison with Similar Components

| Component | Inputs | Outputs | Selection Mechanism | Special Features |

---------------------|----------|----------|---------------------|---------------------------------|

| AL_MUX_5 | 5 | 1 | Index K (UINT) | Adapter-based interface |

| Standard MUX (e.g., SEL) | Variable | 1 | Boolean Select | Based on IEC 61131-3, often elementary |

FB_Alarm_MUX | 4 | 1 | Bitmasks/Selection | Specifically for Alarm Signals |

The AL_MUX_5 is characterized by its addressable index control (0 to 4) and the use of adapters, which enables flexible integration with other 4diac components.

## Conclusion

The **AL_MUX_5** is a compact, generic multiplexer for up to five input channels. It is particularly suitable for applications requiring event-driven switching of adapter signals (e.g., analog measured values). Its simple interface structure and lack of state logic make it easy to integrate and adapt into existing IEC 61499-2 projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
