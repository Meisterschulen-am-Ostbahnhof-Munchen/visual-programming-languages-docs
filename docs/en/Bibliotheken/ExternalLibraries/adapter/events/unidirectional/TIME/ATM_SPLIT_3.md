# ATM_SPLIT_3

![ATM_SPLIT_3](./ATM_SPLIT_3.svg)

* * * * * * * * * *
## Introduction

The **ATM_SPLIT_3** is a generic function block that splits an incoming adapter of type `adapter::types::unidirectional::ATM` into 3 separate outputs (OUT1, OUT2, OUT3). It serves to forward a time signal to 3 subsequent function blocks without modifying the data. The function block is implemented as a generic type (`GEN_ATM_SPLIT`) and is parameterized at runtime.
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
|-----|------|----------|--------------|
| `adapter::types::unidirectional::ATM` | IN | Socket | Input signal (ATM) |
| `adapter::types::unidirectional::ATM` | OUT1 | Plug | Output 1 (identical to IN) |
| `adapter::types::unidirectional::ATM` | OUT2 | Plug | Output 2 (identical to IN) |
| `adapter::types::unidirectional::ATM` | OUT3 | Plug | Output 3 (identical to IN) |

## Functionality

This block forwards the ATM signal present at socket **IN** unchanged to all 3 plugs (OUT1, OUT2, OUT3). No data manipulation, filtering, or delay occurs. The distribution is purely structural: each output receives its own copy of the reference to the underlying time value.

## Technical Features

- **Generic Implementation**: The function block uses the generic class name attribute (`eclipse4diac::core::GenericClassName`) with the value `'GEN_ATM_SPLIT'`, so the same class covers the arities `ATM_SPLIT_2`, `ATM_SPLIT_3`, and `ATM_SPLIT_4` via the GenericClassName mechanism.
- **Unidirectional Adapters**: All adapters are of type `adapter::types::unidirectional::ATM` (forward direction only).
- **No State Automation**: The function block does not have an explicit ECC (Execution Control Chart); signal routing is direct and event-independent.

## State Overview

The function block does not implement state automation. Its functionality is limited to passively routing the input signal to all 3 outputs. Therefore, state visualization is not required.

## Application Scenarios

- **Signal Distribution**: Splitting an ATM-based time signal (e.g., a delay duration) to multiple parallel-operating control components.
- **Redundancy**: Providing the same time value for a primary and a redundant system.
- **Debugging**: Connecting an analysis or logging module in parallel to the existing path without interrupting the original signal chain.

## Comparison with Similar Function Blocks

Similar functionality is offered by the other arities `ATM_SPLIT_2`/`ATM_SPLIT_3`/`ATM_SPLIT_4`, as well as the structurally identical `AR_SPLIT_3` for the `REAL` data type. The choice of arity depends on the required number of outputs.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.

## Conclusion

The **ATM_SPLIT_3** is a simple yet essential module for multiplying a time signal in IEC 61499-based control systems. Its generic design and clear interface make it the first choice when a time value needs to be passed to multiple independent target components.
