# F_WSTRING_AS_USINT

<img width="1492" height="214" alt="F_WSTRING_AS_USINT" src="https://github.com/user-attachments/assets/8e64c350-6c28-45b7-9597-276c03f37b6b" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_USINT` converts a WSTRING value to a USINT value. It is part of the package `iec61131::conversion` and enables the easy conversion of wide strings to unsigned 8-bit integers.
![F_WSTRING_AS_USINT](F_WSTRING_AS_USINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (WSTRING): The input string to be converted to a USINT value.

### **Data Outputs**

- **OUT** (USINT): The result of the conversion as an unsigned 8-bit integer.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs the conversion when the event `REQ` is triggered. The conversion is carried out using the function `WSTRING_AS_USINT`, which converts the WSTRING input value to a USINT value. After the conversion is complete, the event `CNF` is triggered, and the result value is available at output `OUT`.

## Technical Features

- The conversion is performed directly without additional parameters.
- The function block is optimized for use in IEC 61499-compliant environments.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Done**: Sends the `CNF` event and provides the result.

## Application Scenarios

- Conversion of character strings to numeric values for control applications.
- Use in systems that use character strings as input but require numeric processing.

## ⚖️ Comparison with Similar Function Blocks

- Unlike generic conversion blocks, `F_WSTRING_AS_USINT` specializes in converting WSTRING to USINT.
- Other blocks might offer additional parameters or error handling, but this block is designed for simplicity and efficiency.

## Conclusion

The `F_WSTRING_AS_USINT` function block provides a simple and efficient way to convert WSTRING values to USINT values. Its clear interface and direct functionality make it ideal for applications that require fast and straightforward conversions.