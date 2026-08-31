# AQ_OR_10_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AQ_OR_10`](AQ_OR_10.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AQ_OR_10_UNGATED](./AQ_OR_10_UNGATED.svg)

* * * * * * * * * *

## Introduction

**AQ_OR_10_UNGATED** is a generic function block for the bitwise OR operation across 10 input values of type `BYTE` (2-bit value (quarter byte, transmitted as a byte)). Unlike the Boolean operation on single truth values (as in the `AX_OR` blocks), every bit of the data word is combined independently here.

## Interface Structure

### **Event Inputs**

No event inputs available

### **Event Outputs**

No event outputs available

### **Data Inputs**

No direct data inputs available

### **Data Outputs**

No direct data outputs available

### **Adapters**

**Input Adapters:**

- **IN1**: OR input 1 (Type: adapter::types::unidirectional::AQ)
- **IN2**: OR input 2 (Type: adapter::types::unidirectional::AQ)
- **IN3**: OR input 3 (Type: adapter::types::unidirectional::AQ)
- **IN4**: OR input 4 (Type: adapter::types::unidirectional::AQ)
- **IN5**: OR input 5 (Type: adapter::types::unidirectional::AQ)
- **IN6**: OR input 6 (Type: adapter::types::unidirectional::AQ)
- **IN7**: OR input 7 (Type: adapter::types::unidirectional::AQ)
- **IN8**: OR input 8 (Type: adapter::types::unidirectional::AQ)
- **IN9**: OR input 9 (Type: adapter::types::unidirectional::AQ)
- **IN10**: OR input 10 (Type: adapter::types::unidirectional::AQ)

**Output Adapter:**

- **OUT**: OR result (Type: adapter::types::unidirectional::AQ)

## Functionality

As soon as an event arrives at one of the 10 input adapters (`IN1` … `IN10`), the block combines the bit patterns of all 10 inputs bitwise using **OR** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits cleared / 0 (identity element of the OR operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AQ_OR`) and covers all arities (2 to 10 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_OR` blocks, every bit of the `BYTE` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AQ` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AQ_OR_10_UNGATED has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `BYTE` into a single result.
- **Signal aggregation**: Merging multiple `BYTE` data sources (e.g., from different modules) via a shared OR operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_OR_10`, which combines individual Boolean truth values, `AQ_OR_10_UNGATED` operates on the full bit pattern of a `BYTE` value. Compared to the standard block [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md), `AQ_OR_10_UNGATED` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

- **[`AQ_OR_10`](AQ_OR_10.md)**: The gated variant – updates the output only on an actual value change.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

**AQ_OR_10_UNGATED** offers a reliable, generic implementation of the bitwise OR function for `BYTE` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
