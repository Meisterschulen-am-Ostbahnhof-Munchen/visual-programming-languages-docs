# F_SINT_TO_INT

<img width="1426" height="213" alt="F_SINT_TO_INT" src="https://github.com/user-attachments/assets/398a23eb-3229-4f56-8246-e9d579c3932e" />
* * * * * * * * * *
## Introduction

The function block `F_SINT_TO_INT` converts a `SINT` value (8-bit signed integer) to a `INT` value (16-bit signed integer count). This block is particularly useful in scenarios where type conversion between different integer formats is required.
![F_SINT_TO_INT](F_SINT_TO_INT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`SINT`): The input value to be converted.

### **Data Outputs**

- **OUT** (`INT`): The converted output value.

### **Adapters**

- No adapters are available.

## Functionality

This function block directly assigns the `SINT` input value to the `INT` output. Since `SINT` is a smaller data type than `INT`, the conversion is performed without data loss.

The algorithm is defined as follows:

ALGORITHM REQ
OUT := IN;
END_ALGORITHM
## Technical Features

- The conversion is lossless, as the value range of `SINT` (-128 to 127) fits completely within the value range of `INT` (-32768 to 32767).
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where various integer formats need to be processed.
- Integration into larger function block networks where uniform data type processing is required.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_INT_TO_SINT` perform the reverse conversion, but with potential data loss.
- Unlike generic conversion blocks, `F_SINT_TO_INT` is specialized and optimized for this specific conversion.

## Conclusion

The `F_SINT_TO_INT` function block offers a simple and efficient way to convert `SINT` values to `INT` values. Its deterministic and lossless operation makes it a reliable component in control applications.
