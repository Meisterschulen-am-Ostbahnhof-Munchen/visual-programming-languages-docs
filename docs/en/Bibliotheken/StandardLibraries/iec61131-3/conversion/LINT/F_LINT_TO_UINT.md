# F_LINT_TO_UINT
<img width="1436" height="214" alt="F_LINT_TO_UINT" src="https://github.com/user-attachments/assets/da4ca59c-9a44-4c2e-ad16-0ae14c1ab1de" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_UINT` is used to convert a 64-bit integer value (`LINT`) into a 16-bit unsigned integer value (`UINT`). This block is particularly useful in scenarios where type conversion between numeric data types of different sizes is required.
![F_LINT_TO_UINT](F_LINT_TO_UINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: This input expects a value of type `LINT` (64-bit integer) to be converted.

### **Data Outputs**
- **OUT**: This output returns the converted value of type `UINT` (16-bit unsigned integer).

### **Adapters**
No adapters are defined.

#
## ## Functionality

The function block performs the conversion from `LINT` to `UINT` as soon as the event `REQ` is triggered. The algorithm `REQ` uses the function `LINT_TO_UINT` to convert the input value. The result is output via `OUT`, and the event `CNF` signals successful execution.

## Technical Details
- **Type Conversion**: It is important to note that data loss can occur when converting from a larger to a smaller data type if the original value is outside the representable range of `UINT`.

# - **Efficiency**: The conversion is performed directly and without any additional delay.

## State Overview
The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios
- **Data Processing**: In control systems where different data types need to be harmonized.
- **Interface Compatibility**: For communication between systems that use different data types.

## ⚖️ Comparison with Similar Function Blocks
- **F_LINT_TO_INT**: Converts `LINT` to `INT`, while preserving the sign.
- **F_LINT_TO_ULINT**: Converts `LINT` to `ULINT` without reducing the bit width.

## Conclusion
The `F_LINT_TO_UINT` function block is a simple yet effective tool for type conversion in IEC 61499-based systems. Its clear interface and direct operation make it a reliable solution for conversion tasks. However, be aware of potential data loss during the conversion process.
