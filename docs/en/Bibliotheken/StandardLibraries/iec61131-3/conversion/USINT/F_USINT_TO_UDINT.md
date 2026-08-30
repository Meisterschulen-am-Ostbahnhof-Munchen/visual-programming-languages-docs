# F_USINT_TO_UDINT

<img width="1464" height="214" alt="F_USINT_TO_UDINT" src="https://github.com/user-attachments/assets/270403b0-17c3-4974-9d94-16d82c7ec576" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_UDINT` converts a `USINT` value (8-bit unsigned integer) to a `UDINT` value (32-bit unsigned integer). This block is particularly useful in scenarios where type conversion without data loss is required.
![F_USINT_TO_UDINT](F_USINT_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN** (`USINT`): The input value to be converted.

### **Data Outputs**

- **OUT** (`UDINT`): The converted output value.

### **Adapters**

No adapters are available.

## Functionality

This function block directly assigns the input value `IN` of type `USINT` to the output value `OUT` of type `UDINT`. Since `UDINT` covers a larger range of values than `USINT`, the conversion occurs without data loss.

## Technical Features

- **Algorithm**: The algorithm `REQ` performs the assignment `OUT := IN`.
- **Data Integrity**: The original value is preserved during conversion to a larger data type.

## State Overview

The function block has no internal states. The conversion occurs immediately upon the occurrence of the `REQ` event.

## Application Scenarios

- **Type Conversion**: In control systems where different data types need to be processed.
- **Data Processing**: In communication between components that use different data types.

## ⚖️ Comparison with similar function blocks

- **F_USINT_TO_INT**: Converts `USINT` to `INT`, but with a potential sign change.
- **F_USINT_TO_UINT**: Converts `USINT` to `UINT` (16-bit), which offers a smaller value range than `UDINT`.

## 🛠️ Related Exercises

- [Exercise_111](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_111.md)

## Conclusion

The `F_USINT_TO_UDINT` function block is a simple and efficient building block for the safe conversion of `USINT` to `UDINT`. Its direct assignment and the wider range of values for the output type make it ideal for applications where data integrity must be guaranteed.
