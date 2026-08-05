# F_USINT_TO_ULINT
<img width="1466" height="214" alt="F_USINT_TO_ULINT" src="https://github.com/user-attachments/assets/93d99220-51d0-4f22-9315-b8380b7daeae" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_TO_ULINT` converts a `USINT` value (8-bit unsigned integer) to a `ULINT` value (64-bit unsigned integer). This conversion is useful when data needs to be exchanged or processed between systems with different word lengths.
![F_USINT_TO_ULINT](F_USINT_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- `CNF`: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- `IN` (USINT): The input value to be converted.

### **Data Outputs**
- `OUT` (ULINT): The converted output value.

### **Adapters**
No adapters available.

#
## ## Functionality

The function block performs a direct conversion of the input value `IN` of type `USINT` to the output value `OUT` of type `ULINT`. The conversion is lossless because the value range of `USINT` (0 to 255) can be fully mapped to `ULINT` (0 to 2^64-1).

## Technical Features
- The conversion is performed using a single algorithm (`REQ`), which is executed when the `REQ` event is triggered.

# Technical Features
- The conversion is performed using a single algorithm (`REQ`), which is executed when the `REQ` event is triggered.

`` - The algorithm is implemented in ST (Structured Text) and consists of a simple assignment: `OUT := IN;`.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Data conversion in control systems that use different word widths.
- Integration of peripheral devices that provide data in different formats.
- General type conversion in IEC 61131-3-based programs.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_SINT_TO_LINT` or `F_UINT_TO_UDINT` perform similar conversions, but between different data types.
- `F_USINT_TO_ULINT` is specifically optimized for converting 8-bit to 64-bit unsigned integers.

## Conclusion
The function block `F_USINT_TO_ULINT` provides a simple and efficient way to convert values of type `USINT` to `ULINT`. Its clear interface and direct functionality make it ideal for applications requiring type conversion without additional logic.
