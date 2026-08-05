# F_LREAL_TO_LWORD
<img width="1463" height="214" alt="F_LREAL_TO_LWORD" src="https://github.com/user-attachments/assets/a9ab04bc-b63c-4185-a4b8-dfb4db6ffa50" />
* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_LWORD` converts an LREAL value (64-bit floating-point number) to an LWORD value (64-bit unsigned integer). This conversion is particularly necessary in scenarios where floating-point numbers need to be converted to a binary representation.
![F_LREAL_TO_LWORD](F_LREAL_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**
- **IN** (LREAL): The input value to be converted.

### **Data Outputs**
- **OUT** (LWORD): The converted output value.

#### **Adapters**
This function block does not use any adapters.

## Functionality
The function block performs the conversion by transforming the LREAL value at input `IN` into an LWORD value. The conversion is performed directly without additional parameters. When event `REQ` is triggered, the algorithm that converts the value and outputs event `CNF` is executed.

## Technical Features
- The conversion is performed using the function `LREAL_TO_LWORD`, which is implemented in the function block's algorithm.
- The function block is simple and has no internal states or complex logic.

## State Overview
Since it is a simple function block, there are no state transitions or internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of floating-point numbers into a binary representation for further processing in other systems.
- Use in control systems where floating-point values need to be converted into a format understandable to the hardware.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks like `F_REAL_TO_WORD` or `F_DINT_TO_DWORD` perform similar conversions, but with different data types.
- `F_LREAL_TO_LWORD` is specifically for converting 64-bit floating-point numbers to 64-bit unsigned integers.

## Conclusion
The `F_LREAL_TO_LWORD` function block provides a simple and efficient way to convert floating-point numbers to a binary representation. Its clear interface and direct functionality make it ideal for applications requiring such conversions.