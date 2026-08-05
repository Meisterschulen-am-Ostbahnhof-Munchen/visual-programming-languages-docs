# F_UINT_TO_LINT

<img width="1436" height="216" alt="F_UINT_TO_LINT" src="https://github.com/user-attachments/assets/8f25baa4-d194-4dfd-887d-b962e086c413" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_LINT` converts an unsigned 16-bit integer value (UINT) to a signed 64-bit integer value (LINT). This conversion is particularly useful when data needs to be exchanged or processed between systems with different word lengths.

* * * * * * * * * *

![F_UINT_TO_LINT](F_UINT_TO_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `UINT`, which is to be converted to a value of `LINT`.

### **Data Outputs**

- **OUT**: The converted output value of type `LINT`.

### **Adapters**

- No adapters are available.

* * * * * * * * * *
## Functionality
The function block performs a direct assignment of the input value `IN` to the output `OUT`. Since `LINT` has a larger value range than `UINT`, the conversion is lossless. The block is activated by the event `REQ` and signals the completion of the operation with the event `CNF`.

* * * * * * * * * *
## Technical Features

- **Lossless Conversion**: Since `LINT` (64 bits) covers a larger value range than `UINT` (16 bits), no information is lost during the conversion.

- **Simple Implementation**: The block uses a simple algorithm for direct value assignment.


* * * * * * * * * * *
## State Overview

1. **Idle State**: The block is waiting for the event `REQ`.

2. **Activation State**: Upon receiving `REQ`, the input value `IN` is read and converted.

3. **Acknowledgement State**: After successful conversion, the event `CNF` is triggered, and the block returns to the idle state.

* * * * * * * * * *
## Application Scenarios

- **Data Conversion**: In systems that need to process both 16-bit and 64-bit data.

- **Interface Adaptation**: For communication between devices with different word widths.

- **Data Processing**: In algorithms that require higher precision for calculations.

* * * * * * * * * *
## ⚖️ Comparison with similar function blocks

- **F_UINT_TO_INT**: Converts `UINT` to `INT` (16 bits), but with a signed value.

- **F_UINT_TO_DINT**: Converts `UINT` to `DINT` (32 bits), offering a wider range of values than `INT`, but less than `LINT`.

- **F_UINT_TO_ULINT**: Converts `UINT` to `ULINT` (64 bits), remaining unsigned.


* * * * * * * * * *
## Conclusion

The `F_UINT_TO_LINT` function block is a simple and efficient tool for converting 16-bit unsigned integer values to 64-bit signed integer values. Its lossless conversion and ease of use make it ideal for applications requiring higher precision or compatibility with 64-bit systems.