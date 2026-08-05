# ALI_DEMUX_5
![ALI_DEMUX_5](./ALI_DEMUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_DEMUX_5** is a generic demultiplexer for ALI (Application Level Interface) interfaces. It distributes an incoming ALI data stream to one of five unidirectional output adapters, controlled by an integer index. This block is particularly suitable for applications where a single data source needs to be selectively forwarded to multiple receivers.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|---------------|
| `REQ` | This event assigns the index `K` and triggers the demultiplex operation. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirms that the index `K` has been set and the input adapter `IN` has been assigned to the selected output adapter. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `K` | UINT | Selection index (1 … 5). Specifies which output adapter (`OUT1` … `OUT5`) is activated. |

### **Data Outputs**

No standalone data outputs; output is handled via the adapters.

### **Adapters**

| Direction | Label | Type | Description |
|----------|-------------|-----|--------------|
| Input (Socket) | `IN` | `adapter::types::unidirectional::ALI` | Unidirectional ALI input that supplies the data stream to be multiplexed. |
| Output (Plug) | `OUT1` … `OUT5` (5 outputs) | `adapter::types::unidirectional::ALI` | Each is a unidirectional ALI output; only the output selected by `K` is connected to the input `IN`. |

## Functionality

1. The function block waits for an event `REQ`.

2. Upon arrival of `REQ`, the current value of the data input `K` is evaluated.

`` 3. Depending on the value of `K` (valid in the range 1 to 5), the ALI adapter `IN` is routed to the corresponding output adapter `OUT1` … `OUT5`.

* For `K=1`, `IN` is connected to `OUT1`, for `K=2` to `OUT2`, and so on.

4. After successful assignment, the event `CNF` is sent to confirm the operation.

* For `K=1`, `IN` is connected to `OUT1`, for `K=2` to `OUT2`, and so on.
* After successful assignment, the event `CNF` is sent to confirm the operation. 5. For invalid index values (e.g., `K=0` or `K>5`), the connection remains unchanged or no output is activated – the exact response must be defined depending on the application.

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GEN_ALI_DEMUX`) and can be instantiated for other output numbers as needed.
- **Unidirectional Adapters**: All ALI interfaces operate in only one direction – from the input to the outputs.
- **Discrete Index Selection**: The index `K` of type `UINT` allows values from 0 to 65535, but only values 1 to 5 are used effectively. Validation is not included in the function block and must be performed in the calling code.
- **Event-Driven Switching**: The assignment occurs exclusively through the event `REQ`; without an event, the current connection remains open.

## State Overview

The function block does not have an explicit state machine. However, its behavior can be described in two phases:

| State | Description |
|---------|---------------|
| Waiting | No `REQ` was received; the current connection remains open. |
| Processing | After `REQ`, the index is evaluated and the connection is switched. Then, `CNF` is sent and the function block (FB) returns to standby mode. |

## Application Scenarios
- **Signal Distribution**: A sensor (e.g., an ALI encoder) provides data that can be selectively forwarded to five different controllers or displays.
- **Channel Switching**: In a modular machine control system, switching between five different actuator groups is possible via an index.
- **Test and Simulation Environments**: A simulated data stream is routed to specific test instances.

## Comparison with Similar Function Blocks

| Function Block | Difference |
|----------|-------------|
| **ALI_DEMUX_2, _3, _4** | Same principle, but with two, three, or four outputs. |
**ALI_MUX** (Multiplexer) | A multiplexer selects one of several inputs and passes it to a single output – exactly the opposite direction. |
**Standard-DEMUX** (Data-Demux) | Often works with scalar data types instead of adapters; ALI_DEMUX_5 uses complex adapter interfaces. |

## Conclusion

The **ALI_DEMUX_5** enables flexible and event-driven routing of ALI data streams to five unidirectional outputs. Its generic declaration and clear interface structure allow it to integrate seamlessly into IEC 61499 systems and make it suitable for a wide range of automation applications.
