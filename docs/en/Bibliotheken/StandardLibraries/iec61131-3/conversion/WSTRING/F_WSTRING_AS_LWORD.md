# F_WSTRING_AS_LWORD

<img width="1491" height="214" alt="F_WSTRING_AS_LWORD" src="https://github.com/user-attachments/assets/70e780c5-b20e-4cf1-86f9-bc905ada9d1e" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_LWORD` is used to convert a WSTRING data type to an LWORD data type. This functionality is particularly useful in scenarios where strings need to be converted into a binary form suitable for further processing.
![F_WSTRING_AS_LWORD](F_WSTRING_AS_LWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This event input triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. This event is output after successful conversion.

### **Data Inputs**

- **IN**: Input of type WSTRING. This is the string to be converted.

### **Data Outputs**

- **OUT**: Output of type LWORD. This is the result of the conversion.

### **Adapters**

No adapters available.

## Functionality

The function block performs the conversion from WSTRING to LWORD as soon as the event `REQ` is received. The conversion is carried out using the integrated function `WSTRING_AS_LWORD`. After successful conversion, the event `CNF` is output, along with the converted value.

## Technical Features

- The function block is a simple FB (SimpleFB) and uses an ST algorithm for the conversion.
- The conversion is performed directly and without any further delay.

## State Overview

1. **Idle**: Waits for the event `REQ`.
2. **Processing**: Performs the conversion.
3. **Completed**: Outputs the event `CNF` and returns to the idle state.

## Application Scenarios

- Conversion of strings to binary data for further processing in control systems.
- Use in protocol conversions where strings need to be converted to binary form.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion function blocks such as `F_STRING_AS_LWORD`, this function block specifically works with the WSTRING data type, which supports Unicode characters.

## Conclusion

The `F_WSTRING_AS_LWORD` function block provides a simple and efficient way to convert WSTRING data to LWORD data. Its clear interface structure and direct functionality make it a useful tool in various applications.
