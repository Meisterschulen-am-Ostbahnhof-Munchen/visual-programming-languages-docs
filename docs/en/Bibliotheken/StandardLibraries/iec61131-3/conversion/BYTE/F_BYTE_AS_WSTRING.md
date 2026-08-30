# F_BYTE_AS_WSTRING

<img width="1274" height="183" alt="F_BYTE_AS_WSTRING" src="https://github.com/user-attachments/assets/711f52f0-48d7-47e3-bb8c-36a79a97fac4" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_AS_WSTRING` converts a BYTE value into a WSTRING value. This is particularly useful in scenarios where byte data needs to be further processed or output as Unicode strings.
![F_BYTE_AS_WSTRING](F_BYTE_AS_WSTRING.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. It is linked to the input value `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. Returns the converted value via `OUT`.

### **Data Inputs**

- **IN** (BYTE): The byte value to be converted to a WSTRING.

### **Data Outputs**

- **OUT** (WSTRING): The resulting Unicode string after conversion.

#### **Adapters**

- No adapters available.

## Functionality

This function block uses the built-in function `BYTE_AS_WSTRING` to convert the input byte value to a WSTRING. The conversion is triggered by the event `REQ`, and the result is returned via `CNF`.

## Technical Features

- The conversion is performed directly without additional parameters.
- The block is optimized for use in IEC 61131-3 compliant environments.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Completed**: Sends the `CNF` event with the result.

## Application Scenarios

- Converting byte data for display in user interfaces.
- Processing byte streams in Unicode-compatible systems.

## ⚖️ Comparison with Similar Blocks

- Unlike `F_BYTE_AS_STRING`, this block generates a Unicode string (WSTRING) instead of an ASCII string (STRING).
- Similar to `F_WORD_AS_WSTRING`, but optimized for 8-bit data.

## Conclusion

The `F_BYTE_AS_WSTRING` block is a simple and efficient way to convert byte data into Unicode strings. Its clear interface and direct functionality make it ideal for numerous applications in automation technology.
