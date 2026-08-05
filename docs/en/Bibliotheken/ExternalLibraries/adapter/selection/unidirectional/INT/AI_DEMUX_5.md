# AI_DEMUX_5
![AI_DEMUX_5](./AI_DEMUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AI_DEMUX_5** is a generic analog input demultiplexer for the 4diac IDE. It distributes an incoming AI (analog input) value via an adapter to one of five output adapters, controlled by an integer index K. The function block is implemented as a unidirectional adapter block and enables the flexible routing of analog signals in control applications.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K |

The event input **REQ** triggers the demultiplexing function. This event assigns index K and triggers the forwarding of the current input value to the corresponding output.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

The **CNF** event is triggered after successful distribution of the value and confirms the execution of the REQ event.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | index |

The **K** data input determines the target output (1..5) to which the value from the IN adapter is forwarded. Values outside this range are typically ignored or result in error handling (not specified).

### **Data Outputs**

There are no direct data outputs. Output is exclusively via the adapter interfaces.

### **Adapters**

| Role | Name | Type | Comment |

|-------|------|-----|-----------|

Socket | IN | adapter::types::unidirectional::AI | Input Value to demultiplex |

Plug | OUT1 | adapter::types::unidirectional::AI | – |

Plug | OUT2 | adapter::types::unidirectional::AI | – |

Plug | OUT3 | adapter::types::unidirectional::AI | – |

Plug | OUT4 | adapter::types::unidirectional::AI | – |

Plug | OUT5 | adapter::types::unidirectional::AI | – |

Plug | OUT5 | adapter::types::unidirectional::AI | – | The **IN** socket receives the analog value to be distributed. The five plugs **OUT1** to **OUT5** represent the possible destination outputs through which the value is output.

## Functionality

With each REQ event, the current value of index K is read. The analog value present at the IN adapter is then passed unchanged to the OUT plug designated by K (e.g., K=1 → OUT1, K=2 → OUT2, etc.). The remaining four outputs either remain unchanged or are set to a defined default state (e.g., zero) – this depends on the specific implementation of the generic function block. After the transmission is complete, the CNF event is triggered. The function is purely combinatorial; there is no internal memory or state.

```
## Technical Features

- **Generic Block:** The function block is declared as a generic type (`eclipse4diac::core::GenericClassName = 'GEN_AI_DEMUX'`), which allows for easy parameterization and reuse in different projects.
- **Unidirectional Adapters:** The IN and OUT1..OUT5 interfaces are implemented as unidirectional AI adapters, meaning they only allow data flow in one direction (from the socket to the plug). This simplifies wiring in hierarchical structures.
- **No Data Outputs:** The function block does not have traditional data outputs and uses adapters exclusively for value transfer, which promotes modular encapsulation of the analog signals.

## State Overview

The function block does not have an internal state machine. The demultiplex function is executed directly with each REQ event. There are no dependencies on previous calls, except that the index K must be valid at the time of the REQ.

**No Data Outputs:**
## Application Scenarios

- **Signal Routing in Automation:** An analog sensor value (e.g., temperature, pressure) is to be forwarded to various other function blocks for processing or logging, depending on a selection (e.g., product type).
- **Multi-Channel Measurement Systems:** Distribution of an incoming AI value to different paths (e.g., control, monitoring, archiving) without multiple wiring.
- **Test and Simulation Environments:** Switching between different simulation data sources by changing the index K.

## Comparison with Similar Components

A **MUX** (multiplexer) performs the reverse function – multiple inputs are switched to one output. The **AI_DEMUX_5** is a demultiplexer with five fixed outputs. Unlike a generic, configurable DEMUX (e.g., with a variable number of outputs), the number here is fixed at five, providing a clear interface for typical applications with up to five destinations. Compared to a manual, cascaded setup with multiple 1-to-2 demultiplexers, this function block reduces complexity and improves clarity.

## Conclusion

The **AI_DEMUX_5** is a compact, generic demultiplexer for analog input signals in the 4diac IDE. With its simple event control, Index K input, and adapter-based interface, it is ideally suited for routing AI values in modular control applications. The fixed number of five outputs covers many practical requirements, while the generic implementation allows for flexible reuse.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
