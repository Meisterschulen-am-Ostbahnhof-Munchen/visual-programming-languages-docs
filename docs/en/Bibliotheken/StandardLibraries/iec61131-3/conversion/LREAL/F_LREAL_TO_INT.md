# F_LREAL_TO_INT

<img width="1436" height="210" alt="F_LREAL_TO_INT" src="https://github.com/user-attachments/assets/4ae1ab8e-2e6b-42e5-835c-dd7f427c8a55" />
* * * * * * * * * *
## Introduction

The function block `F_LREAL_TO_INT` converts an LREAL value (64-bit floating-point number) into an INT value (16-bit integer). This conversion is performed by rounding the LREAL value down to the nearest integer value.
![F_LREAL_TO_INT](F_LREAL_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion of the input value. The input value is passed with this event.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion and outputs the converted value.

### **Data Inputs**

- `IN` (LREAL): The input value to be converted to an INT value.

### **Data Outputs**

- `OUT` (INT): The converted integer value.

### **Adapters**

This function block does not use any adapters.

## Functionality

Upon receiving the `REQ` event, the algorithm that converts the `IN` value from LREAL to INT is executed. The conversion is performed by the function `LREAL_TO_INT`, which rounds the LREAL value down to the nearest integer value. The result is output to `OUT`, and the `CNF` event is triggered.

## Technical Features

- The conversion truncates decimal places (not rounding, but rounding down).
- Overflow problems may occur with values outside the integer range.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of sensor values (e.g., temperature measurements) for processing in integer-based systems.
- Preparation of floating-point values for output on integer displays or interfaces.

## ⚖️ Comparison with Similar Function Blocks

- `F_REAL_TO_INT`: Converts REAL (32-bit floating-point number) to INT.
- `F_LREAL_TO_DINT`: Converts LREAL to DINT (32-bit integer) for a wider range of values.

## Conclusion

The `F_LREAL_TO_INT` function block is a simple yet effective tool for converting floating-point numbers to integers. It is particularly well-suited for applications requiring fast and direct conversion without additional logic. However, for values exceeding the INT range, alternative function blocks such as `F_LREAL_TO_DINT` should be considered.
