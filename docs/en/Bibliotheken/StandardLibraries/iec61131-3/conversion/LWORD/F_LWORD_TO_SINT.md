# F_LWORD_TO_SINT

<img width="1452" height="216" alt="F_LWORD_TO_SINT" src="https://github.com/user-attachments/assets/53060025-97b1-48c5-abbb-a61940c248b2" />

* * * * * * * * * *
## Introduction
The function block `F_LWORD_TO_SINT` converts a `LWORD` value (64-bit unsigned integer) to a `SINT` value (8-bit signed integer). This conversion is useful when data needs to be transferred from a larger range of values to a smaller, more specific range.

![F_LWORD_TO_SINT](F_LWORD_TO_SINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the execution of the function block. When activated, the input value `IN` is processed.


### **Event Outputs**

- **CNF**: Signals successful completion of the conversion and provides the result value `OUT`.

### **Data Inputs**

- **IN** (`LWORD`): The input value that is converted from `LWORD` to `SINT`.

### **Data Outputs**

- **OUT** (`SINT`): The result of the conversion.

### **Adapters**
This function block does not use adapters.


### ## Functionality

The function block performs a direct type conversion of the input value `IN` from type `LWORD` to type `SINT`. The conversion is carried out by the function `LWORD_TO_SINT(IN)`, which is implemented in the algorithm `REQ`. Upon successful conversion, the event `CNF` is triggered.

## Technical Features

- **Type Conversion**: Since `LWORD` covers a larger range of values than `SINT`, data loss can occur if the input value is outside the representable range of `SINT` (-128 to 127).

- **Algorithm**: The algorithm is implemented in Structured Text (ST) and performs a direct conversion.

## State Overview

1. **Idle State**: Waits for the event `REQ`.

2. **Execution State**: The conversion is performed upon `REQ`.

3. **Acknowledgement State**: After successful conversion, `CNF` is triggered, and the block returns to the idle state.

## Application Scenarios

- **Data Reduction**: When only the lower 8 bits of a 64-bit value are relevant.

- **Communication**: When transferring data between systems with different word sizes.

- **Memory Optimization**: When memory space is limited and smaller data types are preferred.


## ⚖️ Comparison with similar building blocks

- **F_LWORD_TO_INT**: Converts `LWORD` to `INT` (16-bit signed integer).

- **F_LWORD_TO_DINT**: Converts `LWORD` to `DINT` (32-bit signed integer).

- **F_LWORD_TO_USINT**: Converts `LWORD` to `USINT` (8-bit unsigned integer).

Unlike these blocks, `F_LWORD_TO_SINT` is specifically for conversion to an 8-bit signed integer.



## Conclusion

The function block `F_LWORD_TO_SINT` provides a simple and efficient way to convert 64-bit values to 8-bit signed integers. It is particularly useful in scenarios where memory efficiency or the processing of portions of a larger data type is required. However, when using it, care must be taken to avoid potential data loss with values outside the `SINT` range.