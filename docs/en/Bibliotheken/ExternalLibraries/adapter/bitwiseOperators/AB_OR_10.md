# AB_OR_10

![AB_OR_10](./AB_OR_10.svg)

* * * * * * * * * *

## Introduction

**AB_OR_10** is a generic function block for the bitwise OR operation across 10 input values of type `BYTE` (8-bit bit pattern (byte)). Unlike the Boolean operation on single truth values (as in the `AX_OR` blocks), every bit of the data word is combined independently here.

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

- **IN1**: OR input 1 (Type: adapter::types::unidirectional::AB)
- **IN2**: OR input 2 (Type: adapter::types::unidirectional::AB)
- **IN3**: OR input 3 (Type: adapter::types::unidirectional::AB)
- **IN4**: OR input 4 (Type: adapter::types::unidirectional::AB)
- **IN5**: OR input 5 (Type: adapter::types::unidirectional::AB)
- **IN6**: OR input 6 (Type: adapter::types::unidirectional::AB)
- **IN7**: OR input 7 (Type: adapter::types::unidirectional::AB)
- **IN8**: OR input 8 (Type: adapter::types::unidirectional::AB)
- **IN9**: OR input 9 (Type: adapter::types::unidirectional::AB)
- **IN10**: OR input 10 (Type: adapter::types::unidirectional::AB)

**Output Adapter:**

- **OUT**: OR result (Type: adapter::types::unidirectional::AB)

## Functionality

As soon as an event arrives at one of the 10 input adapters (`IN1` … `IN10`), the block combines the bit patterns of all 10 inputs bitwise using **OR** and writes the result to the output adapter `OUT`. The starting value of the operation is the identity element (all bits cleared / 0 (identity element of the OR operation)), so that with only one input actually connected, its value is passed through unchanged.

Only if the newly computed result differs from the value currently held on `OUT` is `OUT` rewritten and its adapter event sent (see "Change Detection" below).

## Technical Features

- **Generic function block**: The FB is defined as a generic type (`GEN_AB_OR`) and covers all arities (2 to 10 inputs) of the same underlying logic via the GenericClassName mechanism.
- **Bitwise operation**: Unlike the Boolean `AX_OR` blocks, every bit of the `BYTE` data word is combined individually here, not just a single truth value.
- **Unidirectional adapters**: All adapters are of type `unidirectional::AB` – data flows only from the socket to the plug.
- **Standard compliance**: The block implements the operation according to IEC 61499-2 / IEC 61131-3.

## State Overview

Since this is a combinational logic block, AB_OR_10 has no internal states. The output is recalculated directly from the current input values on every incoming event.

## Application Scenarios

- **Bit mask combination**: Combining multiple status registers or flag bytes of type `BYTE` into a single result.
- **Signal aggregation**: Merging multiple `BYTE` data sources (e.g., from different modules) via a shared OR operation.
- **Diagnostics and status evaluation**: Checking bit patterns for commonly or differently set bits.

## ⚖️ Comparison with Similar Blocks

Unlike `AX_OR_10`, which combines individual Boolean truth values, `AB_OR_10` operates on the full bit pattern of a `BYTE` value. Compared to the standard block [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md), `AB_OR_10` uses adapter-based interfaces instead of direct data/event inputs/outputs, enabling more flexible integration into adapter-based system architectures.

- **[`AB_OR_10_UNGATED`](AB_OR_10_UNGATED.md)**: Ungated variant – updates the output on every run, even without a value change.

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.

## Conclusion

**AB_OR_10** offers a reliable, generic implementation of the bitwise OR function for `BYTE` values with adapter-based interfaces. Its generic nature makes it versatile for use in automation projects developed according to the IEC 61499 standard that need to combine multiple bit patterns of the same data type.
