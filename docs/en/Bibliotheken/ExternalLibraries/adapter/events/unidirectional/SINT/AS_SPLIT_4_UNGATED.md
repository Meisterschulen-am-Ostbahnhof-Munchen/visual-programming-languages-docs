# AS_SPLIT_4_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AS_SPLIT_4`](AS_SPLIT_4.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AS_SPLIT_4_UNGATED](./AS_SPLIT_4_UNGATED.svg)
*No image available.*

* * * * * * * * * *

## Introduction

The function block **AS_SPLIT_4_UNGATED** splits an incoming unidirectional AS adapter into four identical outputs. It acts as a generic splitter, forwarding the signal received via socket `IN` unchanged to the four plugs `OUT1` to `OUT4`.

## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AS` | IN | Socket | Incoming AS signal path (input) |
| `adapter::types::unidirectional::AS` | OUT1 | Plug | First output (identical to IN) |
| `adapter::types::unidirectional::AS` | OUT2 | Plug | Second output (identical to IN) |
| `adapter::types::unidirectional::AS` | OUT3 | Plug | Third output (identical to IN) |
| `adapter::types::unidirectional::AS` | OUT4 | Plug | Fourth output (identical to IN) |

## Functionality

The function block (FB) operates purely passively: Every signal received via the `IN` adapter is forwarded to all four plugs (`OUT1`–`OUT4`) without delay or transformation. No data buffering, logical processing, or state changes occur. Distribution is deterministic and takes place at compile time or runtime according to the adapter contracts.

## Technical Features

- **No Event/Data Interfaces:** All communication occurs exclusively via adapters.
- **Uniform Type:** All five adapters are of the same unidirectional type, `AS`.
- **Generic Parameterization:** The function block (FB) has the attributes `GenericClassName` (value: `'GEN_AS_SPLIT'`) and `TypeHash`, allowing it to be adapted to specific applications (e.g., through refactoring or model transformation).
- **Stateless:** No ECC, no internal variables – the behavior is completely defined by the adapter contracts.

## State Overview

The FB has no state machines. Its behavior is timeless and constant: The input signal is always immediately duplicated to all outputs.

## Application Scenarios

- **Signal Distribution in Controllers:** Distributing a speed or position command across multiple parallel axes.
- **Sensor Value Multiplexing:** Distributing a measured value to multiple evaluation or monitoring instances.
- **Modular Connection:** Used in hierarchical systems where an adapter signal is needed multiple times without instantiating the sender multiple times.

## Comparison with Similar Components

- **AS_MERGE:** Combines multiple AS inputs into one output – the functional counterpart to Split.
- **AS_SPLIT_2:** Same functionality, but only two outputs. `AS_SPLIT_4_UNGATED` extends this to four.
- **Event-Based Splitters (e.g., E_SPLIT):** Work with event and data inputs/outputs and distribute events. `AS_SPLIT_4_UNGATED`, on the other hand, operates at the adapter level and forwards the entire adapter contract (including all events and data contained within it).

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

AS_SPLIT_4_UNGATED` is a simple yet essential building block for structurally replicating unidirectional AS adapter connections in 4diac applications. Its generic design and pure adapter interface make it ideal for modular and scalable control architectures.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
