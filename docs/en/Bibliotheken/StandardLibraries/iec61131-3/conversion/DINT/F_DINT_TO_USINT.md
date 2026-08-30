# F_DINT_TO_USINT

<img width="1451" height="213" alt="F_DINT_TO_USINT" src="https://github.com/user-attachments/assets/843c633e-25cf-4450-8dd4-2682e876426a" />
* * * * * * * * * *
The function block `F_DINT_TO_USINT` converts a 32-bit integer value (DINT) to an 8-bit unsigned integer value (USINT). This conversion is useful when data needs to be exchanged between systems or components that use different data types.
![F_DINT_TO_USINT](F_DINT_TO_USINT.svg)
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.
- **IN**: The input value of type `DINT` (32-bit integer) to be converted.
- **OUT**: The output value of type `USINT` (8-bit unsigned integer) containing the result of the conversion.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block does not use any adapters.

When the event input `REQ` is triggered, the algorithm is executed. This algorithm converts the value at input `IN` (of type `DINT`) into a value of type `USINT` and outputs the result at output `OUT`. The event output `CNF` is then activated to signal the successful completion of the conversion.

- The conversion is performed by the built-in function `DINT_TO_USINT`.
- Please note that data loss may occur during the conversion from `DINT` to `USINT`, as the value range of `USINT` (0 to 255) is smaller than that of `DINT` (-2,147,483,648 to 2,147,483,647).

1. **Idle State**: The function block is waiting for the event `REQ`.
2. **Active State**: Upon receiving `REQ`, the conversion is performed and `CNF` is triggered.

- Data conversion in control systems when different data types are used.
- Reduction of memory usage when only small unsigned values are required.
- Interface adaptation between different system components.
- **F_INT_TO_USINT**: Converts a 16-bit integer value (INT) to an 8-bit unsigned integer value (USINT). In comparison, `F_DINT_TO_USINT` processes larger input values.
- **F_LINT_TO_USINT**: Converts a 64-bit integer value (LINT) to an 8-bit unsigned integer value (USINT). `F_DINT_TO_USINT` is designed for smaller input ranges.

The function block `F_DINT_TO_USINT` offers a simple and efficient way to convert 32-bit integers to 8-bit unsigned integers. It is particularly useful in scenarios where memory space needs to be optimized or data needs to be exchanged between systems with different data types. However, due to the potential for data loss, it should be ensured that the input values are within the valid range of `USINT`.

## Functionality

## Application Scenarios

## State Overview

## Technical Features

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
