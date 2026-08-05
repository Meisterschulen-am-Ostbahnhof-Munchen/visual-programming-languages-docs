# F_STRING_AS_DWORD

<img width="1477" height="213" alt="F_STRING_AS_DWORD" src="https://github.com/user-attachments/assets/15d7b45e-4104-4052-a553-f9d43f45f903" />

* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_DWORD` converts a `STRING` value to a `DWORD` value. This functionality is particularly useful when strings need to be converted into numeric values, for example, for further processing in control algorithms.

![F_STRING_AS_DWORD](F_STRING_AS_DWORD.svg)

## Interface Structure
### **Event Inputs**

- `REQ`: Starts the execution of the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (`STRING`): The input value to be converted to a `DWORD` value.

### **Data Outputs**

- `OUT` (`DWORD`): The result of the conversion.

### **Adapters**

- No adapters available.


### ## Functionality

The function block converts the input value `STRING`, `IN`, into a value `DWORD` as soon as the event `REQ` is triggered. The conversion is performed using the function `STRING_AS_DWORD`. After successful conversion, the event `CNF` is triggered, and the result value is available at the output `OUT`.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and performs the conversion in a single algorithm.

- The conversion is performed directly without additional state management.

## State Overview
The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of user input or communication data into numeric values.

- Use in control algorithms that require numeric values instead of strings.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion function blocks such as `F_STRING_TO_INT` or `F_STRING_TO_REAL`, this function block is specifically designed for conversion to the `DWORD` data type.

- Direct use of the `STRING_AS_DWORD` function enables efficient and specialized conversion.


## Conclusion

The `F_STRING_AS_DWORD` function block offers a simple and efficient way to convert strings into `DWORD` values. Its clear interface structure and direct functionality make it ideal for applications requiring fast and reliable conversion.