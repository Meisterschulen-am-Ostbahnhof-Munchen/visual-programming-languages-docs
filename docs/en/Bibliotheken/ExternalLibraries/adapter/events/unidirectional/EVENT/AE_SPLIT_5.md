# AE_SPLIT_5

![AE_SPLIT_5](./AE_SPLIT_5.svg)

* * * * * * * * * *

## Introduction

The function block **AE_SPLIT_5** is used to duplicate an incoming adapter event. It receives an adapter event (AE) at its socket `IN` and forwards it identically to five separate output plugs (`OUT1` … `OUT5`). The block is implemented as a generic FB (GenericClassName `'GEN_AE_SPLIT'`), thus enabling easy reuse in different contexts.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |
| ---------- | ------ | ----- | -------------- |
| Socket (Input) | `IN` | `adapter::types::unidirectional::AE` | A unidirectional adapter event whose content is forwarded to all outputs. |
| Plug (Output 1) | `OUT1` | `adapter::types::unidirectional::AE` | First output that provides the incoming event. |
| Plug (Output 2) | `OUT2` | `adapter::types::unidirectional::AE` | Second output providing the incoming event. |
| Plug (Output 3) | `OUT3` | `adapter::types::unidirectional::AE` | Third output providing the incoming event. |
| Plug (Output 4) | `OUT4` | `adapter::types::unidirectional::AE` | Fourth output providing the incoming event. |
| Plug (Output 5) | `OUT5` | `adapter::types::unidirectional::AE` | Fifth output providing the incoming event. |

## Functionality

The FB **AE_SPLIT_5** is a pure distribution block. As soon as an adapter event arrives at socket `IN`, this event is sent – without delay or data manipulation – in parallel to all five output plugs `OUT1` to `OUT5`. No internal storage or state modification occurs; the function block (FB) is entirely combinatorial.

## Technical Features

- **Generic Implementation**: The function block is declared as a generic FB (`GenericClassName = 'GEN_AE_SPLIT'`), so it can be used with different adapter types if needed, provided they are of type `adapter::types::unidirectional::AE`.
- **Unidirectionality**: All adapters involved are unidirectional. There is no communication back to the sender.
- **No Additional Logic**: The FB has neither event nor data inputs/outputs. The forwarding is done entirely via adapters.

## State Overview

This function block has no defined state machine or sequence control. Its behavior is static: Upon receiving an event at `IN`, all outputs are activated simultaneously. There is no latency or intermediate states.

## Application Scenarios

- **Event Distribution in Control Systems**: A sensor event (e.g., "Position Reached") is to be sent to multiple independent control components.
- **Multicast in Modular Architectures**: In a distributed automation environment, a central function block can distribute its event to up to five downstream modules.
- **Prototyping and Test Environments**: For simultaneously testing multiple receivers with the same event.

## Comparison with Similar Function Blocks

- **Event Splitter (E_SPLIT)**: These function blocks distribute **events** (event inputs) to multiple event outputs. **AE_SPLIT_5**, on the other hand, distributes **adapter events** (complex data objects that communicate via adapters), thus offering a higher level of abstraction.
- **Data Splitter (F_SPLIT)**: Splits data streams but does not have an adapter interface. **AE_SPLIT_5** focuses on distributing adapter-based event messages.

## Conclusion

The **AE_SPLIT_5** is a simple yet effective component for replicating a unidirectional adapter event to five outputs. Due to its generic nature and its pure adapter interface, it is particularly suitable for modular and scalable control applications where information needs to be sent to multiple receivers in parallel.
