# AI_DEMUX_4

![AI_DEMUX_4](./AI_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

AI_DEMUX_4 is a generic function block (FB) for demultiplexing an analog input signal (AI) to one of four outputs. It is typically used in IEC 61499-based automation systems to selectively route an incoming data stream to one of several outputs.
## Interface Structure

### **Event Inputs**

- **REQ**: Event that triggers demultiplexing. The target output is determined via the data input K.

### **Event Outputs**

- **CNF**: Confirmation that the index K has been accepted and the signal has been forwarded.

### **Data Inputs**

- **K** (UINT): Index of the target output. Valid values are 0 (OUT1), 1 (OUT2), 2 (OUT3), and 3 (OUT4). No output is set for invalid values.

### **Data Outputs**

No direct data outputs – output is exclusively via the adapters.

### **Adapters**

**Socket (Input)**

- **IN**: Adapter type `adapter::types::unidirectional::AI` for the incoming analog signal.

**Plugs (Outputs)**

- **OUT1, OUT2, OUT3, OUT4**: Four adapters of the same type (`adapter::types::unidirectional::AI`). Only the output selected by K receives the value from IN; the other outputs remain unchanged.

## Functionality

The module operates as a 1-to-4 demultiplexer. Upon the arrival of a REQ event, the current value of the input adapter IN is copied to the output adapter (OUT1…OUT4) specified by the data input K. After successful assignment, the CNF event is sent. The unaddressed outputs retain their previous values. The function logic is provided by the runtime environment; the function block is declared as a generic block (GenericClassName `GEN_AI_DEMUX`).

## Technical Features

- Unidirectional AI adapters according to the interface definition `adapter::types::unidirectional::AI`.
- Generic block (GenericClassName = `'GEN_AI_DEMUX'`) – enables reuse in various applications.
- No explicit ECC (state engine) in the XML description; control is purely event-driven.
- Published under the Eclipse Public License 2.0 (EPL-2.0).

## State Overview

No state machine is defined in the XML declaration. The function block behaves like a simple single-state machine:

1. **Wait** for REQ.
2. Upon REQ: Evaluate index K, transfer the value from IN to OUT[K], send CNF.
3. Return to the wait state.

## Application Scenarios

- Distributing an analog sensor signal to multiple control units (e.g., parallel control loops).
- Switching between different signal paths in process automation.
- Test and simulation environments where a signal is sequentially routed to different evaluation units.

## Comparison with Similar Function Blocks

- **AI_MUX_4**: Performs the reverse operation – multiple inputs to one output (multiplexer).
- **AI_DEMUX_2 / AI_DEMUX_8**: Devices with two or eight outputs, respectively; AI_DEMUX_4 provides a specific set of four outputs.
- **Generic Demultiplexers**: Other implementations often allow a configurable number of channels; AI_DEMUX_4 is fixed at four channels.

## Conclusion

AI_DEMUX_4 is a simple and reliable device for signal demultiplexing in IEC 61499 systems. It enables the flexible distribution of analog signals across up to four channels and, due to its generic design, is suitable for a wide range of automation tasks.
