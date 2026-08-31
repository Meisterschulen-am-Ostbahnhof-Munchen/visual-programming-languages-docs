# AD_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AD_SPLIT_2`](AD_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AD_SPLIT_2_UNGATED](./AD_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The AD_SPLIT_2_UNGATED function block is used to split an incoming unidirectional adapter (AD) into two identical output adapters. It is implemented as a generic function block and allows for the simple branching of an adapter signal into two parallel paths.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapter**

| Name | Type | Direction |
| ------ | ----- | ---------- |
| IN | adapter::types::unidirectional::AD | Socket (Input) |
| OUT1 | adapter::types::unidirectional::AD | Plug (Output) |
| OUT2 | adapter::types::unidirectional::AD | Plug (Output) |

## Functionality

The function block receives a unidirectional adapter via socket `IN`. All data and events transmitted via this adapter are passed unchanged to both output adapters `OUT1` and `OUT2`. No processing or filtering takes place – the signals are simply duplicated. The distribution occurs without any time delay and without internal buffering.

## Technical Features

- **Generic Implementation**: The function block uses the generics mechanisms of Eclipse 4diac (`GenericClassName`). This allows the specific adapter type to be parameterized at design time or runtime, as long as it conforms to the adapter schema `unidirectional::AD`.
- **Type purity**: The output adapters are of the same type as the input adapter; no type conversion takes place.
- **No state logic**: The function block has no internal state machine (ECC) and reacts to adapter communication in an event-driven manner.

## State overview

The function block has no explicit states. It operates continuously and immediately forwards each incoming signal to both outputs.

## Application scenarios

- Splitting a sensor data stream to two independent control or monitoring units.
- Parallelizing adapter signals in industrial automation systems (e.g., distributing a fieldbus adapter value across two control loops).
- Test and simulation setups where a signal must be sent to different devices simultaneously.

## Comparison with Similar Function Blocks

- **AD_SPLIT_3, AD_SPLIT_4**: Extensions with multiple outputs, based on the same mechanism.
- **AD_MERGE**: Combines multiple adapter inputs into one output – the inverse function of AD_SPLIT_2_UNGATED.
- **AD_SELECT**: Selects one of several adapter inputs and passes it on, but requires control logic.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The AD_SPLIT_2_UNGATED is a simple yet effective function block for signal distribution in adapter-based architectures. Its generic nature and lack of state logic make it easy to configure and resource-efficient. It is particularly suitable for modular automation projects where an adapter signal needs to be distributed to multiple downstream components.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
