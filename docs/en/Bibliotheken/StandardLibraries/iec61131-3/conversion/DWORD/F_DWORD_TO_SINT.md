# F_DWORD_TO_SINT

<img width="1248" height="181" alt="F_DWORD_TO_SINT" src="https://github.com/user-attachments/assets/f27122be-9192-4b18-a187-5b5710f2bdcf" />
* * * * * * * * * *
## Introduction

The function block `F_DWORD_TO_SINT` converts a 32-bit DWORD value to an 8-bit SINT value (signed integer). This block is part of the IEC 61131 conversion library and enables simple type conversion between these data types.
![F_DWORD_TO_SINT](F_DWORD_TO_SINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion process. This input is linked to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals successful completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (DWORD): The 32-bit input value to be converted to a SINT value.

### **Data Outputs**

- `OUT` (SINT): The converted 8-bit SINT value.

### **Adapters**

This function block does not have any adapter interfaces.

## Functionality

When the `REQ` event is triggered, the algorithm that converts the `IN` value of type DWORD into a SINT value is executed. The conversion is performed by the built-in function `DWORD_TO_SINT`. After the conversion is complete, the `CNF` event is triggered, and the converted value is available at the `OUT` output.

## Technical Features

- Data loss can occur during the conversion if the DWORD value is outside the representable range of a SINT (-128 to 127).
- The function block is a simple block without internal state management.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where DWORD values need to be converted to more compact SINT values.
- Data reduction when only the least significant part of a DWORD value is required.

## ⚖️ Comparison with Similar Function Blocks

- Compared to `F_DWORD_TO_INT` or `F_DWORD_TO_USINT`, this function block converts to a signed 8-bit value.
- Similar function blocks for other target types are available in the IEC 61131 conversion library.

## Conclusion

The `F_DWORD_TO_SINT` function block provides a simple and efficient way to convert DWORD values to SINT values. It is particularly useful in applications where storage space or data bandwidth needs to be optimized. When using it, the possible value range of the SINT data type must be considered to avoid unwanted data loss.
