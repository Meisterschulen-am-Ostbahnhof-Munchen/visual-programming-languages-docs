# AX_XOR_2

<img width="1009" height="261" alt="image" src="https://github.com/user-attachments/assets/8e5ec6ce-d2bb-4517-ac38-d14a7e43976b" />
* * * * * * * * * *
## Introduction

The AX_XOR_2 function block is a generic function block for calculating the Boolean XOR operation (exclusive OR). It processes two input signals and outputs the logical XOR result.
![AX_XOR_2](AX_XOR_2.svg)
## Interface Structure

### **Event Inputs**

No direct event inputs are available – processing is handled via adapter interfaces.

### **Event Outputs**

No direct event outputs are available – output is handled via adapter interfaces.

### **Data Inputs**

No direct data inputs are available – input is handled via adapter interfaces.

### **Data Outputs**

No direct data outputs are available – output is handled via adapter interfaces.

### **Adapter**

- **IN1** (Socket): XOR Input 1 - Receives the first input signal
- **IN2** (Socket): XOR Input 2 - Receives the second input signal
- **OUT** (Plug): XOR Result - Outputs the calculated XOR result

All adapters use the type `adapter::types::unidirectional::AX` for unidirectional communication.

## Functionality

The function block continuously calculates the XOR operation between the two input signals IN1 and IN2. The XOR function outputs a true signal (TRUE) if and only if exactly one of the two inputs is true (TRUE). If both inputs are the same (both TRUE or both FALSE), a false signal (FALSE) is output.

## Technical Features

- Generic function block with the class `GEN_AX_XOR`
- Uses unidirectional adapters for inputs and outputs
- Implemented according to the IEC 61499-2 standard
- Part of the `adapter::booleanOperators` package

## State Overview

The function block has a continuous operating state and constantly calculates the XOR result based on the current input values.

## Application Scenarios

- Logic circuits in control systems
- Comparison of two binary signals
- Detection of signal differences
- Safety-related circuits
- Digital signal processing

## ⚖️ Comparison with similar function blocks

Compared to other logical operators such as AND or OR, XOR has the unique feature that a TRUE signal is only generated when the input values are different. This makes it particularly suitable for comparison and difference detection tasks.

Comparison with [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md)

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The AX_XOR_2 function block provides an efficient and reliable solution for XOR operations in 4diac-based control systems. Its use of adapter interfaces allows for flexible integration into various system architectures and makes it particularly suitable for applications where signal differences need to be detected.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
