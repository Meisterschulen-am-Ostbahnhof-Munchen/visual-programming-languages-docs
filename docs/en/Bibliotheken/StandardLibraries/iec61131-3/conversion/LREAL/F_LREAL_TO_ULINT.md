# F_LREAL_TO_ULINT
<img width="1463" height="214" alt="F_LREAL_TO_ULINT" src="https://github.com/user-attachments/assets/245c53eb-336f-4028-bcc0-275993708239" />
* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_ULINT` converts an LREAL value (64-bit floating-point number) to a ULINT value (64-bit unsigned integer). This conversion is particularly necessary in scenarios where floating-point numbers need to be converted to unsigned integers, for example, for certain calculations or for storage in specific data formats.
![F_LREAL_TO_ULINT](F_LREAL_TO_ULINT.svg)
## Interface Structure
### **Event Inputs**
- `REQ` (Normal Execution Request): Starts the conversion of the input value. It is linked to the data input `IN`.

### **Event Outputs**
- `CNF` (Execution Confirmation): Signals the completion of the conversion. Linked to the data output `OUT`.

### **Data Inputs**
- `IN` (LREAL): The input value to be converted.

### **Data Outputs**
- `OUT` (ULINT): The converted output value.

### **Adapters**
No adapters available.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The algorithm `REQ` converts the LREAL value `IN` into a ULINT value using the function `LREAL_TO_ULINT` and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features
- The conversion is performed without rounding; that is, the decimal portion is truncated.
- Values outside the representable range of ULINT (0 to 2^64-1) may result in overflow or unexpected results.

## State Overview
The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Conversion of sensor values (e.g., temperature measurements) into unsigned integers for further processing.
- Conversion of floating-point numbers for storage in databases or protocols that only support integers.
- Use in control algorithms that require unsigned integers.

## ⚖️ Comparison with Similar Components
- `F_REAL_TO_UINT`: Converts REAL (32-bit floating-point number) to UINT (16-bit unsigned integer).
- `F_LREAL_TO_LINT`: Converts LREAL to LINT (64-bit signed integer).
- `F_LREAL_TO_ULINT` is specific to 64-bit unsigned conversions and therefore offers higher accuracy and a wider range of values compared to 16- or 32-bit versions.

## Conclusion

The function block `F_LREAL_TO_ULINT` offers a simple and efficient way to convert floating-point numbers to unsigned integers. Its clear interface and direct functionality make it ideal for applications requiring precise conversion without rounding.