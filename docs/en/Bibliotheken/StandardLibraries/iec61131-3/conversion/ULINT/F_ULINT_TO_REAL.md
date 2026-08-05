# F_ULINT_TO_REAL
<img width="1451" height="214" alt="F_ULINT_TO_REAL" src="https://github.com/user-attachments/assets/d7208c65-91e3-47f3-bfd6-6141f68edc4f" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_REAL` converts a `ULINT` value (64-bit unsigned integer) to a `REAL` value (32-bit floating-point number). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_ULINT_TO_REAL](F_ULINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `ULINT`, which is to be converted to a `REAL` value.

### **Data Outputs**
- **OUT**: The output value of type `REAL`, representing the result of the conversion.

### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is triggered. The algorithm within the function block uses the function ``ULINT_TO_REAL`` to convert the value ``ULINT`` into a value ``REAL``. The result is output via the data output ``OUT``, and the event ``CNF`` signals successful execution.

## Technical Features
- The function block is part of the package ``iec61131::conversion``.
- Supports the conversion of 64-bit unsigned integers to 32-bit floating-point numbers.
- Simple and direct implementation without additional parameters or complex logic.

## State Overview

The function block has a simple state machine:

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion.

3. **Complete**: Sends the `CNF` event and outputs the result.

## Application Scenarios
- Data processing in control systems where type conversion is required.
- Integration into larger control algorithms that perform floating-point calculations with values originally stored as integers.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_DINT_TO_REAL` or `F_LINT_TO_REAL` offer conversions from other integer types to `REAL`, but with different input sizes and precisions.
- `F_ULINT_TO_REAL` is specifically optimized for 64-bit unsigned integers.

## Conclusion
The `F_ULINT_TO_REAL` function block is a simple yet essential building block for type conversion in IEC 61499-based control systems. Its clear interface and efficient operation make it a reliable solution for conversion tasks.
