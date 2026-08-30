# F_ABS

![F_ABS](https://user-images.githubusercontent.com/116869307/214144890-f2f5a18b-13b5-47b4-bcf1-57e064e6dc00.png)

* * * * * * * * * *

## Introduction

The F_ABS function block calculates the absolute value of a numeric input. It belongs to the category of standard functions for numeric variables according to IEC 61131-3 and is part of the iec61131::numerical package.
![F_ABS](F_ABS.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - triggers the calculation of the absolute value

### **Event Outputs**

- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**

- **IN**: Numeric Input (ANY_NUM) - the value whose absolute value is to be calculated

### **Data Outputs**

- **OUT**: Numeric Output (ANY_NUM) - the calculated absolute value of the input

### **Adapters**

No adapter interfaces are available.

## Functionality

Upon receiving a REQ event, the F_ABS block calculates the absolute value of the numeric value passed to IN. The result is output to OUT and confirmed by a CNF event. The block supports all numeric data types (ANY_NUM).

## Technical Features

- Supports all numeric data types according to IEC 61131-3
- Simple, deterministic operation without internal states
- Immediate calculation upon REQ event

## State Overview

The F_ABS block has no internal states. It behaves purely functionally and reacts immediately to incoming REQ events.

## Application Scenarios

- Signal processing for sign removal
- Magnitude calculations in mathematical operations
- Use in control engineering for distance calculations
- Preprocessing of measured values

## ⚖️ Comparison with Similar Function Blocks

Compared to other mathematical function blocks, F_ABS stands out due to its simplicity and specific functionality. While blocks like F_ADD or F_MUL perform more complex operations, F_ABS focuses exclusively on magnitude calculation.

## Conclusion

The F_ABS function block offers a reliable and standards-compliant solution for calculating absolute values in IEC 61131-3-based control systems. Its simple interface and deterministic functionality make it a robust building block for numerical operations.
