# F_LWORD_BCD_TO_ULINT

<img width="1304" height="185" alt="F_LWORD_BCD_TO_ULINT" src="https://github.com/user-attachments/assets/0e3846eb-9d65-4ac0-b7c1-067b148e9884" />

* * * * * * * * * *
## Introduction
The function block `F_LWORD_BCD_TO_ULINT` converts a BCD-encoded `LWORD` value to a `ULINT` value. This is particularly useful in applications where BCD-encoded data needs to be processed, such as in industrial control systems or communication protocols.

![F_LWORD_BCD_TO_ULINT](F_LWORD_BCD_TO_ULINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input for the BCD-encoded `LWORD` value to be converted.

### **Data Outputs**

- **OUT**: The output for the converted `ULINT` value.

### **Adapters**
No adapters are present.

## Operation
The function block performs the conversion when the `REQ` event occurs. The BCD-encoded value `LWORD` at input `IN` is converted into a value `ULINT` and made available at output `OUT`. The `CNF` event signals successful conversion.

## Technical Features
- The function block uses the BCD-to-ULINT conversion algorithm defined in the IEC 61131-3 standard library.

- The conversion occurs synchronously with the `REQ` event.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event.

2. **Conversion State**: Upon receipt of `REQ`, the conversion is performed and the `CNF` event is triggered.

## Application Scenarios

- Processing of BCD-encoded data in industrial controllers.

- Conversion of BCD-encoded values to numeric values for further calculations.

## ⚖️ Comparison with Similar Function Blocks

- **F_BCD_TO_ULINT**: Converts BCD-encoded values to `ULINT`, but for different data types than `LWORD`.

- **F_LWORD_TO_ULINT**: Converts `LWORD` to `ULINT`, but without BCD encoding.

## Conclusion
The `F_LWORD_BCD_TO_ULINT` function block is a specialized building block for converting BCD-encoded `LWORD` values to `ULINT`. It is easy to use and particularly suitable for applications that work with BCD-encoded data.