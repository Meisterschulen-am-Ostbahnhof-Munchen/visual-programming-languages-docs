# F_BOOL_TO_INT
<img width="1221" height="182" alt="F_BOOL_TO_INT" src="https://github.com/user-attachments/assets/b06391ef-074e-42e4-a3ae-ee819a369ccb" />
* * * * * * * * * *
## Introduction
The function block `F_BOOL_TO_INT` converts a Boolean value (`BOOL`) into an integer value (`INT`). Specifically, `TRUE` is converted to `1`, and `FALSE` to `0`. This block is particularly useful in scenarios where Boolean logic needs to be integrated into numerical calculations.
![F_BOOL_TO_INT](F_BOOL_TO_INT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. The input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The Boolean value (`BOOL`) to be converted.

### **Data Outputs**
- **OUT**: The converted integer value (`INT`). `TRUE` becomes `1`, and `FALSE` becomes `0`.

### **Adapter**
- No adapters available.

## Functionality
When the event `REQ` is triggered, the Boolean value at input `IN` is read and converted into an integer value. The result is output at `OUT`, and the event `CNF` is triggered to signal the completion of the operation.

## Technical Features
- The block is a simple function block (`SimpleFB`) without internal states.
- The conversion is performed directly and without delay.

## State Overview
Because it is a simple function block, there are no state transitions or internal states. The operation is re-executed with each `REQ` event.

## Application Scenarios
- Integration of Boolean logic into numerical control systems.
- Conversion of switching states (`TRUE`/`FALSE`) into numerical values for further calculations.
- Use in control engineering, where Boolean signals need to be converted into numerical control signals.

## ⚖️ Comparison with Similar Function Blocks
- **F_BOOL_TO_REAL**: Converts `BOOL` to `REAL` (floating-point number), similar to `F_BOOL_TO_INT`, but with floating-point output.
- **F_INT_TO_BOOL**: Performs the reverse conversion (`INT` to `BOOL`).

## Conclusion
The `F_BOOL_TO_INT` function block is a simple yet effective tool for converting Boolean values to integer values. Its simplicity and direct operation make it ideal for applications requiring fast and straightforward conversion.