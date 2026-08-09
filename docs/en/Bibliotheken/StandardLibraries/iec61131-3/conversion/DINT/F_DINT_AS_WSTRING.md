# F_DINT_AS_WSTRING

<img width="1268" height="182" alt="F_DINT_AS_WSTRING" src="https://github.com/user-attachments/assets/74b253fa-2cf2-41b1-9ad5-20ffb46856c2" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_AS_WSTRING` converts a 32-bit integer value (DINT) into a Unicode string (WSTRING). This functionality is particularly useful when numeric values are needed as text for display or further processing.
![F_DINT_AS_WSTRING](F_DINT_AS_WSTRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the input value. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (DINT): The 32-bit integer value to be converted.

### **Data Outputs**

- **OUT** (WSTRING): The resulting Unicode string after conversion.

#### **Adapters**

No adapters available.

## Functionality

When the `REQ` event is triggered, the value at input `IN` is read and converted into a Unicode string using the function `DINT_AS_WSTRING`. The result is output at `OUT`, and the `CNF` event signals successful execution.

## Technical Features

- The function block is a simple algorithm without state machines.
- Conversion is performed directly without additional parameters.

## State Overview

Since it is a simple function block, there are no state transitions or management.

## Application Scenarios

- Displaying numeric values in user interfaces.
- Logging numeric data in text format.
- Preparing data for text-based communication protocols.

## ⚖️ Comparison with Similar Blocks

- Compared to `F_INT_AS_WSTRING`, this block processes 32-bit integers instead of 16-bit integers.
- Similar blocks like `F_DINT_AS_STRING` convert to ASCII instead of Unicode strings.

## Conclusion

The `F_DINT_AS_WSTRING` function block offers a simple and efficient way to convert 32-bit integers to Unicode strings. Its clear interface and direct functionality make it ideal for applications that require numerical data in text format.