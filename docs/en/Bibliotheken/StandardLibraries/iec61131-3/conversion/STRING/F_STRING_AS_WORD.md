# F_STRING_AS_WORD

<img width="1472" height="212" alt="F_STRING_AS_WORD" src="https://github.com/user-attachments/assets/8e482512-b995-4049-9756-73367fae1729" />

* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_WORD` is used to convert a `STRING` value to a `WORD` value. This functionality is particularly useful in scenarios where strings need to be converted into numeric values for use in further calculations or control logic.

![F_STRING_AS_WORD](F_STRING_AS_WORD.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Normal execution request input. Used to start the conversion. Connected to the data input `IN`.


### **Event Outputs**

- **CNF**: Execution Confirmation. Triggered after successful conversion. Associated with the data output `OUT`.

### **Data Inputs**

- **IN**: Input of type `STRING`. Contains the string value to be converted.

### **Data Outputs**

- **OUT**: Output of type `WORD`. Contains the result of the input string conversion.

### **Adapters**
No adapters available.

## Functionality
The function block performs the conversion when the event `REQ` is received. The input string `IN` is converted into a `WORD` value using the function `STRING_AS_WORD`, and the result is output to `OUT`. The confirmation event `CNF` is then triggered.

## Technical Features

- The function block has a simple structure and contains only one conversion algorithm.

- The conversion is performed directly without additional state management.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of user input or communication data into numerical values.

- Use in control logic that requires numerical processing.

- Integration into larger automation systems that process string and word data.

## ⚖️ Comparison with similar function blocks

- Compared to other conversion function blocks such as `F_STRING_TO_INT` or `F_STRING_TO_REAL`, this function block specifically converts to the `WORD` data type.

- Simpler and more direct than function blocks with additional features such as error handling or formatting.

## Conclusion
The `F_STRING_AS_WORD` function block offers a simple and efficient way to convert strings to `WORD` values. Its clear interface and direct functionality make it ideal for use in various automation and control scenarios.