# F_OR

<img width="1324" height="244" alt="F_OR" src="https://github.com/user-attachments/assets/aef4acae-7a18-40f2-85a5-69e0c6e0ef3b" />

* * * * * * * * * *
## Introduction
The function block `F_OR` implements a bitwise OR operation according to the IEC 61131-3 standard. It performs a logical OR operation on two input variables of type `ANY_BIT` and outputs the result.

![F_OR](F_OR.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the OR operation. Upon this event, the inputs `IN1` and `IN2` are evaluated.

### **Event Outputs**

- **CNF**: Signals the successful completion of the operation. This event is output along with the result `OUT`.

### **Data Inputs**

- **IN1**: First input for the bitwise OR operation (Type: `ANY_BIT`).

- **IN2**: Second input for the bitwise OR operation (Type: `ANY_BIT`).

### **Data Outputs**

- **OUT**: Result of the bitwise OR operation (Type: `ANY_BIT`).

### **Adapters**
This function block does not use any adapters.


## Functionality
When the `REQ` event is triggered, the `F_OR` block performs a bitwise OR operation on the values at `IN1` and `IN2`. The result is output to `OUT`, and the `CNF` event signals successful computation.

## Technical Features
- **Type Flexibility**: Supports all `ANY_BIT` data types (e.g., BOOL, BYTE, WORD, DWORD, LWORD).

- **Simple Implementation**: No state machine is required, as this is a static operation.


## State Overview

The function block has no internal state machine, as the operation is performed directly upon the occurrence of the `REQ` event.

## Application Scenarios
- Bitwise operation in control algorithms
- Mask operations in signal processing
- Logical combination of digital signals

## ⚖️ Comparison with similar function blocks
- **F_AND**: Performs a bitwise AND operation
- **F_XOR**: Performs a bitwise exclusive OR operation
- **F_NOT**: Performs a bitwise negation

## Conclusion
The `F_OR` function block offers a simple and efficient way to perform bitwise OR operations in IEC 61131-3 compliant control systems. Its type flexibility and direct operation make it a universally applicable function block for logical operations.