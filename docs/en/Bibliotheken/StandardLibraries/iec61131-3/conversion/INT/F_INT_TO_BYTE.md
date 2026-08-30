# F_INT_TO_BYTE

<img width="1222" height="184" alt="F_INT_TO_BYTE" src="https://github.com/user-attachments/assets/abc57835-6182-406b-9b56-87c0a227a94c" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_BYTE` is used to convert an integer value (`INT`) to a byte value (`BYTE`). It is part of the package `iec61131::conversion` and provides a simple and efficient way to convert data types within IEC 61499 systems.
![F_INT_TO_BYTE](F_INT_TO_BYTE.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The integer value (`INT`) to be converted to a byte value.

### **Data Outputs**

- **OUT**: The resulting byte value (`BYTE`) after the conversion.

### **Adapters**

This function block does not use any adapters.

## Functionality

When an event is received at input `REQ`, the algorithm is executed, converting the value of `IN` from `INT` to `BYTE` and outputting the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

The algorithm is defined as follows:

ALGORITHM REQ
OUT := INT_TO_BYTE(IN);
END_ALGORITHM

## Technical Features

- The function block is implemented simply and efficiently, without additional states or complex logic.
- The conversion is performed directly and without delay.

## State Overview

Since it is a simple function block, there are no explicit states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where integer values need to be converted to byte values.
- Integration into larger systems that require strict type control.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_DINT_TO_BYTE` or `F_WORD_TO_BYTE` offer conversions between other data types but are designed for different source types.
- `F_INT_TO_BYTE` is specifically optimized for converting `INT` to `BYTE`.

## Conclusion

The function block `F_INT_TO_BYTE` is a useful tool for type conversion in IEC 61499-based systems. Its simple and efficient implementation makes it ideal for applications requiring fast and reliable conversions.
