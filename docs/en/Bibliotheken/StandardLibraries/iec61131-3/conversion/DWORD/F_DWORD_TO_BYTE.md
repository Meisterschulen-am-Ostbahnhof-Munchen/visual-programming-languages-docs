# F_DWORD_TO_BYTE

<img width="1248" height="184" alt="F_DWORD_TO_BYTE" src="https://github.com/user-attachments/assets/3a6b0a87-3a1e-478f-a160-dfbaca28aa01" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_BYTE` converts a 32-bit value (DWORD) to an 8-bit value (BYTE). This conversion is useful in scenarios where data reduction or type conversion is required.

![F_DWORD_TO_BYTE](F_DWORD_TO_BYTE.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `DWORD` (32-bit) to be converted to `BYTE`.

### **Data Outputs**

- **OUT**: The output value of type `BYTE` (8-bit) containing the result of the conversion.

#### **Adapters**

- No adapters are available.

## Functionality
This function block performs the conversion from `DWORD` to `BYTE` as soon as the event `REQ` is received. The conversion is performed using the function `DWORD_TO_BYTE`. After successful conversion, the event `CNF` is triggered.

## Technical Details
- Data loss can occur if the original `DWORD` value is outside the representable range of `BYTE` (0-255).

- The function block is implemented as a simple FB (SimpleFB) and uses an ST algorithm for the conversion.

## State Overview
1. **Idle**: Waits for the event `REQ`.

2. **Processing**: Performs the conversion.

3. **Completed**: Sends the event `CNF` and returns to the idle state.

## Application Scenarios
- Data reduction in control systems.

- Type conversion in communication protocols.

- Adapting data for specific hardware interfaces.

## ⚖️ Comparison with similar function blocks

- **F_WORD_TO_BYTE**: Converts a 16-bit value (WORD) to a BYTE.

- **F_DWORD_TO_WORD**: Converts a 32-bit value (DWORD) to a 16-bit value (WORD).

- **F_BYTE_TO_DWORD**: Performs the reverse conversion (BYTE to DWORD).

## Conclusion
The function block `F_DWORD_TO_BYTE` provides a simple and efficient way to convert 32-bit values to 8-bit values. However, due to the potential for data loss with large values, its use should be carefully considered.