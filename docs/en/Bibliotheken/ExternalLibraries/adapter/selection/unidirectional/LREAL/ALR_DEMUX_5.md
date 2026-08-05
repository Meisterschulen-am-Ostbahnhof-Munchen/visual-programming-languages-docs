# ALR_DEMUX_5
![ALR_DEMUX_5](./ALR_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **ALR_DEMUX_5** is a generic demultiplexer for ALR data (adapter type `unidirectional`). It distributes the data present at its input `IN` to one of five outputs (`OUT1`...`OUT5`). The active output is selected via the index `K`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Trigger the demultiplexing operation with the current index `K` |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation that the selected output has been set |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index of the output to be activated (1...5) |

### **Data Outputs**

No direct data outputs are available. Data is transmitted via the adapters.

#
## ### **Adapter**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| Socket (Input) | `IN` | `adapter::types::unidirectional::ALR` | Input value to be demultiplexed |
| Plug (Output) | `OUT1`...`OUT5` | `adapter::types::unidirectional::ALR` | Outputs for the demultiplexed value |

## Functionality

1. The function block expects an event at input `REQ`.

2. Upon arrival of `REQ`, the currently valid value of index `K` is read (value range typically 1 to 5).

3. The value present at adapter `IN` is transferred to adapter `OUT<K>`.

4. After successful transfer, the acknowledgment event `CNF` is sent.

The demultiplexer operates on a "copy-on-event" principle – data is only forwarded upon `REQ`. Outside of this event, all outputs remain unchanged.

## Technical Features
- **Generic Block**: The FB is marked as a "generic FB" (`GEN_ALR_DEMUX`), so it can be used with different ALR adapter variants.
- **Unidirectional Adapters**: Both the input and outputs use the unidirectional ALR adapter type, meaning data flows in only one direction (from the socket to the plug).
- **Fixed Number of Outputs**: The FB provides exactly five adapter outputs. An index outside the specified range (e.g., 0 or >5) should be avoided – the behavior is not specified.
- **Event-Driven**: All logic is triggered by the event `REQ`; no cyclic or continuous copying occurs.

## State Overview

The FB does not have explicit states with a state machine. Its operation can be reduced to two phases:

1. **Waiting** – The function block waits for a `REQ` event.

2. **Forwarding** – After the `REQ` event, the value is copied to the selected output and sent as `CNF`.

This makes it a purely event-driven function block without internal memory (apart from the adapter values).

## Application Scenarios
- **Distribution of a sensor signal to multiple actuators** – Depending on the index `K`, a measured value is passed on to one of five downstream ALR receivers.
- **Switching between different operating modes** – A central value (e.g., setpoint) is switched to different control loops.
- **Test Routines** – A test signal is applied sequentially to various outputs to test the functionality of the subsequent components.

## Comparison with Similar Components
- **ALR_MUX** – A multiplexer that combines multiple inputs into a single output. The `ALR_DEMUX_5` is the logical inverse.
- **ALR_SWITCH** – A one-to-one switch that selects a single output from multiple inputs but does not distribute the signal to multiple outputs.
- **Components with a fixed number of outputs** (e.g., `ALR_DEMUX_2`, `ALR_DEMUX_8`) differ only in the number of available adapter plugs.

## Conclusion

The `ALR_DEMUX_5` is a compact, event-driven demultiplexer for ALR adapters. It is particularly suitable for applications where a single data stream needs to be switched to one of several lines. Its generic design and unidirectional adapter interface allow for flexible integration into a wide variety of control environments.
