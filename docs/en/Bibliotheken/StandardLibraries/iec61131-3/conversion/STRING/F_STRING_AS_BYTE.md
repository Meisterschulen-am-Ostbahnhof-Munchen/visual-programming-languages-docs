# F_STRING_AS_BYTE
<img width="1464" height="213" alt="F_STRING_AS_BYTE" src="https://github.com/user-attachments/assets/cf7a5899-d56c-4a37-b212-e79196ce79e9" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_BYTE` converts a `STRING` value to a `BYTE` value. This functionality is particularly useful when strings need to be converted into their corresponding byte values, for example, for processing in protocols or when communicating with hardware.
![F_STRING_AS_BYTE](F_STRING_AS_BYTE.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Normal execution request. This event input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Execution confirmation. This event is triggered after successful conversion and is associated with the data output `OUT`.

### **Data Inputs**
- **IN**: Input of type `STRING`, which is to be converted to a `BYTE` value.

### **Data Outputs**
- **OUT**: Output of type `BYTE`, containing the result of the conversion.

### **Adapters**
No adapters are present.

#
## ## Functionality

The function block converts the `STRING` value `IN` to the `BYTE` value `OUT` as soon as the event `REQ` is received. The conversion is performed using the function `STRING_AS_BYTE`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm for the conversion.
- The conversion occurs directly and without any additional delay.

## State Overview

1. **Wait State**: The function block waits for the event `REQ`.

2. **Execution State**: Upon receiving `REQ`, the conversion is performed.

3. **Acknowledgement State**: After successful conversion, `CNF` is triggered, and the function block returns to the wait state.

## Application Scenarios
- Conversion of strings to byte values for communication with serial interfaces.
- Processing of ASCII characters in byte form for protocols or hardware controls.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks like `F_STRING_TO_INT` or `F_STRING_TO_REAL`, `F_STRING_AS_BYTE` is specifically designed to convert to a `BYTE` value.
- A similar block could be `F_CHAR_AS_BYTE`, which converts individual characters, while `F_STRING_AS_BYTE` works with strings.

## Conclusion
The `F_STRING_AS_BYTE` function block offers a simple and efficient way to convert strings to byte values. Its clear interface structure and direct functionality make it ideal for applications requiring such conversion.
