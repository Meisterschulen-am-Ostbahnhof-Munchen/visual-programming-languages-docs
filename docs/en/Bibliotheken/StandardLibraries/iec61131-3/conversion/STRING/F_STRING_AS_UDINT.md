# F_STRING_AS_UDINT
<img width="1478" height="220" alt="F_STRING_AS_UDINT" src="https://github.com/user-attachments/assets/703603e7-5595-4570-8772-7efeb1ea4785" />
* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_UDINT` converts a `STRING` value to a `UDINT` value (unsigned double integer). It is part of the `iec61131::conversion` package and enables the easy conversion of strings to numeric values.
![F_STRING_AS_UDINT](F_STRING_AS_UDINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: The input expects a `STRING` value, which is to be converted to a `UDINT` value.

### **Data Outputs**
- **OUT**: The output provides the converted `UDINT` value.

### **Adapters**
The function block does not use any adapters.

## Functionality
The function block performs the conversion using the built-in function `STRING_AS_UDINT`. When the event `REQ` is triggered, the `STRING` value at input `IN` is converted to a `UDINT` value and output `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features
- The conversion is performed directly without additional parameters.
- The function block is optimized for simple conversions and does not support complex formatting or error handling.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Conversion**: Performs the conversion and outputs the result.

3. **Acknowledgement**: Triggers the event `CNF` and returns to the idle state.

## Application Scenarios
- Conversion of user input or communication data into numeric values.
- Integration into systems that require numeric processing but receive strings as input.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion function blocks, `F_STRING_AS_UDINT` offers a specialized and efficient solution for converting `STRING` to `UDINT`.
- Other function blocks might offer additional features such as error handling or formatting, but are more complex to use.

## Conclusion
The `F_STRING_AS_UDINT` function block is a simple and efficient solution for converting strings to numeric values. It is particularly suitable for applications where a fast and direct conversion is required.