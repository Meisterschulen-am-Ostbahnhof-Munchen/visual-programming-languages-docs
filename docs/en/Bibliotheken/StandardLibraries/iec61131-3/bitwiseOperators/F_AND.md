# F_AND

<img width="1336" height="244" alt="F_AND" src="https://github.com/user-attachments/assets/a65a419c-0126-4dd6-9ab3-6e40b32ddcac" />
* * * * * * * * * *
## Introduction

The function block `F_AND` is a standardized bitwise Boolean AND operator according to IEC 61131-3. It performs a bitwise AND operation on two input variables and outputs the result. This block is particularly useful for logical operations in control applications.
![F_AND](F_AND.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Service Request. Triggers the execution of the AND operation. Linked to the data inputs `IN1` and `IN2`.

### **Event Outputs**

- **CNF**: Confirmation of the requested service. Triggered after successful execution of the operation. Linked to the data output `OUT`.

### **Data Inputs**

- **IN1**: First input for the bitwise AND operation. Type: `ANY_BIT`.
- **IN2**: Second input for the bitwise AND operation. Type: `ANY_BIT`.

### **Data Outputs**

- **OUT**: Result of the bitwise AND operation. Type: `ANY_BIT`.

### **Adapters**

- No adapters available.

## Functionality

The `F_AND` block performs a bitwise AND operation between the input variables `IN1` and `IN2` when the event `REQ` is triggered. The result is passed to the output `OUT`, and the event `CNF` is triggered to confirm successful execution.

## Technical Features

- Supports the data type `ANY_BIT`, which means that various bit types such as `BOOL`, `BYTE`, `WORD`, `DWORD`, etc., can be used.
- The block conforms to the IEC 61131-3 standard and is classified as a "standard bitwise boolean function".

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Execution State**: Executes the bitwise AND operation when `REQ` is received.
3. **Acknowledgement State**: Sends the `CNF` event and outputs the result to `OUT`.

## Application Scenarios

- Logical controls in industrial automation systems.
- Bitwise mask operations in data processing applications.
- Combination with other logic blocks for complex control logic.

## ⚖️ Comparison with Similar Blocks

- **F_OR**: Performs a bitwise OR operation.
- **F_XOR**: Performs a bitwise exclusive OR operation.
- **F_NOT**: Performs a bitwise negation.

## 🛠️ Related Exercises

* [Exercise_002a2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a2.md)
* [Exercise_002a2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a2_AX.md)

## Conclusion

The `F_AND` function block is a fundamental building block for bitwise logic operations in IEC 61131-3 compliant control systems. Its simple and standardized interface makes it reliable and versatile for use in various automation applications.
