# F_BOOL_TO_DWORD
<img width="1241" height="182" alt="F_BOOL_TO_DWORD" src="https://github.com/user-attachments/assets/50cc2830-dbd7-4208-8a02-78369915f85c" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_DWORD` converts a Boolean value (`BOOL`) into a 32-bit unsigned integer value (`DWORD`). This block is particularly useful in scenarios where Boolean signals need to be converted into numerical values, for example, for communication with systems that can only process numeric input.
![F_BOOL_TO_DWORD](F_BOOL_TO_DWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The Boolean value (`BOOL`) to be converted to `DWORD`.

### **Data Outputs**
- **OUT**: The converted 32-bit unsigned integer value (`DWORD`). The value is either `1` (TRUE) or `0` (FALSE).

### **Adapters**
- No adapters are available.


**
## Functionality

The function block performs the conversion as soon as the event `REQ` is received. The Boolean value `IN` is converted to `DWORD`:

- `TRUE` becomes `1`
- `FALSE` becomes `0`

After successful conversion, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The conversion occurs instantly and without delay.
- The block is deterministic and has no internal state.

## State Overview

This function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios
- Conversion of switching states (On/Off) into numerical control signals.
- Integration into control systems that can only process numerical inputs.
- Logging of Boolean events as numerical values.

## ⚖️ Comparison with Similar Blocks
- Unlike `F_BOOL_TO_INT` or `F_BOOL_TO_REAL`, this block specifically converts to a `DWORD` type, which is optimized for 32-bit systems.
- Similar blocks, such as `F_DWORD_TO_BOOL`, perform the reverse conversion.

## Conclusion

The `F_BOOL_TO_DWORD` function block is a simple and efficient building block for converting Boolean values to `DWORD`. Its deterministic functionality and clear interface make it a reliable component in control and communication applications.
