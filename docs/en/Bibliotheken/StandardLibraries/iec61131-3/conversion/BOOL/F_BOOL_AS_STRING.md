# F_BOOL_AS_STRING

<img width="1257" height="182" alt="F_BOOL_AS_STRING" src="https://github.com/user-attachments/assets/943966eb-d165-4fd6-aead-9d6b33d6078d" />
* * * * * * * * * *
## Introduction

The function block `F_BOOL_AS_STRING` is used to convert a Boolean value (`BOOL`) into a string (`STRING`). This functionality is particularly useful when Boolean values are needed for output or further processing in a text format.
![F_BOOL_AS_STRING](F_BOOL_AS_STRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The Boolean value (`BOOL`) to be converted into a string.

### **Data Outputs**

- **OUT**: The resulting string (`STRING`) representing the converted Boolean value.

### **Adapters**

No adapters are defined for this function block.

## Functionality

The function block uses a simple algorithm to convert the Boolean value `IN` into a string `OUT`. The conversion is performed by the function ``BOOL_AS_STRING(IN)``, which internally converts the value of ``IN`` into a corresponding string (e.g., ``TRUE`` or ``FALSE``).

## Technical Features

- The function block is implemented simply and efficiently, without additional states or complex logic.
- The conversion occurs synchronously with the triggering of the ``REQ`` event.

## State Overview

Since this is a simple function block, there are no explicit states. Execution occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios

- **Logging**: Conversion of Boolean values for logging purposes.
- **User Interfaces**: Display of Boolean values in a human-readable format.
- **Data Communication**: Preparation of Boolean values for transmission as text.

## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_TO_BOOL**: Performs the reverse conversion from `STRING` to `BOOL`.
- **F_BOOL_TO_***: Other conversion blocks that convert Boolean values into various data types.

## Conclusion

The `F_BOOL_AS_STRING` function block offers a simple and effective way to convert Boolean values to strings. Its clear interface and direct functionality make it a useful tool in many use cases.