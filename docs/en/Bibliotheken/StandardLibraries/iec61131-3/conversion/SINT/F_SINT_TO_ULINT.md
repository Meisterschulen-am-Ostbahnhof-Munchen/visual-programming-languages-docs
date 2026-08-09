# F_SINT_TO_ULINT

<img width="1450" height="213" alt="F_SINT_TO_ULINT" src="https://github.com/user-attachments/assets/e86a91a2-2770-46c2-8677-2d3c90a6111a" />
* * * * * * * * * *
## Introduction

The function block `F_SINT_TO_ULINT` converts a signed 8-bit integer value (`SINT`) to an unsigned 64-bit integer value (`ULINT`). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_SINT_TO_ULINT](F_SINT_TO_ULINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `SINT` to be converted.

### **Data Outputs**

- **OUT**: The converted output value of type `ULINT`.

### **Adapters**

No adapters are present.

## Operation

The function block performs the conversion when the event `REQ` is received. The input value `IN`, of type `SINT`, is converted to a value of `ULINT` and output `OUT`. Successful conversion is indicated by the event `CNF`.

## Technical Features

- The conversion is performed by the built-in function `SINT_TO_ULINT`.
- The function block is simple and deterministic, as it does not store any internal states.

## State Overview

The function block has no internal state. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Type conversion in control applications where `SINT` values need to be converted to larger unsigned integer types.
- Data processing in systems that work with different integer formats.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_INT_TO_ULINT` or `F_DINT_TO_ULINT` perform similar conversions, but with different input types.
- `F_SINT_TO_ULINT` is specifically optimized for converting `SINT` to `ULINT`.

## Conclusion

The `F_SINT_TO_ULINT` function block provides a simple and efficient way to convert `SINT` values to `ULINT`. It is particularly useful in applications where safe and fast type conversion is required.