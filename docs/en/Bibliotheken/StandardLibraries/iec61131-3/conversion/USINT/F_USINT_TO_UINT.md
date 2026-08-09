# F_USINT_TO_UINT

<img width="1453" height="214" alt="F_USINT_TO_UINT" src="https://github.com/user-attachments/assets/50a399dd-73aa-4f6f-aff9-6b747efe0874" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_UINT` converts a `USINT` value (Unsigned Short Integer) to a `UINT` value (Unsigned Integer). This block is particularly useful in scenarios where a type conversion without data loss is required.
![F_USINT_TO_UINT](F_USINT_TO_UINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `USINT` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `UINT`, containing the result of the conversion.

#### **Adapters**

No adapters available.

## Functionality

This function block directly assigns the input value `IN` of type `USINT` to the output value `OUT` of type `UINT`. Since `USINT` has a smaller value range than `UINT`, the conversion occurs without data loss.

The algorithm is triggered by the event `REQ` and outputs the result via the event `CNF`.

## Technical Features

- The function block is implemented in the ST (Structured Text) programming language.
- The conversion occurs without additional calculations or checks, as `USINT` can be automatically converted to `UINT`.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Type conversion in control applications, where `USINT` values need to be converted to `UINT`.
- Use in data processing chains where different data types need to be made compatible.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion function blocks such as `F_INT_TO_REAL` or `F_BOOL_TO_STRING`, this function block is specifically for conversion between two unsigned integer types.
- Similar function blocks might perform additional checks or scaling, which is not necessary here.

## Conclusion

The `F_USINT_TO_UINT` function block is a simple and efficient building block for converting `USINT` to `UINT`. It is ideally suited for applications where fast and lossless type conversion is required.