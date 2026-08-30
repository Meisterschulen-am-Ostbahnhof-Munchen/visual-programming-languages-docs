# F_WSTRING_TO_STRING

<img width="1507" height="214" alt="F_WSTRING_TO_STRING" src="https://github.com/user-attachments/assets/7dab60b1-32bc-41ee-a2f0-2ca57a0e11e2" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_TO_STRING` is used to convert a WSTRING data type to a STRING data type. This function block is particularly useful in scenarios where converting wide strings (Unicode) to simple strings (ASCII or similar) is required.
![F_WSTRING_TO_STRING](F_WSTRING_TO_STRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event is triggered, the WSTRING input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion and outputs the result via the STRING output `OUT`.

### **Data Inputs**

- **IN** (WSTRING): The input string in WSTRING format to be converted.

### **Data Outputs**

- **OUT** (STRING): The converted string in STRING format.

### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The conversion is performed using the integrated function `WSTRING_TO_STRING`, which converts the WSTRING input `IN` into a STRING output `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- The function block does not support any additional parameters or configurations for the conversion.
- The conversion is performed directly without intermediate storage.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Complete**: Triggers `CNF` and outputs the result.

## Application Scenarios

- Conversion of Unicode text to ASCII text.
- Use in systems that do not support wide strings.
- Integration into existing systems that only work with STRING data types.

## ⚖️ Comparison with Similar Function Blocks

- Unlike generic conversion blocks, `F_WSTRING_TO_STRING` specializes in converting WSTRING to STRING.
- Similar function blocks might offer additional options such as character set conversion, but this block is limited to basic functionality.

## Conclusion

The `F_WSTRING_TO_STRING` function block provides a simple and efficient way to convert WSTRING data to STRING data. Its clear interface and direct functionality make it ideal for projects that require fast and straightforward conversion.
