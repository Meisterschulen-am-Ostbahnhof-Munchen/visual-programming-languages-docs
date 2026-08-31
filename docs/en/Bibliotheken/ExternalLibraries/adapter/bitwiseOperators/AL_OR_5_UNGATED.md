# AL_OR_5_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AL_OR_5`](AL_OR_5.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AL_OR_5_UNGATED](./AL_OR_5_UNGATED.svg)

* * * * * * * * * *

## Introduction

**AL_OR_5_UNGATED** is a generic function block for the bitwise OR operation across 5 input values of type `LWORD` (64-bit bit pattern (long word)). Unlike the Boolean operation on single truth values (as in the `AX_OR` blocks), every bit of the data word is combined independently here.

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

- **IN1**: OR input 1 (Type: adapter::types::unidirectional::AL)
- **IN2**: OR input 2 (Type: adapter::types::unidirectional::AL)
- **IN3**: OR input 3 (Type: adapter::types::unidirectional::AL)
- **IN4**: OR input 4 (Type: adapter::types::unidirectional::AL)
- **IN5**: OR input 5 (Type: adapter::types::unidirectional::AL)

**Output Adapter:**

- **OUT**: OR result (Type: adapter::types::unidirectional::AL)

## Functionality

As soon as an event arrives at one of the 5 input adapters (`IN1` … `IN5`), the block combines the bit patterns of all 5 inputs bitwise using **OR** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits cleared / 0 (identity element of the OR operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AL_OR`) and covers all arities (2 to 10 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_OR` blocks, every bit of the `LWORD` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AL` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AL_OR_5_UNGATED has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `LWORD` into a single result.
- **Signal aggregation**: Merging multiple `LWORD` data sources (e.g., from different modules) via a shared OR operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_OR_5`, which combines individual Boolean truth values, `AL_OR_5_UNGATED` operates on the full bit pattern of a `LWORD` value. Compared to the standard block [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md), `AL_OR_5_UNGATED` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

- **[`AL_OR_5`](AL_OR_5.md)**: The gated variant – updates the output only on an actual value change.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

**AL_OR_5_UNGATED** offers a reliable, generic implementation of the bitwise OR function for `LWORD` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
