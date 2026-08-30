# F_NOT

![F_NOT](https://user-images.githubusercontent.com/116869307/214144000-4586686b-f3a0-4caa-9896-3dfb75baa550.png)

* * * * * * * * * *

## Introduction

The F_NOT function block implements a bitwise logical NOT operation according to the IEC 61131-3 standard. It performs a bitwise inversion of the input value and outputs the result.
![F_NOT](F_NOT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - Triggers the calculation of the NOT operation

### **Event Outputs**

- **CNF**: Confirmation of Requested Service - Signals the completion of the calculation

### **Data Inputs**

- **IN**: Input value of type ANY_BIT - The value to be inverted

### **Data Outputs**

- **OUT**: Output value of type ANY_BIT - The inverted result

### **Adapters**

No adapters available

## Functionality

Upon receiving a REQ event, the F_NOT block performs a bitwise logical NOT operation on the input value IN. Each bit of the input value is inverted (0 becomes 1, 1 becomes 0). The result is output at output OUT and confirmed by the CNF event.

## Technical Features

- Supports the ANY_BIT data type, enabling use with various bit data types (BOOL, BYTE, WORD, DWORD, etc.)
- Real-time capable execution
- Standard-compliant implementation according to IEC 61131-3

## State Transition

1. Wait state for REQ event
2. On REQ: Execute the NOT operation
3. Output the result to OUT
4. Send the CNF event
5. Return to wait state

## Application Scenarios

- Bit manipulation in control programs
- Inversion of status bits
- Logical negation of conditions
- Signal inversion in digital circuits

## ⚖️ Comparison with Similar Function Blocks

Compared to other logical operations such as F_AND or F_OR, F_NOT performs only a unary operation (one operand), while other logical function blocks typically implement binary operations (two operands).

## 🛠️ Related Exercises

- [Exercise_006a3_sub](../../../../Uebungen/test_B/Uebungen_doc/Uebung_006a3_sub.md)

## Conclusion

The F_NOT function block offers a standards-compliant, efficient solution for bitwise inversion operations in IEC 61131-3 compliant control systems. Its simple interface and universal ANY_BIT type support make it a versatile building block for various applications.
