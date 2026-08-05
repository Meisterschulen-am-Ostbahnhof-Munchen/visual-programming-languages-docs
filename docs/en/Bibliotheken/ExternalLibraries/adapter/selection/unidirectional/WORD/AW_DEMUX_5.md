# AW_DEMUX_5
![AW_DEMUX_5](./AW_DEMUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AW_DEMUX_5** is a generic demultiplexer for unidirectional AW adapters. It distributes the signal present at an input adapter to one of five output adapters, depending on a numerical index. This block is used when data from a source needs to be selectively routed to multiple sinks.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| REQ | Event | Set Index K |

The event input **REQ** triggers the demultiplex operation and uses the current value of the data input `K`.

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of Set Index K |

After a successful switchover, the **CNF** event is output.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (expected values 1-5) |

The input `K` determines which of the five output adapters is activated.

### **Data Outputs**

None.

### **Adapters**

**Plugs (Outputs):**

| Name | Type | Comment |

|------|-----|-----------|

| OUT1 | adapter::types::unidirectional::AW | Output 1 |

| OUT2 | adapter::types::unidirectional::AW | Output 2 |

| OUT3 | adapter::types::unidirectional::AW | Output 3 |

| OUT4 | adapter::types::unidirectional::AW | Output 4 |

| OUT5 | adapter::types::unidirectional::AW | Output 5 |

**Sockets (Input):**

| Name | Type | Comment |

|------|-----|-----------|

| IN | adapter::types::unidirectional::AW | Input signal for demultiplexing |

## Functionality

The function block operates according to the demultiplex principle:

1. The **IN** socket continuously receives data from a unidirectional AW adapter.

2. Upon a **REQ** event, the value of **K** is evaluated.

3. Depending on the index (1..5), the connection from the **IN** socket is switched to the corresponding **OUT**_n_ plug.

4. After switching, **CNF** is output.

The data connection remains open until a new REQ with a different index arrives. For invalid indices, no action is performed, or an undefined state occurs (depending on the implementation).

## Technical Features
- **Generic Type**: The function block is declared as a generic FB (`GEN_AW_DEMUX`), allowing it to be reused for different AW adapter configurations.
- **Unidirectional Adapter**: The adapters used are unidirectional, meaning data flows in only one direction (Socket → Plug).
- **Index Limits**: The index `K` is of type `UINT`; values from 1 to 5 are recommended. Values outside this range do not result in any defined behavior.
- **No Data Outputs**: The function block does not output any data itself but merely forwards the adapter connections.

## State Overview

The function block does not have an explicitly modeled state machine. Its internal behavior can be described by the following implicit state machine:

- **IDLE**: Waiting for a **REQ** event.
- **SELECT**: Upon **REQ**, the index `K` is evaluated, and the corresponding connection is established.
- **DONE**: After successful switching, **CNF** is sent, and the function block returns to the IDLE state.

## Application Scenarios
- **Signal Distribution**: A sensor signal (e.g., an adapter for an analog value) can be selectively sent to different control units.
- **Routing**: In a networked automation environment, a data stream can be selectively routed to five different downstream function blocks.
- **Test Environments**: Switching between different test paths without changing the wiring.

## Comparison with Similar Function Blocks
- **Standard Demultiplexers**: Conventional demultiplexers usually work with data lines and have separate output events. This function block uses adapters, which enables the encapsulation of complex data structures.
- **AW_SELECT**: An analog multiplexer that switches multiple inputs to one output. AW_DEMUX_5 is the inverse function.
- **MUX/DEMUX with Event Control**: Many demultiplexers have separate enable inputs; here, activation occurs via the **REQ** event, enabling synchronous processing.

## Conclusion

The **AW_DEMUX_5** is a specialized demultiplexer for unidirectional AW adapters in the 4diac IDE. Its use of adapters makes it particularly suitable for modular automation solutions where data streams need to be flexibly switched between components. Its simple interface (one event, one index, five outputs) makes it easy to use, while its generic nature allows for broad reuse.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]