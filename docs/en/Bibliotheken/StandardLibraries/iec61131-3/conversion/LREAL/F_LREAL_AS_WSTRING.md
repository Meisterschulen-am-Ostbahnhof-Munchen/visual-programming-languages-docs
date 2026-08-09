# F_LREAL_AS_WSTRING

<img width="1280" height="182" alt="F_LREAL_AS_WSTRING" src="https://github.com/user-attachments/assets/440d684c-51cd-48e7-a918-9a5a0d6dcc22" />
* * * * * * * * * *
## Introduction

The function block `F_LREAL_AS_WSTRING` converts an LREAL value (64-bit floating-point number) into a WSTRING (wide string). This is particularly useful when numeric values are needed for display or further processing as text.
![F_LREAL_AS_WSTRING](F_LREAL_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the input value. The input value `IN` is associated with this event.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output value `OUT` is output with this event.

### **Data Inputs**

- **IN** (LREAL): The input value to be converted to a WSTRING.

### **Data Outputs**

- **OUT** (WSTRING): The result string after conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

When the `REQ` event is triggered, the input value `IN` of type LREAL is converted to a WSTRING using the function `LREAL_AS_WSTRING` and made available at output `OUT`. The `CNF` event signals successful conversion.

## Technical Features

- The conversion is performed directly without additional parameters.
- This function block is suitable for use in real-time systems.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Converts the input value.
3. **Done**: Sends the `CNF` event with the converted value.

## Application Scenarios

- Displaying floating-point values on user interfaces.
- Logging measured values to text files.
- Preparing data for communication with systems that expect string data.

## ⚖️ Comparison with Similar Function Blocks

- Compared to `F_REAL_AS_WSTRING`, this function block processes 64-bit floating-point numbers instead of 32-bit.
- Similar to `F_DINT_AS_WSTRING`, but for floating-point numbers instead of integers.

## Conclusion

The `F_LREAL_AS_WSTRING` function block offers a simple and efficient way to convert LREAL values to WSTRINGs. Its clear interface and direct functionality make it a useful tool in various use cases.