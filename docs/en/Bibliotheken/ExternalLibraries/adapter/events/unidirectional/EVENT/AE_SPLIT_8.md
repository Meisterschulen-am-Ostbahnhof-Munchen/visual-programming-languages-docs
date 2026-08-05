# AE_SPLIT_8
![AE_SPLIT_8](./AE_SPLIT_8.svg)
*Image of the function block: [Insert here if available]*

* * * * * * * * * *
## Introduction
The function block **AE_SPLIT_8** serves as a generic distributor for one unidirectional adapter input (AE) to eight identical adapter outputs. It allows the multiple use of an incoming signal without modifying it.

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
|----------|-----|-----|--------------|
**Socket** | `IN` | `adapter::types::unidirectional::AE` | Incoming unidirectional AE adapter |
**Plug** | `OUT1` | `adapter::types::unidirectional::AE` | First outgoing AE adapter |
**Plug** | `OUT2` | `adapter::types::unidirectional::AE` | Second outgoing AE adapter |
**Plug** | `OUT3` | `adapter::types::unidirectional::AE` | Third Outgoing AE Adapter |
**Plug** | `OUT4` | `adapter::types::unidirectional::AE` | Fourth Outgoing AE Adapter |
**Plug** | `OUT5` | `adapter::types::unidirectional::AE` | Fifth Outgoing AE Adapter |
**Plug** | `OUT6` | `adapter::types::unidirectional::AE` | Sixth Outgoing AE Adapter |
**Plug** | `OUT7` | `adapter::types::unidirectional::AE` | Seventh Outgoing AE Adapter |
**Plug** | `OUT8` | `adapter::types::unidirectional::AE` | Eighth Outgoing AE Adapter |

## Functionality
This function block forwards the adapter signal present at socket `IN` to all eight plugs (`OUT1` to `OUT8`) without delay or modification. No logical or timing processing takes place – the incoming adapter is duplicated one-to-one.

## Technical Features
- **Generic Type**: The function block is defined as a generic function block (`GenericClassName: GEN_AE_SPLIT`) and can be reused in various contexts.
- **Unidirectionality**: Both the input and output adapters are unidirectional. Feedback from the outputs to the input is not possible.
- **No Event Control**: The function block has no event inputs and operates purely passively. Forwarding occurs immediately upon connection establishment.
- **Scalability**: With a fixed number of eight outputs, the function block is optimized for applications requiring a precise 1:8 distribution.

## State Overview
The function block has no internal states or sequence control. There is no ECC (Execution Control Chart) – functionality is purely combinatorial.

## Application Scenarios
- **Signal Distribution in Control Networks**: An AE adapter signal from a sensor or a higher-level controller is to be simultaneously passed on to several downstream function blocks.
- **Test and Simulation Environments**: Multiple receivers are to receive the same adapter signal to observe parallel responses.
- **Redundant Connection**: The same signal can be processed in parallel on multiple paths, for example, for safety or monitoring functions.

## Comparison with Similar Function Blocks
- **AE_SPLIT_2/AE_SPLIT_4**: Function blocks with a smaller number of outputs (2 or 4, respectively) for smaller distributions. **AE_SPLIT_8** extends this to eight outputs.
- **Data Splitters (e.g., SPLIT_INT, SPLIT_BOOL)**: These distribute data values, while **AE_SPLIT_8** distributes adapter signals. Adapters can bundle complex composite interfaces (events and data).
- **Event Splitters (e.g., E_SPLIT)**: Distribute only events. **AE_SPLIT_8** transmits the entire adapter context, including all data and event connections it contains.

## Conclusion
The **AE_SPLIT_8** is a simple and efficient function block for 1:8 distribution of unidirectional adapter signals. Due to its generic nature and the absence of event control, it is particularly suitable for applications where a signal needs to be forwarded to multiple receivers in parallel without delay.
