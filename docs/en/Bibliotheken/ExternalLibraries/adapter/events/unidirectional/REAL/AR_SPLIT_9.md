# AR_SPLIT_9

![AR_SPLIT_9](./AR_SPLIT_9.svg)

* * * * * * * * * *
## Introduction

The function block **AR_SPLIT_9** splits an incoming AR adapter (type `unidirectional`) into nine separate AR outputs. It serves as a distributor for an AR signal to multiple downstream components. The block is designed to be completely generic.
## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapter**

| Direction | Adapter | Type | Description |
|----------|---------|-----|--------------|
| **Socket** (Input) | `IN` | `adapter::types::unidirectional::AR` | Incoming AR signal that is distributed. |
| **Plug** (Output) | `OUT1` … `OUT9` | `adapter::types::unidirectional::AR` | Nine identical outputs that forward the incoming AR signal. |

## Functionality

The module forwards the AR signal present at the **IN** socket unchanged to all nine outputs **OUT1** to **OUT9**. No delay, filtering, or conversion takes place. Signal propagation is purely combinatorial.

## Technical Features

- **Generic Function Block**: The function block uses a generic class name attribute (`eclipse4diac::core::GenericClassName` with the value `'GEN_AR_SPLIT'`) and a type hash attribute to enable flexible type adaptation in the IEC 61499 model.
- **Unidirectional Adapters**: Both the input and all outputs are defined as unidirectional AR adapters. Feedback or bidirectional communication is not provided.
- **No Events or Data**: All logic is handled exclusively via adapter interfaces – there are no event or data inputs/outputs.

## State Overview

The function block has no internal state (no state machine). The output signal corresponds to the current input signal at any given time. There are no initialization or error states.

## Application Scenarios

- **Distribution of a Start/Stop Signal**: A central AR command (e.g., "Start") is distributed to multiple actuators or machine parts.
- **Multicast Coupling**: An AR signal originating from a higher-level controller is simultaneously sent to multiple subordinate modules.
- **Parallel Control** of nine identical or different components using the same AR protocol.

## Comparison with Similar Function Blocks

| Function Block | Number of Outputs | Remarks |
|----------|------------------|-----------|
| `AR_SPLIT_4` | 4 | Same functionality, but only four outputs. |
| `AR_SPLIT_9` | 9 | Presented function block (nine outputs). |
| `AR_SPLIT_2` | 2 | Minimal splitter for two paths. |

The function blocks differ only in the number of outputs; the functionality and generic properties are identical.

## Conclusion

The **AR_SPLIT_9** is a simple yet useful splitter function block for unidirectional AR signals. Due to its generic design, it can be flexibly used in different control architectures without requiring manual type adaptation. It is particularly suitable for scenarios where a signal needs to be duplicated to multiple paths simultaneously.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
