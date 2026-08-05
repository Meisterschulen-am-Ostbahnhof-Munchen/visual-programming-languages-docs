# AIS_DEMUX_2
![AIS_DEMUX_2](./AIS_DEMUX_2.svg)

* * * * * * * * * *
## Introduction
The **AIS_DEMUX_2** function block is a generic AIS demultiplexer for the 4diac IDE. It allows an incoming AIS signal to be routed to one of two outputs, controlled by an index. The block is designed for use with the unidirectional AIS adapter and is used in agricultural technology.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Sets the selection index K and triggers the demultiplexing. The IN input is routed to the output determined by K. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirms successful processing of the REQ event. |

### **Data Inputs**

| Variable | Type | Description |

|----------|------|--------------------|

| K | UINT | Index for selecting the output (1 or 2). |

### **Data Outputs**

This function block has no data outputs. Output is exclusively via the adapter interfaces.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|----------------------------------|------------------------------------------------|

| Socket | IN | adapter::types::unidirectional::AIS | Input AIS signal that is demultiplexed. |

| Plug | OUT1 | adapter::types::unidirectional::AIS | First output for the AIS signal. |

| Plug | OUT2 | adapter::types::unidirectional::AIS | Second output for the AIS signal. |

## Functionality
This module operates as a 1-to-2 demultiplexer for AIS data streams. Upon the arrival of the **REQ** event, the value of the **K** index is evaluated:

- If **K** = 1**, the AIS signal present at socket **IN** is forwarded to plug **OUT1**.
- If **K** = 2**, it is forwarded to **OUT2**.
- For other values of **K**, no output is activated (the signal is discarded).

After the switching, the **CNF** event is sent. It is assumed that the AIS data on the outputs remains valid until the next **REQ**.

-
## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GEN_AIS_DEMUX`), allowing it to be parameterized in different contexts.
- **Unidirectional Adapters**: All AIS adapters are unidirectional, meaning data flows only from the socket to the plugs.
- **License**: The function block is licensed under the **Eclipse Public License 2.0**.
- **No Data Outputs**: Output is provided solely via the plug adapters, simplifying integration into adapter-based architectures.

## State Overview
The function block does not have an explicit state machine in its XML description. Its implicit behavior can be described as follows:

1. **Idle**: Waiting for a **REQ** event.

2. **Processing**: Upon receipt of **REQ**, the index K is read and the corresponding routing is set.

3. **Done**: **CNF** output and return to the idle state.

## Application Scenarios
- **Control of AIS Signals in Agricultural Machinery**: Distribution of a central AIS data stream to two different consumers (e.g., two actuators or sensor groups).
- **Testing and Simulation**: Use in simulation environments to selectively redirect the data flow between different components.
- **Redundancy**: Ability to route the AIS signal to a backup output if the primary receiver fails.

## Comparison with Similar Components
- **Standard Demultiplexers (e.g., `DEMUX_2`)**: These typically work with scalar data types and events. The `AIS_DEMUX_2` is specifically optimized for the AIS protocol and adapter-based communication.
- **Multiplexer (`AIS_MUX_2`)**: The multiplexer combines multiple AIS inputs into a single output; the demultiplexer performs the reverse function.
- **Advantages**: The use of adapters allows for loose coupling and easy reuse in various applications.

## Conclusion
The **AIS_DEMUX_2** is a specialized, generic function block for demultiplexing AIS signals. It offers a clear, event-driven interface with adapters and is particularly suitable for use in agricultural technology and other areas where unidirectional AIS data needs to be distributed. Its EPL 2.0 license makes it open and extensible.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
