# F_BOOL_TO_SINT
<img width="1231" height="184" alt="F_BOOL_TO_SINT" src="https://github.com/user-attachments/assets/f88ef12a-b389-4669-b68c-8527d08d1d6e" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_SINT` converts a Boolean value (`BOOL`) into a signed 8-bit integer (`SINT`). This conversion is useful when Boolean values are used in calculations or controls that require integer values.
![F_BOOL_TO_SINT](F_BOOL_TO_SINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this event input is triggered, the Boolean value at data input `IN` is converted to a value `SINT`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event is output along with the converted value at data output `OUT`.

### **Data Inputs**
- **IN**: The Boolean value (`BOOL`) to be converted to a value `SINT`.

### **Data Outputs**
- **OUT**: The converted value (`SINT`). The output value is `1` if the input is `IN` or `TRUE`; otherwise, it is `0`.

### **Adapters**
This function block does not use any adapters.

## Functionality
The function block converts the Boolean input value `IN` to a value `SINT`. The conversion is performed according to the following rule:

- `TRUE` is converted to `1`.
- `FALSE` is converted to `0`.

The conversion is triggered by the event `REQ`. After successful conversion, the event `CNF` is triggered, and the converted value is output at `OUT`.

## Technical Features
- The function block is a simple algorithm (`SimpleFB`) that performs the conversion directly.
- The conversion occurs without delay as soon as the event `REQ` arrives.

## State Overview

The function block has no internal state. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of Boolean signals into numerical values for mathematical operations.
- Integration of Boolean control signals into systems that expect integer values.

## ⚖️ Comparison with Similar Function Blocks
- **F_BOOL_TO_INT**: Converts `BOOL` to a 16-bit integer (`INT`). This block is similar, but the output value has a larger bit width.
- **F_BOOL_TO_USINT**: Converts `BOOL` to an unsigned 8-bit integer (`USINT`). The difference lies in the interpretation of the output value (signed vs. unsigned).

## Conclusion
The function block `F_BOOL_TO_SINT` is a simple and efficient tool for converting Boolean values to signed 8-bit integers. It is particularly useful in control systems where Boolean signals need to be converted into numerical values.