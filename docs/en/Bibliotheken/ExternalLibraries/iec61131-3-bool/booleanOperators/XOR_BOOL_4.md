# XOR_BOOL_4

<img width="1383" height="304" alt="image" src="https://github.com/user-attachments/assets/50f4bab5-ea69-4673-9279-dcd715e0bef0" />
* * * * * * * * * *
## Introduction

The function block `XOR_BOOL_4` is a standard block for calculating the logical exclusive OR (XOR) operation for up to four Boolean input values. It complies with the IEC 61131-3 standard and is implemented as a generic block used in control applications for combinational logic processing.
![XOR_BOOL_4](XOR_BOOL_4.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Normal Execution Request): This event triggers the calculation of the XOR operation. It is linked to all four data inputs (`IN1` to `IN4`).

### **Event Outputs**

- **CNF** (Execution Confirmation): This event signals the completion of the calculation. It is output along with the calculated result at data output `OUT`.

### **Data Inputs**

- **IN1** (BOOL): XOR input 1.
- **IN2** (BOOL): XOR input 2.
- **IN3** (BOOL): XOR input 3.
- **IN4** (BOOL): XOR input 4.

### **Data Outputs**

- **OUT** (BOOL): Result of the XOR operation of all active inputs.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

When the event `REQ` occurs, the function block reads the values of all four Boolean inputs (`IN1`, `IN2`, `IN3`, `IN4`). It then calculates the logical exclusive OR over these values. The result `OUT` is `TRUE` (1) if and only if an odd number of the inputs have the value `TRUE`. If the number of `TRUE` inputs is even (0, 2, or 4), the result is `FALSE` (0). After the calculation, the confirmation event `CNF` is output along with the result value.

## Technical Features

- **Generic Block:** The block is marked with the attribute `eclipse4diac::core::GenericClassName` as `'GEN_XOR'`. This allows for flexible instantiation and reuse within the 4diac IDE.
- **Event-Driven Execution:** The functionality is strictly event-driven. A calculation only takes place upon an incoming `REQ` event.
- **Four Inputs:** Unlike a simple 2-input XOR, this block offers direct processing of up to four signals without additional nesting.

## State Overview

The function block has no internal state (memory-free, combinatorial). Its behavior depends solely on the current values at the data inputs during each call.

## Application Scenarios

- **Parity Check:** Detects whether an odd number of conditions (e.g., error messages, limit exceedances) are active in a group of four signals.
- **Control Logic:** Implements safety circuits where exactly one of several possible input combinations is allowed to trigger an action.
- **Nested Logic Simplification:** Replaces multiple cascaded 2-input XOR blocks with a single `XOR_BOOL_4` block for improved clarity in the function block diagram (FBD).

## ⚖️ Comparison with Similar Blocks

- **Standard XOR (2 Inputs):** A classic XOR block with only two inputs. The `XOR_BOOL_4` consolidates the functionality of several such blocks. See: [XOR_4](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_4.md)
- **OR_BOOL_4 / AND_BOOL_4:** These blocks calculate the logical OR or AND operation across four inputs. The XOR operation differs fundamentally, as it evaluates the case where all inputs are `TRUE` as `FALSE`.
- **Parity Check Blocks:** Specialized blocks for parity calculation often exist for data words (BYTE, WORD). `XOR_BOOL_4` provides this function for individual bits/Bool values.

## Conclusion

The `XOR_BOOL_4` is a useful and efficient standard block for implementing exclusive OR logic with up to four inputs in 4diac-based control applications. Its event-driven, stateless architecture and direct support for multiple inputs make it a practical choice for parity checks and specialized combinatorial control tasks.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
