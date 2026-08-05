# F_STRING_TO_WSTRING
<img width="1509" height="212" alt="F_STRING_TO_WSTRING" src="https://github.com/user-attachments/assets/4ece7977-3ec9-493b-8cb5-e1ba73c202f8" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_TO_WSTRING` converts a `STRING` data type to a `WSTRING` data type. This is particularly useful in environments where conversion between narrow (8-bit) and wide (16-bit) strings is required, for example, when internationalizing applications or communicating with systems that use different character encodings.
![F_STRING_TO_WSTRING](F_STRING_TO_WSTRING.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Initiates the conversion. When this event is triggered, the input value `IN` is read and processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event is output along with the converted output value `OUT`.

### **Data Inputs**
- **IN** (`STRING`): The input string to be converted to `WSTRING`.

### **Data Outputs**
- **OUT** (`WSTRING`): The resulting wide string after the conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
The function block performs the conversion as soon as the `REQ` event arrives. The value `STRING` from `IN` is converted to `WSTRING` using the function `STRING_TO_WSTRING`, and the result is output to `OUT`. Simultaneously, the `CNF` event is triggered to signal the successful completion of the operation.

## Technical Features
- The conversion is performed without additional parameters or configuration.
- The block is implemented as a simple function block (`SimpleFB`), which guarantees efficient execution.

## State Overview

The function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios
- **Internationalization**: Conversion of local strings to Unicode-enabled `WSTRING` values.
- **System Communication**: Exchange of data between systems using different character sets.
- **Data Processing**: Processing of text data in different encodings.

## ⚖️ Comparison with Similar Building Blocks
- Compared to generic conversion blocks, `F_STRING_TO_WSTRING` specializes in converting between `STRING` and `WSTRING`.
- Other blocks, such as `F_WSTRING_TO_STRING`, offer the reverse functionality.

## Conclusion
The `F_STRING_TO_WSTRING` function block is a simple and efficient tool for converting strings between different encodings. Its clear interface and direct functionality make it particularly suitable for applications that require fast and reliable conversion.