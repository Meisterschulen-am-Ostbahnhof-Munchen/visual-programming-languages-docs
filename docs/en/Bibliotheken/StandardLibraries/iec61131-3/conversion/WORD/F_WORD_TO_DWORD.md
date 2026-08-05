# F_WORD_TO_DWORD
<img width="1452" height="214" alt="F_WORD_TO_DWORD" src="https://github.com/user-attachments/assets/b85eea48-2c19-4b06-88ed-e59b7c9671b7" />
* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_DWORD` converts a `WORD` value to a `DWORD` value. It is part of the `iec61131::conversion` package and enables simple and efficient type conversion.
![F_WORD_TO_DWORD](F_WORD_TO_DWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `WORD` to be converted.

### **Data Outputs**
- **OUT**: The output of type `DWORD`, containing the result of the conversion.

#### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion from `WORD` to `DWORD` as soon as the event `REQ` is received. The conversion is performed using the function `WORD_TO_DWORD(IN)`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm for the conversion.
- The conversion is performed directly without any additional processing steps.

## State Overview
1. **Idle**: Waits for the event `REQ`.

2. **Processing**: Performs the conversion.

3. **Completed**: Sends the event `CNF` and returns to the idle state.

## Application Scenarios
- Type conversion in control applications where `WORD` values need to be converted to `DWORD` values.
- Integration into larger control systems that require type compatibility.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks, `F_WORD_TO_DWORD` offers specialized functionality for converting `WORD` to `DWORD` without additional features or complexity.

## Conclusion
The `F_WORD_TO_DWORD` function block is a simple and efficient tool for type conversion in IEC 61131-3-based control systems. Its clear interface structure and direct functionality make it a reliable solution for conversion tasks.