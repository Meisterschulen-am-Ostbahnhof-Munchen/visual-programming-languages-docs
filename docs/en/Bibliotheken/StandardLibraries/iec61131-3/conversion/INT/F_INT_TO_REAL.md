# F_INT_TO_REAL

<img width="1423" height="216" alt="F_INT_TO_REAL" src="https://github.com/user-attachments/assets/6294145e-fd3f-497a-ada1-e0cf83c00ba8" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_REAL` converts an integer value (`INT`) into a floating-point number (`REAL`). This functionality is particularly useful when data needs to be converted between different numerical representations in control applications.
![F_INT_TO_REAL](F_INT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: This input triggers the execution of the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: This output signals the completion of the conversion. It is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`INT`): The integer value to be converted to a floating-point number.

### **Data Outputs**

- **OUT** (`REAL`): The resulting floating-point value after conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

When the event `REQ` is triggered, the value of the data input `IN` is read and converted to the type `REAL`. The result is output at data output `OUT`, and the event `CNF` signals the successful completion of the operation.

## Technical Features

- The conversion is performed directly without additional parameters or settings.
- The function block is implemented simply and efficiently, ensuring fast execution.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of sensor values (e.g., acquired as `INT`) into floating-point numbers for further calculations.
- Integration into control logic that needs to process mixed data types.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic conversion blocks, `F_INT_TO_REAL` is specialized and therefore more efficient for this specific use case.
- Other blocks might offer additional features such as range checks or scaling, which are not required here.

## Conclusion

The `F_INT_TO_REAL` function block is a simple and effective tool for converting integer values to floating-point numbers. Its clear interface and direct functionality make it ideal for applications requiring fast and reliable type conversion.