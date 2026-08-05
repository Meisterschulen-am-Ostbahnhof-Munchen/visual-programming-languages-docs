# AUS_DEMUX_2
![AUS_DEMUX_2](./AUS_DEMUX_2.svg)
* * * * * * * * * *
## Introduction
The function block **AUS_DEMUX_2** is a generic demultiplexer for unidirectional AUS adapters. It distributes a value received via socket `IN` to either one of the two output adapters, `OUT1` or `OUT2`. The selection is made via the index `K`, which is set by a REQ event. The function block is implemented as a generic type (`GEN_AUS_DEMUX`) and can be used for various AUS data structures.
## Interface Structure

### **Event Inputs**
- **REQ**

Event that triggers the demultiplexing process. The corresponding data input `K` is assigned the current value.

### **Event Outputs**
- **CNF**

Acknowledgement signal sent after successful forwarding of the input value to the selected output.

### **Data Inputs**
- **K** (UINT)

Index for selecting the target output. Typical values: `1` → `OUT1`, `2` → `OUT2`.

### **Data Outputs**

No direct data outputs – data is passed through adapters.

#
## ### **Adapters**
- **IN** (Socket, type `AUS`)

Input adapter through which the value to be demultiplexed is received.

- **OUT1** (Plug, type `AUS`)

First output adapter, which receives the value of `IN` when `K=1` is received.

- **OUT2** (Plug, type `AUS`)

Second output adapter, which receives the value of `IN` when `K=2` is received.

## Functionality

1. A REQ event is received.

2. The current value of the data input `K` is evaluated.

3. The value of the socket adapter `IN` is copied to the plug adapter corresponding to index `K`:

- `K=1` → value is placed on `OUT1`.
- `K=2` → value is placed on `OUT2`.

4. After the forwarding is complete, the CNF event is sent.

If `K` assumes a different value than `1` or `2`, the assignment has no effect (no output is written) – the behavior then depends on the implementation.

## Technical Features
- **Generic Block**

The attribute `GenericClassName` specifies the generic name `'GEN_AUS_DEMUX'`. This allows the function block to be reused for different output data types without modifying the interface.

- **Emitter / Plug Adapter**

The outputs are defined as plugs, so they can be directly connected to corresponding sockets. Data transfer is unidirectional (only from the function block to the connected socket).

- **No State Machine**

The XML does not contain an internal ECC; processing is event-driven and performed in a single step.

## State Overview
The function block does not have an explicit state machine. Its behavior is limited to the immediate response to a REQ event.

## Application Scenarios
- **Sensor Data Distribution:** A measured value (e.g., from a pressure sensor) can be passed on to either a display (`OUT1`) or a controller (`OUT2`).
- **Operating Mode Switching:** Depending on the selected mode (index `K`), a signal is routed to different actuators.
- **Test/Production Routing:** In modular systems, a test signal can be routed either to a test output or to the production path.

## Comparison with Similar Function Blocks
- **MUX_BASIC** (multiplexer) selects one output from multiple inputs – the AUS_DEMUX_2 does the opposite: one input is distributed across multiple outputs.
- **AUS_DEMUX_N** (generic for more than two outputs) – this function block is limited to exactly two outputs, making it simpler and clearer.
- **EXTRACT** / **SELECT** – unlike dataflow-based function blocks, routing here is controlled by an explicit event.

## Conclusion
The **AUS_DEMUX_2** is a lean, generic demultiplexer for AUS adapters, characterized by its clear event interface and ease of use. It is suitable for all cases where a single data stream needs to be redirected to one of two target adapters based on an event. Its generic design allows its use with any AUS data type – ideal for modular and reusable automation solutions.
