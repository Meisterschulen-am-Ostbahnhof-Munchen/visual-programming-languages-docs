# F_BOOL_TO_USINT
<img width="1450" height="212" alt="F_BOOL_TO_USINT" src="https://github.com/user-attachments/assets/72e9600a-837a-49a8-b423-6f5380816310" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_USINT` converts a Boolean value (`BOOL`) into an unsigned 8-bit integer (`USINT`). This conversion is useful when Boolean values need to be used in numerical operations or for communication with systems that do not directly support Boolean values.
![F_BOOL_TO_USINT](F_BOOL_TO_USINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The Boolean input value (`BOOL`) to be converted.

### **Data Outputs**
- **OUT**: The converted unsigned 8-bit integer (`USINT`).

### **Adapters**
This function block does not use adapters.

### **Adapters**

### **Adapters**
****
## Functionality

The function block performs the conversion by transforming the Boolean value `IN` into a numeric value:

- `FALSE` is converted to `0`.
- `TRUE` is converted to `1`.

The conversion is triggered by the event `REQ`, and the result is output via the output `OUT`, accompanied by the confirmation event `CNF`.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and performs the conversion in a single algorithm.
- The conversion occurs directly and without delay as soon as the `REQ` event arrives.

## State Overview
The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Conversion of Boolean switching states into numerical values for processing in mathematical operations.
- Communication with systems or devices that do not directly support Boolean values but can process numerical values.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion function blocks such as `F_BOOL_TO_INT` or `F_BOOL_TO_UINT`, `F_BOOL_TO_USINT` is specifically optimized for conversion to an unsigned 8-bit integer.

Similar function blocks can use larger or signed integer types, which may be more or less suitable depending on the use case.

## Conclusion
The `F_BOOL_TO_USINT` function block is a simple and efficient tool for converting Boolean values to unsigned 8-bit integers. Its direct and lag-free operation makes it ideal for real-time applications where fast and reliable conversions are required.
