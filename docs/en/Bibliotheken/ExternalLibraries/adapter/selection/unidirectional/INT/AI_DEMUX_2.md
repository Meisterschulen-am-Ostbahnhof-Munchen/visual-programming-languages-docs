# AI_DEMUX_2

![AI_DEMUX_2](./AI_DEMUX_2.svg)

* * * * * * * * * *
## Introduction
The function block **AI_DEMUX_2** is a generic demultiplexer for unidirectional analog input (AI) adapters. It distributes an AI value arriving via socket **IN** to either one of the two output adapters **OUT1** or **OUT2**, based on an index **K** passed at event input **REQ**. The block is implemented as a generic FB (`GEN_AI_DEMUX`), thus enabling flexible adaptation to different AI data types.

## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K (connected to data input **K**) |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of index selection (after successful forwarding) |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index for selecting output (1 or 2) |

### **Data Outputs**

No direct data outputs – data is forwarded via downstream adapters.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Socket | IN | Adapter `adapter::types::unidirectional::AI` | Input value to be demultiplexed |

| Plug | OUT1 | Adapter `adapter::types::unidirectional::AI` | First output (index 1) |

| Plug | OUT2 | Adapter `adapter::types::unidirectional::AI` | Second output (index 2) |

## Functionality
1. The function block waits for an event at the **REQ** input.

2. Simultaneously with the event, the **K** index is evaluated.

- **K = 1**: The current value of the socket adapter **IN** is forwarded to the **OUT1** plug.

- **K = 2**: The value is forwarded to the **OUT2** plug.

- For other values of **K**, the behavior remains undefined (no selection).

3. After successful forwarding, the **CNF** event is output.


The internal logic is event-driven and purely combinatorial – no intermediate states are stored.

## Technical Features

- **Generic Type**: The function block (FB) is assigned the attribute `GenericClassName = 'GEN_AI_DEMUX'` and can be instantiated for various implementations of the AI adapter.

- **Type Check**: The adapter type (`adapter::types::unidirectional::AI`) must be supported by the sources and sinks used. Compatibility is checked during development.

- **Copyright**: This function block is subject to the Eclipse Public License 2.0 (EPL-2.0) and was originally developed by HR Agrartechnik GmbH.

## State Overview
The FB does not have explicit states in the sense of a state machine. Processing is event-driven and is entirely determined by the current combination of **REQ** and **K**.


## Application Scenarios

- **Multiple Sensors on One Bus**: A single AI value (e.g., from a transmitter) should be switched to two different control paths depending on the operating mode.

- **Redundancy Switching**: Selection between two different signal sources (e.g., primary and secondary sensor) that arrive via the same socket.

- **Configurable Signal Distribution**: In a machine controller, an index can be used to select between two outputs, e.g., for heating or cooling.

## Comparison with Similar Function Blocks

- **AI_DEMUX_1**: A simpler demultiplexer with only one output – this function block serves more as a passthrough (MUX) than a DEMUX.

- **AI_SWITCH**: An event-level switch that toggles between two event paths but does not pass any adapter data.

- **Demultiplexers with more than two outputs**: These could be implemented by extending the index range and adding plugs, but are not available as predefined function blocks.

Compared to a software-based demultiplexer (e.g., in IEC 61499 with multiple SEND events), **AI_DEMUX_2** is characterized by its tight coupling to the AI adapter type and its clean socket/plug separation.

## Conclusion
The **AI_DEMUX_2** is a specialized function block for the directed distribution of analog adapter signals. Its generic nature and clear interface make it a useful tool in modular automation projects, especially for signal switching or distribution to two parallel paths. The use of adapters ensures data integrity, and the simple index control allows for flexible integration into higher-level control logic.