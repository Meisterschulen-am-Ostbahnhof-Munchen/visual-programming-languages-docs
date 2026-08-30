# F_INT_AS_WSTRING

<img width="1253" height="182" alt="F_INT_AS_WSTRING" src="https://github.com/user-attachments/assets/eecc33ca-d283-4589-bca8-ce57829c7162" />
* * * * * * * * * *
## Introduction

The function block `F_INT_AS_WSTRING` converts an integer value (`INT`) into a wide string (`WSTRING`). This functionality is particularly useful when numeric values are needed as text for display or further processing.
![F_INT_AS_WSTRING](F_INT_AS_WSTRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN**: The integer value (`INT`) to be converted into a wide string.

### **Data Outputs**

- **OUT**: The resulting wide string (`WSTRING`) after conversion.

#### **Adapters**

- No adapters are available.

## Functionality

The function block uses the built-in function `INT_AS_WSTRING` to convert the integer input value into a wide string. The conversion is initiated by the event `REQ` and confirmed by the event `CNF`.

## Technical Features

- The function block has a simple structure and performs only basic data type conversion.
- No additional parameters or complex algorithms are required.

## State Overview

1. **Ready**: Waits for the event `REQ`.
2. **Active**: Performs the conversion and sets the output `OUT`.
3. **Confirmed**: Sends the event `CNF` and returns to the ready state.

## Application Scenarios

- Displaying numeric values in user interfaces.
- Logging numeric data in text format.
- Preparing data for communication with systems that expect text formats.

## ⚖️ Comparison with Similar Function Blocks

- **F_DINT_AS_WSTRING**: Converts a long integer value (`DINT`) to a wide string.
- **F_REAL_AS_WSTRING**: Converts a floating-point value (`REAL`) to a wide string.
- **F_STRING_AS_INT**: Performs the reverse conversion (string to integer).

## Conclusion

The `F_INT_AS_WSTRING` function block is a simple and efficient tool for converting integers to wide strings. Its clear interface and direct functionality make it a reliable solution for basic data type conversions.
