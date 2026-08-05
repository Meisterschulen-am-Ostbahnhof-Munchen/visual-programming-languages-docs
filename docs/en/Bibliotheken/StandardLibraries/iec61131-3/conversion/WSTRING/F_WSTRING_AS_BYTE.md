# F_WSTRING_AS_BYTE

<img width="1480" height="214" alt="F_WSTRING_AS_BYTE" src="https://github.com/user-attachments/assets/5af29946-8d1c-495b-a40a-d21f8d38b1fc" />

* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_BYTE` is used to convert a WSTRING data type to a BYTE data type. This block is particularly useful in scenarios where converting wide strings into individual bytes is required.

![F_WSTRING_AS_BYTE](F_WSTRING_AS_BYTE.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the execution of the function block. The input value `IN` is processed upon this event.

### **Event Outputs**

- **CNF**: Signals the completion of processing and outputs the result via the output `OUT`.


### **Data Inputs**

- **IN** (WSTRING): The input value to be converted into a BYTE value.

### **Data Outputs**

- **OUT** (BYTE): The result of the conversion.

### **Adapters**
- No adapters available.

## Functionality
When the `REQ` event occurs, the function block converts the WSTRING input `IN` into a BYTE value. The result is output via `OUT`, and the `CNF` event signals the successful completion of the operation.

## Technical Features

- The function block uses the `WSTRING_AS_BYTE` function for the conversion.

- This is a simple function block without internal state management.

## State Overview
The function block has no internal states. Processing occurs directly upon the occurrence of the `REQ` event.

## Application Scenarios

- Conversion of WSTRING data to BYTE values for further processing in systems that only support BYTE data.

- Use in communication protocols where strings need to be converted to bytes.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks such as `F_STRING_AS_BYTE`, this one is specifically designed for WSTRING data types.

- Similar blocks might have additional parameters or states, but this function block is limited to simple conversion.


## Conclusion

The `F_WSTRING_AS_BYTE` function block offers a simple and efficient way to convert WSTRING data into BYTE values. Its clear interface structure and direct functionality make it a reliable solution for corresponding use cases.