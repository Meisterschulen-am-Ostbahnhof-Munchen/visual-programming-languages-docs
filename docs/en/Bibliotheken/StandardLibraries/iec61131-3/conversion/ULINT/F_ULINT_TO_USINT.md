# F_ULINT_TO_USINT

<img width="1462" height="214" alt="F_ULINT_TO_USINT" src="https://github.com/user-attachments/assets/317d59b5-d0e5-42d1-9ad1-3b37c6c9f91d" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_USINT` converts a 64-bit unsigned integer value (`ULINT`) to an 8-bit unsigned integer value (`USINT`). This block is particularly useful in scenarios where type conversion between these two data types is required.

![F_ULINT_TO_USINT](F_ULINT_TO_USINT.svg)

## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. Connected to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. Connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `ULINT` (64-bit unsigned integer) to be converted.

### **Data Outputs**

- **OUT**: The output value of type `USINT` (8-bit unsigned integer) containing the result of the conversion.

### **Adapters**
This function block does not use any adapters.


### ## Functionality

When the event `REQ` is triggered, the algorithm is executed, converting the value of `IN` of type `ULINT` to type `USINT` and outputting the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Details

- The conversion truncates the value of `ULINT` to the size of `USINT`. It is important to ensure that the input value is within the range of `USINT` (0 to 255) to avoid unexpected results.


# Technical Details

- The conversion truncates the value of `ULINT` to the size of `USINT`. It is important to ensure that the input value is within the range of `USINT` (0 to 255) to avoid unexpected results.


# Technical Details - The algorithm is implemented in Structured Text (ST).

## State Overview
The function block has a simple state machine:

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Performs the conversion and triggers `CNF`.

## Application Scenarios

- Type conversion in control systems where data is in different formats.

- Reducing data storage size when only small value ranges are needed.

## ⚖️ Comparison with Similar Blocks

- Similar function blocks such as `F_DINT_TO_INT` or `F_LREAL_TO_REAL` perform similar type conversions, but for different data types.

Unlike generic conversion blocks, `F_ULINT_TO_USINT` is specialized and optimized for converting between `ULINT` and `USINT`.

## Conclusion
The `F_ULINT_TO_USINT` function block provides an efficient and simple way to convert values from `ULINT` to `USINT`. Its clear interface and simple operation make it a useful building block in IEC 61131 programming.