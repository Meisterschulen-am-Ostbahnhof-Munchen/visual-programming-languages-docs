# F_ULINT_TO_SINT

<img width="1451" height="214" alt="F_ULINT_TO_SINT" src="https://github.com/user-attachments/assets/ea87d94b-8362-4fe9-8673-31aa7be11c85" />
* * * * * * * * * *
## Introduction

The function block `F_ULINT_TO_SINT` converts a `ULINT` value (64-bit unsigned integer) to a `SINT` value (8-bit signed integer). This block is particularly useful in applications where type conversion between these two data types is required.
![F_ULINT_TO_SINT](F_ULINT_TO_SINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input expects a `ULINT` value to be converted.

### **Data Outputs**

- **OUT**: The output provides the converted `SINT` value.

### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the `REQ` event is triggered. The algorithm converts the `ULINT` value to `IN` and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Details

- The conversion is performed directly by the function `ULINT_TO_SINT`.
- Note that data loss can occur when converting from a larger to a smaller data type if the `ULINT` value is outside the representable range of `SINT`.

## State Overview

The function block has no internal state. The conversion is performed on every `REQ` event.

## Application Scenarios

- Type conversion in control applications
- Data processing where different data types need to be handled
- Communication between systems with different data types

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks like `F_DINT_TO_SINT` or `F_LINT_TO_SINT` perform similar conversions, but with different output data types.
- `F_ULINT_TO_SINT` is specifically for converting `ULINT` to `SINT`.

## Conclusion

The `F_ULINT_TO_SINT` function block provides a simple and efficient way to convert `ULINT` values to `SINT` values. It is particularly useful in applications where type conversion is required; however, potential data loss during the conversion should be considered.