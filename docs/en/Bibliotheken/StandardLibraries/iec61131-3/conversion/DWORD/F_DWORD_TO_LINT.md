# F_DWORD_TO_LINT
<img width="1246" height="184" alt="F_DWORD_TO_LINT" src="https://github.com/user-attachments/assets/ac17b63e-de6d-4ccb-9123-b8d797333e3e" />
* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_LINT` converts a `DWORD` value to a `LINT` value. This conversion is particularly useful when data needs to be exchanged between systems or components that use different data types.
![F_DWORD_TO_LINT](F_DWORD_TO_LINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `DWORD`, which is to be converted to a `LINT` value.

### **Data Outputs**
- **OUT**: The output value of type `LINT`, which contains the result of the conversion.

### **Adapters**
This function block does not use any adapters.

### ## Functionality
When an event is received at input `REQ`, the algorithm is executed. This algorithm converts the `DWORD` value at input `IN` into a `LINT` value and outputs the result at output `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features
- The function block has a simple structure and contains only one algorithm that performs the conversion.
- The conversion is performed directly without any additional processing steps.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios
- Converting data between systems that use different data types.
- Use in control systems where type conversion is required.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion function blocks, `F_DWORD_TO_LINT` specializes in converting `DWORD` to `LINT`.
- Other function blocks could perform similar conversions for other data types, such as `F_WORD_TO_INT`.

## Conclusion
The `F_DWORD_TO_LINT` function block is a simple and efficient tool for converting `DWORD` values to `LINT` values. Its clear interface structure and direct functionality make it a reliable solution for type conversions in control systems.