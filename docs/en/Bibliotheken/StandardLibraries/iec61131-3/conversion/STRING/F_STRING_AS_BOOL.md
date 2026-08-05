# F_STRING_AS_BOOL
<img width="1462" height="213" alt="F_STRING_AS_BOOL" src="https://github.com/user-attachments/assets/493e97a2-4fe1-488e-b506-d4a41641a727" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_BOOL` converts a `STRING` value to a `BOOL` value. This block is particularly useful when strings need to be converted into Boolean values, for example, when processing user input or interpreting text data.
![F_STRING_AS_BOOL](F_STRING_AS_BOOL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request. This input triggers the conversion.

### **Event Outputs**
- **CNF**: Execution confirmation. This output signals the successful completion of the conversion.

### **Data Inputs**
- **IN** (`STRING`): The input string to be converted into a Boolean value.

### **Data Outputs**
- **OUT** (`BOOL`): The resulting Boolean value after conversion.

#### **Adapters**
No adapters are present.

## Functionality
The function block uses the function `STRING_AS_BOOL` to convert the input string `IN` into a Boolean value `OUT`. The conversion is triggered by the event `REQ`, and the event `CNF` is output upon completion of the operation.

## Technical Features
- The conversion is performed according to the IEC 61131-3 specification for converting strings to Boolean values.
- The function block is part of the `iec61131::conversion` package.

## State Overview

1. **Initialization**: The function block waits for the `REQ` event.

2. **Execution**: Upon receiving `REQ`, the string `IN` is converted to a Boolean value, and the result is output to `OUT`.

3. **Acknowledgement**: After successful conversion, the `CNF` event is output.

## Application Scenarios
- Processing user input in string form (e.g., "true" or "false").
- Interpreting text data from external sources (e.g., configuration files or network communication).
- Integration into systems that store or transmit Boolean values as strings.

## ⚖️ Comparison with Similar Function Blocks
- **F_STRING_TO_BOOL**: A similar function block that may offer additional options for string interpretation.
- **F_STRING_AS_***: Other conversion function blocks for various data types (e.g., `F_STRING_AS_INT`).

## Conclusion
The `F_STRING_AS_BOOL` function block provides a simple and efficient way to convert string values to Boolean values. Its clear interface structure and reliability make it ideal for applications requiring such conversion.