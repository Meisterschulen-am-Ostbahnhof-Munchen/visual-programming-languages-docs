# OR_9

<img width="1109" height="384" alt="OR_9" src="https://github.com/user-attachments/assets/32910d98-c116-4a57-b0e3-bcb3ac9241a5" />
* * * * * * * * * *
## Introduction

The OR_9 function block is a generic function block for calculating a bitwise logical OR operation. It supports up to nine input variables and outputs the result of the OR operation. The function block is part of the IEC 61131-3 standard library for bitwise Boolean functions.
![OR_9](OR_9.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request input. Triggers the calculation of the OR operation. Linked to all data inputs (IN1 to IN9).

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after the calculation of the OR operation. Linked to the data output OUT.

### **Data Inputs**

- **IN1** (ANY_BIT): OR Input 1
- **IN2** (ANY_BIT): OR Input 2
- **IN3** (ANY_BIT): OR Input 3
- **IN4** (ANY_BIT): OR Input 4
- **IN5** (ANY_BIT): OR Input 5
- **IN6** (ANY_BIT): OR Input 6
- **IN7** (ANY_BIT): OR Input 7
- **IN8** (ANY_BIT): OR Input 8
- **IN9** (ANY_BIT): OR Input 9

### **Data Outputs**

- **OUT** (ANY_BIT): Result of the OR operation of all inputs

### **Adapters**

This module does not have any adapters.

## Functionality

The OR_9 function block performs a bitwise logical OR operation on all active inputs (IN1 to IN9) when the REQ event is received. The result is output at the OUT output, and the CNF event is triggered simultaneously.

## Technical Features

- Supports the generic data type ANY_BIT for all inputs and the output
- Can work with different bit lengths (e.g., BYTE, WORD, DWORD)
- Implemented as a generic function block (GEN_OR)

## State Overview

1. Wait state: Waits for a REQ event
2. Compute state: Performs an OR operation
3. Output state: Sets OUT and triggers CNF
4. Returns to wait state

## Application Scenarios

- Bitwise signal processing
- Combinational logic circuits
- Control logic with multiple input conditions
- Signal processing in industrial automation systems

## ⚖️ Comparison with Similar Function Blocks

- Compared to simpler OR function blocks, OR_9 offers the ability to process up to nine inputs
- Similar to other bitwise operators, but specifically optimized for OR operations
- Generic implementation allows for more flexible application than type-specific variants

## Conclusion

The The OR_9 function block is a versatile building block for bitwise OR operations in industrial control systems. Its generic implementation and support for up to nine inputs make it particularly flexible for various applications. The clear interface structure and compliance with IEC 61131-3 enable easy integration into existing automation solutions.
