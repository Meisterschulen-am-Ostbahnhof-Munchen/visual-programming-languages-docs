# F_DINT_TO_INT

<img width="1425" height="212" alt="F_DINT_TO_INT" src="https://github.com/user-attachments/assets/5147e94b-3493-443d-9b11-48a63ecf9d50" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_INT` converts a 32-bit DINT value to a 16-bit INT value. This conversion is particularly necessary in scenarios where data needs to be exchanged between systems with different word lengths.
![F_DINT_TO_INT](F_DINT_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- `REQ` (Normal Execution Request): Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- `CNF` (Execution Confirmation): Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- `IN` (DINT): The 32-bit DINT value to be converted.

### **Data Outputs**

- `OUT` (INT): The resulting 16-bit INT value after conversion.

### **Adapters**

No adapters available.

## Functionality

This function block performs the conversion of a 32-bit DINT value (`IN`) to a 16-bit INT value (`OUT`) as soon as the event `REQ` is triggered. The conversion is carried out by the function `DINT_TO_INT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Details

- Data loss can occur if the original DINT value is outside the representable range of an INT value (-32768 to 32767).
- This function block is part of the package `iec61131::conversion`.

## State Overview

This function block has no internal state. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Data conversion in control systems with different word widths.
- Integration of systems that use different data types.
- Reduction of memory usage when the higher precision of DINT is not required.

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, `F_DINT_TO_INT` specializes in converting DINT to INT and therefore offers a simple and direct solution for this specific use case.
- Other conversion blocks, such as `F_INT_TO_DINT`, perform the opposite conversion.

## Conclusion

The function block `F_DINT_TO_INT` is an efficient tool for converting 32-bit DINT values to 16-bit INT values. Its simple and specialized functionality makes it ideal for applications where such conversions are required regularly. However, when using it, the potential for data loss with large values must be taken into account.
