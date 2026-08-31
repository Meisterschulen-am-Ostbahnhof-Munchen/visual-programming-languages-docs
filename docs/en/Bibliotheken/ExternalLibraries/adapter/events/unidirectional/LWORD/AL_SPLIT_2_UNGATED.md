# AL_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AL_SPLIT_2`](AL_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AL_SPLIT_2_UNGATED](./AL_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **AL_SPLIT_2_UNGATED** is used to split an incoming unidirectional adapter signal into two identical outputs. It is designed as a generic function block, so the specific adapter type is only determined during use.

## Interface Structure

### **Event Inputs**

*None*

### **Event Outputs**

*None*

### **Data Inputs**

*None*

### **Data Outputs**

*None*

### **Adapter**

| Type | Direction | Name | Description |
| ----- | ---------- | ------ | -------------- |
| `adapter::types::unidirectional::AL` | **Socket** (Input) | `IN` | Input signal distributed to both outputs |
| `adapter::types::unidirectional::AL` | **Plug** (Output) | `OUT1` | First output with the same adapter signal as `IN` |
| `adapter::types::unidirectional::AL` | **Plug** (Output) | `OUT2` | Second output with the same adapter signal as `IN` |

## Functionality

The function block forwards the unidirectional adapter signal present at socket `IN` unchanged to both plugs `OUT1` and `OUT2`. No data processing or transformation takes place – the function block operates purely passively and by passing the signal through. As soon as a signal is present at the input, it is simultaneously available at both outputs.

## Technical Features

- **Generic Type**: The function block is defined as a generic function block (attributes `GenericClassName` and `TypeHash`). This allows it to be used with different unidirectional adapter instances without requiring any modifications to the source code.
- **Adapters instead of Data Points**: Signal transmission occurs exclusively via adapters, not via discrete event or data inputs/outputs. This enables structured and reusable encapsulation of communication interfaces.
- **No State Dependency**: The function block has no internal memory and no state machine. The output signals follow the input signal directly.

## State Overview

The function block does not have its own state management. It can be considered a **combinatorial** block where the outputs are always assigned the current input value. There is no explicit state machine.

## Application Scenarios

- **Signal Distribution**: When an adapter signal needs to be passed from one source to multiple independent receivers (e.g., a control command to two actuators).
- **Logging / Monitoring**: An adapter signal can be split into a path for actual processing and simultaneously into a monitoring or logging path.
- **Modular Architectures**: In complex systems that use adapters, the `AL_SPLIT_2_UNGATED` simplifies the topological distribution of signals without requiring manual connections or duplicates.

## Comparison with Similar Components

The 4diac IDE offers various splitter components for different signal types:

| Component | Signal Type | Outputs | Special Feature |
| ---------- | ----------- | ----------- | ------------- |
| `AL_SPLIT_2_UNGATED` | Adapter (unidirectional) | 2 | Generic, no data/events |
| `SPLIT` | Events | 2 | Distributes events without data |
| `E_SPLIT` | Events (with data) | 2 | Distributes events along with accompanying data |
| `F_SPLIT` | Data (any type) | n | Distributes a data value to multiple outputs |

The `AL_SPLIT_2_UNGATED` is specifically optimized for adapter interfaces, providing a clean way to split complex, adapter-based connections without interfering with the data or event layer.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AL_SPLIT_2_UNGATED` is a simple yet useful generic function block for splitting unidirectional adapter signals. It enables flexible and structured signal distribution in modular automation solutions without additional logic or state dependencies. Its generic nature makes it universally applicable.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
