# AB_AND_4

![AB_AND_4](./AB_AND_4.svg)

* * * * * * * * * *

## Introduction

**AB_AND_4** is a generic function block for the bitwise AND operation across 4 input values of type `BYTE` (8-bit bit pattern (byte)). Unlike the Boolean operation on single truth values (as in the `AX_AND` blocks), every bit of the data word is combined independently here.

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

- **IN1**: AND input 1 (Type: adapter::types::unidirectional::AB)
- **IN2**: AND input 2 (Type: adapter::types::unidirectional::AB)
- **IN3**: AND input 3 (Type: adapter::types::unidirectional::AB)
- **IN4**: AND input 4 (Type: adapter::types::unidirectional::AB)

**Output Adapter:**

- **OUT**: AND result (Type: adapter::types::unidirectional::AB)

## Functionality

As soon as an event arrives at one of the 4 input adapters (`IN1` … `IN4`), the block combines the bit patterns of all 4 inputs bitwise using **AND** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits set (identity element of the AND operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AB_AND`) and covers all arities (2 to 4 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_AND` blocks, every bit of the `BYTE` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AB` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AB_AND_4 has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `BYTE` into a single result.
- **Signal aggregation**: Merging multiple `BYTE` data sources (e.g., from different modules) via a shared AND operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_AND_4`, which combines individual Boolean truth values, `AB_AND_4` operates on the full bit pattern of a `BYTE` value. Compared to the standard block [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md), `AB_AND_4` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.

## Conclusion

**AB_AND_4** offers a reliable, generic implementation of the bitwise AND function for `BYTE` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
