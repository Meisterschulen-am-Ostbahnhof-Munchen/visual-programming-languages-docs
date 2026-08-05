# F_UDINT_TO_ULINT

<img width="1470" height="216" alt="F_UDINT_TO_ULINT" src="https://github.com/user-attachments/assets/71a1772b-ddff-44fd-b7e6-9dcd0ad29c71" />

* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_ULINT` converts a 32-bit unsigned integer (UDINT) value to a 64-bit unsigned integer (ULINT). This block is particularly useful when exchanging data between systems or components that use different integer sizes.

![F_UDINT_TO_ULINT](F_UDINT_TO_ULINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the function block reads the value at the data input `IN` and performs the conversion.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is activated along with the converted value at data output `OUT`.

### **Data Inputs**

- **IN**: The input for the 32-bit unsigned integer (UDINT) value to be converted.

### **Data Outputs**

- **OUT**: The output for the converted 64-bit unsigned integer (ULINT) value.

### **Adapters**
This function block does not use adapters.

## Operation
The function block performs a direct type conversion. When the ``REQ`` event is triggered, the value of ``IN`` is read and assigned to ``OUT`` without further processing. Since ULINT covers a larger range of values than UDINT, this conversion is always safe and lossless.

The algorithm is implemented as follows:


``````ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```
## Technical Features
- **Lossless Conversion**: Since ULINT can represent all values of UDINT, there is no data loss.

- **Simple Implementation**: The function block requires no additional logic or error handling.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- **Data Compatibility**: Used when systems need to communicate with different integer sizes.

- **Extended Value Range**: Enables the use of UDINT values in contexts that require ULINT.

## ⚖️ Comparison with Similar Function Blocks

- **F_UDINT_TO_LINT**: Converts UDINT to a 64-bit signed integer (LINT). In contrast, `F_UDINT_TO_ULINT` retains the unsigned character.

- **F_DINT_TO_ULINT**: Converts a 32-bit signed integer (DINT) to ULINT. `F_UDINT_TO_ULINT` is specific for unsigned values.

## Conclusion
The `F_UDINT_TO_ULINT` function block is a simple and efficient tool for safely converting 32-bit unsigned integers to 64-bit unsigned integers. Its lossless operation and ease of use make it ideal for applications requiring an extended range of values.