# F_INT_TO_LWORD
<img width="1232" height="182" alt="F_INT_TO_LWORD" src="https://github.com/user-attachments/assets/af2f07c7-56ec-498d-94f5-170a88e6a3e3" />
* * * * * * * * * *
## Introduction
The function block `F_INT_TO_LWORD` converts an integer value (`INT`) into a 64-bit unsigned integer value (`LWORD`). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_INT_TO_LWORD](F_INT_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Triggers the execution of the function block. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals successful execution of the function block. This output is connected to the data output `OUT`.

### **Data Inputs**
- **IN** (`INT`): The input value to be converted to a `LWORD` value.

### **Data Outputs**
- **OUT** (`LWORD`): The converted output value.

### **Adapters**
No adapters available.

#
## ## Functionality

Upon receiving an incoming `REQ` event, the function block converts the `INT` value at the input `IN` to a `LWORD` value. The result is output at `OUT`, and the `CNF` event signals successful execution.

The algorithm is defined as follows:

ALGORITHM REQ
OUT := INT_TO_LWORD(IN);
END_ALGORITHM
## Technical Features
- The function block is simple and efficient because it directly utilizes the built-in `INT_TO_LWORD` function.
- No additional states or complex logic are required.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Type conversion in control applications where `INT` values need to be converted to `LWORD` values.
- Integration into larger systems that process different data types.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_DINT_TO_LWORD` or `F_SINT_TO_LWORD` offer conversions from other integer types to `LWORD`.
- `F_INT_TO_LWORD` is specifically optimized for converting `INT` to `LWORD`.

## Conclusion
The `F_INT_TO_LWORD` function block provides a simple and efficient solution for converting `INT` values to `LWORD` values. Its clear interface and direct functionality make it ideal for use in control applications.
