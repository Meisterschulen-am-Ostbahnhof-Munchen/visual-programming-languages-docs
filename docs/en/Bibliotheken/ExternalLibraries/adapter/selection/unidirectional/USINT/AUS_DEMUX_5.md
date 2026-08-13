# AUS_DEMUX_5

![AUS_DEMUX_5](./AUS_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The function block **AUS_DEMUX_5** is a generic OFF demultiplexer. It distributes an OFF signal (adapter interface) applied to its input to one of five outputs. The active output is selected via an index that is set by an event. The block is designed for use in distributed automation systems according to IEC 61499.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Sets the index K and triggers the switching |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation of successful switching |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index of the output to be activated (1..5) |

### **Data Outputs**

No data outputs defined.

### **Adapters**

| Role | Name | Type | Comment |
|-------|------|-----|-----------|
Socket (Input) | IN | adapter::types::unidirectional::OFF | Input signal to be demultiplexed |
| Plug (Output) | OUT1 | adapter::types::unidirectional::OFF | First Output |
| Plug (Output) | OUT2 | adapter::types::unidirectional::OFF | Second Output |
| Plug (Output) | OUT3 | adapter::types::unidirectional::OFF | Third Output |
| Plug (Output) | OUT4 | adapter::types::unidirectional::OFF | Fourth Output |
| Plug (Output) | OUT5 | adapter::types::unidirectional::OFF | Fifth Output |

## Functionality

The function block operates purely event-driven. With each **REQ** event, the value of the data input **K** is read. Depending on this index (1–5), the OFF signal present at the adapter socket **IN** is switched to the corresponding plug (OUT1 to OUT5). After a successful switch, the **CNF** event is output. The function block does not have its own state machine; The logic is implemented at runtime through the adapter connections and event processing.

## Technical Features

- **Generic Type**: The function block (FB) is defined as a generic function block (`GEN_AUS_DEMUX`) and can therefore be used with various output adapters, as long as the interface is compatible.
- **Unidirectional Adapters**: Both the input (socket) and the outputs (plugs) use the unidirectional output adapter type. Feedback from the output to the input is not provided.
- **Validity Range of K**: The index **K** is assumed to be in the range 1 to 5. An invalid value (e.g., 0 or >5) can lead to undefined behavior – a plausibility check is not implemented.
- **No Data Outputs**: The actual user data is transmitted exclusively via the adapter interfaces. The FB itself does not have any traditional data output variables.

## State Overview

This function block has **no explicit state machine** (no ECC). All logic is event-driven: A REQ event immediately updates the output adapters and outputs CNF. There are no internal states or delays.

## Application Scenarios

- **Signal Distribution in Automation**: A sensor value (e.g., an OFF-encoded measurement signal) should be forwarded to different actuators or downstream functions depending on the operating mode.
- **Multiplexing/Demultiplexing in Communication Structures**: In industrial networks where data streams are routed via adapter connections, this function block can serve as a demultiplexer for 1:5 distribution.
- **Configurable Forwarding**: For machines with multiple parallel process lines, an index (e.g., from a higher-level control computer) can be used to specify which line receives data.
-
## Comparison with Similar Components

- **AUS_DEMUX_5 vs. AUS_DEMUX_2** (not shown): Both are structured similarly but differ in the number of outputs (5 vs. 2). The generic approach allows the number of outputs to be varied by changing the type.
- **AUS_DEMUX_5 vs. Conventional DEMUX with Data Outputs**: While classic demultiplexers often have scalar data outputs, this function block uses adapter interfaces. This enables closer coupling to other adapter-based components and facilitates modular system design.
- **AUS_DEMUX_5 vs. MUX Components**: The AUS_DEMUX performs the opposite function of a multiplexer (e.g., AUS_MUX), combining multiple inputs into a single output.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AUS_DEMUX_5** is a specialized, generic function block for unidirectional signal distribution via adapter interfaces. Its clear, event-driven logic and the use of up to five outputs make it a useful tool for modular and flexible automation according to IEC 61499. Its generic design allows it to be easily adapted to different adapter variants, increasing reusability.
