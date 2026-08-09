# F_BYTE_TO_USINT

<img width="1244" height="181" alt="F_BYTE_TO_USINT" src="https://github.com/user-attachments/assets/a6df83fd-735f-4694-b3c4-f581d43eac55" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_TO_USINT` converts a `BYTE` value to a `USINT` value (Unsigned Short Integer). This function block is particularly useful in scenarios where type conversion between these two data types is required, for example, in communication between different systems or in data processing.
![F_BYTE_TO_USINT](F_BYTE_TO_USINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `BYTE` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `USINT`, containing the result of the conversion.

### **Adapters**

No adapters are available.

## Functionality

The function block performs the conversion by transforming the `BYTE` value at input `IN` into a `USINT` value and providing the result at output `OUT`. The conversion occurs synchronously with the triggering of the `REQ` event and is confirmed by the `CNF` event.

## Technical Features

- The function block uses the built-in function `BYTE_TO_USINT` for the conversion.
- It is a simple function block without a state machine or complex logic.

## State Overview

Because it is a simple function block, there are no state transitions or state management. The operation is atomic and is executed on every `REQ` event.

## Application Scenarios

- Type conversion in communication protocols where different systems use different data types.
- Data processing in control systems where conversion between `BYTE` and `USINT` is required.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_WORD_TO_UINT` or `F_DWORD_TO_UDINT` perform similar conversions, but with different data types.
- `F_BYTE_TO_USINT` is specifically optimized for converting `BYTE` to `USINT` and is therefore more efficient for this use case.

## Conclusion

The `F_BYTE_TO_USINT` function block is a simple yet effective building block for converting between `BYTE` and `USINT`. Its simplicity and efficiency make it ideal for applications requiring fast and reliable type conversion.
