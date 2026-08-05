# F_DWORD_TO_INT

<img width="1233" height="184" alt="F_DWORD_TO_INT" src="https://github.com/user-attachments/assets/06ada230-9c73-4717-8b06-0aee3362b757" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_INT` converts a DWORD value to an INT value. It is part of the package `iec61131::conversion` and enables easy conversion between these two data types.

![F_DWORD_TO_INT](F_DWORD_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion process. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.


### **Data Inputs**

- **IN**: The input of type `DWORD`, containing the value to be converted.

### **Data Outputs**

- **OUT**: The output of type `INT`, providing the result of the conversion.

#### **Adapters**
This function block has no adapters.

## Operation
When an event is received at input `REQ`, the algorithm is executed, converting the value of `IN` (of type `DWORD`) to a value of type `INT`. The result is output at `OUT` and confirmed by the event `CNF`.


## Technical Features
- The function block uses the standard function `DWORD_TO_INT` for conversion.

- It is a simple function block without internal states or complex logic.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Conversion of DWORD values supplied by hardware or other systems into INT values for further processing.

- Integration into control systems that need to process different data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks such as `F_WORD_TO_INT` or `F_BYTE_TO_INT`, this function block is specifically optimized for converting DWORD to INT.

- It offers a simple and direct solution without additional functions or parameters.

## Conclusion
The `F_DWORD_TO_INT` function block is a useful tool for converting between DWORD and INT data types. Its simplicity and direct functionality make it a reliable solution for various use cases.