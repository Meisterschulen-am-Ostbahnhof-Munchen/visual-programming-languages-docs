# AX_AND_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AX_AND_2`](AX_AND_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

<img width="1009" height="265" alt="image" src="https://github.com/user-attachments/assets/e9225b9f-ba25-427f-bf49-71f15c562b73" />
* * * * * * * * * *
## Introduction

The AX_AND_2_UNGATED is a generic function block for calculating the logical AND operation. The block processes two Boolean input signals and outputs the logical AND result.
![AX_AND_2_UNGATED](AX_AND_2_UNGATED.svg)

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

**Input Adapter:**

- **IN1** - AND input 1 (Adapter type: adapter::types::unidirectional::AX)
- **IN2** - AND input 2 (Adapter type: adapter::types::unidirectional::AX)

**Output Adapter:**

- **OUT** - AND result (Adapter type: adapter::types::unidirectional::AX)

## Functionality

The function block performs a logical AND operation on the two input signals IN1 and IN2. The result is output via the output adapter OUT. Processing is unidirectional via the adapter interfaces.

## Technical Features

- Generic function block with the specific class name 'GEN_AX_AND'
- Uses unidirectional adapters for signal transmission
- Implemented according to the IEC 61499-2 standard

## State Overview

Since it is a combinational logic block, the AX_AND_2_UNGATED has no internal states. The output is calculated directly from the current input values.

## Application Scenarios

- Safety-critical controllers where two conditions must be met simultaneously
- Linking sensor signals in industrial automation systems
- Logical operations in control systems
- Safety shutdowns with multiple conditions

## ⚖️ Comparison with Similar Blocks

Compared to standard AND blocks, the AX_AND_2_UNGATED uses adapter-based interfaces instead of direct data and event inputs/outputs. This enables more flexible integration into adapter-based system architectures.

Comparison [AND_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/AND_2.md)

- **[`AX_AND_2`](AX_AND_2.md)**: The gated variant – updates the output only on an actual value change.

## 🛠️ Related Exercises

- [Exercise_002a_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a_AX.md)
- [Exercise_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
- [Exercise_006a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_AX.md)

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The AX_AND_2_UNGATED offers a reliable and standards-compliant implementation of the logical AND function with adapter-based interfaces. Its generic nature makes it versatile for use in various automation projects developed according to the IEC 61499 standard.
