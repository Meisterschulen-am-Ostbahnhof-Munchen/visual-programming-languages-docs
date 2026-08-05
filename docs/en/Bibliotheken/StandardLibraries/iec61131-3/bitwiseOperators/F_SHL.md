# F_SHL

<img width="1342" height="208" alt="F_SHL" src="https://github.com/user-attachments/assets/91a9f7fd-3552-4524-91ed-e888afe9acdd" />

* * * * * * * * * *
## Introduction
The function block `F_SHL` performs a left shift on any bit data type. The bits of the input value are shifted left by a specified number of positions, and the resulting free positions on the right are padded with zeros. This block is classified according to the IEC 61131-3 standard and is suitable for bitwise operations.

![F_SHL](F_SHL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service request. Triggers the left shift. Linked to the data inputs `IN` and `N`.


### **Event Outputs**

- **CNF**: Confirmation of the requested service. Signals the completion of the operation. Linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value to be left-shifted. The data type is `ANY_BIT` (any bit data type).

- **N**: The number of positions to shift. The data type is `ANY_INT` (any integer data type).

### **Data Outputs**

- **OUT**: The result of the left shift. The data type is the same as the input value `IN`. The resulting free positions on the right are padded with zeros.

### **Adapters**
No adapters are defined.


### **Adapters** ## Functionality
The function block `F_SHL` performs a bitwise left shift of the input value `IN` by `N` positions. The bits are shifted to the left, and the newly created positions on the right side are padded with zeros. The operation is triggered by the event `REQ` and acknowledged by `CNF`.

## Technical Features
- Supports any bit data type (`ANY_BIT`) for the input value `IN`.

- The number of shifts `N` can be any integer data type (`ANY_INT`).


- The operation is standardized according to IEC 61131-3.

## State Overview

1. **Idle State**: Waits for the event `REQ`.

2. **Execution State**: Performs the left shift when `REQ` is received.

3. **Acknowledge State**: Sends `CNF` after the operation is complete.

## Application Scenarios

- Bit manipulation in control applications.

- Shift operations in digital signal processing algorithms.

- General bitwise operations in IEC 61131-3 compliant control systems.


## ⚖️ Comparison with Similar Function Blocks

- **F_SHR**: Performs a right shift, unlike the left shift of `F_SHL`.

- **F_ROL** and **F_ROR**: Rotate bits instead of shifting them, with overflowing bits being reinserted on the other side.

## 🛠️ Related Exercises

* [Exercise_034](../../../../Uebungen/test_B/Uebungen_doc/Uebung_034.md)]

## Conclusion
The `F_SHL` function block is an efficient tool for bitwise left shifts in control systems. Its flexibility in supporting various bit and integer data types makes it versatile. Clear event handling and compliance with the IEC 61131-3 standard ensure reliable integration into existing systems.