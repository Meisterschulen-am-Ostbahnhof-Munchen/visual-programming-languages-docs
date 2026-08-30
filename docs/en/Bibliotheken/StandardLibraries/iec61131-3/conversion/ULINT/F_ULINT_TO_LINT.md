# F_ULINT_TO_LINT

<img width="1448" height="214" alt="F_ULINT_TO_LINT" src="https://github.com/user-attachments/assets/198ce0c4-05ea-4392-8b16-aa83ed6ab931" />
* * * * * * * * * *
## Introduction

The function block `F_ULINT_TO_LINT` converts an unsigned 64-bit integer value (ULINT) to a signed 64-bit integer value (LINT). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_ULINT_TO_LINT](F_ULINT_TO_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (ULINT): The unsigned 64-bit integer value to be converted.

### **Data Outputs**

- **OUT** (LINT): The resulting signed 64-bit integer value after conversion.

#### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion by transforming the value of input `IN` from type `ULINT` to type `LINT`. The conversion is performed directly and without further processing. The result is output at `OUT` as soon as the event `CNF` is triggered.

## Technical Features

- The conversion is performed using the function `ULINT_TO_LINT`, which is implemented in the function block's algorithm.
- The block is suitable for use in real-time systems because it does not involve any delays or complex calculations.

## State Overview

The function block has no internal states. The conversion is performed and immediately acknowledged each time the `REQ` event occurs.

## Application Scenarios

- Type conversion in control and automation systems.
- Data processing in industrial applications where unsigned and signed values need to be processed.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion blocks, such as `F_DINT_TO_INT`, this one is specifically designed for 64-bit data types.
- Similar blocks might include additional features like range checks or error handling, which is not the case here.

## Conclusion

The `F_ULINT_TO_LINT` function block is a simple and efficient tool for converting between the data types `ULINT` and `LINT`. Its simplicity makes it reliable and easy to integrate into existing systems.
