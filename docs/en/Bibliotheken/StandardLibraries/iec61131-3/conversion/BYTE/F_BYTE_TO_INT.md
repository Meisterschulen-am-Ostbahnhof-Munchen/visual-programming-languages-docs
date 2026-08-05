# F_BYTE_TO_INT
<img width="1421" height="210" alt="F_BYTE_TO_INT" src="https://github.com/user-attachments/assets/776dfcd4-d0f2-4a7f-9ef6-b4d4a2df49d0" />
* * * * * * * * * *
## Introduction
The function block `F_BYTE_TO_INT` converts a `BYTE` value to a `INT` value. It is part of the `iec61131::conversion` package and enables simple and efficient type conversion between these two data types.
![F_BYTE_TO_INT](F_BYTE_TO_INT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the execution of the function block. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `BYTE`, containing the value to be converted.

### **Data Outputs**
- **OUT**: The output of type `INT`, containing the result of the conversion.

### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion from `BYTE` to `INT` as soon as the event `REQ` is received. The conversion is performed using the integrated function `BYTE_TO_INT`. After successful conversion, the result is output via output `OUT`, and the event `CNF` is triggered.

## Technical Features
- The function block is a simple FB without internal state management.
- The conversion is performed directly and without delay.

## State Overview
Since it is a simple function block, there are no state transitions or complex state logic.

## Application Scenarios
- Type conversion in control applications where `BYTE` values need to be converted to `INT` values.
- Integration into larger control systems that need to process different data types.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks like `F_WORD_TO_INT` or `F_DWORD_TO_INT` offer conversions for other data types, but with the same basic principle.
- Unlike more complex conversion blocks, `F_BYTE_TO_INT` provides a simple and direct solution for the specific conversion of `BYTE` to `INT`.

## Conclusion
The `F_BYTE_TO_INT` function block is an efficient and easy-to-use tool for converting `BYTE` values to `INT` values. Its simplicity and direct operation make it ideal for applications that require fast and reliable type conversions.