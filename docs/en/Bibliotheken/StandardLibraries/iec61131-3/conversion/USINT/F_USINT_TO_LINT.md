# F_USINT_TO_LINT

<img width="1448" height="214" alt="F_USINT_TO_LINT" src="https://github.com/user-attachments/assets/d5f2a448-fc5d-4ba6-952d-0852c28b6ea5" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_LINT` converts a `USINT` value (8-bit unsigned integer) to a `LINT` value (64-bit signed integer). This conversion is particularly useful when values from smaller data types need to be converted to larger ones without losing the original information.
![F_USINT_TO_LINT](F_USINT_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `USINT` to be converted.

### **Data Outputs**

- **OUT**: The converted output value of type `LINT`.

### **Adapters**

No adapters are available.

## Functionality

This function block directly assigns the input value `IN` to the output value `OUT`. Since `USINT` is an 8-bit unsigned integer and `LINT` is a 64-bit signed integer, the value is converted to the larger data type without any change to the numeric value.

## Technical Features

- **Algorithm**: The algorithm consists of a simple assignment (`OUT := IN;`).
- **Data Type Compatibility**: Since `USINT` is an unsigned data type and `LINT` is a signed data type, the value is implicitly extended without any data loss.

## State Overview

The function block has no internal state. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- **Data Processing**: When values need to be converted from smaller to larger data types.
- **Communication**: When transferring data between systems with different data type requirements.

## ⚖️ Comparison with Similar Function Blocks

- **F_USINT_TO_INT**: Converts `USINT` to `INT` (16-bit signed integer). In contrast, `F_USINT_TO_LINT` offers greater range due to its 64-bit output.
- **F_USINT_TO_ULINT**: Converts `USINT` to `ULINT` (64-bit unsigned integer). Here, the output is also treated as unsigned.

## Conclusion

The `F_USINT_TO_LINT` function block is a simple yet effective building block for converting 8-bit unsigned integer values to 64-bit signed integer values. Its direct and lossless conversion makes it ideal for applications where preserving the numeric value in a larger data type is required.