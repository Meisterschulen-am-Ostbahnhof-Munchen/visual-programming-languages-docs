# AIWS_DEMUX_5

![AIWS_DEMUX_5](./AIWS_DEMUX_5.svg)

* * * * * * * * * *

## Introduction

The AIWS_DEMUX_5 function block is a generic demultiplexer for the **AIWS** data type. It distributes an incoming data stream, provided via a unidirectional adapter, to one of five possible output adapters. The target output is selected via an index `K`, which is evaluated upon an event at input `REQ`. Confirmation of successful routing is provided via the event output `CNF`.

## Interface Structure

### **Event Inputs**

| Event | Description |

| :--- | :--- |

| REQ | Starts the demultiplex operation. The current value of `K` determines which output the incoming data value is routed to. |

### **Event Outputs**

| Event | Description |

| :--- | :--- |

| CNF | Confirms that the demultiplex operation is complete and the data value has been sent to the selected output. |

### **Data Inputs**

| Name | Data Type | Description |

| :--- | :--- | :--- |

| K | UINT | Index of the desired output (range 1–5). |

### **Data Outputs**

No data outputs available.

### **Adapters**

| Direction | Name | Type | Description |

| :--- | :--- | :--- | :--- |

Socket (Input) | IN | adapter::types::unidirectional::AIWS | The incoming data value to be demultiplexed. |

| Plug (Output 1) | OUT1 | adapter::types::unidirectional::AIWS | Destination output 1 for the incoming data value (if `K = 1`). |

| Plug (Output 2) | OUT2 | adapter::types::unidirectional::AIWS | Destination output 2 (if `K = 2`). |

| Plug (Output 3) | OUT3 | adapter::types::unidirectional::AIWS | Destination output 3 (if `K = 3`). |

| Plug (Output 4) | OUT4 | adapter::types::unidirectional::AIWS | Destination output 4 (if `K = 4`). |

Plug (Output 5) | OUT5 | adapter::types::unidirectional::AIWS | Target output 5 (if `K = 5`). |

## Functionality

1. The function block waits for an event at input `REQ`.

2. Simultaneously, the incoming index `K` (1–5) is read.

3. The current value received via socket `IN` (adapter) is forwarded to plug `OUTx`, whose number corresponds to the value of `K`.

4. After successful forwarding, an event is output at output `CNF`.


5. If the value of `K` is outside the valid range (1–5), the event is handled inconsistently (no output is written, but `CNF` is still sent – this depends on the specific implementation).

The adapters used are unidirectional, meaning that data flows only from the socket to the plug. No feedback or acknowledgment occurs via the adapter.

## Technical Features

- **Generic Function Block**: The function block carries the attribute `GenericClassName` and can be used as a template in a generic context.

- **Adapter-Based Communication**: Instead of direct data ports, an adapter type (`unidirectional::AIWS`) is used, enabling flexible coupling with other function blocks of the same protocol.

- **No State Machine**: The action is event-driven and stateless. Output selection and routing are deterministic.

## State Overview

The function block does not have an explicit state machine defined in the ECC. The operation is performed **purely functionally**: With each `REQ` event, the index is evaluated and the data value is immediately sent to the corresponding output. After the `CNF` event, the function block remains ready for the next call.

## Application Scenarios

- **Protocol Demultiplexing**: A data stream from a sensor (e.g., via a bus) is to be distributed to different downstream processing units depending on the configuration.

- **Test and Simulation Environments**: Feeding a single data path into multiple parallel test channels.

- **Control of Multiple Actuators**: An analog setpoint is passed on to different actuators depending on the index.

## Comparison with Similar Components

| Component | Type | Selection Criterion |

| :--- | :--- | :--- |

| `AIWS_DEMUX_5` | Demultiplexer (1→5) | Index at Event Input |

| `AIWS_MUX_5` | Multiplexer (5→1) | Index for Source Selection |

| `AIWS_SWITCH` | Switch (1→1) | Binary Decision |

The `AIWS_DEMUX_5` is specifically designed for the simultaneous provision of five unidirectional outputs, whereas a simple switch only offers two paths. Unlike a multiplexer, here an input source is distributed to one of many outputs.


## Conclusion

The `AIWS_DEMUX_5` is a structured, generic demultiplexer for the unidirectional AIWS adapter data type. It enables the flexible distribution of an incoming data stream to up to five destinations, controlled by an external index. Thanks to its adapter technology and simple event-driven interface, it can be easily integrated into complex automation and data processing systems.