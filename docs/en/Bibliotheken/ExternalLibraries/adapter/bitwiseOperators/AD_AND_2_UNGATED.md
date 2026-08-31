# AD_AND_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AD_AND_2`](AD_AND_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AD_AND_2_UNGATED](./AD_AND_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

**AD_AND_2_UNGATED** is a generic function block for the bitwise AND operation across 2 input values of type `DWORD` (32-bit bit pattern (double word)). Unlike the Boolean operation on single truth values (as in the `AX_AND` blocks), every bit of the data word is combined independently here.

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

- **IN1**: AND input 1 (Type: adapter::types::unidirectional::AD)
- **IN2**: AND input 2 (Type: adapter::types::unidirectional::AD)

**Output Adapter:**

- **OUT**: AND result (Type: adapter::types::unidirectional::AD)

## Functionality

As soon as an event arrives at one of the 2 input adapters (`IN1` … `IN2`), the block combines the bit patterns of all 2 inputs bitwise using **AND** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits set (identity element of the AND operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AD_AND`) and covers all arities (2 to 4 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_AND` blocks, every bit of the `DWORD` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AD` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AD_AND_2_UNGATED has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `DWORD` into a single result.
- **Signal aggregation**: Merging multiple `DWORD` data sources (e.g., from different modules) via a shared AND operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_AND_2`, which combines individual Boolean truth values, `AD_AND_2_UNGATED` operates on the full bit pattern of a `DWORD` value. Compared to the standard block [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md), `AD_AND_2_UNGATED` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

- **[`AD_AND_2`](AD_AND_2.md)**: The gated variant – updates the output only on an actual value change.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

**AD_AND_2_UNGATED** offers a reliable, generic implementation of the bitwise AND function for `DWORD` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
