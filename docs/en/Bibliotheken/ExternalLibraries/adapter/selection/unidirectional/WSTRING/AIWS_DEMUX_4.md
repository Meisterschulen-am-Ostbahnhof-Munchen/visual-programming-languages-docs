# AIWS_DEMUX_4

![AIWS_DEMUX_4](./AIWS_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The function block **AIWS_DEMUX_4** is a generic demultiplexer for AIWS data. It distributes an incoming AIWS data stream (via socket `IN`) to one of four AIWS outputs (`OUT1`–`OUT4`), which is selected by the index `K`. This block is used for the targeted routing of data in structured control systems and is typically employed in agricultural automation technology.
## Interface Structure

### **Event Inputs**

| Event | Data Type | With Var | Comment |
|----------|----------|---------|-----------|
| `REQ` | Event | `K` | Sets the index `K` and triggers demultiplexing. |

### **Event Outputs**

| Event | Data Type | With Var | Comment |
|----------|----------|----------|----------|
| `CNF` | Event | – | Confirms successful index assignment and selection update. |

### **Data Inputs**

| Name | Data Type | Comment |
|------|----------|-----------|
| `K` | UINT | Index of the desired output (value range typically 1…4). |

### **Data Outputs**

This function block does not have its own data outputs. The actual user data is transmitted via the adapter interfaces.

### **Adapters**

| Direction | Name | Type | Comment |
|----------|------|-----|-----------|
| **Plug** (Output) | `OUT1` | `adapter::types::unidirectional::AIWS` | First output adapter for AIWS data. |
| **Plug** (Output) | `OUT2` | `adapter::types::unidirectional::AIWS` | Second output adapter for AIWS data. |
**Plug** (Output) | `OUT3` | `adapter::types::unidirectional::AIWS` | Third output adapter for AIWS data. |
**Plug** (Output) | `OUT4` | `adapter::types::unidirectional::AIWS` | Fourth output adapter for AIWS data. |
**Socket** (Input) | `IN` | `adapter::types::unidirectional::AIWS` | Input adapter for the AIWS data stream to be demultiplexed. |

## Functionality

1. The function block waits for an event at `REQ`.
2. The current value of input `K` is retrieved at `REQ`.
3. The AIWS data stream arriving via adapter `IN` is switched to the output adapter (`OUT1`–`OUT4`) determined by `K`.
4. After successful switching, an acknowledgment event is output at output `CNF`.
5. The unselected outputs remain inactive or do not provide valid data (depending on the implementation of the underlying adapter type).

The adapters are of type `unidirectional::AIWS`, indicating unidirectional data transmission without feedback.

## Technical Features

- **Generic Component**: The class is generic (`GEN_AIWS_DEMUX`), allowing it to be extended for any number of channels. This version supports exactly four outputs.
- **Adapter-Based Interface**: User data is exchanged not via traditional input/output variables, but via platform-independent adapters. This increases modularity and reusability.
- **Index Check**: Although the index `K` is of type `UINT`, it is recommended to use only values from 1 to 4. Values outside this range result in undefined behavior (e.g., no output is activated).
- **No Data with CNF**: The confirmation event `CNF` is not linked to any further data – it simply signals that the selection has been updated.

## State Overview

The function block has only a very simple state logic:

- **Idle**: Waiting for `REQ`.
- **Processing**: Upon receipt of `REQ`, the index `K` is read and the selection is updated. After completion, `CNF` is sent and the function block returns to the idle state.

There are no internal error states or timeout mechanisms.

## Application Scenarios

- **Data Distribution in Control Systems**: A sensor delivers AIWS data to a bus. The demultiplexer forwards the data to various actuators or downstream processing units as needed.
- **Agricultural Automation**: In field robots or irrigation control systems, several identical devices (e.g., valves, nozzles) can be supplied from a common data source.
- **Test and Simulation Environments**: Used as a flexible multiplexer switch to connect different data sources to a common analysis path (or vice versa).

## Comparison with Similar Components

- **AIWS_DEMUX_4 vs. Generic Demux with Data Ports**: Components with classic `ANY` data ports are often less type-safe, while adapter-based solutions offer a clearly defined interface (AIWS).
- **AIWS_DEMUX_4 vs. Multiplexer (AIWS_MUX)**: The demultiplexer distributes one input to multiple outputs, while the multiplexer selects one of several inputs. Both operate complementarily.
- **AIWS_DEMUX_4 vs. Manual Index Control**: Without this component, data forwarding would have to be implemented programmatically in function blocks or scripts – the demux encapsulates this logic for reuse.

## Conclusion

The **AIWS_DEMUX_4** is a compact, adapter-based demultiplexer for AIWS data streams in IEC 61499 systems. It enables a clean separation of data forwarding and control logic and is particularly suitable for modular automation applications. Its generic design allows for easy scaling to different channel counts.
