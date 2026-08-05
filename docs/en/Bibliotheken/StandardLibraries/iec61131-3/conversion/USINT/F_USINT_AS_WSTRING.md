# F_USINT_AS_WSTRING
<img width="1495" height="214" alt="F_USINT_AS_WSTRING" src="https://github.com/user-attachments/assets/f7e08d34-adb5-4269-aad6-74d5d362a5a3" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_AS_WSTRING` converts an unsigned 8-bit integer value (`USINT`) into a Unicode string (`WSTRING`). This functionality is particularly useful in scenarios where numeric values need to be output or processed as text.
![F_USINT_AS_WSTRING](F_USINT_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**
- **IN**: An unsigned 8-bit integer value (`USINT`) to be converted to a Unicode string.

### **Data Outputs**
- **OUT**: The resulting Unicode string (`WSTRING`) after the conversion.

### **Adapters**
- No adapters are available.

## Operation
The function block performs the conversion as soon as the event `REQ` is triggered. The input value `IN` is taken and converted into a Unicode string using the function `USINT_AS_WSTRING`. The result is output `OUT`, and the event `CNF` signals successful execution.

## Technical Features
- Uses the built-in function `USINT_AS_WSTRING` for conversion.
- Supports the full value range of `USINT` (0 to 255).

## State Overview
1. **Idle**: Waits for the event `REQ`.

2. **Conversion**: Processes the input value and generates the output.

3. **Acknowledgement**: Sends the event `CNF` and returns to the idle state.

## Application Scenarios
- Displaying numeric values in user interfaces.
- Logging numeric data to text files.
- Communicating with systems that expect text data.

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_USINT_AS_WSTRING` specializes in converting `USINT` to `WSTRING`.
- Other blocks might support different data types or additional formatting options.

## Conclusion
The `F_USINT_AS_WSTRING` function block provides a simple and efficient way to convert unsigned 8-bit integer values to Unicode strings. Its clear interface and direct functionality make it ideal for projects that require such conversions.