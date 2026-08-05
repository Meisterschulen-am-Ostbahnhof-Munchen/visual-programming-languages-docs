# F_SINT_TO_UDINT

<img width="1450" height="213" alt="F_SINT_TO_UDINT" src="https://github.com/user-attachments/assets/a5b8dca8-4533-4578-b402-729f15415b91" />

* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_UDINT` converts a signed 8-bit integer value (SINT) to an unsigned 32-bit integer value (UDINT). This conversion is particularly useful when exchanging data between systems that use different data types.

![F_SINT_TO_UDINT](F_SINT_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `SINT` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `UDINT`, containing the result of the conversion.

#### **Adapters**

- No adapters are available.

## Functionality
The function block performs the conversion by transforming the `SINT` value at input `IN` into a `UDINT` value and providing the result at output `OUT`. The conversion is triggered by an event at input `REQ` and confirmed by an event at output `CNF`.

## Technical Details
- The conversion is performed using the function `SINT_TO_UDINT`.

- This function block is part of the package `iec61131::conversion`.

## State Overview
1. **Idle State**: Waits for an event at input `REQ`.

2. **Active State**: Executes the conversion and signals its completion with an event at output `CNF`.


## Application Scenarios

- Conversion of sensor values stored as `SINT` to a `UDINT` value for further processing.

- Data preparation for systems that expect unsigned integer values.

## ⚖️ Comparison with Similar Function Blocks

- **F_INT_TO_UDINT**: Converts a signed 16-bit integer (`INT`) to an unsigned 32-bit integer (`UDINT`).

- **F_DINT_TO_UDINT**: Converts a signed 32-bit integer (`DINT`) to an unsigned 32-bit integer (`UDINT`).

## Conclusion
The function block `F_SINT_TO_UDINT` provides a simple and efficient way to convert `SINT` values to `UDINT` values. Its clear interface structure and simple operation make it ideal for applications requiring such conversion.