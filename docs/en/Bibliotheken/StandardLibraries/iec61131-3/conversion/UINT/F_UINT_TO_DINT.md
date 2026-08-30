# F_UINT_TO_DINT

<img width="1438" height="216" alt="F_UINT_TO_DINT" src="https://github.com/user-attachments/assets/ace89eda-70cf-4dc2-bcac-b1e3365ef7df" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_DINT` converts an unsigned 16-bit integer value (UINT) to a signed 32-bit integer value (DINT). This conversion is useful when exchanging data between systems that use different data types.
![F_UINT_TO_DINT](F_UINT_TO_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `UINT` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `DINT`, containing the result of the conversion.

### **Adapters**

This function block does not use any adapters.

## Operation

When an event is received at input `REQ`, the value of `IN` is read and directly converted to the data type `DINT`. The result is output to `OUT`, and the event `CNF` is triggered to signal the completion of the conversion.

## Technical Features

- The function block performs a direct type conversion without additional calculations or scaling.
- The conversion is lossless because the `DINT` type covers a larger range of values than `UINT`.

## State Overview

1. **Idle**: Waits for an event at input `REQ`.
2. **Converting**: Performs the conversion and outputs the result.
3. **Completed**: Signals the completion of the conversion with the event `CNF`.

## Application Scenarios

- Data conversion in control systems that use different data types.
- Integration of sensor data in the format `UINT` into systems that expect `DINT`.

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, `F_UINT_TO_DINT` is specialized and efficient for converting `UINT` to `DINT`.
- Other blocks might offer additional features such as scaling or range checking, which are not required here.

## Conclusion

The `F_UINT_TO_DINT` function block is a simple and efficient building block for the direct conversion of `UINT` to `DINT`. It is particularly useful in scenarios where lossless type conversion is required.
