# AQ_DEMUX_3
![AQ_DEMUX_3](./AQ_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AQ_DEMUX_3** implements a generic demultiplexer for analog signals (AQ – Analog Quantity). It routes the signal present at its input adapter to one of three output adapters. The active output is selected via the index parameter K, which is set by an event at the **REQ** input. The block is designed as a **generic FB** and can be used in IEC 61499-based control systems for flexible signal distribution.
## Interface Structure

### **Event Inputs**

| Name | Description |

|------|--------------|

| `REQ` | Event for setting index K. The newly passed value of K determines which output is active after processing. |

### **Event Outputs**

| Name | Description |

|------|--------------|

| `CNF` | Confirmation event after index K has been successfully applied. Only after this event is the new output ready to forward the input signal. |

### **Data Inputs**

| Name | Data Type | Description |

|------|----------|--------------|

| `K` | `UINT` | Index of the output to be selected (1-based). Allowed values: 1, 2, 3. Values outside this range result in undefined behavior (no output active). |

### **Data Outputs**

No standalone data outputs. The output data is provided via the adapter outputs.

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| **Sockets** (Input) | `IN` | `adapter::types::unidirectional::AQ` | Adapter input that provides the analog signal to be demultiplexed. |

| **Plugs** (Outputs) | `OUT1`, `OUT2`, `OUT3` | `adapter::types::unidirectional::AQ` | Three unidirectional adapter outputs. Only the output selected by `K` passes on the signal from the input adapter; the others remain inactive. |

## Functionality

1. The module waits for an event at input `REQ`.

2. Upon receiving this event, the current value of data input `K` is read.

3. Depending on the value of `K` (1, 2, or 3), the corresponding output adapter (`OUT1`, `OUT2`, or `OUT3`) is activated, and the signal present at the adapter input `IN` is routed to it.

4. After the switchover, the confirmation event `CNF` is output.

The module behaves like a 1-to-3 demultiplexer: The input signal is always routed to only one of the three outputs. The other two outputs do not provide a valid value (usually 0 or undefined).

## Technical Features

- **Generic Function Block:** The function block is declared as a type with the generic class name `'GEN_AQ_DEMUX'`. This allows it to be used in various forms (e.g., with more outputs) by adapting the metadata.
- **Adaptive Adapter Interface:** Using the type `adapter::types::unidirectional::AQ` enables loose coupling of signal sources and sinks. The exact AQ data structure may vary in the specific implementation.
- **Event-Driven Switching:** The output is changed exclusively via the `REQ` event. Without another event, the current output remains unchanged.
- **No Cyclic Update:** The input signal is not passed on autonomously; the output data is only updated after a `REQ` event.

## State Overview

The function block (FB) does not have a state machine explicitly defined in the XML, as it operates in an event-driven manner. Its internal behavior can be described as follows:

- **Idle** → Waiting for `REQ`
- **Processing** → Evaluation of `K` and switching of the active output
- **Done** → Output of `CNF`, return to Idle

After a valid `REQ`, the **Processing** state is entered, followed immediately by **Idle**.

## Application Scenarios
- **Dividing an analog sensor signal** to various actuators or downstream control blocks.
- **Switching between multiple consumers** (e.g., depending on the operating mode or product recipe).
- **Test and diagnostic environments** where a signal must be selectively routed to different analysis paths.
- **Redundant signal distribution** where only one active path is used at a time.

## Comparison with similar components

| Component | Function | Difference |

|----------|----------|-------------|

| `AQ_DEMUX_3` | Analog demultiplexer with 3 outputs | Specifically for AQ adapters, generically expandable. |

| `AQ_MUX_3` | Analog multiplexer (3 inputs → 1 output) | Reverse direction: multiple sources to one output. |

| `E_DEMUX` | Event demultiplexer | Distributes events, not data adapters; uses Boolean selection. |

| `SAMPLE_3` | Example demux with specific data types | No generic adapter approach, therefore less flexible. |

This function block is characterized by its loose adapter coupling and generic design.

## Conclusion

The **AQ_DEMUX_3** is a useful, generic IEC 61499 function block for distributed signal routing based on AQ adapters. With its event-driven index switching, it is suitable for flexible routing tasks in automation technology. The clear interface and the possibility of generic extension make it a good choice when multiple analog signals need to be routed to different receivers at different times.
