# F_STRING_AS_TIME
<img width="1467" height="220" alt="F_STRING_AS_TIME" src="https://github.com/user-attachments/assets/58d71ae2-9654-4005-b405-0b569a14e4f1" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_TIME` converts a time value in STRING format to TIME format. This is particularly useful when time values are in text format and need to be converted into a machine-readable format for further processing.
![F_STRING_AS_TIME](F_STRING_AS_TIME.svg)
## Interface Structure
### **Event Inputs**
- `REQ`: Starts the conversion of the time value. When this event input is triggered, the function block begins converting the string passed to `IN`.

### **Event Outputs**
- `CNF`: Signals the successful completion of the conversion. This event, along with the converted time value, is output at data output `OUT`.

### **Data Inputs**
- `IN` (STRING): The input for the time value in STRING format, which is to be converted to TIME format.

### **Data Outputs**
- `OUT` (TIME): The output at which the converted time value is displayed in TIME format.

#### **Adapters**
No adapters are available.

## Functionality
The function block uses the built-in function `STRING_AS_TIME` to convert the string received via input `IN` into a TIME value. The conversion is triggered by the event `REQ` and confirmed by the event `CNF` upon successful conversion.

## Technical Features
- The conversion is performed directly without intermediate steps.
- The function block is part of the package `iec61131::conversion`.

## State Overview
1. **Idle**: The function block waits for the event `REQ`.

2. **Processing**: Upon receiving `REQ`, the conversion is performed.

3. **Completion**: After successful conversion, the event `CNF` is triggered, and the state changes back to Idle.

## Application Scenarios
- Processing of time values that are available as text in user input or external data sources.
- Integration into systems that require time values in TIME format for control or regulation tasks.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks, `F_STRING_AS_TIME` specializes in converting time values and therefore offers a direct and efficient solution for this specific use case.

## Conclusion
The `F_STRING_AS_TIME` function block is an efficient tool for converting time values in STRING format to TIME format. Its simple and direct operation makes it ideal for applications that require fast and reliable conversion.