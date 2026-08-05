# F_LINT_AS_STRING
<img width="1256" height="183" alt="F_LINT_AS_STRING" src="https://github.com/user-attachments/assets/c1d86074-155a-49cf-b025-bacefa300e09" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_AS_STRING` converts a LINT data type (64-bit integer) to a STRING data type (character string). This block is particularly useful when numeric values are needed as text for output or further processing.
![F_LINT_AS_STRING](F_LINT_AS_STRING.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this event is triggered, the value at the data input `IN` is processed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event, along with the converted value, is output at data output `OUT`.

### **Data Inputs**
- **IN** (LINT): The input for the LINT value to be converted.

### **Data Outputs**
- **OUT** (STRING): The output for the converted STRING value.

#### **Adapters**
- No adapters are present.

## Functionality
When the `REQ` event is triggered, the function block converts the LINT value at input `IN` into a STRING value. The result is output at `OUT` and confirmed by the `CNF` event.

## Technical Features
- The function block is a simple function block (SimpleFB) and uses an ST algorithm for conversion.
- The conversion is performed directly by the function `LINT_AS_STRING(IN)`.

## State Overview

1. **Initialization**: The function block waits for the `REQ` event.

2. **Conversion**: The LINT value is converted upon `REQ`.

3. **Acknowledgement**: The `CNF` event is triggered, and the converted value is output.

## Application Scenarios
- Displaying numeric values in user interfaces.
- Logging numeric data to text files.
- Preparing data for communication via text-based protocols.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks like `F_INT_AS_STRING` or `F_DINT_AS_STRING`, this block supports the larger LINT data type (64-bit).

## Conclusion
The `F_LINT_AS_STRING` function block offers a simple and efficient way to convert large integers into readable strings. Its clear interface and straightforward operation make it ideal for applications requiring conversion between these data types.