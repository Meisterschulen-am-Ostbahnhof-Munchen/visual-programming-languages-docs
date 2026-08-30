# F_BOOL_TO_UDINT

<img width="1447" height="213" alt="F_BOOL_TO_UDINT" src="https://github.com/user-attachments/assets/2efcda08-ff53-40f4-ba50-1a4fa948991e" />
* * * * * * * * * *
## Introduction

The function block `F_BOOL_TO_UDINT` converts a `BOOL` value to a `UDINT` value. This conversion is useful when Boolean values are used in calculations or storage operations that require a larger numeric data type.
![F_BOOL_TO_UDINT](F_BOOL_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `BOOL` to be converted.

### **Data Outputs**

- **OUT**: The output of type `UDINT`, containing the result of the conversion.

### **Adapters**

No adapters are supported.

## Functionality

The function block performs the conversion from `BOOL` to `UDINT` when the event `REQ` is triggered. The Boolean value `TRUE` is converted to `1`, and `FALSE` to `0`. The result is output at data output `OUT`, and the event `CNF` signals successful execution.

## Technical Features

- The conversion is instantaneous and without delay.
- The function block is suitable for use in real-time systems.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of Boolean switching states for numerical calculations.
- Integration of Boolean signals into systems that can only process numeric values.

## ⚖️ Comparison with similar building blocks

- Compared to other conversion blocks such as `F_BOOL_TO_INT` or `F_BOOL_TO_DINT`, this block offers conversion to an unsigned 32-bit integer.

## Conclusion

The `F_BOOL_TO_UDINT` function block is a simple and efficient building block for converting Boolean values to unsigned 32-bit integers. It is particularly useful in scenarios where Boolean signals need to be integrated into numerical processes.
