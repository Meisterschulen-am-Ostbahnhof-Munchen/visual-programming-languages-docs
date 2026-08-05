# F_LINT_AS_WSTRING

<img width="1265" height="183" alt="F_LINT_AS_WSTRING" src="https://github.com/user-attachments/assets/541513e7-d8aa-464e-9e9c-48ecd85a527a" />

* * * * * * * * * *
## Introduction
The function block `F_LINT_AS_WSTRING` is used to convert a LINT value (64-bit integer) into a WSTRING (wide string). This block is particularly useful in scenarios where numeric values need to be output as strings or processed further.

![F_LINT_AS_WSTRING](F_LINT_AS_WSTRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the LINT value to a WSTRING. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN** (LINT): The LINT value to be converted to a WSTRING.

### **Data Outputs**

- **OUT** (WSTRING): The resulting WSTRING after conversion.

### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion as soon as the `REQ` event occurs. The LINT value from `IN` is converted to a WSTRING and output to `OUT`. The conversion is confirmed by the `CNF` event.


## Technical Features
- The function block uses the `LINT_AS_WSTRING` function for conversion.

- The conversion is performed directly without additional parameters.

## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Conversion State**: Performs the conversion and outputs the result.

3. **Confirmation State**: Sends the `CNF` event to confirm the conversion.

## Application Scenarios

- Displaying numeric values in user interfaces.

- Logging numeric data to text files.

- Communicating with systems that expect string data.


## ⚖️ Comparison with Similar Function Blocks

- **F_INT_AS_WSTRING**: Converts INT (16-bit) to WSTRING.

- **F_DINT_AS_WSTRING**: Converts DINT (32-bit) to WSTRING.

- **F_LINT_AS_STRING**: Converts LINT to STRING (not Wide String).

## Conclusion
The `F_LINT_AS_WSTRING` function block provides a simple and efficient way to convert 64-bit integers to wide strings. Its clear interface and direct functionality make it ideal for applications that require conversion between these data types.