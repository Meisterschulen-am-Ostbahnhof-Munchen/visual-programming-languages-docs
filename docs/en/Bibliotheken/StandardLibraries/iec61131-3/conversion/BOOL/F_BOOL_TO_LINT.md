# F_BOOL_TO_LINT
<img width="1234" height="182" alt="F_BOOL_TO_LINT" src="https://github.com/user-attachments/assets/4c333a4d-5021-4e63-8ee2-fdf1494dd38f" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_LINT` converts a Boolean value (`BOOL`) into a 64-bit integer value (`LINT`). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_BOOL_TO_LINT](F_BOOL_TO_LINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: This input triggers the execution of the function block. It is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: This output signals the successful execution of the function block. It is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input for the Boolean value (`BOOL`) to be converted.

### **Data Outputs**
- **OUT**: The output for the converted 64-bit integer value (`LINT`).

### **Adapters**
This function block has no adapters.

## Functionality
The function block performs the conversion from `BOOL` to `LINT` when the event `REQ` is received. The conversion is performed using the function ``BOOL_TO_LINT(IN)``, where the Boolean value ``IN`` is converted into a value ``LINT``. The result is output at ``OUT``, and the event ``CNF`` is triggered.

## Technical Features
- The block is a simple function block (``SimpleFB``) and uses an ST algorithm for the conversion.
- The conversion is deterministic and occurs without delay.

## State Overview

The function block has no internal state. The conversion occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios
- Type conversion in control applications where Boolean values need to be converted to numeric values.
- Integration into larger systems that require consistent data type handling.

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks such as `F_BOOL_TO_INT` or `F_BOOL_TO_DINT`, this block offers higher precision through the use of the `LINT` data type (64-bit).

## Conclusion
The `F_BOOL_TO_LINT` function block is an efficient tool for converting Boolean values to 64-bit integer values. Its simple and deterministic operation makes it a reliable component in control applications.