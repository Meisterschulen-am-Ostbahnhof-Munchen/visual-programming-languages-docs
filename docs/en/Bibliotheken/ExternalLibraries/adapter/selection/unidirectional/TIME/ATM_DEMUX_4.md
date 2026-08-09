# ATM_DEMUX_4

![ATM_DEMUX_4](./ATM_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The function block **ATM_DEMUX_4** is a generic ATM demultiplexer. It distributes a data stream arriving via an incoming adapter (socket) to one of four outgoing adapters (plugs). The output channel is selected via an index `K`, which is evaluated upon the arrival of an event.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| `REQ` | Event | Set Index K – triggers the forwarding |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of successful forwarding |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index of the desired output channel (1…4) |

### **Data Outputs**

*No direct data outputs* – output is via the adapters.

### **Adapters**

| Role | Name | Type | Comment |
|-------|------|-----|-----------|
| Socket | `IN` | `adapter::types::unidirectional::ATM` | Input value to be demultiplexed |
| Plug | `OUT1` | `adapter::types::unidirectional::ATM` | Output channel 1 |
| Plug | `OUT2` | `adapter::types::unidirectional::ATM` | Output channel 2 |
| Plug | `OUT3` | `adapter::types::unidirectional::ATM` | Output channel 3 |
| Plug | `OUT4` | `adapter::types::unidirectional::ATM` | Output channel 4 |

## Functionality

1. The function block expects an event at input `REQ`. This event **must** be synchronized with the data input `K` (using a "With" declaration).
2. Upon arrival of `REQ`, the current value of `K` is evaluated. Valid values are in the range 1–4.
3. The pending value (or received message) via adapter `IN` is forwarded to adapter `OUTX`, where `X` corresponds to index `K`.
4. After successful forwarding, the event `CNF` is output.
5. If the index `K` is invalid (e.g., 0 or >4), no forwarding occurs – the behavior then depends on the implementation (typically an error or output of the event without any action).

## Technical Features

- **Generic Function Block** – the function block is declared as a generic class (`GEN_ATM_DEMUX`) and can be instantiated in various contexts as long as the adapters used are of type `ATM`.
- **Adapter-Based Coupling** – the inputs and outputs are implemented as unidirectional adapters, which allows for loose coupling of the components.
- **Event-Driven Selection** – the index `K` is only evaluated upon an event; statically setting the input alone does not trigger any action.
- **No internal buffering** – the function block forwards the currently received value at the `IN` adapter. The calling application is responsible for handling time-shifted data.

## State Overview

A state machine is not explicitly included in the provided XML. The typical behavior of a demultiplexer results in the following sequence:

- **IDLE** – Waiting for the `REQ` event.
- **FORDER** – As soon as `REQ` arrives and `K` is within the valid range, the value of `IN` is copied to the corresponding `OUTK`.
- **CONFIRM** – After successful forwarding, `CNF` is sent, and the function block returns to the IDLE state.

An incorrect index can result in a separate **ERROR** state (not defined in the XML, but common).

## Application Scenarios

- **Signal Distribution** – A signal from a sensor can be selectively forwarded to various actuators or controllers.
- **Routing** – In a modular machine control system, data packets can be sent to different modules depending on the operating state.
- **Test/Simulation Environments** – Switching between real and simulated data streams by selecting the corresponding output.

## Comparison with Similar Function Blocks

| Function Block | Properties |
|----------|---------------|
| **ATM_DEMUX_4** | Specifically for the adapter type `ATM`, fixed number of four outputs, event-driven. |
**DEMUX (general)** | Often implemented as a data multiplexer/demultiplexer with a variable number of channels and without adapter connectivity. |
**MUX_4** | Multiplexer (multiple inputs → one output) – inverse operation. |

This function block is designed for use in environments where communication occurs via `ATM` adapters and offers a compact solution for 1-out-of-4 selection.

## Conclusion

The **ATM_DEMUX_4** is a specialized, generic demultiplexer for adapter-based control architectures. It enables clean, event-driven selection of one of four output channels and, due to its generic declaration, can be flexibly reused in different projects. For applications that require a standardized point-to-point distribution of ATM messages, it represents an efficient and clear building block.
