# F_XOR

<img width="1149" height="208" alt="F_XOR" src="https://github.com/user-attachments/assets/5f3451b6-8e0a-479b-9d80-1af4d73f9e69" />
* * * * * * * * * *
## Introduction

The function block `F_XOR` performs a bitwise XOR operation (exclusive OR) on two input values. It is part of the standard bitwise operations according to IEC 61131-3 and is suitable for logical processing in control applications.
![F_XOR](F_XOR.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the XOR operation. When activated, the input data `IN1` and `IN2` are processed.

### **Event Outputs**

- `CNF`: Confirms successful execution of the XOR operation and outputs the result via `OUT`.

### **Data Inputs**

- `IN1`: First input value for the XOR operation (Type: `ANY_BIT`).
- `IN2`: Second input value for the XOR operation (Type: `ANY_BIT`).

### **Data Outputs**

- `OUT`: Result of the bitwise XOR operation (Type: `ANY_BIT`).

### **Adapters**

No adapters available.

## Functionality

When the event input `REQ` is activated, the function block performs a bitwise XOR operation between the values `IN1` and `IN2`. The result is output via the data output `OUT`, and the event `CNF` is triggered to signal the completion of the operation.

## Technical Features

- Supports the data type `ANY_BIT`, meaning that various bit data types (e.g., BOOL, BYTE, WORD, DWORD) can be processed.
- The initial values of the inputs are empty, requiring explicit assignment of the input values.

## State Overview

1. **Idle State**: Waits for the event `REQ`.
2. **Processing State**: Performs the XOR operation when `REQ` is activated.
3. **Output State**: Sends the result via `OUT` and triggers `CNF`.

## Application Scenarios

- Logical processing in control systems.
- Bitwise manipulation of data in industrial automation processes.
- Implementation of security checks or checksum calculations.

## ⚖️ Comparison with Similar Function Blocks

- **F_AND / F_OR**: Perform bitwise AND and OR operations, respectively, while `F_XOR` offers an exclusive OR operation. - **F_NOT**: Inverts bits while `F_XOR` compares two input values.

## Conclusion

The `F_XOR` function block is an efficient tool for bitwise XOR operations in IEC 61131-3 compliant control systems. Its flexibility with the `ANY_BIT` data type makes it versatile for use in various automation applications.
