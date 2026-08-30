# F_LWORD_TO_UDINT

<img width="1466" height="216" alt="F_LWORD_TO_UDINT" src="https://github.com/user-attachments/assets/dc4619b7-62b1-4a3b-b1d5-90a09aeeb2e5" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_UDINT` converts a `LWORD` value (64-bit unsigned integer) to a `UDINT` value (32-bit unsigned integer). This conversion is useful when data needs to be transferred or processed between systems with different word lengths.
![F_LWORD_TO_UDINT](F_LWORD_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- `IN` (LWORD): The 64-bit unsigned integer value to be converted.

### **Data Outputs**

- `OUT` (UDINT): The resulting 32-bit unsigned integer value after the conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

When the `REQ` event is triggered, the value of `IN` is converted from `LWORD` to `UDINT`, and the result is output to `OUT`. The `CNF` event signals the successful completion of the conversion.

The conversion is performed by the function `LWORD_TO_UDINT`, which returns the lower 32 bits of the `LWORD` value as `UDINT`.

## Technical Features

- The function block is suitable for use in real-time systems.
- The conversion is deterministic and has a constant execution time.
- Values greater than the maximum `UDINT` value (2^32 - 1) are truncated.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Communication between systems with different word widths.
- Processing data from external sources that provide 64-bit values, but only 32-bit values are required.
- Reducing memory usage when dealing with known small value ranges.

## ⚖️ Comparison with Similar Function Blocks

- `F_LWORD_TO_DINT`: Converts to a 32-bit signed integer.
- `F_LWORD_TO_UINT`: Converts to a 16-bit unsigned integer.
- `F_LWORD_TO_WORD`: Converts to a 16-bit unsigned value.

## Conclusion

The `F_LWORD_TO_UDINT` function block provides a simple and efficient way to convert 64-bit values to 32-bit values. It is particularly useful in systems that need to handle different word lengths.
