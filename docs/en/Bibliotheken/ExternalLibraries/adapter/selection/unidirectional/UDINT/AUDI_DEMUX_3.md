# AUDI_DEMUX_3

![AUDI_DEMUX_3](./AUDI_DEMUX_3.svg)

* * * * * * * * * *
## Introduction

The function block **AUDI_DEMUX_3** is a generic demultiplexer for the unidirectional adapter type `AUDI`. It distributes an incoming adapter signal to one of three possible outputs, based on an index specified via the data input `K`. The block is controlled by an event at `REQ`.
## Interface Structure

### **Event Inputs**

| Name | Data Type | Description |
|------|----------|-----------------------------------------------|
| REQ | Event | Control signal: Adoption of the index `K` and execution of the demultiplex function |

### **Event Outputs**

| Name | Data Type | Description |
|------|----------|--------------------------------------------------|
| CNF | Event | Acknowledgement after successful demultiplexing |

### **Data Inputs**

| Name | Data Type | Description |
|------|----------|--------------------------------------------------------------|
| K | UINT | Index (1, 2, or 3) of the desired output channel. Values outside this range will not result in a valid pass-through. |

### **Data Outputs**

No standalone data outputs are available. Output is exclusively via the following adapters.

### **Adapters**

| Type | Name | Direction | Description |
|-------|------|----------|----------------------------------------------------------|
| Socket | IN | Input | Unidirectional AUDIO adapter that provides the signal to be multiplexed |
| Plug | OUT1 | Output | First unidirectional AUDIO output (K=1) |
| Plug | OUT2 | Output | Second unidirectional AUDIO output (K=2) |
| Plug | OUT3 | Output | Third unidirectional AUDIO output (K=3) |

## Functionality

1. **Initial State:** All adapter outputs are inactive (no signal transmission).
2. **Event REQ:** The module reads the current value of the data input `K`.
3. **Demultiplexing:** Depending on the value of `K`, the incoming `IN` signal is routed to the corresponding adapter output:
- `K = 1` → `OUT1` receives the signal from `IN`
- `K = 2` → `OUT2` receives the signal from `IN`
- `K = 3` → `OUT3` receives the signal from `IN`
4. **Acknowledgement:** After routing, the event `CNF` Triggered.
5. **Side note:** Unselected outputs remain inactive. The value of `K` at the time of the `REQ` event is crucial.

## Technical Features

- The function block is implemented as a generic function block (`GenericClassName = 'GEN_AUDI_DEMUX'`) but remains fixed to three outputs.
- There is no state machine – the function block operates in an event-driven and stateless manner.
- The adapters are unidirectional (`adapter::types::unidirectional::AUDI`), meaning communication only occurs in one direction.
- The input of `K` is not validated. Values greater than 3 or equal to 0 do not result in any switching (outputs remain inactive). However, `CNF` is still triggered.

## State Overview

This function block has no explicit states. It behaves like a combinatorics function: Each `REQ` event is immediately followed by a pass operation and a `CNF` event.

## Application Scenarios

- **Audio Signal Distribution:** Passing an audio stream to one of three target components (e.g., loudspeaker, recording device, analysis module).
- **Channel Selection in Measurement Systems:** Switching a sensor signal to one of three data paths.
- **Adapter Routing:** Within an IEC 61499-based controller, this function block can be used to implement flexible signal paths based on index selection.

## Comparison with Similar Function Blocks

- **AUDI_MUX_3** (Multiplexer): Performs the reverse function – selects one of three inputs and outputs it to one output.

**AUDI_MUX_3** (Multiplexer):** Selects one of three inputs and outputs it to one output. - **AUDI_DEMUX_2**, **AUDI_DEMUX_4**: Variants with two or four outputs, respectively. The present module is designed for exactly three channels.

- **Generic DEMUX**: A general-purpose demultiplexer with a configurable number of channels (if available) would be more flexible but requires more configuration. `AUDI_DEMUX_3` is static and therefore easier to use.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The `AUDI_DEMUX_3` is a simple yet effective module for channel-based forwarding of a unidirectional adapter signal. Its clear interface and event-driven operation make it a reliable component in IEC 61499 applications that require signal distribution to exactly three outputs.
