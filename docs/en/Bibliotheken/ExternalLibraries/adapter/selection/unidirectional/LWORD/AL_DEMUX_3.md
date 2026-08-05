# AL_DEMUX_3
![AL_DEMUX_3](./AL_DEMUX_3.svg)
* * * * * * * * * *
## Introduction
The function block **AL_DEMUX_3** is a generic demultiplexer for unidirectional AL adapter data. It routes an incoming adapter data stream (via socket **IN**) to one of three output adapters (**OUT1**, **OUT2**, **OUT3**). Switching is performed via a data input **K** and is triggered by an event **REQ**. This block is particularly suitable for applications where a signal needs to be distributed to different paths depending on its index.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Sets the index K and redirects the data |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation of successful switching |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index (1, 2, or 3) for the output to be activated |

### **Data Outputs**
– None –

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Plug | **OUT1** | adapter::types::unidirectional::AL | First Output Channel |

| Plug | **OUT2** | adapter::types::unidirectional::AL | Second Output Channel |

| Plug | **OUT3** | adapter::types::unidirectional::AL | Third Output Channel |

| Socket | **IN** | adapter::types::unidirectional::AL | Input signal that is demultiplexed |

## Functionality

1. The **IN** adapter continuously provides data (e.g., a measured value or a control signal).

2. An external call triggers the **REQ** event.

3. The function block reads the current value of the data input **K**. This must be in the range 1 to 3.

4. Depending on **K**, the input adapter **IN** is connected to the corresponding output adapter (**OUT1**, **OUT2**, or **OUT3**).

- For **K=1**, the data is forwarded to **OUT1**.
- For **K=2**, the data is forwarded to **OUT2**.
- For **K=3**, the data is forwarded to **OUT3**.

5. After a successful switchover, the **CNF** event is output.

> **Note:** The value of **K** is only evaluated during a **REQ** event. A change in the data input between two events has no immediate effect.

## Technical Features
- **Generic Function Block:** The FB is defined as a generic type (GenericClassName `GEN_AL_DEMUX`) and can be used in various projects with the adapter type **AL**.
- **No Data Outputs:** The output data is transported exclusively via the adapter plugs. This allows for flexible further processing in downstream function blocks.
- **Unidirectional Adapters:** Both the input and outputs use the adapter type `adapter::types::unidirectional::AL`. This assumes that data flow is unidirectional.
- **Index Limit:** The function block expects values between 1 and 3 for **K**. Values outside this range result in no defined behavior (or may be ignored).

## State Overview

The **AL_DEMUX_3** has a simple internal flow without a persistent state machine. The only action occurs synchronously with the **REQ** event:

| State | Event | Action |

|---------|----------|--------|

| Ready | REQ | Read K, switch connection, send CNF |

After sending **CNF**, the function block immediately returns to the Ready state.

## Application Scenarios
- **Sensor Multiplexing:** A single sensor (e.g., temperature, pressure) is alternately routed to different evaluation units.
- **Control Routing:** In a machine control system, control signals are distributed to different actuators depending on the operating mode.
- **Test and Verification Benches:** A test signal can be selectively routed to different measuring points.
- **Agricultural Technology:** In agricultural electronics (e.g., ISOBUS applications), a data signal can be split to different implements.

## Comparison with Similar Function Blocks

| FB | Difference |

|----|-------------|

| **AL_DEMUX_2** | Offers only two output adapters instead of three |

| **AL_MUX** | Performs the reverse function (multiplexer: multiple inputs → one output) |

| **E_SWITCH** | Works with individual signals (bit/byte), not with adapters |

**FBD_DEMUX** | Data demultiplexer at the level of elementary data types (e.g., INT, REAL), without adapter support |

The **AL_DEMUX_3** features a direct adapter interface, enabling seamless integration into adapter-based communication paths.

## Conclusion

The **AL_DEMUX_3** is a compact and efficient function block for distributing unidirectional AL adapter data across three channels. Its index-driven switching via an event makes it easy to use and suitable for a wide range of routing tasks. Its generic architecture allows it to be used in different projects without modification.