# F_USINT_TO_DWORD

<img width="1464" height="214" alt="F_USINT_TO_DWORD" src="https://github.com/user-attachments/assets/b8d67a72-e0b2-46fb-ac98-031aa3054888" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_DWORD` converts a `USINT` value (8-bit unsigned integer) to a `DWORD` value (32-bit unsigned integer). This conversion is particularly useful when data needs to be exchanged or processed between systems with different word lengths.
![F_USINT_TO_DWORD](F_USINT_TO_DWORD.svg)
## Interface Structure

### **Event Inputs**

- `REQ` (Normal Execution Request): Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- `CNF` (Execution Confirmation): Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- `IN` (USINT): The input value to be converted. The data type is `USINT` (8-bit unsigned integer).

### **Data Outputs**

- `OUT` (DWORD): The converted output value. The data type is `DWORD` (32-bit unsigned integer).

### **Adapters**

No adapters available.

## Functionality

The function block performs the conversion from `USINT` to `DWORD` as soon as the event `REQ` is triggered. The algorithm `REQ` uses the function `USINT_TO_DWORD` to convert the input value `IN` to the output value `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- The function block has a simple structure and contains only one algorithm.
- The conversion is performed without data loss because the `DWORD` data type covers a larger value range than `USINT`.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion.
3. **Acknowledgement State**: Triggers the `CNF` event and returns to the idle state.

## Application Scenarios

- Data conversion in control systems that use different word lengths.
- Integration of peripheral devices that deliver data in different formats.
- Data processing in industrial automation solutions.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_BYTE_TO_DWORD` or `F_WORD_TO_DWORD` offer conversions between other data types.
- `F_USINT_TO_DWORD` specializes in converting 8-bit unsigned integers to 32-bit unsigned integers.

## Conclusion

The `F_USINT_TO_DWORD` function block is a simple and efficient tool for converting `USINT` values to `DWORD` values. Its clear interface structure and simple functionality make it a reliable solution for data conversion tasks in industrial automation systems.
