# F_REAL_AS_WSTRING
<img width="1256" height="180" alt="F_REAL_AS_WSTRING" src="https://github.com/user-attachments/assets/bc7fddcb-82a0-423e-aabe-56670bf82552" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_AS_WSTRING` converts a `REAL` value into a `WSTRING` value. This block is particularly useful when numeric values need to be converted into a string suitable for output or further processing.
![F_REAL_AS_WSTRING](F_REAL_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: This input triggers the conversion. Upon receiving an event, the algorithm for converting the `REAL` value into a `WSTRING` value is started.

### **Event Outputs**
- **CNF**: This event signals the successful completion of the conversion and returns the result as a `WSTRING` value.

### **Data Inputs**
- **IN**: The input expects a `REAL` value, which is to be converted to a `WSTRING` value.

### **Data Outputs**
- **OUT**: The output returns the converted `WSTRING` value after the conversion is complete.

### **Adapters**
This function block does not have any adapter interfaces.

#
## ## Functionality
The function block `F_REAL_AS_WSTRING` converts the `REAL` value at input `IN` to a `WSTRING` value upon receiving an incoming `REQ` event. The result is provided at output `OUT` and confirmed by a `CNF` event.

The conversion algorithm is implemented as a simple ST (Structured Text) statement:

```ST
ALGORITHM REQ
OUT := REAL_AS_WSTRING(IN);
END_ALGORITHM
## Technical Features
- The function block is part of the `iec61131::conversion` package.
- The conversion is performed directly without additional parameters or settings.

## Status Overview

1. **Idle**: Waits for a `REQ` event.

2. **Processing**: Performs the conversion.

3. **Completed**: Sends the `CNF` event with the result.

## Application Scenarios
- **Data Output**: Converts numeric values for display on a control panel or in a log file.
- **Data Communication**: Prepares numeric values for transmission as strings in network protocols.

## ⚖️ Comparison with Similar Function Blocks
- **F_REAL_TO_STRING**: Similar function block, but it converts to `STRING` instead of `WSTRING`. `F_REAL_AS_WSTRING` is better suited for Unicode-enabled environments.
- **F_WSTRING_AS_REAL**: Performs the reverse conversion (from `WSTRING` to `REAL`).

## Conclusion
The function block `F_REAL_AS_WSTRING` provides a simple and efficient way to convert `REAL` values to `WSTRING` values. Its clear interface and direct functionality make it ideal for applications that require a Unicode-compatible string representation of floating-point numbers.
