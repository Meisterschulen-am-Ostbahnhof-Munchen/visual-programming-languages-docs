# F_LINT_TO_REAL
<img width="1438" height="214" alt="F_LINT_TO_REAL" src="https://github.com/user-attachments/assets/0609cf87-5b1c-45c8-95bd-9cfaa561c08c" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_REAL` converts an integer value of type `LINT` (64-bit integer) to a floating-point value of type `REAL`. This conversion is useful when data needs to be transformed from an integer format to a floating-point format, for example, for further calculations or display.
![F_LINT_TO_REAL](F_LINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this event is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event, along with the converted value, is output at data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `LINT`, which provides the integer value to be converted.

### **Data Outputs**
- **OUT**: The output of type `REAL`, which provides the result of the conversion.

### **Adapters**
- This function block does not use any adapters.

## Operation
The function block performs the conversion as soon as the event `REQ` is received. The algorithm reads the value of `IN`, converts it using the function `LINT_TO_REAL`, and writes the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features
- The conversion is performed without rounding or scaling, as it is a direct type conversion.
- The function block is suitable for use in real-time systems because it does not involve any delays or complex calculations.

## State Overview

The function block has no internal state. The operation is re-executed with each `REQ` event.

## Application Scenarios
- Conversion of sensor values stored as `LINT` to `REAL` for further processing.
- Integration into systems that require floating-point operations but receive input data as integers.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_INT_TO_REAL` or `F_DINT_TO_REAL` perform similar conversions, but with smaller integer types (`INT` or `DINT`).
- `F_LINT_TO_REAL` is specifically optimized for 64-bit integers (`LINT`).

## Conclusion

The `F_LINT_TO_REAL` function block offers a simple and efficient way to convert 64-bit integer values to floating-point numbers. Its clear interface and direct functionality make it ideal for applications requiring type conversion without additional processing.