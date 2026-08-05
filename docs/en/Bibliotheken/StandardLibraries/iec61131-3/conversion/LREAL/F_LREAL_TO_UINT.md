# F_LREAL_TO_UINT

<img width="1452" height="214" alt="F_LREAL_TO_UINT" src="https://github.com/user-attachments/assets/4379189d-901b-46e8-aab5-83f178f84371" />

* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_UINT` converts an LREAL value (64-bit floating-point number) to a UINT value (unsigned 16-bit integer). This block is part of the `iec61131::conversion` library and enables simple and efficient type conversion in automation applications.

![F_LREAL_TO_UINT](F_LREAL_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event occurs, the algorithm for converting the input value is executed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event is output after successful conversion of the value.

### **Data Inputs**

- **IN**: The input expects an LREAL number (64-bit floating-point number) to be converted into a UINT value.

### **Data Outputs**

- **OUT**: Outputs the result of the conversion as a UINT value (unsigned 16-bit integer).

#### **Adapters**
This function block has no adapters.

## Operation
When the `REQ` event occurs, the algorithm for converting the LREAL value at input `IN` into a UINT value is executed. The result is output at `OUT`, and the `CNF` event signals the successful completion of the operation.


# The algorithm uses the function `LREAL_TO_UINT` to directly convert the input value. Note that rounding down or overflow may occur when converting floating-point numbers to integers.

## Technical Specifications
- **Data Types**: The function block processes 64-bit floating-point numbers (LREAL) and outputs 16-bit unsigned integers (UINT).

- **Algorithm**: The conversion is performed directly by the built-in `LREAL_TO_UINT` function.

- **Error Handling**: The function block does not have built-in error handling for overflow or invalid input values.

## State Overview

1. **Wait State**: The function block waits for the `REQ` event.

2. **Execution State**: The conversion is performed at `REQ`.

3. **Confirmation State**: After successful conversion, `CNF` is output, and the function block returns to the wait state.

## Application Scenarios

- Conversion of sensor values (e.g., temperature measurements) into integer values for further processing.

- Type conversion in control applications where floating-point numbers are required to integers for specific operations.

- Interface adaptation between system components with different data types.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic conversion blocks, `F_LREAL_TO_UINT` is specialized for converting LREAL to UINT.

- Other conversion blocks might offer additional functions such as range checking or error handling, but are more complex to use.


## Conclusion

The `F_LREAL_TO_UINT` function block offers a simple and efficient solution for the specific conversion of 64-bit floating-point numbers to 16-bit unsigned integers. Its simple interface and direct operation make it ideal for applications where fast type conversion without additional functions is required. However, for applications with critical values, additional checks should be implemented.