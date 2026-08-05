# AR_SPLIT_4
![AR_SPLIT_4](./AR_SPLIT_4.svg)

* * * * * * * * * *
## Introduction
The function block **AR_SPLIT_4** is used to split one incoming AR adapter (unidirectional) into four outgoing AR adapters. It is implemented as a generic function block (`GenericClassName = 'GEN_AR_SPLIT'`) and enables simple signal multiplication for adapter-based communication in control systems.
## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

| Name | Type | Comment |
|------|-----|------------|
| (none) | – | – |

### **Data Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| (none) | – | – |

### **Adapter**

| Type | Name | Direction | Description |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AR` | **IN** | Socket (Input) | Incoming AR adapter signal, which is distributed to the four outputs. |
| `adapter::types::unidirectional::AR` | **OUT1** | Plug (Output) | First outgoing AR channel. |
| `adapter::types::unidirectional::AR` | **OUT2** | Plug (Output) | Second outgoing AR channel. |
| `adapter::types::unidirectional::AR` | **OUT3** | Plug (Output) | Third outgoing AR channel. |
| `adapter::types::unidirectional::AR` | **OUT4** | Plug (Output) | Fourth outgoing AR channel. |

## Functionality

The function block receives an AR adapter signal via socket **IN** and forwards it unchanged to all four plugs **OUT1** to **OUT4**. Distribution occurs in parallel – every event or data value received via **IN** is simultaneously available on all outputs. The function block itself does not perform any logical processing or transformation; it functions purely as a splitter for unidirectional AR adapters.

## Technical Features
- **Generic Type**: The function block is defined as a generic function block (`GenericClassName`), which means that the specific AR adapter type is determined at compile time. This increases reusability in various applications.

`` - **No State Machine**: The function block (FB) has no Execution Control Chart (ECC) and no internal states. All operations are purely combinatorial or event-driven.

- **Unidirectional**: The adapter type is specified as unidirectional; feedback from the target block is not provided.

## State Overview

Since the FB has no state machine, no explicit states exist. The behavior is deterministic: An incoming trigger at socket **IN** is immediately forwarded to all outputs.

## Application Scenarios
- **Signal Multiplication**: A control signal (e.g., "Start" or "Reset") should reach several parallel function blocks simultaneously.
- **Monitoring and Parallel Processing**: A measured value or an alarm is distributed to several independent evaluation blocks.
- **Testing and Simulation**: During development, a signal can be recorded or simulated while simultaneously being sent to the actual target block.

## Comparison with Similar Function Blocks
- **AR_SPLIT_2**: Splits an AR signal into two outputs – suitable for smaller distributions.
- **AR_SPLIT_N**: A non-standard, configurable splitter (e.g., via parameters) designed for any number of outputs.
- **AR_MERGE**: Merges multiple AR signals into one – the inverse function of AR_SPLIT_4.

Compared to these alternatives, AR_SPLIT_4 offers a fixed number of four outputs, enabling a compact and clear implementation without configuration overhead.

## Conclusion

The **AR_SPLIT_4** is a simple yet useful generic function block for distributing a unidirectional AR adapter signal across four parallel paths. Due to its streamlined design (no event/data interfaces, no state machine), it is ideally suited for all applications where a signal is needed multiple times without introducing additional logic.
