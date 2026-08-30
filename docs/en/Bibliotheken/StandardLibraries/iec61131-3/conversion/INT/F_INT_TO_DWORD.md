# F_INT_TO_DWORD

<img width="1233" height="182" alt="F_INT_TO_DWORD" src="https://github.com/user-attachments/assets/2e21163c-54a9-4408-b67f-b1a8a5dc7dee" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_DWORD` converts an integer value (INT) to a double-word value (DWORD). This conversion is particularly useful when exchanging data between systems that use different data types.
![F_INT_TO_DWORD](F_INT_TO_DWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Confirms the successful execution of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (INT): The integer value to be converted to a DWORD value.

### **Data Outputs**

- **OUT** (DWORD): The resulting DWORD value after conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs the INT to DWORD conversion as soon as the event `REQ` is triggered. The conversion is carried out using the function `INT_TO_DWORD`, which converts the input value `IN` to the output value `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- This function block is a simple function block (SimpleFB) and uses an ST algorithm for conversion.
- The conversion is performed directly and without any additional delay.

## State Overview

The function block has no internal states. The conversion occurs immediately after the `REQ` event is triggered.

## Application Scenarios

- Data conversion in control systems that use different data types.
- Integration of systems that generate INT values but require DWORD values.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion blocks such as `F_INT_TO_REAL` or `F_DWORD_TO_INT`, this function block specializes in converting INT to DWORD.
- Simpler and more direct than universal conversion blocks that support multiple data types.

## Conclusion

The `F_INT_TO_DWORD` function block is an efficient and simple tool for converting integer to double-word values. Its clear interface and direct functionality make it ideal for applications requiring fast and reliable data type conversion.
