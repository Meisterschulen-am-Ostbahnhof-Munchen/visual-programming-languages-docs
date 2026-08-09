# F_DINT_AS_STRING

<img width="1255" height="182" alt="F_DINT_AS_STRING" src="https://github.com/user-attachments/assets/541e2cdc-bed5-4e61-822c-cb2a32505087" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_AS_STRING` converts a 32-bit integer value (DINT) into a string (STRING). This functionality is particularly useful when numeric values are needed for display or logging in a human-readable format.
![F_DINT_AS_STRING](F_DINT_AS_STRING.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is activated along with the converted value at data output `OUT`.

### **Data Inputs**

- **IN**: Expects a 32-bit integer value (DINT) to be converted into a string.

### **Data Outputs**

- **OUT**: Returns the converted value as a string (STRING).

#### **Adapters**

This function block has no adapter interfaces.

## Operation

When the `REQ` event is triggered, the algorithm is started that converts the value of `IN` (DINT type) into a STRING. The result is output to `OUT`, and the `CNF` event signals successful conversion.

## Technical Features

- The conversion is performed directly without additional parameters.
- The function block is part of the `iec61131::conversion` package.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Displaying numeric values in user interfaces.
- Logging measured values to text files or databases.
- Preparing data for communication with systems that can only process strings.

## ⚖️ Comparison with Similar Blocks

Compared to other conversion blocks, `F_DINT_AS_STRING` offers a specialized and efficient solution for converting DINT to STRING. Other blocks might offer additional features such as formatting or locale settings, but are often more complex to use.

## Conclusion

The `F_DINT_AS_STRING` function block is a simple and effective solution for converting integers to strings. Its clear interface and direct functionality make it ideal for applications requiring fast and straightforward conversion.