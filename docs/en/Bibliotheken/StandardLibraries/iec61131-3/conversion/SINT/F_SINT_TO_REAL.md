# F_SINT_TO_REAL

<img width="1439" height="213" alt="F_SINT_TO_REAL" src="https://github.com/user-attachments/assets/9477ea11-2b6e-441e-8fe2-16588d70cf27" />
* * * * * * * * * *
## Introduction

The function block `F_SINT_TO_REAL` converts a signed 8-bit integer value (`SINT`) into a floating-point value (`REAL`). This conversion is particularly useful in control applications where different data types need to be processed.
![F_SINT_TO_REAL](F_SINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`SINT`): The signed 8-bit integer value to be converted.

### **Data Outputs**

- **OUT** (`REAL`): The resulting floating-point value after conversion.

#### **Adapters**

No adapters available.

## Functionality

The function block performs a direct type conversion. When an event arrives at input `REQ`, the value of `IN` is converted to the data type `REAL` and output to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features

- **Simple Conversion**: The conversion occurs without additional calculations or scaling.
- **No Error Handling**: There is no special handling for overflow or underflow conditions.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- **Measurement Processing**: Conversion of sensor data, which is available as `SINT`, to `REAL` for further calculations.
- **Control Algorithms**: Integration into control loops where floating-point values are required.

## ⚖️ Comparison with Similar Function Blocks

- **F_INT_TO_REAL**: Converts a 16-bit integer (`INT`) to `REAL`.
- **F_DINT_TO_REAL**: Converts a 32-bit integer (`DINT`) to `REAL`.
- **F_SINT_TO_REAL** is specific to 8-bit integers, providing a more compact solution for this data type.

## Conclusion

The `F_SINT_TO_REAL` function block is a simple and efficient tool for converting 8-bit integer values to floating-point numbers. Its clear interface and direct functionality make it ideal for applications that require fast and straightforward type conversion.