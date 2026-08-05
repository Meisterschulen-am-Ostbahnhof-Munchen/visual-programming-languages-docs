# F_ULINT_TO_DWORD

<img width="1465" height="214" alt="F_ULINT_TO_DWORD" src="https://github.com/user-attachments/assets/a6ee56d4-2343-4d88-8833-ac9e66579ade" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_DWORD` converts a `ULINT` value (64-bit unsigned integer) to a `DWORD` value (32-bit unsigned integer). This block is part of the `iec61131::conversion` package and enables simple and efficient type conversion.

![F_ULINT_TO_DWORD](F_ULINT_TO_DWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN** (`ULINT`): The 64-bit unsigned integer value to be converted to `DWORD`.

### **Data Outputs**

- **OUT** (`DWORD`): The resulting 32-bit unsigned integer value after the conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
The function block performs the conversion as soon as the `REQ` event is received. The `ULINT` value at input `IN` is converted to a `DWORD` value and output `OUT`. The conversion is confirmed by the `CNF` event.

## Technical Features

- Data loss can occur if the `ULINT` value is greater than the maximum representable value of a `DWORD` (2³² - 1).

- The function block is implemented as a simple FB (`SimpleFB`) and uses an ST algorithm for the conversion.


## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Conversion**: Performs the conversion and outputs the result via `OUT`.

3. **Acknowledgement**: Sends the `CNF` event and returns to the idle state.

## Application Scenarios

- Type conversion in control applications where 64-bit values need to be converted to 32-bit values.

- Data processing in systems with different word lengths.


## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_DINT_TO_DWORD` or `F_LINT_TO_DWORD` offer conversions between other data types, but not specifically from `ULINT` to `DWORD`.

- Unlike generic conversion blocks, this one is specialized and optimized for the `ULINT` to `DWORD` conversion.

## Conclusion
The `F_ULINT_TO_DWORD` function block provides a simple and efficient solution for converting 64-bit unsigned integers to 32-bit unsigned integers. Its clear interface structure and simple functionality make it ideal for applications that require such type conversions. However, be aware of the potential for data loss with large input values.