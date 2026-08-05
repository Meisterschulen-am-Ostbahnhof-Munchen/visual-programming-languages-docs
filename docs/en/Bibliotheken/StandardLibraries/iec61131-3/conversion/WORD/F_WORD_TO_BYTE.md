# F_WORD_TO_BYTE
<img width="1439" height="214" alt="F_WORD_TO_BYTE" src="https://github.com/user-attachments/assets/f145baeb-c930-43aa-803f-40e3e50a88fe" />
* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_BYTE` is used to convert a `WORD` data type to a `BYTE` data type. It is part of the `iec61131::conversion` package and is suitable for applications where type conversion between these two data types is required.
![F_WORD_TO_BYTE](F_WORD_TO_BYTE.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`WORD`): The input value to be converted from `WORD` to `BYTE`.

### **Data Outputs**
- **OUT** (`BYTE`): The converted output value of type `BYTE`.

### **Adapters**
No adapters are defined for this function block.

## Operation
The function block performs the conversion when the event `REQ` is received. The input value `IN`, of type `WORD`, is converted to a `BYTE` value using the function `WORD_TO_BYTE` and output `OUT`. After the conversion is complete, the event `CNF` is triggered.

## Technical Features
- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm for the conversion.
- The conversion is performed directly and without any additional delay.

## State Overview

1. **Idle State**: The function block waits for the event `REQ`.

2. **Conversion State**: Upon receiving `REQ`, the conversion is performed and `CNF` is triggered.

## Application Scenarios
- Type conversion in control applications where `WORD` data needs to be converted to `BYTE` data.
- Integration into larger control systems that require compatible data type conversion.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion functions, this function block offers a specialized and optimized solution for converting `WORD` to `BYTE`.
- Other similar blocks might offer additional features such as error handling or optional parameters, which is not the case here.

## Conclusion

The `F_WORD_TO_BYTE` function block is an efficient and simple solution for converting `WORD` to `BYTE` data. It is particularly suitable for applications where fast and direct type conversion is required.