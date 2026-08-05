# ALI_DEMUX_4
![ALI_DEMUX_4](./ALI_DEMUX_4.svg)

* * * * * * * * * *
## Introduction
The function block **ALI_DEMUX_4** is a generic demultiplexer for the ALI protocol (Agriculture-Agriculture Interface). It distributes an ALI value received via a socket to one of four adapter outputs, controlled by an index parameter. This block is typically used in agricultural control applications to selectively route signals to different downstream components.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Sets the index `K` and starts the demultiplexing operation. |

### **Event Outputs**

| Event | Description |
|----------|-------------|
| `CNF` | Confirmation that the selected output has been supplied with the input value. |

### **Data Inputs**

| Variable | Type | Description |
|----------|--------|-------------|
| `K` | UINT | Index of the desired output (1 to 4 for OUT1 to OUT4). Values outside this range have no defined behavior. |

### **Data Outputs**

*None declared.* The output data is transmitted via the adapter interfaces.

### **Adapters**

| Type | Name | Direction | Description |
|-----|-------------|----------|-------------|
Socket | `IN` | Input | Incoming ALI values (e.g., measurement data or control commands). |
Plug | `OUT1` | Output | First output (Index 1). |
Plug | `OUT2` | Output | Second output (Index 2). |
Plug | `OUT3` | Output | Third output (Index 3). |
Plug | `OUT4` | Output | Fourth output (Index 4). |

All adapters are of type `adapter::types::unidirectional::ALI` (unidirectional, data-flowing).

## Functionality

1. In idle mode, the FB waits for a `REQ` event.

2. Upon arrival of `REQ`, the current value of the data input `K` is read.

3. The ALI adapter value received via socket `IN` is transferred to the plug with the corresponding number (`OUT1` … `OUT4`).

4. After successful transfer, the event `CNF` is sent, confirming the execution.

5. The function block remains ready for the next `REQ` call.

## Technical Features
- **Generic Extension:** The function block is declared as a generic type (attribute `GenericClassName = 'GEN_ALI_DEMUX'`). More specific variants for different ALI adapter subtypes can be created using type hashing without changing the underlying demultiplex logic.
- **Simple Index Control:** The index `K` is implemented as `UINT` and covers the values 1 to 4. The assignment is done directly via the plug numbering.
- **Adapter-Based:** All data transmission occurs via ALI adapters, allowing the function block to be integrated into existing ALI communication environments.

## State Overview

The ALI_DEMUX_4 function block has an implicit, event-driven sequence:

- **IDLE** (Wait State): The function block performs no operation; no `REQ` is present.
- **EXEC** (Execution): Upon receipt of `REQ`, the demultiplexing process is started. In this state, the index is evaluated and the adapter forwarding is performed.
- **DONE** (Completion): The transfer is complete, and `CNF` is output. The function block then returns to the IDLE state.

A detailed state machine is not explicitly modeled because the function block operates purely event-driven.

## Application Scenarios
- **Signal Distribution in Agricultural Engineering:** A sensor delivers a measured value (e.g., soil temperature, humidity) via the `IN` adapter. Depending on the index, this value is forwarded to one of four actuators or higher-level control blocks.
- **Radio or Fieldbus Selection:** In a machine with multiple parallel communication channels, the FB can be used to route an incoming ALI packet specifically to the correct processing module.
- **Test and Simulation Environments:** By switching the index, different output paths can be quickly changed without rewiring the data flow.

## Comparison with Similar Modules

| Criterion | ALI_DEMUX_4 | Standard Demultiplexer (e.g., DEMUX_4) |
|-----------|-------------|----------------------------------------|
| Interface | Adapter-based (ALI protocol) | Mostly simple data I/O (BOOL, INT) |
| Flexibility | Generic type with hash | Fixed data type |
| Complexity | Low – simple forwarding | Similar, but without adapter coupling |
| Application | Specifically for ALI-enabled systems | General control engineering |

The ALI_DEMUX_4 is specifically optimized for the ALI adapter interface and therefore offers seamless integration into ALI-based applications.

## Conclusion

The **ALI_DEMUX_4** function block provides a simple and effective way to distribute an incoming ALI signal stream to four outputs. It is characterized by its generic design, clear interfaces, and ease of use. Thanks to its adapter architecture, it is particularly suitable for use in agricultural control systems with the ALI protocol and contributes to a clean structuring of the data flow.
