# AIS_DEMUX_4

![AIS_DEMUX_4](./AIS_DEMUX_4.svg)

* * * * * * * * * *

## Introduction

The **AIS_DEMUX_4** function block is a generic AIS demultiplexer. It receives an AIS data stream via a single input adapter and selectively forwards it to one of four output adapters. Switching is performed via the index input K. The block is designed for use in IEC 61499 applications that require flexible distribution of AIS signals.

## Interface Structure

### **Event Inputs**

| Event | Description | Accompanying Signal |

|----------|---------------|---------------------|

| REQ | Sets the index K and triggers forwarding | K (UINT) |


### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirms that the forwarding according to index K has been completed |

### **Data Inputs**

| Variable | Type | Description |

|----------|--------|--------------|

| K | UINT | Index of the desired output (1-4) |

### **Data Outputs**

No explicit data outputs. Output is provided via adapters OUT1 … OUT4.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Plug (Output) | OUT1 | `adapter::types::unidirectional::AIS` | First AIS output channel |

| Plug (Output) | OUT2 | `adapter::types::unidirectional::AIS` | Second AIS output channel |

| Plug (Output) | OUT3 | `adapter::types::unidirectional::AIS` | Third AIS output channel |

| Plug (Output) | OUT4 | `adapter::types::unidirectional::AIS` | Fourth AIS output channel |

| Socket (Input) | IN | `adapter::types::unidirectional::AIS` | AIS input signal that is demultiplexed |

## Functionality

1. In its initial state, the module is ready to receive a new index.

2. An event at input **REQ** takes the current value of **K** (an integer between 1 and 4).

3. The function block connects the input adapter **IN** to the output adapter **OUT_K** determined by K. All other outputs remain inactive or in a neutral state.

4. After successful switching, the event **CNF** is sent.

5. The function block behaves like a 1-to-4 switch for AIS data streams. Each REQ event re-switches the connection.

The exact handling of the input signal (e.g., whether buffering or direct pass-through) depends on the implementation of the underlying AIS adapter type.


## Technical Features

- **Generic Type** – The function block is managed under the generic class name `GEN_AIS_DEMUX` and can be instantiated for various AIS adapter implementations.

- **Adapter-Based Communication** – Instead of direct data inputs/outputs, the function block uses the IEC 61499 adapter concept, which enables loose coupling and easy reuse in different distribution architectures.

- **No Internal State Machine Predefined** – The exact sequence control is determined by the implementation; typically, a simple two-state state machine (IDLE → ROUTE → IDLE) is used.

## State Overview

An explicit ECC diagram is not included in this type definition. Typical states would be:

1. **IDLE** – Waiting for a REQ event.

2. **ROUTE** – Forwarding the input to the output specified by K.

The transition from IDLE to ROUTE is performed using REQ, and after the forwarding is complete, CNF is triggered, and the function block returns to IDLE.

## Application Scenarios

- **AIS Data Distribution** – An incoming AIS data stream should be forwarded to different downstream processing units depending on the context (e.g., season or operating mode).

- **Load or Signal Routing** – Four parallel paths are available; the index K can be dynamically set by a higher-level controller.

- **Test and Simulation Environments** – Switching between different signal sources or sinks during operation.

## Comparison with Similar Function Blocks

| Function Block | Type | Outputs | Special Features |

|----------|-----|----------|--------------|

| `AIS_DEMUX_4` | Adapter-based | 4 | Specifically for AIS data, generic class |

| `GEN_DEMUX` (generic data demultiplexer) | Direct data | Variable | Works with elementary data types, no adapters |

| `MUX` (multiplexer) | Adapter/data | 1 input → multiple outputs | Reverse direction |

The AIS_DEMUX_4 stands out due to its adapter interface and its specific focus on AIS protocols.


## Conclusion

The **AIS_DEMUX_4** is a simple yet effective demultiplexer for AIS adapter connections. Its generic design allows for use in various environments, while its clear event-driven control ensures robust switching between four output paths. It is an ideal component when AIS data streams need to be flexibly distributed across multiple sinks.