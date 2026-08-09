# F_WSTRING_AS_BOOL

<img width="1480" height="214" alt="image" src="https://github.com/user-attachments/assets/fba2dd5d-7fa7-4291-b6c5-c59d389db81c" />
* * * * * * * * * *
## Introduction

The function block `F_WSTRING_AS_BOOL` is used to convert a WSTRING value to a BOOL value. This is particularly useful in scenarios where strings need to be converted to Boolean values, for example, when processing user input or interpreting configuration data.
![F_WSTRING_AS_BOOL](F_WSTRING_AS_BOOL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**

- **IN**: WSTRING. The input value to be converted to a BOOL value.

### **Data Outputs**

- **OUT**: BOOL. The result of the conversion.

### **Adapters**

No adapters available.

## Functionality

The function block performs the conversion when the event `REQ` is received. The conversion is carried out using the function `WSTRING_AS_BOOL`, which converts the WSTRING input value `IN` into a BOOL value `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- The conversion is performed directly and without any additional delay.
- The function block is implemented as a simple function block (SimpleFB) and uses an ST algorithm for the conversion.

## State Overview

1. **Idle**: Waits for the event `REQ`.
2. **Processing**: Performs the conversion.
3. **Complete**: Triggers the event `CNF` and returns to the idle state.

## Application Scenarios

- Processing user input in string form.
- Interpreting configuration files that store Boolean values as strings.
- Interfaces between systems that use different data types.

## ⚖️ Comparison with Similar Function Blocks

- **F_STRING_AS_BOOL**: Converts STRING to BOOL instead of WSTRING.
- **F_BOOL_AS_WSTRING**: Performs the reverse conversion (BOOL to WSTRING).

## Conclusion

The `F_WSTRING_AS_BOOL` function block offers a simple and efficient way to convert WSTRING values to BOOL values. Its clear interface structure and direct functionality make it a useful tool in various application scenarios.