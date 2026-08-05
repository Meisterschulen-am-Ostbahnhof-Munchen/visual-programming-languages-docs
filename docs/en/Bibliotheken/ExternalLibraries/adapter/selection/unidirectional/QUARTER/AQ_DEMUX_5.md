# AQ_DEMUX_5
![AQ_DEMUX_5](./AQ_DEMUX_5.svg)
* * * * * * * * * *
## Introduction
The function block **AQ_DEMUX_5** implements a 1-to-5 demultiplexer for adapters of type `AQ` (unidirectional). It forwards incoming data from a central adapter input to one of five outputs. The target output is selected via the index `K`. The block is defined as a generic type (`GEN_AQ_DEMUX`) and can therefore be reused in different environments.
## Interface Structure
### **Event Inputs**

| Event | Comment |

|----------|-----------|

| `REQ` | Starts forwarding the current value from input adapter `IN` to the output specified by `K`. |

### **Event Outputs**

| Event | Comment |

|----------|-----------|

| `CNF` | Acknowledges successful execution of the demultiplex operation. |

### **Data Inputs**

| Name | Type | Comment |

|------|-------|---------------------------|

| `K` | `UINT`| Index of the desired output (1..5). |

### **Data Outputs**

– No dedicated data outputs; output is handled via the adapter plugs.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|-------|-----------------------------------|--------------------------------------|

| Socket (Input) | `IN` | `adapter::types::unidirectional::AQ` | Input data to be demultiplexed. |

| Plug (Output) | `OUT1`| `adapter::types::unidirectional::AQ` | First output channel. |

| Plug (Output) | `OUT2`| `adapter::types::unidirectional::AQ` | Second output channel. |

| Plug (Output) | `OUT3` | `adapter::types::unidirectional::AQ` | Third output channel. |

| Plug (Output) | `OUT4` | `adapter::types::unidirectional::AQ` | Fourth output channel. |

| Plug (Output) | `OUT5` | `adapter::types::unidirectional::AQ` | Fifth output channel. |

## Functionality

1. **Input Signal Provision:** The connected socket `IN` continuously provides data for a unidirectional `AQ` channel.

2. **Triggering:** An event at the input `REQ` starts the demultiplex operation. The current value of index `K` is read.

3. **Forwarding:** The function block internally connects input `IN` to the output adapter referenced by `K` (`OUT1` … `OUT5`). The data is propagated **once** to the selected output.

4. **Confirmation:** After successful transmission, an event is sent at output `CNF` to signal completion to the calling function block.

> **Note:** Index `K` must be within the valid range `1 … 5`. Values outside this range are ignored or result in undefined behavior – depending on the specific implementation.

## Technical Features
- **Generic Type:** The function block (FB) has the attribute `GenericClassName` with the value `'GEN_AQ_DEMUX'` and can therefore serve as a basis for similar demultiplexers with a different number of channels.
- **Type Hash:** A unique hash (`TypeHash`) is managed by the development tool and serves for version control and identification of the function block.
- **Unidirectional Adapters:** All involved adapters are of type `adapter::types::unidirectional::AQ`, meaning data flows only in one direction (from the input to the outputs). Feedback from the outputs is not provided.

## State Overview
The FB internally goes through two main states:

| State | Description |

|-----------|--------------------------------------------------|

| **IDLE** | Waiting for a `REQ` event. |

**BUSY** | Current demultiplex operation is being executed. |

**DONE** | Operation completed; `CNF` is being sent; return to **IDLE**. |

The transition from **IDLE** to **BUSY** occurs via a `REQ` event. After successful forwarding, the function block briefly enters the **DONE** state and sends `CNF` before returning to **IDLE**.

## Application Scenarios
- **Channel Switching:** Distributing an analog measured value (e.g., temperature, pressure) to various higher-level controllers, with the target channel being switched at runtime.

**IDLE** - **Data Routing:** Forwarding a serial data stream (e.g., Modbus RTU via adapter) to different end devices based on a specified index.

- **Test and Simulation Environments:** Method for cyclically activating different outputs by incrementing the index `K`.

## Comparison with Similar Function Blocks
- **AQ_DEMUX_N** (different number of outputs): Function blocks such as `AQ_DEMUX_2` and `AQ_DEMUX_8` differ only in the number of output adapters. The `AQ_DEMUX_5` described here offers exactly five channels.
- **AQ_MUX_5 (Multiplexer)**: A multiplexer reverses the direction – it reads one input from several and outputs one value. A demultiplexer, on the other hand, distributes one input to several outputs.
- **Unidirectional vs. Bidirectional Demultiplexers**: Bidirectional variants (e.g., `AQ_BI_DEMUX`) also allow data flow from an output back to the input, which is not the case here.

## Conclusion
The `AQ_DEMUX_5` is a specialized function block for the point-by-point distribution of unidirectional `AQ` data across five channels. Its generic architecture facilitates reuse in different control systems. Clear event-driven control (REQ/CNF) and simple indexing make it a reliable component for applications requiring dynamic channel selection.