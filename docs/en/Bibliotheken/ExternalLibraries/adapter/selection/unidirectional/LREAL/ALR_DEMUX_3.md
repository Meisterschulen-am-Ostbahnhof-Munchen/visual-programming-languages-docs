# ALR_DEMUX_3

![ALR_DEMUX_3](./ALR_DEMUX_3.svg)

* * * * * * * * * *
## Introduction

The function block `ALR_DEMUX_3` is a generic demultiplexer for ALR adapter interfaces (unidirectional). It forwards the ALR data stream present at socket `IN` to one of three output adapters (`OUT1`, `OUT2`, `OUT3`). The target output is selected via the index `K`. This function block is suitable for use in applications where a signal path needs to be dynamically switched to different downstream components.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `REQ` | Event | Set the index `K` and trigger the forwarding |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| `CNF` | Event | Confirmation of successful switching/forwarding |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| `K` | UINT | Index of the target output (1..3) |

### **Data Outputs**

*No data outputs available.* The actual data transmission occurs via the adapters.

### **Adapters**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| `IN` | ALR (unidirectional) | Socket | Input adapter (data source) |
| `OUT1` | ALR (unidirectional) | Plug | First output channel |
| `OUT2` | ALR (unidirectional) | Plug | Second output channel |
| `OUT3` | ALR (unidirectional) | Plug | Third output channel |

## Functionality

The module operates according to the demultiplexing principle. Upon an event at input `REQ`, the ALR value present at socket `IN` is taken and passed to the output adapter (`OUT1`, `OUT2`, or `OUT3`) determined by the index `K` (integer value 1–3). The event `CNF` is then sent to signal successful completion. If the index is outside the valid range (e.g., 0 or >3), the request may be ignored or an undefined state may be reached, depending on the specific implementation.

...
## Technical Features

- **Generic Design**: The function block is declared as an instantiable generic function block (`GEN_ALR_DEMUX`), meaning it can be used in various contexts with different ALR types, provided they have the same adapter interface.
- **Unidirectional Adapters**: Both inputs and outputs use the unidirectional ALR adapter type. Feedback from the output to the input is not possible.
- **No State Machine**: According to the provided XML definition, the function block does not have an explicit ECC (Execution Control Chart). Its behavior is purely event-driven and limited to the moment of `REQ` processing.

## State Overview

The `ALR_DEMUX_3` does not have an explicit state machine. It is always in a basic ready state. Upon receiving `REQ`, it immediately executes the demultiplex operation and signals completion with `CNF`. There are no internal states such as "Waiting" or "Busy."

## Application Scenarios

- **Resource Switching**: Several sensors or actuators share a data source, which must be switched to different units depending on the context (e.g., in automation technology for controlling multiple identical loads).
- **Test and Diagnostic Setups**: An ALR signal is routed sequentially to different test points without requiring any physical changes to the wiring.
- **Redundancy Circuits**: A primary signal is redirected to one of three redundant units as needed.

## Comparison with Similar Components

Compared to a classic, data-oriented demultiplexer (e.g., `F_MUX/DEMUX`), which works with scalar data types (INT, REAL, etc.), the `ALR_DEMUX_3` is specifically designed for structured adapter communication. While a data demuxer only forwards individual values, this component transmits an entire ALR connection, including all its data fields. It is less flexible regarding the number of outputs (fixed at three), but offers clean separation at the adapter level.

## Conclusion

The `ALR_DEMUX_3` is a specialized, generic component for the unidirectional distribution of ALR adapter connections. It enables flexible and dynamic signal routing in automation systems and expands the range of industrial demultiplexers to include the component of adapter-based communication. Its simple event logic and the fixed number of three outputs make it equally powerful and easy to use for practical scenarios.
