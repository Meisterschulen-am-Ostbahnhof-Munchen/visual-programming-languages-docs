# F_DWORD_TO_REAL

<img width="1248" height="181" alt="F_DWORD_TO_REAL" src="https://github.com/user-attachments/assets/0ae16249-44e5-4ae0-8d75-1705e8beef34" />
* * * * * * * * * *
## Introduction

The function block `F_DWORD_TO_REAL` converts a DWORD value (32-bit unsigned integer) to a REAL value (32-bit floating-point number). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_DWORD_TO_REAL](F_DWORD_TO_REAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is activated as soon as the conversion is complete and the result value is available at data output `OUT`.

### **Data Inputs**

- **IN**: DWORD value to be converted to a REAL value.

### **Data Outputs**

- **OUT**: The converted REAL value.

#### **Adapters**

No adapters available.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The value at input `IN` is converted to a REAL value using the function `DWORD_TO_REAL` and output at output `OUT`. Finally, the event `CNF` is triggered to signal the successful completion of the operation.

## Technical Features

- The conversion is performed directly and without any additional delay.
- No special error handling is performed, e.g., for invalid input values.

## State Overview

1. **Idle State**: Waits for the `REQ` event.
2. **Conversion State**: Performs the conversion and sets the output `OUT`.
3. **Confirmation State**: Enables `CNF` and returns to the idle state.

## Application Scenarios

- Type conversion in control applications where DWORD data needs to be converted to floating-point numbers.
- Integration into larger function blocks that require type conversion.

## ⚖️ Comparison with similar function blocks

- Similar function blocks such as `F_WORD_TO_REAL` or `F_INT_TO_REAL` offer similar functionality, but for different input types.
- `F_DWORD_TO_REAL` is specifically optimized for converting DWORD to REAL.

## Conclusion

The `F_DWORD_TO_REAL` function block is a simple and efficient building block for converting DWORD to REAL values. Its clear interface and direct functionality make it a reliable component in control applications.