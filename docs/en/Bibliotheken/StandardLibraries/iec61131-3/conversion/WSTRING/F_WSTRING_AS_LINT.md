# F_WSTRING_AS_LINT

<img width="1480" height="214" alt="F_WSTRING_AS_LINT" src="https://github.com/user-attachments/assets/a8ed434d-17fa-45f9-8839-16517ab7d6b0" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_LINT` is used to convert a WSTRING value to a LINT value. This block is particularly useful in scenarios where strings need to be converted into numeric values, for example, when processing user input or interpreting text data.
![F_WSTRING_AS_LINT](F_WSTRING_AS_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This event input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution confirmation. This event is output after successful conversion and is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (WSTRING): The input for the string to be converted to a LINT value.

### **Data Outputs**

- **OUT** (LINT): The output for the converted LINT value.

#### **Adapters**

This function block does not use any adapters.

## Functionality

The function block converts the WSTRING value at input `IN` to a LINT value at output `OUT` as soon as the event `REQ` is received. The conversion is performed using the function `WSTRING_AS_LINT`. After successful conversion, the event `CNF` is output.

## Technical Features

- The function block has a simple structure and contains only one conversion algorithm.
- The conversion can fail if the string does not contain a valid numeric representation. In this case, the event `CNF` is not output.

## State Overview

1. **Idle**: The function block waits for the event `REQ`.
2. **Processing**: Upon receiving `REQ`, the conversion is performed.
3. **Confirmation**: After successful conversion, `CNF` is output, and the function block returns to the idle state.

## Application Scenarios

- Processing user input that is in string form but should be interpreted as numeric values.
- Interpreting text data from external sources that contains numeric information.

## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_AS_LINT**: Similar function block, but for the STRING data type instead of WSTRING.
- **F_WSTRING_AS_INT**: Converts WSTRING to INT, but offers a smaller value range than LINT.

## Conclusion

The `F_WSTRING_AS_LINT` function block is a simple and effective tool for converting strings to large numeric values. Its clear interface and simple functionality make it a reliable solution for corresponding use cases.
