# SPLIT_DWORD_INTO_BOOLS

![SPLIT_DWORD_INTO_BOOLS](https://github.com/user-attachments/assets/6450d832-86ef-4de3-96ad-82a9b4c7bb3e)

* * * * * * * * * *
## Introduction

The function block `SPLIT_DWORD_INTO_BOOLS` is used to split a 32-bit DWORD into its individual bits and output them as separate BOOL values. This is particularly useful when compressed data needs to be processed in a controller and the individual bits need to be addressed separately.
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. When this input is activated, the bits of the input DWORD are evaluated and made available at the outputs.

### **Event Outputs**

- **CNF**: Confirms the successful execution of the function block. This event is triggered along with the updated BOOL outputs.

### **Data Inputs**

- **IN**: The input DWORD to be split into 32 individual bits.

### **Data Outputs**

- **BIT_00** to **BIT_31**: The 32 individual bits of the input DWORD, each output as a BOOL value. Each output represents one bit of the DWORD, where `BIT_00` corresponds to the least significant bit (LSB) and `BIT_31` to the most significant bit (MSB).

### **Adapters**

This function block does not use adapters.

## Operation

The function block extracts each bit of the input DWORD `IN` and assigns it to the corresponding BOOL outputs. The mapping is direct:

- `BIT_00` = Bit 0 (LSB)
- `BIT_01` = Bit 1
- ...
- `BIT_31` = Bit 31 (MSB)

When the `REQ` event is triggered, all bits are evaluated, and the `CNF` event is triggered as soon as the outputs are updated.

## Technical Features

- The function block is implemented in ST (Structured Text) and uses direct bit access to the DWORD (`IN.%X0` to `IN.%X31`).
- The outputs are updated synchronously with the `CNF` event, enabling deterministic processing.

## State Overview

The function block has no internal state. The outputs are recalculated with each `REQ` event.

## Application Scenarios

- Processing compressed status information, e.g., from a fieldbus or interface.
- Decoding bitmasks in control applications.
- Splitting DWORD values for individual bit manipulation.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic bit manipulation functions, this function block offers a direct and efficient method for extracting all bits of a DWORD.
- Similar function blocks might only process parts of a DWORD or contain additional logic, which is not the case here.

## Conclusion

The `SPLIT_DWORD_INTO_BOOLS` function block is a specialized tool for efficiently splitting a DWORD into its individual bits. Its simple and deterministic operation makes it ideal for applications requiring bit manipulation.
