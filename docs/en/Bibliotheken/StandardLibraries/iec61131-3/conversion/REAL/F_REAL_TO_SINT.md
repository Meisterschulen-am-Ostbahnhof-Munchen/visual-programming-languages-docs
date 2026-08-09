# F_REAL_TO_SINT

<img width="1441" height="213" alt="F_REAL_TO_SINT" src="https://github.com/user-attachments/assets/90ac7b2b-bde1-414a-9764-7b9723463b8e" />
* * * * * * * * * *
## Introduction

The function block `F_REAL_TO_SINT` converts a `REAL` value (floating-point number) to a `SINT` value (8-bit signed integer). This block is particularly useful in control applications where type conversion between these two data types is required.
![F_REAL_TO_SINT](F_REAL_TO_SINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. The value at input `IN` is processed upon this event.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event, along with the converted value, is output at `OUT`.

### **Data Inputs**

- **IN**: Input for the `REAL` value to be converted to a `SINT` value.

### **Data Outputs**

- **OUT**: Output for the converted `SINT` value.

### **Adapters**

- This function block does not have any adapters.

## Functionality

The function block performs the conversion by transforming the `REAL` value at input `IN` into a `SINT` value using the function `REAL_TO_SINT`. The conversion occurs when the event `REQ` is triggered, and the result is output with the event `CNF`.

## Technical Features

- The function block is implemented as a simple function block (`SimpleFB`) containing only one algorithm.
- The conversion truncates the `REAL` value to the value range of `SINT` (-128 to 127). Values outside this range result in an overflow.

## State Overview

The function block has no internal state. The conversion occurs immediately upon the occurrence of the `REQ` event.

## Application Scenarios

- Type conversion in control algorithms where floating-point values need to be converted to integers.
- Signal processing where `REAL` sensor data needs to be reduced to `SINT`.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_REAL_TO_INT` or `F_REAL_TO_USINT` offer conversions to other integer types. `F_REAL_TO_SINT` is specific to 8-bit signed integers.

## Conclusion

The `F_REAL_TO_SINT` function block is a simple and efficient building block for converting floating-point numbers to 8-bit signed integers. Its use is advantageous in scenarios where such type conversion is required, particularly in control and signal processing applications.
