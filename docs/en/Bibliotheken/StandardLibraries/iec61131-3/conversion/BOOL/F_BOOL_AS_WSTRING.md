# F_BOOL_AS_WSTRING
<img width="1267" height="182" alt="F_BOOL_AS_WSTRING" src="https://github.com/user-attachments/assets/846eba87-3267-475f-8b1c-02faddc7fcca" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_AS_WSTRING` converts a Boolean value (`BOOL`) into a wide string (`WSTRING`). This functionality is particularly useful when Boolean values need to be output or further processed in a human-readable format.
![F_BOOL_AS_WSTRING](F_BOOL_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**
- `REQ`: Starts the conversion of the Boolean input value `IN`.

### **Event Outputs**
- `CNF`: Signals the completion of the conversion and returns the result `OUT`.

### **Data Inputs**
- `IN` (`BOOL`): The Boolean value to be converted.

### **Data Outputs**
- `OUT` (`WSTRING`): The converted value as a wide string.

### **Adapters**
No adapters available.

## Functionality
This function block converts the Boolean input value `IN` into a wide string (`WSTRING`). The conversion is performed using the function ``BOOL_AS_WSTRING``, which converts the value ``TRUE`` to ``"TRUE"`` and ``FALSE`` to ``"FALSE"``. The conversion is triggered by the event ``REQ``, and the result is confirmed by the event ``CNF``.

## Technical Features
- The function block has a simple structure and contains only one conversion algorithm.
- The conversion is performed directly and without delay.

## State Overview

The function block has no internal states. The conversion occurs immediately after the ``REQ`` event is triggered.

## Application Scenarios
- Displaying Boolean values in user interfaces.
- Logging Boolean states to log files.
- Further processing of Boolean values in systems that expect strings.

## ⚖️ Comparison with Similar Function Blocks
- Unlike `F_BOOL_TO_STRING`, this function block generates a wide string (`WSTRING`) instead of a regular string (`STRING`).
- Similar function blocks like `F_INT_AS_WSTRING` or `F_REAL_AS_WSTRING` convert other data types to `WSTRING`.

## Conclusion
The function block `F_BOOL_AS_WSTRING` provides a simple and efficient way to convert Boolean values to wide strings. Its slim design makes it particularly suitable for applications where fast and uncomplicated conversion is required.