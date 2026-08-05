# F_REAL_TO_LINT
<img width="1433" height="216" alt="F_REAL_TO_LINT" src="https://github.com/user-attachments/assets/27a08bc4-5fb5-42da-95cd-5c700436c357" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_LINT` converts a REAL value (floating-point number) to a LINT value (64-bit integer). This conversion is particularly useful when numerical calculations need to be performed with different data types.
![F_REAL_TO_LINT](F_REAL_TO_LINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this event input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event, along with the converted value, is output at data output `OUT`.

### **Data Inputs**
- **IN**: The input for the REAL value to be converted to a LINT value.

### **Data Outputs**
- **OUT**: The output where the converted LINT value is displayed.

### **Adapters**
This function block has no adapters.

## Operation
When the `REQ` event is triggered, the algorithm `REQ` is executed. This function converts the REAL value at input `IN` into a LINT value using the function `REAL_TO_LINT` and writes the result to output `OUT`. The `CNF` event is then triggered to signal the successful completion of the conversion.

## Technical Details
- Converting REAL to LINT can result in data loss if the REAL value has decimal places, as these are truncated during the conversion.
- This function block is part of the `iec61131::conversion` package.

## State Overview

This function block has no internal states. The conversion occurs immediately after the `REQ` event is triggered.

## Application Scenarios
- Conversion of sensor values (e.g., temperature measurements) for further processing into integer operations.
- Integration into control systems that need to process mixed data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks (e.g., `F_REAL_TO_INT`), `F_REAL_TO_LINT` offers higher precision through the use of the 64-bit LINT data type.
- Similar blocks, such as `F_LINT_TO_REAL`, perform the reverse conversion.

## Conclusion
The `F_REAL_TO_LINT` function block is a simple and efficient block for converting floating-point numbers to 64-bit integers. Its use is particularly recommended in scenarios with high precision requirements, although potential data loss during conversion must be taken into account.