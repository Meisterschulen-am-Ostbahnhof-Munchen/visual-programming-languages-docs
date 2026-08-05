# ATM_DEMUX_5

![ATM_DEMUX_5](./ATM_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The **ATM_DEMUX_5** is a generic demultiplexer IC for five output channels. It forwards data received via a unidirectional ATM adapter to one of the five outputs, which is selected by an index **K**. The IC thus implements a 1-to-N distribution (N=5) based on the ATM adapter type.

## Interface Structure

### **Event Inputs**

| Event | Description |

| :------- | :----------- |

| `REQ` | Sets the index **K** and triggers the forwarding. The index value is updated at the time of the event. |


### **Event Outputs**

| Event | Description |

| :------- | :----------- |

| `CNF` | Confirms successful forwarding to the selected output. |

### **Data Inputs**

| Date | Type | Description |

| :---- | :--- | :----------- |

| `K` | UINT | Index of the target output (value range 1…5). |

### **Data Outputs**

No dedicated data outputs; data is passed through the adapter outputs.

### **Adapters**

| Direction | Name | Type | Description |

| :------- | :--- | :--- | :----------- |

Socket (Input) | `IN` | `adapter::types::unidirectional::ATM` | Receives the data to be distributed. |

Plug (Output 1) | `OUT1` | `adapter::types::unidirectional::ATM` | First output channel. |

Plug (Output 2) | `OUT2` | `adapter::types::unidirectional::ATM` | Second output channel. |

Plug (Output 3) | `OUT3` | `adapter::types::unidirectional::ATM` | Third output channel. |

Plug (Output 4) | `OUT4` | `adapter::types::unidirectional::ATM` | Fourth output channel. |

| Plug (Output 5) | `OUT5` | `adapter::types::unidirectional::ATM` | Fifth output channel. |

## Functionality

1. The module waits for a `REQ` event.

2. At the time of the event, the current value of **K** is read.

3. The data present at adapter `IN` is passed on to the output adapter determined by **K** (`OUT1` … `OUT5`).

4. After successful forwarding, the event `CNF` is triggered.


Valid values for **K** are 1 to 5. For values outside this range or undefined indices (e.g., 0), the behavior may be undefined – in this case, the function block will not perform any action or send `CNF`. The maximum number of outputs is fixed at five.

## Technical Features

- **Generic Design**

The function block is declared as a generic demultiplexer (`GEN_ATM_DEMUX`). This allows for easy adjustment of the number of channels or the adapter type used by re-instantiating with different parameters.

- **Unidirectional ATM Adapters**

Both the input and output adapters are of type `adapter::types::unidirectional::ATM`. Communication is unidirectional (from input to output), which is sufficient for typical distribution tasks.


- **Index as UINT**

The index **K** is defined as an unsigned 16-bit value, resulting in 65,536 possible values, but only the first five (1…5) are assigned to an output. This allows for easy expansion if the number of channels is increased later.

## State Overview

The component does not have an explicit state machine. Its behavior is purely event-driven:

- **Idle State**: Waiting for `REQ`.

- **Processing State**: Upon arrival of `REQ`, the index is evaluated and the data is forwarded. Immediately afterward, `CNF` is sent. The component returns to the idle state.

There is no persistent memory or internal state.


## Application Scenarios

- **Distributing ATM data streams** in industrial communication networks where a data channel needs to be split across up to five target devices.

- **Routing in automation systems** – for example, to control multiple identical actuators via a common control channel.

- **Test bench and testing environments** where a signal needs to be applied sequentially to different measurement points.

## Comparison with Similar Components

| Component | Function |

| :------- | :------- |

| `ATM_MUX` | Multiplexer: selects one of several inputs and routes it to an output. |

| `ATM_DEMUX_5` | Demultiplexer: distributes one input to one of five outputs. |

| `ATM_DEMUX_X` | Variant with variable channel count (e.g., `ATM_DEMUX_8` for eight outputs). |

Unlike the multiplexer, the `ATM_DEMUX_5` implements the reverse direction – from a common input to multiple outputs. It is therefore suitable for star or bus topologies with one transmitter and multiple receivers.

## Conclusion

The **ATM_DEMUX_5** is a simple yet effective generic demultiplexer for unidirectional ATM adapters. With five output channels and event-driven selection via an index **K**, it covers many typical distribution tasks in automation technology. Its generic declaration allows it to be easily adapted to other adapter types or channel counts without changing the underlying functional logic.