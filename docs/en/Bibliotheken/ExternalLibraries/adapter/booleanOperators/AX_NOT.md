# AX_NOT

<img width="820" height="231" alt="image" src="https://github.com/user-attachments/assets/dc31ab7f-e7b2-434e-88d6-7cf13a88d725" />
* * * * * * * * * *
## Introduction

The AX_NOT function block is a standardized Boolean NOT operator implemented according to the IEC 61131-3 standard. This block performs a logical negation (NOT operation) on the input values and outputs the inverted result.
![AX_NOT](AX_NOT.svg)

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs.

### **Event Outputs**

The function block has no direct event outputs.

### **Data Inputs**

The function block has no direct data inputs.

### **Data Outputs**

The function block has no direct data outputs.

### **Adapters**

- **IN** (Socket): Input adapter of type `adapter::types::unidirectional::AX` - used to transmit input data
- **OUT** (Plug): Output adapter of type `adapter::types::unidirectional::AX` - used to output the processed data

## Functionality

The AX_NOT function block performs a logical negation on the Boolean values received via the IN adapter. The result of the NOT operation is output via the OUT adapter. Processing is bidirectional between the application and resource layers.

## Technical Features

- Implemented according to the IEC 61131-3 standard for Boolean functions
- Uses unidirectional AX adapters for data transmission
- Works with the `adapter::booleanOperators` package
- Supports TypeHash functionality for type identification

## State Overview

The function block operates statelessly and performs the NOT operation directly on the incoming data without storing any internal state.

## Application Scenarios

- Logical inversion of Boolean signals in control applications
- Signal reversal in automation systems
- Use in combinational circuits
- Integration into larger control logic for signal processing

## ⚖️ Comparison with Similar Function Blocks

Compared to other Boolean operators such as AND or OR, AX_NOT performs only the negation operation. The use of adapters instead of direct inputs/outputs allows for more flexible integration into more complex system architectures.

Comparison with [F_NOT](../../../StandardLibraries/iec61131-3/bitwiseOperators/F_NOT.md)

## 🛠️ Related Exercises

- [Exercise_006a3_sub_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_sub_AX.md)

## Conclusion

The AX_NOT function block offers a reliable and standards-compliant implementation of the Boolean NOT operation. Its adapter-based interface design makes it particularly suitable for modular system designs and enables easy integration into existing automation solutions.
