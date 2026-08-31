# ATM_SPLIT_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ATM_SPLIT_3`](ATM_SPLIT_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ATM_SPLIT_3_UNGATED](./ATM_SPLIT_3_UNGATED.svg)

* * * * * * * * * *

## Introduction

The **ATM_SPLIT_3_UNGATED** is a generic function block that splits an incoming adapter of type `adapter::types::unidirectional::ATM` into 3 separate outputs (OUT1, OUT2, OUT3). It serves to forward a time signal to 3 subsequent function blocks without modifying the data. The function block is implemented as a generic type (`GEN_ATM_SPLIT`) and is parameterized at runtime.

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
| `adapter::types::unidirectional::ATM` | IN | Socket | Input signal (ATM) |
| `adapter::types::unidirectional::ATM` | OUT1 | Plug | Output 1 (identical to IN) |
| `adapter::types::unidirectional::ATM` | OUT2 | Plug | Output 2 (identical to IN) |
| `adapter::types::unidirectional::ATM` | OUT3 | Plug | Output 3 (identical to IN) |

## Functionality

This block forwards the ATM signal present at socket **IN** unchanged to all 3 plugs (OUT1, OUT2, OUT3). No data manipulation, filtering, or delay occurs. The distribution is purely structural: each output receives its own copy of the reference to the underlying time value.

## Technical Features

- **Generic Implementation**: The function block uses the generic class name attribute (`eclipse4diac::core::GenericClassName`) with the value `'GEN_ATM_SPLIT'`, so the same class covers the arities `ATM_SPLIT_2`, `ATM_SPLIT_3_UNGATED`, and `ATM_SPLIT_4` via the GenericClassName mechanism.
- **Unidirectional Adapters**: All adapters are of type `adapter::types::unidirectional::ATM` (forward direction only).
- **No State Automation**: The function block does not have an explicit ECC (Execution Control Chart); signal routing is direct and event-independent.

## State Overview

The function block does not implement state automation. Its functionality is limited to passively routing the input signal to all 3 outputs. Therefore, state visualization is not required.

## Application Scenarios

- **Signal Distribution**: Splitting an ATM-based time signal (e.g., a delay duration) to multiple parallel-operating control components.
- **Redundancy**: Providing the same time value for a primary and a redundant system.
- **Debugging**: Connecting an analysis or logging module in parallel to the existing path without interrupting the original signal chain.

## Comparison with Similar Function Blocks

Similar functionality is offered by the other arities `ATM_SPLIT_2`/`ATM_SPLIT_3_UNGATED`/`ATM_SPLIT_4`, as well as the structurally identical `AR_SPLIT_3` for the `REAL` data type. The choice of arity depends on the required number of outputs.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The **ATM_SPLIT_3_UNGATED** is a simple yet essential module for multiplying a time signal in IEC 61499-based control systems. Its generic design and clear interface make it the first choice when a time value needs to be passed to multiple independent target components.
