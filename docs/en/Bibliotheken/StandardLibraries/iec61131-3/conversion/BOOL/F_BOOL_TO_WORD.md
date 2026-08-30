# F_BOOL_TO_WORD

<img width="1434" height="212" alt="F_BOOL_TO_WORD" src="https://github.com/user-attachments/assets/2108fbdb-57b2-48c1-9549-416c9024f862" />
* * * * * * * * * *
## Introduction

The function block `F_BOOL_TO_WORD` converts a Boolean value (`BOOL`) into a 16-bit word value (`WORD`). This conversion is particularly useful in scenarios where Boolean signals need to be embedded in or further processed within word data structures.
![F_BOOL_TO_WORD](F_BOOL_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion. Linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution Confirmation. Triggered after successful conversion. Linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `BOOL` to be converted to `WORD`.

### **Data Outputs**

- **OUT**: The output value of type `WORD` containing the result of the conversion.

### **Adapters**

- No adapters available.

## Functionality

This function block performs the conversion of `BOOL` to `WORD` when the event `REQ` is received. The Boolean value `IN` is converted into a 16-bit word, with `FALSE` being interpreted as `0` and `TRUE` as `1`. The result is output via `OUT`, and the event `CNF` is triggered to indicate successful conversion.

## Technical Features

- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm for conversion.
- The conversion is performed directly by the function `BOOL_TO_WORD(IN)`.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Embedding Boolean signals in word data structures for communication with other systems.
- Use in control logic where Boolean values need to be processed as part of larger data words.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_BOOL_TO_BYTE` or `F_BOOL_TO_DWORD` offer conversions to other data types (`BYTE` or `DWORD`). `F_BOOL_TO_WORD` is specific to 16-bit word values.

## Conclusion

The function block `F_BOOL_TO_WORD` provides a simple and efficient way to convert Boolean values to word values. Its clear interface structure and direct functionality make it ideal for applications that require such conversions.
