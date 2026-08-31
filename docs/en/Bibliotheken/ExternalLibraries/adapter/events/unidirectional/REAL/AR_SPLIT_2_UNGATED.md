# AR_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AR_SPLIT_2`](AR_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AR_SPLIT_2_UNGATED](./AR_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The **AR_SPLIT_2_UNGATED** is a generic function block that splits an incoming adapter of type `adapter::types::unidirectional::AR` into two separate outputs (OUT1, OUT2). It serves to forward a signal to two subsequent function blocks without modifying the data. The function block is implemented as a generic type (`GEN_AR_SPLIT`) and is parameterized at runtime.

## Interface Structure

### **Event Inputs**

No event inputs available.

#### **Event Outputs**

No event outputs available.

#### **Data Inputs**

No data inputs available.

#### **Data Outputs**

No data outputs available.

### **Adapter**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AR` | IN | Socket | Input signal (AR) |
| `adapter::types::unidirectional::AR` | OUT1 | Plug | First output (identical to IN) |
| `adapter::types::unidirectional::AR` | OUT2 | Plug | Second output (identical to IN) |

## Functionality

This module forwards the AR signal present at socket **IN** unchanged to both plugs **OUT1** and **OUT2**. No data manipulation, filtering, or delay occurs. The distribution is purely structural: Each output receives its own copy of the reference to the underlying AR object.

## Technical Features

- **Generic Implementation**: The function block uses the generic class name attribute (`eclipse4diac::core::GenericClassName`) with the value `'GEN_AR_SPLIT'`, allowing for application-specific configuration.
- **Unidirectional Adapters**: All adapters are of type `adapter::types::unidirectional::AR` (forward direction only).
- **No State Automation**: The function block does not have an explicit ECC (Execution Control Chart); signal routing is direct and event-independent.

## State Overview

The function block does not implement state automation. Its functionality is limited to passively routing the input signal to both outputs. Therefore, state visualization is not required.

## Application Scenarios

- **Signal Distribution**: Splitting an AR-based sensor signal to two parallel-operating control components.
- **Redundancy**: Providing the same AR data stream for a primary and a redundant system.
- **Debugging**: Connecting an analysis or logging module in parallel to the existing path without interrupting the original signal chain.

## Comparison with Similar Modules

Modules such as `AR_SPLIT_3` or `AR_SPLIT_N` offer similar functionality, distributing a signal to three or N outputs, respectively. The choice depends on the required number of outputs. Cascading multiple `AR_SPLIT_2_UNGATED` instances is also possible, but increases complexity compared to a dedicated multi-output splitter.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **AR_SPLIT_2_UNGATED** is a simple yet essential module for multiplying an AR signal in IEC 61499-based control systems. Its generic design and clear interface make it the first choice when a signal needs to be passed between two independent target components.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
