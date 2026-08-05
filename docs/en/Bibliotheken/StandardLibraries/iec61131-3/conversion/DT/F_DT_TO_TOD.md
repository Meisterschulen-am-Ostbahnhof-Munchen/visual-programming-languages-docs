# F_DT_TO_TOD

<img width="1198" height="187" alt="F_DT_TO_TOD" src="https://github.com/user-attachments/assets/15e611cf-4581-41b1-a782-bf2f2d2920af" />

* * * * * * * * * *
## Introduction
The function block `F_DT_TO_TOD` converts a date and time value (DT) into a pure time value (TOD - Time of Day). This function is particularly useful when only the time of day needs to be extracted from a combined date and time stamp.

![F_DT_TO_TOD](F_DT_TO_TOD.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the function block performs the conversion.

### **Event Outputs**
- **CNF**: Signals the successful completion of the conversion.


### ### **Data Inputs**

- **IN**: The input of type `DT`, containing the date and time value to be converted.

### **Data Outputs**

- **OUT**: The output of type `TOD`, providing the converted time value (without the date).

### **Adapters**
This function block does not use any adapters.

## Operation
When the `REQ` event is triggered, the algorithm is executed, converting the input value `IN` of type `DT` into a `TOD` value. The result is output at `OUT`, and the `CNF` event signals the successful completion of the operation.

## Technical Features
- The function block is implemented as a simple FB (SimpleFB), ensuring fast and efficient execution.

- The conversion is performed using the built-in function `DT_TO_TOD`.

## State Overview

The function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios

- Extracting the time of day from timestamps for time-based control systems.

- Preprocessing data for systems that only require the time of day.

## ⚖️ Comparison with Similar Function Blocks

- Unlike `F_TOD_TO_DT`, this function block converts in the opposite direction.

- Similar function blocks like `F_DT_TO_DATE` or `F_DT_TO_TIME` extract other parts of a date and time value.

## Conclusion
The `F_DT_TO_TOD` function block provides a simple and efficient way to extract the time of day from a combined date and time value. Its clear interface and simple functionality make it a useful tool in control applications.