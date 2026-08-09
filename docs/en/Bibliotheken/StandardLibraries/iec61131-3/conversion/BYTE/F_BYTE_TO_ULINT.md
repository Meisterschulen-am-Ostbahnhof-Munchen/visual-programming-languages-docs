# F_BYTE_TO_ULINT

<img width="1451" height="212" alt="F_BYTE_TO_ULINT" src="https://github.com/user-attachments/assets/d4e7fc4c-195c-4c12-b30d-9326c5eea4de" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_TO_ULINT` converts a `BYTE` value to a `ULINT` value. This conversion is particularly useful in scenarios where data of varying sizes needs to be processed or transferred.
![F_BYTE_TO_ULINT](F_BYTE_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: This input triggers the execution of the function block. The input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: This output signals the successful execution of the function block. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a `BYTE` value, which is to be converted to a `ULINT` value.

### **Data Outputs**

- **OUT**: The output provides the converted `ULINT` value.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion from `BYTE` to `ULINT` as soon as the event `REQ` is received. The conversion is performed using the function ``BYTE_TO_ULINT``, which converts the input value ``IN`` into the corresponding value ``ULINT``. After successful conversion, the event ``CNF`` is triggered, and the converted value is available at the output ``OUT``.

## Technical Features

- The function block has a simple structure and contains only one conversion algorithm.
- The conversion is performed without additional parameters or complex logic.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios

- Data conversion in control applications where `BYTE` values need to be converted to larger data types such as `ULINT`.
- Integration into larger systems that require uniform data processing in `ULINT`.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_WORD_TO_ULINT` or `F_DWORD_TO_ULINT` perform conversions from other data types to `ULINT`. `F_BYTE_TO_ULINT` is specifically for converting `BYTE`.

## Conclusion

The `F_BYTE_TO_ULINT` function block offers a simple and efficient way to convert `BYTE` values into `ULINT` values. Its clear interface and direct functionality make it a useful component in automation technology.