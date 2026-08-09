# F_WORD_TO_DINT

<img width="1439" height="214" alt="F_WORD_TO_DINT" src="https://github.com/user-attachments/assets/b1305cee-de08-4bea-9af0-84521b8ee895" />
* * * * * * * * * *
## Introduction

The function block `F_WORD_TO_DINT` converts a `WORD` data type to a `DINT` data type. This function block is particularly useful in scenarios where type conversion between these two data types is required, for example, when processing data from different sources or adapting data for different system components.
![F_WORD_TO_DINT](F_WORD_TO_DINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. This input triggers the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Execution Confirmation. This output signals the completion of the conversion. It is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Input variable of type `WORD` containing the value to be converted.

### **Data Outputs**

- **OUT**: Output variable of type `DINT` containing the result of the conversion.

### **Adapters**

This function block has no adapters.

## Functionality

The function block `F_WORD_TO_DINT` performs the conversion from a `WORD` to a `DINT` data type. When the `REQ` event is triggered, the value at input `IN` is read and converted using the function `WORD_TO_DINT`. The result is output to `OUT`, and the `CNF` event signals the completion of the operation.

## Technical Features

- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion occurs directly and without any additional delay as soon as the `REQ` event arrives.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Type conversion in control systems where data of different types needs to be processed.
- Integration of components that use different data types.
- Data preparation for further processing steps.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion function blocks such as `F_INT_TO_REAL` or `F_BOOL_TO_BYTE`, `F_WORD_TO_DINT` is specifically designed for converting `WORD` to `DINT`.
- Similar function blocks might offer additional features such as range checks or scaling, which is not the case here.

## Conclusion

The function block `F_WORD_TO_DINT` is a simple and efficient tool for converting `WORD` values to `DINT` values. Its clear interface structure and direct functionality make it a reliable component in control applications where such type conversions are required.