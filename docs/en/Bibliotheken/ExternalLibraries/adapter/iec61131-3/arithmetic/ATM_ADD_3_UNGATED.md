# ATM_ADD_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ATM_ADD_3`](ATM_ADD_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ATM_ADD_3_UNGATED](./ATM_ADD_3_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block **ATM_ADD_3_UNGATED** is used to calculate the arithmetic addition of two time values (type `TIME`). It is designed as a generic function block and implements the basic arithmetic operation via adapter interfaces. The block is platform-independent and complies with the IEC 61499 standard.

## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapters**

| Name | Direction | Type | Comment |
| ------------- | ---------- | ----- | ----------- |
| `IN1` | Socket | `adapter::types::unidirectional::ATM` | ADD input 1 |
| `IN2` | Socket | `adapter::types::unidirectional::ATM` | ADD input 2 |
| `IN3` | Socket | `adapter::types::unidirectional::ATM` | ADD input 3 |
| `OUT` | Plug | `adapter::types::unidirectional::ATM` | ADD result |

The adapters are of type `unidirectional::ATM` and enable type-safe connections with other function blocks that support the same adapter type.

## Functionality

The function block sums the time values received via adapters `IN1` and `IN2` and provides the result at adapter `OUT`. The starting point of the summation is the identity value `TIME#0s`, so that with only one input actually connected, its value is passed through unchanged. The function block operates generically – the calculation is re-executed on every event at one of the input adapters.

## Technical Features

- **Generic Structure** – The function block uses a generic class name (`GEN_ATM_ADD`) at runtime, defined by the attribute `eclipse4diac::core::GenericClassName`. The same class covers the arities `ATM_ADD_3_UNGATED`, `ATM_ADD_3_UNGATED`, and `ATM_ADD_4` via the GenericClassName mechanism.
- **Adapter-Based** – Instead of individual data inputs and outputs, all signals are routed via unidirectional adapters.
- **Package Information** – The function block is organized in the package `adapter::iec61131::arithmetic`.
- **No State Logic** – The addition is stateless; there is no internal state machine.

## State Overview

The function block does not have a state machine. The calculation is purely event-driven – on any event at one of the input adapters, the sum is recalculated.

## Application-Specific Scenarios

- **Time accumulation** – Summing multiple delay or runtime values into a total duration.
- **Control Engineering** – Combining two dynamically determined time values, e.g., base time plus a surcharge.
- **Generic Library Function Blocks** – Use as the adapter-based counterpart to the classic `ADD` function, specialized for `TIME`.

## Comparison with Similar Function Blocks

Compared to `AR_ADD_2` (addition of two `REAL` values via adapters), `ATM_ADD_3_UNGATED` is specialized for the `TIME` data type. Unlike `AR_MULTIME`/`ATM_AR_MULTIME`, which multiply a time value by a numeric factor, `ATM_ADD_3_UNGATED` adds two values of the same kind.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

`ATM_ADD_3_UNGATED` is a compact, generic function block for adding two time values using adapter interfaces. It is particularly suitable for applications where multiple durations need to be combined into a total duration.
