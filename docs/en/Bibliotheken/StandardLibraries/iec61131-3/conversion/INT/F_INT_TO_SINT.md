# F_INT_TO_SINT

<img width="1222" height="187" alt="F_INT_TO_SINT" src="https://github.com/user-attachments/assets/81773477-cbb0-47ae-bfa8-b2bda3807bca" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_SINT` converts an integer value of type `INT` into a signed 8-bit integer value of type `SINT`. This conversion is useful when data needs to be exchanged or processed between systems with different data types.
![F_INT_TO_SINT](F_INT_TO_SINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `INT` to be converted.

### **Data Outputs**

- **OUT**: The converted output value of type `SINT`.

### **Adapters**

No adapters are present.

## Functionality

This function block performs the conversion from `INT` to `SINT` as soon as the event `REQ` is triggered. The algorithm within the block uses the function ``INT_TO_SINT`` to perform the conversion. After the conversion is complete, the event ``CNF`` is triggered, and the converted value is available at the output ``OUT``.

## Technical Features

- The function block has a simple structure and contains only one algorithm for the conversion.
- There is no additional error handling for overflow or underflow conditions. The user must ensure that the input value is within the valid range for ``SINT`` (-128 to 127).

## State Overview

The function block has no internal states. The conversion occurs immediately after the ``REQ`` event is triggered.

## Application Scenarios

- Data conversion in control systems where different data types need to be processed.
- Communication between systems that use different data types.
- Reducing memory usage when a smaller data type is sufficient.

## ⚖️ Comparison with Similar Function Blocks

- **F_INT_TO_USINT**: Converts `INT` to `USINT` (unsigned 8-bit integer).
- **F_INT_TO_DINT**: Converts `INT` to `DINT` (32-bit integer), which does not involve data reduction.
- **F_INT_TO_REAL**: Converts `INT` to `REAL` (floating-point number).

## Conclusion

The `F_INT_TO_SINT` function block is a simple and efficient tool for converting `INT` to `SINT` values. It is particularly suitable for applications that need to optimize storage space or exchange data between systems with different data types. However, users should ensure that the input values are within the valid range for `SINT` to avoid unexpected results.