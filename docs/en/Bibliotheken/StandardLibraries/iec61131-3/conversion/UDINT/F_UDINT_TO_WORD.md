# F_UDINT_TO_WORD
<img width="1449" height="216" alt="F_UDINT_TO_WORD" src="https://github.com/user-attachments/assets/31e92c35-2b63-4389-99d2-83dc3fda9dc5" />
* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_WORD` converts a 32-bit unsigned integer value (UDINT) to a 16-bit unsigned integer value (WORD). This conversion is particularly necessary in scenarios where data needs to be exchanged between systems with different word lengths.
![F_UDINT_TO_WORD](F_UDINT_TO_WORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (UDINT): The 32-bit unsigned integer value to be converted.

### **Data Outputs**
- **OUT** (WORD): The resulting 16-bit unsigned integer value after conversion.

#### **Adapters**
No adapters are available.

## Functionality
This function block performs the conversion from UDINT to WORD by executing the algorithm `REQ`. The input value `IN`, of type UDINT, is converted into a WORD value and output at `OUT`. The conversion occurs synchronously with the event `REQ`, and the result is confirmed with the event `CNF`.

## Technical Details
- The conversion truncates the 16 most significant bits of the UDINT value, since a WORD only contains 16 bits.
- The function block is part of the package `iec61131::conversion`.

## State Overview

The function block has no internal state. The conversion is re-executed with each event `REQ`.

## Application Scenarios
- Data reduction from 32-bit to 16-bit in embedded systems.
- Compatibility with legacy systems that can only process 16-bit data.
- Memory optimization in resource-constrained environments.

## ⚖️ Comparison with Similar Function Blocks
- Compared to `F_DINT_TO_WORD` or `F_INT_TO_WORD`, this function block processes unsigned values.
- Similar function blocks like `F_UDINT_TO_DWORD` do not perform bit width reduction.

## Conclusion
The `F_UDINT_TO_WORD` function block provides a simple and efficient way to convert 32-bit unsigned integer values to 16-bit unsigned integer values. It is particularly useful in scenarios where a reduction in data width is required without altering the fundamental semantics of the data.