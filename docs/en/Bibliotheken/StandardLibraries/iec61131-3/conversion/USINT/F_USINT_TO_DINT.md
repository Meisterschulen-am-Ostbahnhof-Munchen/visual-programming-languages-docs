# F_USINT_TO_DINT
<img width="1454" height="214" alt="F_USINT_TO_DINT" src="https://github.com/user-attachments/assets/94cb99ea-b608-4a9b-b390-02601460c14b" />
* * * * * * * * * *
## Introduction
The function block `F_USINT_TO_DINT` converts a `USINT` value (8-bit unsigned integer) to a `DINT` value (32-bit signed integer). This conversion is useful when values need to be converted between different data types, especially when an extension of the bit width is required.
![F_USINT_TO_DINT](F_USINT_TO_DINT.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this event is triggered, the value of `IN` is converted to `OUT`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event is output along with the updated value of `OUT`.

### **Data Inputs**
- **IN** (`USINT`): The input value to be converted.

### **Data Outputs**
- **OUT** (`DINT`): The converted output value.

### **Adapters**
No adapters available.

#
## ## Functionality

The function block directly assigns the input value `IN` (of type `USINT`) to the output `OUT` (of type `DINT`). Since `DINT` has a larger bit width than `USINT`, the value is extended without data loss.

The algorithm is triggered by the `REQ` event and outputs the `CNF` event after the conversion.

## Technical Features
- The function block is deterministic and has no internal state.
- The conversion is lossless, as `DINT` can represent all values of `USINT`.

## State Overview
The function block has no internal states. Execution occurs immediately after the `REQ` event is triggered.

## Application Scenarios
- Extension of 8-bit unsigned values to 32-bit signed values in control applications.
- Compatibility between different parts of a control system that use different data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to `F_SINT_TO_DINT` or `F_INT_TO_DINT`, this function block handles only unsigned 8-bit values.

Similar conversion blocks exist for other data types, such as `F_BOOL_TO_INT` or `F_REAL_TO_LREAL`.

## Conclusion
The `F_USINT_TO_DINT` function block is a simple and efficient building block for converting 8-bit unsigned integer values to 32-bit signed integer values. It is particularly useful in scenarios where type extension without data loss is required.
