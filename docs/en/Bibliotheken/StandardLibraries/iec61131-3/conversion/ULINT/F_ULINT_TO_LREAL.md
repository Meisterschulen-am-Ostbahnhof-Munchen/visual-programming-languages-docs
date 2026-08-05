# F_ULINT_TO_LREAL
<img width="1466" height="214" alt="F_ULINT_TO_LREAL" src="https://github.com/user-attachments/assets/deffb0a4-6080-4c01-b592-e27e26f1d382" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_LREAL` converts a `ULINT` value (64-bit unsigned integer) to a `LREAL` value (64-bit floating point). This conversion is particularly necessary in scenarios where integer values need to be converted to floating-point numbers for further calculations.
![F_ULINT_TO_LREAL](F_ULINT_TO_LREAL.svg)
## Interface Structure
### **Event Inputs**
- `REQ`: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- `CNF`: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**
- `IN` (`ULINT`): The input value to be converted.

### **Data Outputs**
- `OUT` (`LREAL`): The converted output value.

### **Adapters**
No adapters available.

#
## ## Functionality

The function block performs the conversion from `ULINT` to `LREAL` when the `REQ` event is triggered. The conversion is carried out using the built-in function `ULINT_TO_LREAL`. After the conversion is complete, the `CNF` event is triggered, and the converted value is made available at output `OUT`.

## Technical Features
- The function block has a simple structure and contains only one algorithm (`REQ`) that performs the conversion.
- The conversion is lossless because `LREAL` covers a larger range of values than `ULINT`.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of integer values to floating-point numbers for further calculations.
- Use in control systems where floating-point operations are required.

## ⚖️ Comparison with Similar Blocks
- Compared to other conversion blocks (e.g., `F_INT_TO_REAL`), this one is specifically optimized for converting 64-bit unsigned integers to 64-bit floating points.
- Similar blocks may have lower precision or a smaller range of values.

## Conclusion

The `F_ULINT_TO_LREAL` function block offers a simple and efficient way to convert `ULINT` values to `LREAL` values. Its clear interface and lossless conversion make it a useful component in various applications.
