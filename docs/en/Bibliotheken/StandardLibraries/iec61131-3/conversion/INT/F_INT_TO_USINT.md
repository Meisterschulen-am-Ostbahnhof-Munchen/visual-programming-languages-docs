# F_INT_TO_USINT

<img width="1232" height="183" alt="F_INT_TO_USINT" src="https://github.com/user-attachments/assets/936ae83a-1805-4eae-89d4-6a1f41f0e727" />

* * * * * * * * * *
## Introduction
The function block `F_INT_TO_USINT` converts an integer value of data type `INT` (16-bit signed integer) to data type `USINT` (8-bit unsigned integer). This block is particularly useful in scenarios where type conversion between numeric values of different sizes is required.

![F_INT_TO_USINT](F_INT_TO_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Type: `Event`): Starts the execution of the conversion. The input is linked to the data input `IN`.

### **Event Outputs**

- **CNF** (Type: `Event`): Signals successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (Type: `INT`): The input value to be converted.

### **Data Outputs**

- **OUT** (Type: `USINT`): The result of the conversion from `INT` to `USINT`.

### **Adapters**
This function block does not have any adapter interfaces.


### **Adapters** ... ## Functionality
When the event input `REQ` is triggered, the algorithm of the function block is executed. This converts the value at the data input `IN` from type `INT` to type `USINT` and stores the result in the data output `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Details

- The conversion is performed by the function `INT_TO_USINT`, which converts the `INT` value into a `USINT` value. Data loss can occur if the original `INT` value is outside the representable range of `USINT` (0 to 255).

- This function block is part of the `iec61131::conversion` package, which provides various type conversions.

## State Overview
The function block has no internal state. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where different data types need to be processed.

- Reducing memory usage by converting to smaller data types where possible.

- Preparing data for communication with systems that can only process `USINT` values.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_DINT_TO_USINT` or `F_SINT_TO_USINT` offer conversions from other integer types to `USINT`. `F_INT_TO_USINT` is specifically optimized for converting `INT` to `USINT`.

- Unlike generic conversion blocks, this function block provides a direct and efficient solution for specific type conversion.

## Conclusion
The `F_INT_TO_USINT` function block is a simple and efficient function block for converting `INT` to `USINT` values. It is ideally suited for applications that require precise and specific type conversion, especially in environments with limited resources or specific data type requirements.