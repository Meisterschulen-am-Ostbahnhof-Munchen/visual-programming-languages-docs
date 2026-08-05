# XOR_7

<img width="1308" height="390" alt="XOR_7" src="https://github.com/user-attachments/assets/8d4bc1de-83b7-41c4-bcdf-e5f584e271dd" />

* * * * * * * * * *
## Introduction
The function block `XOR_7` performs a bitwise XOR operation on seven input values. It is a generic function block that can be used with various bit data types (e.g., BOOL, BYTE, WORD, DWORD, LWORD). The block is classified according to the IEC 61131-3 standard and is used for processing Boolean operations.

![XOR_7](XOR_7.svg)

## Interface Structure
### **Event Inputs**

- **REQ** (Normal Execution Request): Triggers the calculation of the XOR operation. It is linked to all data inputs (`IN1` to `IN7`).


### **Event Outputs**

- **CNF** (Execution Confirmation): Signals successful calculation and outputs the result via the data output `OUT`.

### **Data Inputs**

- **IN1** (XOR input 1): First input value (Type: `ANY_BIT`).

- **IN2** (XOR input 2): Second input value (Type: `ANY_BIT`).

- **IN3** (XOR input 3): Third input value (Type: `ANY_BIT`).

- **IN4** (XOR input 4): Fourth input value (Type: `ANY_BIT`).

- **IN5** (XOR input 5): Fifth input value (Type: `ANY_BIT`).

- **IN6** (XOR input 6): Sixth input value (Type: `ANY_BIT`).

- **IN7** (XOR input 7): Seventh input value (Type: `ANY_BIT`).

### **Data Outputs**

- **OUT** (XOR result): Result of the bitwise XOR operation (Type: `ANY_BIT`).

### **Adapters**
No adapters available.

## Functionality
The function block performs a bitwise XOR operation on the seven input values (`IN1` to `IN7`). The operation is triggered by the event `REQ`. The result is output via `OUT` and confirmed by the event `CNF`.

## Technical Features

- **Generic Implementation**: Supports various bit data types (`ANY_BIT`).

- **Flexibility**: Can operate with up to seven input values.

- **Standard Compliant**: Complies with the IEC 61131-3 standard.

## State Overview
The function block has no internal states. The operation is re-executed with each `REQ` event.

## Application Scenarios

- Bitwise encryption.

- Error detection in data transmissions.

- Logical controls in automation systems.


## ⚖️ Comparison with Similar Function Blocks
- **XOR (Standard)**: Typically offers only two inputs, while `XOR_7` supports seven inputs.

- **AND/OR Blocks**: Perform other logical operations, while `XOR_7` is specifically optimized for the XOR operation.

## Conclusion
The `XOR_7` function block is a powerful tool for bitwise XOR operations with up to seven input values. Its generic nature and standards compliance make it versatile for use in various automation and control scenarios.