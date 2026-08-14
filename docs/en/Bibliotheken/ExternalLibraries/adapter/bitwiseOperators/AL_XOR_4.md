# AL_XOR_4

![AL_XOR_4](./AL_XOR_4.svg)

* * * * * * * * * *
## Introduction

**AL_XOR_4** is a generic function block for the bitwise XOR (exclusive OR) operation across 4 input values of type `LWORD` (64-bit bit pattern (long word)). Unlike the Boolean operation on single truth values (as in the `AX_XOR` blocks), every bit of the data word is combined independently here.

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

- **IN1**: XOR (exclusive OR) input 1 (Type: adapter::types::unidirectional::AL)
- **IN2**: XOR (exclusive OR) input 2 (Type: adapter::types::unidirectional::AL)
- **IN3**: XOR (exclusive OR) input 3 (Type: adapter::types::unidirectional::AL)
- **IN4**: XOR (exclusive OR) input 4 (Type: adapter::types::unidirectional::AL)

**Output Adapter:**

- **OUT**: XOR (exclusive OR) result (Type: adapter::types::unidirectional::AL)

## Functionality

As soon as an event arrives at one of the 4 input adapters (`IN1` … `IN4`), the block combines the bit patterns of all 4 inputs bitwise using **XOR (exclusive OR)** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits cleared / 0 (identity element of the XOR operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AL_XOR`) and covers all arities (2 to 8 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_XOR` blocks, every bit of the `LWORD` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AL` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AL_XOR_4 has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `LWORD` into a single result.
- **Signal aggregation**: Merging multiple `LWORD` data sources (e.g., from different modules) via a shared XOR (exclusive OR) operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_XOR_4`, which combines individual Boolean truth values, `AL_XOR_4` operates on the full bit pattern of a `LWORD` value. Compared to the standard block [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md), `AL_XOR_4` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.

## Conclusion

**AL_XOR_4** offers a reliable, generic implementation of the bitwise XOR (exclusive OR) function for `LWORD` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
