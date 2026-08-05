# F_WSTRING_AS_SINT
<img width="1481" height="214" alt="F_WSTRING_AS_SINT" src="https://github.com/user-attachments/assets/5c42bc49-eddd-4518-b97f-197880155b0d" />
* * * * * * * * * *
## Introduction
The function block `F_WSTRING_AS_SINT` converts a WSTRING value to a SINT value (8-bit integer). This block is particularly useful in scenarios where strings need to be converted to numeric values.
![F_WSTRING_AS_SINT](F_WSTRING_AS_SINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Triggering event for the conversion. Linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Confirms successful completion of the conversion. Linked to the data output `OUT`.

### **Data Inputs**
- **IN** (WSTRING): The input string to be converted to a SINT value.

### **Data Outputs**
- **OUT** (SINT): The resulting 8-bit integer value after conversion.

### **Adapters**
No adapters available.

## Functionality
The function block performs the conversion as soon as the `REQ` event occurs. The function `WSTRING_AS_SINT` is applied to the input value `IN`, and the result is output to `OUT`. Successful execution is indicated by the `CNF` event.

## Technical Features
- The conversion is performed using the built-in function `WSTRING_AS_SINT`.
- The block is optimized for use in IEC 61131-3 compliant environments.

## State Overview

The block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of user input to numeric values.
- Processing of strings from external sources (e.g., sensors or network communication).

## ⚖️ Comparison with Similar Blocks
- Compared to generic conversion blocks, `F_WSTRING_AS_SINT` specializes in converting WSTRING to SINT.
- Other blocks might offer additional features such as error handling or type checking.

## Conclusion

The `F_WSTRING_AS_SINT` block offers an efficient and direct method for converting WSTRING values to SINT values. Its simplicity and specialization make it ideal for specific use cases.