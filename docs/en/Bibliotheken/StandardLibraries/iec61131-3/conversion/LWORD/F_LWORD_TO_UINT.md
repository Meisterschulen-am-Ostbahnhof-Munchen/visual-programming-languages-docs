# F_LWORD_TO_UINT

<img width="1451" height="216" alt="F_LWORD_TO_UINT" src="https://github.com/user-attachments/assets/1cbf487c-9149-449a-95ba-ada7735f19cc" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_UINT` converts a `LWORD` data type to a `UINT` data type. This function block is particularly useful in scenarios where type conversion between these two data types is required, for example, in communication between systems with different data formats.
![F_LWORD_TO_UINT](F_LWORD_TO_UINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This event input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution Confirmation. This event is triggered after successful conversion and is associated with the data output `OUT`.

### **Data Inputs**

- **IN**: Input data of type `LWORD` to be converted to the `UINT` data type.

### **Data Outputs**

- **OUT**: Output data of type `UINT` containing the result of the conversion.

### **Adapters**

No adapters available.

## Functionality

The function block performs the conversion from `LWORD` to `UINT` when the event `REQ` is received. The conversion is performed using the function `LWORD_TO_UINT(IN)`, which converts the value of `IN` and passes the result to `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- The function block is a simple algorithm (SimpleFB) and does not perform any complex state transitions.
- The conversion occurs directly without additional conditions or delays.

## State Overview

Since it is a simple function block, there are no explicit states. The functionality is limited to directly responding to the ``REQ`` event, subsequently outputting the converted value, and triggering the ``CNF`` event.

## Application Scenarios

- Type conversion in communication interfaces between systems that use different data types.
- Data processing in control systems where conversion from ``LWORD`` to ``UINT`` is required.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks could be ``F_DWORD_TO_UINT`` or ``F_WORD_TO_UINT``, which, however, process different input data types.
- The main difference lies in the input data type (`LWORD`), which has a larger bit width than `DWORD` or `WORD`.

## Conclusion

The `F_LWORD_TO_UINT` function block provides a simple and efficient way to convert `LWORD` data to the `UINT` data type. Its clear interface structure and direct functionality make it a useful component in various use cases, especially where type conversions between these data types are required.
