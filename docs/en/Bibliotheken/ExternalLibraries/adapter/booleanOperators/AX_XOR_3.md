# AX_XOR_3

<img width="1009" height="299" alt="image" src="https://github.com/user-attachments/assets/716a2f15-e5b5-4f7f-b30c-42b13251bace" />
* * * * * * * * * *
## Introduction

The AX_XOR_3 function block is a generic function block for calculating the Boolean XOR operation with three inputs. It implements the exclusive OR operation for three binary input signals and outputs the corresponding result.
![AX_XOR_3](AX_XOR_3.svg)

## Interface Structure

### **Event Inputs**

*No event inputs available*

### **Event Outputs**

*No event outputs available*

### **Data Inputs**

*No direct data inputs available*

### **Data Outputs**

*No direct data outputs available*

### **Adapters**

**Sockets (Inputs):**

- **IN1**: XOR input 1 (Adapter type: unidirectional::AX)
- **IN2**: XOR input 2 (Adapter type: unidirectional::AX)
- **IN3**: XOR input 3 (Adapter type: unidirectional::AX)

**Plugs (Outputs):**

- **OUT**: XOR result (Adapter type: unidirectional::AX)

## Functionality

This function block calculates the XOR operation for three input signals. The XOR operation outputs a "true" signal if and only if an odd number of the inputs are "true". With three inputs, this means:

- The result is true if exactly one or all three inputs are true.
- The result is false if none or exactly two inputs are true.

## Technical Features

- Generic function block with the class name identifier 'GEN_AX_XOR'
- Uses unidirectional adapters for communication
- Implemented according to the IEC 61499-2 standard
- No internal states or storage required

## State Overview

The function block has no internal states and operates statically. The output is calculated solely based on the current input values.

## Application Scenarios

- Three-input switching networks
- Parity checks
- Safety-critical controllers where odd-numbered activation is required
- Logical operations in automation systems

## ⚖️ Comparison with similar function blocks

Compared to standard two-input XOR blocks, AX_XOR_3 offers the extension to three inputs. While a two-input XOR only returns true if the inputs are unequal, the three-input XOR takes the parity of all three signals into account.

Comparison with [XOR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_3.md)]

## 🛠️ Related Exercises

* [Exercise_002a7_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a7_AX.md)]

## Conclusion

The AX_XOR_3 function block provides a reliable and efficient solution for triple XOR operations in IEC 61499-based control systems. By using adapters, it enables flexible integration into different system architectures and is particularly suitable for applications that require parity checking or special logical conditions with three input signals.
