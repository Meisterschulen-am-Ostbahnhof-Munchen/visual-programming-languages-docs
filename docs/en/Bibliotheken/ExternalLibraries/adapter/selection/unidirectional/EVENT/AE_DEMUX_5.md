# AE_DEMUX_5
![AE_DEMUX_5](./AE_DEMUX_5.svg)
* * * * * * * * * *
## Introduction
The **AE_DEMUX_5** function block is a generic AE demultiplexer that routes an incoming AE signal via socket **IN** to one of five output adapters (OUT1 … OUT5) based on a selected index. This allows for the targeted distribution of a data stream to different paths.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| **REQ** | Trigger to set index **K** and select the output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| **CNF** | Confirms successful processing of **REQ**. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| **K** | UINT | Index value for selecting the output (valid values: 1 … 5). |

### **Data Outputs**
No data outputs available.

### **Adapter**

| Role | Name | Type | Description |

|-------|------|----------------------------|--------------|

| Socket| **IN** | `adapter::types::unidirectional::AE` | Input signal that is demultiplexed. |

| Plug | **OUT1** | `adapter::types::unidirectional::AE` | Output 1 |

| Plug | **OUT2** | `adapter::types::unidirectional::AE` | Output 2 |

| Plug | **OUT3** | `adapter::types::unidirectional::AE` | Output 3 |

| Plug | **OUT4** | `adapter::types::unidirectional::AE` | Output 4 |

| Plug | **OUT5** | `adapter::types::unidirectional::AE` | Output 5 |

## Functionality

1. An index **K** (1 … 5) is passed to the event input **REQ**.

2. The AE signal present at socket **IN** is switched to plug **OUTx** (x = K).

3. After successful switching, the event output **CNF** is displayed.

- If the index is invalid (< 1 oder > 5), no switching occurs; **CNF** is not used.

## Technical Features
- **Generic Block**: The class can be instantiated under the name `GEN_AE_DEMUX`, where the number of outputs is determined by the symbol name (here, 5).
- **Adapter-Based**: Instead of fixed data ports, AE adapters are used, enabling flexible coupling with other blocks.
- **Type Hash**: A type hash is provided via an attribute for runtime identification.
- **No Internal State Machine**: The functionality is purely event-driven without internal states.

## State Overview
The block does not have an explicit state machine. It operates event-driven in one step per **REQ** call. An implicit idle state is represented by waiting for the next event.

## Application Scenarios
- **Signal Distribution**: Transmission of an AE signal (e.g., sensor value, control command) to various actuators or sub-functions.
- **Channel Selection**: Selection of one of five output channels, e.g., in multi-valve or multiplexer applications.
- **Routing Switch**: Dynamic switching of the target path within a controller.

## Comparison with Similar Function Blocks
- **AE_DEMUX_2 / AE_DEMUX_10**: Corresponding variants with two or ten outputs – same logic, different number of channels.
- **AE_MUX_X**: Multiplexer (multiple inputs, one output) – the inverse function.
- Compared to a specialized selection block at the data level (e.g., `SELECT_INT`), this block operates at the adapter level and transmits the entire AE context.

## Conclusion
The **AE_DEMUX_5** offers a simple yet effective way to route an AE signal based on an index to one of five outputs. Its generic implementation and the use of adapters make it particularly suitable for modular control applications that allow for flexible, subsequent expansion of the channel count.