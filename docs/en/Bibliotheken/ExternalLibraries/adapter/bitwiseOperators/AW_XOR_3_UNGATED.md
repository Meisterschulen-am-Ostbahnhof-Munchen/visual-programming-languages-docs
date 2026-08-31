# AW_XOR_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AW_XOR_3`](AW_XOR_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AW_XOR_3_UNGATED](./AW_XOR_3_UNGATED.svg)

* * * * * * * * * *

## Introduction

**AW_XOR_3_UNGATED** is a generic function block for the bitwise XOR (exclusive OR) operation across 3 input values of type `WORD` (16-bit bit pattern (word)). Unlike the Boolean operation on single truth values (as in the `AX_XOR` blocks), every bit of the data word is combined independently here.

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

- **IN1**: XOR (exclusive OR) input 1 (Type: adapter::types::unidirectional::AW)
- **IN2**: XOR (exclusive OR) input 2 (Type: adapter::types::unidirectional::AW)
- **IN3**: XOR (exclusive OR) input 3 (Type: adapter::types::unidirectional::AW)

**Output Adapter:**

- **OUT**: XOR (exclusive OR) result (Type: adapter::types::unidirectional::AW)

## Functionality

As soon as an event arrives at one of the 3 input adapters (`IN1` … `IN3`), the block combines the bit patterns of all 3 inputs bitwise using **XOR (exclusive OR)** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits cleared / 0 (identity element of the XOR operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AW_XOR`) and covers all arities (2 to 8 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_XOR` blocks, every bit of the `WORD` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AW` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AW_XOR_3_UNGATED has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `WORD` into a single result.
- **Signal aggregation**: Merging multiple `WORD` data sources (e.g., from different modules) via a shared XOR (exclusive OR) operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_XOR_3`, which combines individual Boolean truth values, `AW_XOR_3_UNGATED` operates on the full bit pattern of a `WORD` value. Compared to the standard block [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md), `AW_XOR_3_UNGATED` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

- **[`AW_XOR_3`](AW_XOR_3.md)**: The gated variant – updates the output only on an actual value change.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

**AW_XOR_3_UNGATED** offers a reliable, generic implementation of the bitwise XOR (exclusive OR) function for `WORD` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
