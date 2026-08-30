# XOR_8

<img width="1122" height="359" alt="XOR_8" src="https://github.com/user-attachments/assets/f41acaf2-1c82-4e78-b340-e454c61c1fc8" />
* * * * * * * * * *
## Introduction

The XOR_8 function block performs a bitwise XOR operation on up to 8 input variables. It is a generic function block that can work with various bit data types (ANY_BIT). The block is classified according to the IEC 61131-3 standard and provides a simple way to perform XOR operations in control applications.
![XOR_8](XOR_8.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Normal Execution Request): Starts the calculation of the XOR operation. It is linked to all data inputs.

### **Event Outputs**

- **CNF** (Execution Confirmation): Signals the completion of the calculation. It is linked to the data output OUT.

### **Data Inputs**

- **IN1** (ANY_BIT): XOR Input 1
- **IN2** (ANY_BIT): XOR Input 2
- **IN3** (ANY_BIT): XOR Input 3
- **IN4** (ANY_BIT): XOR Input 4
- **IN5** (ANY_BIT): XOR Input 5
- **IN6** (ANY_BIT): XOR Input 6
- **IN7** (ANY_BIT): XOR Input 7
- **IN8** (ANY_BIT): XOR Input 8

### **Data Outputs**

- **OUT** (ANY_BIT): Result of the XOR operation

### **Adapters**

The function block does not have any adapter interfaces.

## Functionality

Upon receiving the REQ event, the function block performs a bitwise XOR operation on all active input variables (IN1 to IN8). The result is output at OUT, and the CNF event is triggered to signal the completion of the operation.

## Technical Features

- Supports the generic data type ANY_BIT, meaning that various bit data types (e.g., BOOL, BYTE, WORD, DWORD, LWORD) can be used.
- The operation is strictly bitwise.
- The function block is part of the "iec61131::bitwiseOperators" package.

## State Overview

The function block has no complex states. It responds to the REQ event with an immediate calculation and output of the result.

## Application Scenarios

- Bitwise Checksum Calculation
- Data Encryption Operations
- Error Detection in Data Transmissions
- Control Logic with Bitwise Operations

## ⚖️ Comparison with Similar Function Blocks

Compared to simpler XOR blocks (e.g., with only 2 inputs), XOR_8 offers the ability to process up to 8 inputs simultaneously. Other bitwise operators (such as AND_8 or OR_8) perform similar operations with different logical combinations.

## Conclusion

The XOR_8 function block provides a flexible and standards-compliant solution for bitwise XOR operations in control systems. Its generic nature allows its use with various bit data types, while support for up to 8 inputs enables more complex logical operations. Its simple interface and deterministic execution make it a reliable component for control applications.
