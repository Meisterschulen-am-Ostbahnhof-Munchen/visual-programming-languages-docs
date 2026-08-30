# F_WORD_TO_UINT

<img width="1439" height="214" alt="F_WORD_TO_UINT" src="https://github.com/user-attachments/assets/a5a364ba-2187-4117-a0c8-e74cd0324890" />
* * * * * * * * * *
## Introduction

The function block `F_WORD_TO_UINT` converts a `WORD` data type to a `UINT` data type. This conversion is particularly useful in scenarios where type conversion between these two data types is required, for example, in communication between different systems or when processing data from different sources.
![F_WORD_TO_UINT](F_WORD_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `WORD` to be converted.

### **Data Outputs**

- **OUT**: The output of type `UINT`, containing the result of the conversion.

### **Adapters**

This function block has no adapters.

## Operation

The function block performs the conversion from `WORD` to `UINT` as soon as the event `REQ` is received. The conversion is performed using the function `WORD_TO_UINT(IN)`. After successful conversion, the result is output via output `OUT`, and the event `CNF` is triggered.

## Technical Features

- The function block has a simple structure and contains only one algorithm for the conversion.
- The conversion is performed directly without any additional processing steps.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Type conversion in control systems.
- Data processing in industrial automation solutions.
- Communication between systems with different data types.

## ⚖️ Comparison with Similar Building Blocks

Compared to other conversion building blocks, `F_WORD_TO_UINT` is specifically designed to convert `WORD` to `UINT`. Other building blocks might offer additional functions or a wider range of conversions, but they may be more complex in their structure.

## Conclusion

The `F_WORD_TO_UINT` function block is a simple and efficient tool for the specific conversion of `WORD` to `UINT`. Its simplicity makes it particularly suitable for applications where fast and direct type conversion is required.
