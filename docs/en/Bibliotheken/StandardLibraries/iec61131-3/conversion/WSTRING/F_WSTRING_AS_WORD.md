# F_WSTRING_AS_WORD
<img width="1482" height="214" alt="F_WSTRING_AS_WORD" src="https://github.com/user-attachments/assets/a3b2eb5b-24e3-4685-bc76-b8864d468811" />
* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_WORD` converts a WSTRING data type to a WORD data type. This functionality is particularly useful when strings need to be converted into numeric values, for example, for further processing in control algorithms.
![F_WSTRING_AS_WORD](F_WSTRING_AS_WORD.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the successful completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: Expects an input of type `WSTRING`, which is to be converted into a `WORD` value.

### **Data Outputs**
- **OUT**: Returns the result of the conversion as `WORD`.

### **Adapters**
This function block has no adapters.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The conversion is performed using the function ``WSTRING_AS_WORD``, which converts the input ``WSTRING`` into a value ``IN`` and outputs the result via the output ``OUT``. Successful execution is signaled by the event ``CNF``.

## Technical Features
- The conversion is performed directly without additional parameters.
- The function block is optimized for use in IEC 61131-compliant environments.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the event ``REQ``.

## Application Scenarios
- Conversion of strings to numeric values for control commands.

## - Processing text input in numerical control systems.
- Integration into systems that require conversion between different data types.

## ⚖️ Comparison with similar function blocks
- Compared to generic conversion function blocks, `F_WSTRING_AS_WORD` specializes in converting `WSTRING` to `WORD`.
- Other function blocks might offer additional parameters or error handling, but this function block is designed for simplicity and efficiency.

## Conclusion
The `F_WSTRING_AS_WORD` function block provides a simple and efficient way to convert `WSTRING` data to `WORD` values. Its clear interface and direct operation make it ideal for applications that require fast and reliable conversions.