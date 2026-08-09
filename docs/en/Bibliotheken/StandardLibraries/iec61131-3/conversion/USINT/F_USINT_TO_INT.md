# F_USINT_TO_INT

<img width="1436" height="214" alt="F_USINT_TO_INT" src="https://github.com/user-attachments/assets/d630e0ac-d3d0-4568-913f-698cfdc7ad6c" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_INT` converts an unsigned 8-bit integer value (USINT) to a signed 16-bit integer value (INT). This block is part of the `iec61131::conversion` package and enables simple type conversion between these two data types.
![F_USINT_TO_INT](F_USINT_TO_INT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (USINT): The unsigned 8-bit integer value to be converted.

### **Data Outputs**

- **OUT** (INT): The resulting signed 16-bit integer value after the conversion.

### **Adapters**

This function block does not use any adapters.

## Operation

The function block performs the conversion by directly assigning the value of input `IN` to output `OUT`. The conversion occurs when event `REQ` is triggered and is confirmed by event `CNF`.

## Technical Features

- **Simple Type Conversion**: The function block performs no additional processing or validation of the data.
- **Efficient Implementation**: The conversion is performed directly in an ST algorithm without additional logic.

## State Overview

The function block has no internal states. The conversion occurs immediately upon the occurrence of the `REQ` event.

## Application Scenarios

- **Type Conversion in Control Applications**: When an unsigned 8-bit value needs to be converted to a signed 16-bit value.
- **Data Compatibility**: In scenarios where different components expect different data types.

## ⚖️ Comparison with Similar Function Blocks

- **F_USINT_TO_UINT**: Converts USINT to UINT (unsigned 16-bit integer).
- **F_USINT_TO_DINT**: Converts USINT to DINT (signed 32-bit integer).
- **F_USINT_TO_UDINT**: Converts USINT to UDINT (unsigned 32-bit integer).

## Conclusion

The `F_USINT_TO_INT` function block provides a simple and efficient way to convert unsigned 8-bit integer values to signed 16-bit integer values. It is particularly useful in applications where type conversion without additional processing is required.