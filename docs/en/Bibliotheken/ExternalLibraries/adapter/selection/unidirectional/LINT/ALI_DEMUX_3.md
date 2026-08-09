# ALI_DEMUX_3

![ALI_DEMUX_3](./ALI_DEMUX_3.svg)

* * * * * * * * * *
## Introduction

The function block **ALI_DEMUX_3** is a generic demultiplexer for the ALI (Application Layer Interface) data type. It distributes an incoming ALI data stream to three separate output adapters, with the selection of the active output controlled by an index `K`. This block is suitable for applications where a data source needs to be sequentially routed to different sinks.
## Interface Structure

### **Event Inputs**

| Event | Description | Carried |
|----------|---------------|-------------|
| `REQ` | Execution of the demultiplexing operation | `K` |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirmation that the switching process is complete |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `K` | UINT | Index of the output to be activated (1–3) |

### **Data Outputs**

This function block does not have traditional data outputs. The output data is provided via the adapters.

### **Adapters**

| Adapter | Type | Direction | Description |
|---------|-----|----------|--------------|
| `IN` | ALI | Socket | Input data stream to be demultiplexed |
| `OUT1` | ALI | Plug | First output (active with `K = 1`) |
| `OUT2` | ALI | Plug | Second output (active with `K = 2`) |
| `OUT3` | ALI | Plug | Third output (active with `K = 3`) |

## Functionality

The module operates on the principle of a 1-out-of-3 demultiplexer. As soon as an event `REQ` arrives, the index `K` is evaluated. Depending on the value of `K`, the incoming ALI data stream **from socket `IN`** is routed to the corresponding plug (`OUT1`, `OUT2`, or `OUT3`). After successful routing, the event `CNF` is output.

- Upon `K = 1`, the module forwards the data to `OUT1`.
- For `K = 2`, it forwards the data to `OUT2`.
- For `K = 3`, it forwards the data to `OUT3`.
- All other values of `K` (especially 0 or >3) do not result in any defined behavior; the function block should be limited to valid values in the calling application.

The function block is implemented as a **generic function block** (`GEN_ALI_DEMUX`). This allows the number of outputs to be varied by type parameterization. For the specific instance `ALI_DEMUX_3`, exactly three outputs are defined.

## Technical Features

- **Generic Class:** The function block is based on the generic type `GEN_ALI_DEMUX`. This allows for easy reuse with different channel counts.
- **Adapter-Based Communication:** All data interfaces are implemented as ALI adapters, enabling loose coupling and modular integration into adapter networks.
- **Unidirectional Data Flow:** The socket `IN` and the plugs `OUT1..OUT3` are unidirectional (inbound/outbound), clearly defining the data flow direction.
- **No State Machine:** The function block operates purely event-driven and does not have an explicit internal state machine. Switching occurs synchronously with each `REQ` event.

## State Overview

The component has **no explicit state machine**. The process is deterministic:

1. Wait for `REQ`.
2. Upon `REQ`: Evaluate `K`, pass the ALI data stream to the corresponding output.
3. Send `CNF`.
4. Return to the wait state.

Distinguishing between multiple internal states is not required.

## Application Scenarios

- **Controlling Multiple Actuators:** A sensor provides ALI data that can be selectively forwarded to three different actuators. The index is set by a higher-level control logic.
- **Channel Selection in Communication Systems:** Distributing an incoming data stream to three parallel receivers, e.g., for testing or monitoring purposes.
- **Resource Switching:** In a manufacturing plant, a measured value can be sent to one of three evaluation units depending on the operating mode.

## Comparison with Similar Function Blocks

Unlike a **multiplexer** (e.g., `ALI_MUX`), which combines multiple inputs into one output, the `ALI_DEMUX_3` distributes a single input to multiple outputs. Compared to a **static splitter** (which copies all inputs in parallel), the demux allows index-based selection, thus reducing the bus load. Similar function blocks exist for other data types (e.g., `GEN_DEMUX` for generic data), but this function block is specifically optimized for the ALI adapter type.

## Conclusion

The **ALI_DEMUX_3** is a compact, generic demultiplexer for ALI data streams with three outputs. It is particularly suitable for modular architectures that require flexible signal rerouting. Thanks to its adapter interface, it can be seamlessly integrated into existing IEC 61499 applications and offers high reusability due to its generic basis.
