# F_LINT_TO_ULINT
<img width="1448" height="214" alt="F_LINT_TO_ULINT" src="https://github.com/user-attachments/assets/ad56b68e-ba86-4df1-ada2-b318dda134f6" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_ULINT` converts a signed 64-bit integer value (`LINT`) to an unsigned 64-bit integer value (`ULINT`). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_LINT_TO_ULINT](F_LINT_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: This input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: This output signals the completion of the conversion. It is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`LINT`): The signed 64-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`ULINT`): The unsigned 64-bit integer value output as the result of the conversion.

### **Adapters**
This function block has no adapters.

### ## Functionality

The function block performs the conversion from `LINT` to `ULINT` as soon as the event `REQ` is triggered. The conversion is carried out using the function `LINT_TO_ULINT(IN)`, which converts the value of `IN` into the corresponding unsigned type. After successful conversion, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The function block is a simple block without internal state management.
- The conversion occurs directly and without delay.

## State Overview
Since it is a simple function block, there are no state transitions or complex state logic.

## Application Scenarios
- Type conversion in control applications where signed and unsigned values need to be processed.
- Data processing in industrial automation systems where different data types need to be made compatible.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks could be `F_INT_TO_UINT` or `F_DINT_TO_UDINT`, but these are designed for smaller integer types.
- Unlike generic conversion function blocks, `F_LINT_TO_ULINT` is specialized for the 64-bit variants of the data types.

## Conclusion
The `F_LINT_TO_ULINT` function block provides a simple and efficient way to convert signed 64-bit integer values to unsigned values. Its clear interface structure and direct functionality make it a reliable tool in industrial automation.