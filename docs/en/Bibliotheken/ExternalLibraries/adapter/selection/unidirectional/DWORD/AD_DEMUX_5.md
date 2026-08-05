# AD_DEMUX_5
![AD_DEMUX_5](./AD_DEMUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AD_DEMUX_5** is a generic demultiplexer for adapter connections. It distributes an incoming unidirectional adapter data stream to one of five output channels, controlled by an index value. This block is used for dynamically switching signals in distributed automation systems and increases the flexibility in connecting communication adapters.
## Interface Structure
### **Event Inputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| REQ | Event | Sets the index K and triggers the demultiplexer action |

### **Event Outputs**

| Event | Data Type | Comment |

|----------|----------|-----------|

| CNF | Event | Confirmation that index K has been adopted and the connection activated |

### **Data Inputs**

| Variable | Data Type | Comment |

|----------|----------|-----------|

| K | UINT | Target index (range 1..5) for selecting the output adapter |

### **Data Outputs**
*None* – data is passed via the adapter interfaces.

### **Adapter**

| Direction | Identifier | Type | Comment |

|----------|------------|----------------------------|------------------------------------|

| Socket | IN | adapter::types::unidirectional::AD | Input adapter (signal to be distributed) |

| Plug | OUT1 | adapter::types::unidirectional::AD | Output 1 |

| Plug | OUT2 | adapter::types::unidirectional::AD | Output 2 |

| Plug | OUT3 | adapter::types::unidirectional::AD | Output 3 |

| Plug | OUT4 | adapter::types::unidirectional::AD | Output 4 |

| Plug | OUT5 | adapter::types::unidirectional::AD | Output 5 |

## Functionality
The module expects an index **K** (1-based) at the data input. When the **REQ** event is received, the demultiplexer copies the entire data stream of the adapter socket **IN** to the output plug (**OUT1** to **OUT5**) determined by **K**. After a successful switchover, the confirmation event **CNF** is sent.

If **K** returns a value outside the valid range (e.g., 0 or >5), the **CNF** event is not triggered, and no action is taken (error handling is handled by the higher-level application).

The function block is **stateless** with respect to a previous connection – each REQ call overwrites the previous assignment.

## Technical Features
- **Generic Type:** The function block is implemented as a generic FB (ClassName `'GEN_AD_DEMUX'`) and can be reused in different adapter contexts.
- **Unidirectional Adapters:** Both the input and output adapters are of type `unidirectional::AD`, meaning that data flow is only in one direction (from the socket to the selected plug).
- **Easy Extensibility:** The generic definition allows the number of outputs to be adjusted, provided the interface definition is extended accordingly.
- **No Data Buffering:** Switching occurs without intermediate storage – delays only arise from event processing.

## State Overview
The function block has a minimalist flow control – it implicitly consists of two states:

1. **IDLE** – Waiting for the **REQ** event.

- Upon receipt of REQ, the **K** index is evaluated.

2. **ACTIVE** – Forwarding the adapter current to the selected output and sending **CNF**.

- Then returning to the IDLE state.

A state machine is not explicitly defined in the XML, but corresponds to the typical behavior of an event-driven service block.

## Application Scenarios
- **Dynamic Signal Distribution:** In production plants where a sensor value (e.g., analog measurement value) must be forwarded to different control units depending on the operating mode.
- **Multiplexing in Communication Networks:** Switching adapter connections in systems with multiple peripheral devices (e.g., bus couplers, I/O modules).
- **Test and Simulation Environments:** Easy redirection of data streams between different logical units for troubleshooting.

## Comparison with Similar Function Blocks

| Function Block | Features |

|------------------------|----------------|

| **AD_DEMUX_5** | Adapter-based, unidirectional, 5 outputs, generic |

| **E_DEMUX** (Standard) | Distributes events to one of several outputs – no adapter data forwarding |

| **F_DEMUX** (Data) | Distributes data values across multiple OUT ports via INDEX – works with elementary data types |

**Adapter-SELECT** | Similar function, but often with bidirectional adapters and multiple sockets |

The **AD_DEMUX_5** stands out due to its purely adapter-based interface, which enables loose coupling and flexible type adaptation via generic adapter definitions.

## Conclusion
The **AD_DEMUX_5** is a compact and efficient function block for adapter demultiplexing. It allows the dynamic selection of one of five output channels and is particularly suitable for systems that rely on unidirectional adapter connections. Its generic design allows it to be reused in various automation environments without modifying its internal logic. The block simplifies the implementation of switching logic at the adapter level and contributes to a clearer, modular system architecture.