# AQ_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AQ_SPLIT_2`](AQ_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AQ_SPLIT_2_UNGATED](./AQ_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `AQ_SPLIT_2_UNGATED` serves as a fan-out block. It distributes an incoming AQ (Analog Quantity) signal unidirectionally to two identical outputs. It thus implements a simple 1:2 signal multiplication for analog quantities.

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

| Type | Name | Direction | Description |
| ------ | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AQ` | `IN` | Socket (Input) | Input adapter for the AQ signal to be split. |
| `adapter::types::unidirectional::AQ` | `OUT1` | Plug (Output) | First output – provides the unaltered input signal. |
| `adapter::types::unidirectional::AQ` | `OUT2` | Plug (Output) | Second output – also provides the unaltered input signal. |

## Functionality

The module receives an analog signal via the adapter socket `IN`. This signal is passed internally without delay or conversion to both adapter plugs `OUT1` and `OUT2`. No signal processing takes place – the function block acts purely as a splitter.

## Technical Features

- **Generic Implementation**: The function block is declared as the generic type `GEN_AQ_SPLIT` and can be used with any AQ adapter, as long as it conforms to the unidirectional AQ interface.
- **No Event Control**: The function block operates purely data-driven without events – a change in state at the input immediately affects both outputs.
- **Unidirectional**: The adapters are designed for one direction only (input → outputs).

## State Overview

The function block has no internal states. It is stateless (combinatory) and outputs the currently present input signal at both outputs at any given time.

## Application Scenarios

- **Signal Distribution** in Control Systems: An analog signal provided by a sensor is to be passed on in parallel to two different devices (e.g., two controllers or display units).
- **Test and Simulation Setups**: A reference signal is split across multiple test points without affecting the signal flow.
- **Redundant Transmission**: The signal is sent to two independent paths to increase reliability.

## Comparison with Similar Components

- **`AQ_SPLIT_N`** (hypothetical): A comparable component with outputs like `N` – `AQ_SPLIT_2_UNGATED` is a specialized 1:2 version.
- **Event-Driven Split Components**: These often require trigger events and then perform signal transmission. In contrast, `AQ_SPLIT_2_UNGATED` operates purely signal-driven without events.
- **Bus-based splitters**: These distribute multiple signals over a shared bus (e.g., via multicast). `AQ_SPLIT_2_UNGATED` operates selectively and individually via adapters.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AQ_SPLIT_2_UNGATED` is a simple yet useful component for distributing an analog signal to two identical outputs. Thanks to its generic nature, it can be used in various 4diac projects without modification. Its stateless operation minimizes complexity and makes it ideal for real-time applications requiring immediate signal transmission.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
