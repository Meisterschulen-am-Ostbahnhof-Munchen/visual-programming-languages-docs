# F_WSTRING_AS_DINT

<img width="1480" height="214" alt="F_WSTRING_AS_DINT" src="https://github.com/user-attachments/assets/364137ca-5b73-4be9-b4dd-475b9e5b8768" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_DINT` converts a WSTRING value to a DINT value. It is part of the package `iec61131::conversion` and enables the easy conversion of wide strings to integer values.
![F_WSTRING_AS_DINT](F_WSTRING_AS_DINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**

- **IN**: Input variable of type `WSTRING`. Contains the string to be converted.

### **Data Outputs**

- **OUT**: Output variable of type `DINT`. Contains the result of the conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block converts the value of the input variable `IN` of type `WSTRING` to a value of type `DINT` and stores the result in the output variable `OUT`. The conversion is performed by calling the function `WSTRING_AS_DINT` within the algorithm `REQ`.

## Technical Features

- The conversion is performed directly via the built-in function `WSTRING_AS_DINT`.
- The function block is simple and has no additional states or complex logic.

## State Overview

The function block has no internal states. Execution occurs directly upon receiving the `REQ` event.

## Application Scenarios

- Conversion of user input into numeric values.
- Processing of strings containing numeric data in control systems.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_STRING_AS_DINT` convert simple strings (`STRING`) to `DINT`, while this block processes wide strings (`WSTRING`).
- Compared to generic conversion blocks, this one is specifically designed to convert ``WSTRING`` to ``DINT``.

## Conclusion

The ``F_WSTRING_AS_DINT`` function block provides a simple and efficient way to convert wide strings to integer values. It is particularly useful in scenarios where wide strings need to be processed.