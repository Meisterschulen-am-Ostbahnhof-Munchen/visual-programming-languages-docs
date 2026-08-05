# F_BYTE_TO_DINT
<img width="1234" height="183" alt="F_BYTE_TO_DINT" src="https://github.com/user-attachments/assets/33fb3b6c-7400-46dd-b1bd-7f5031adddf3" />
* * * * * * * * * *
## Introduction
The function block `F_BYTE_TO_DINT` converts a `BYTE` value to a `DINT` value. It is part of the `iec61131::conversion` library and enables simple and efficient type conversion between these two data types.
![F_BYTE_TO_DINT](F_BYTE_TO_DINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: This input triggers the execution of the function block. It is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: This output signals the successful execution of the function block. It is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input expects a `BYTE` value, which is to be converted to a `DINT` value.

### **Data Outputs**
- **OUT**: The output provides the converted `DINT` value.

### **Adapters**
This function block does not have any adapters.

#
## ## Functionality

The function block performs the conversion from `BYTE` to `DINT` as soon as the event `REQ` is received. The conversion is carried out using the function `BYTE_TO_DINT(IN)`, which converts the value of the input `IN` to the corresponding `DINT` value and outputs it as `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion is performed directly without any additional processing steps.

## State Overview
The function block has no internal states. The execution occurs once each time the `REQ` event is received.

## Application Scenarios
- Type conversion in control applications where `BYTE` data needs to be converted to `DINT` data.
- Integration into larger systems that require type compatibility between different data formats.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks such as `F_WORD_TO_DINT` or `F_INT_TO_DINT`, this function block is specifically designed for converting `BYTE` to `DINT`.
- It offers a simple and direct solution for this specific conversion.

## Conclusion

The `F_BYTE_TO_DINT` function block is a useful tool for type conversion in IEC 61131-3-based control systems. Its simple and efficient operation makes it a reliable solution for applications requiring conversion from `BYTE` to `DINT`.
