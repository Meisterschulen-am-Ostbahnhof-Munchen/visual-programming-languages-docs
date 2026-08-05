# ATM_DEMUX_2

![ATM_DEMUX_2](./ATM_DEMUX_2.svg)

* * * * * * * * * *

## Introduction

The function block `ATM_DEMUX_2` implements a generic demultiplexer for ATM signals. It distributes an ATM signal present at its input to either one of two outputs. The target output is selected via an integer index, which is passed when the function is called.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Set Index K, triggers the demultiplex operation. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirmation that indexing and forwarding are complete. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Index indicating which output (1 or 2) should be connected to the input signal. |

### **Data Outputs**

No dedicated data outputs; the signals are provided via the adapter outputs.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|------|-----|-----------|

| Plug (Output) | OUT1 | `adapter::types::unidirectional::ATM` | First ATM output channel. |

| Plug (Output) | OUT2 | `adapter::types::unidirectional::ATM` | Second ATM output channel. |

| Socket (Input) | IN | `adapter::types::unidirectional::ATM` | ATM input signal that is demultiplexed. |

## Functionality

This component operates as a **1-to-2 demultiplexer** for ATM signals. Upon an event at the **REQ** input, the index passed at the **K** data input (data type `UINT`) is evaluated. Possible values for `K` are:

- `1` → The signal present at socket **IN** is forwarded to plug **OUT1**.

- `2` → The signal is forwarded to plug **OUT2**.

After a successful switchover, the event **CNF** is output. The underlying ATM protocol is provided by the adapter type definition `adapter::types::unidirectional::ATM`.

## Technical Features

- **Generic Structure**: The function block is declared as a generic function block (`GenericClassName` = `'GEN_ATM_DEMUX'`). This allows it to be derived in various forms (e.g., as `ATM_DEMUX_N` with more than two outputs) through inheritance or parameterization.

- **Adapter-based communication**: The inputs and outputs are defined as adapters (plug/socket). This enables flexible coupling with other components of the same protocol without relying on direct DataConnections.

- **Minimal state logic**: The component does not have an explicit state diagram (ECC); the logic is limited to the immediate implementation of the index switch.

## State overview

The component implements a trivial finite state machine, which is represented in the service sequence:

1. **Waiting** for a REQ event.

2. Upon REQ, the index K is evaluated and the corresponding connection is established.

3. After switching, CNF is output.

4. Return to standby state.

## Application Scenarios

- **ATM Stream Routing**: Distribution of an incoming ATM signal to two different processing paths (e.g., monitoring and data analysis).

- **Test and Simulation Environments**: Targeted application of test signals to one of two outputs.

- **Redundancy Circuits**: Switching between a primary and a secondary path depending on a control index.

## Comparison with Similar Components

| Component | Property |

|----------|-------------|

| `ATM_DEMUX_2` | Specific for 2-output demultiplexing, generically expandable. |

| `ATM_SWITCH_2` | Implements a 2-to-1 multiplex function (selection of one of two inputs). |

| `DEMUX` (general) | Often used as a pure data demultiplexer without an adapter protocol, event-driven. |

The `ATM_DEMUX_2` stands out due to its integration of the ATM adapter protocol and its generic architecture.

## Conclusion

The function block **ATM_DEMUX_2** offers a compact, reusable solution for demultiplexing ATM signals in automation technology. Its generic design and adapter interfaces make it easily adaptable to different channel counts and suitable for modular control systems according to IEC 61499.