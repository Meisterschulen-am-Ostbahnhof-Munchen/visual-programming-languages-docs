# XOR_6

![XOR_6](https://user-images.githubusercontent.com/116869307/214143825-a01dfad5-e15c-4869-bac8-379a175f01d9.png)

* * * * * * * * * *

## Introduction
The XOR_6 function block is a generic function block for calculating bitwise XOR operations with six inputs. It implements the Boolean exclusive OR operation at the bit level according to the IEC 61131-3 standard and can work with various bit data types.


![XOR_6](XOR_6.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal Execution Request - triggers the calculation of the XOR operation

### **Event Outputs**
- **CNF**: Execution Acknowledgement - signals the completion of the calculation

### **Data Inputs**
- **IN1**: XOR Input 1 (ANY_BIT data type)
- **IN2**: XOR Input 2 (ANY_BIT data type)
- **IN3**: XOR Input 3 (ANY_BIT data type)
- **IN4**: XOR Input 4 (ANY_BIT data type)
- **IN5**: XOR Input 5 (ANY_BIT data type)
- **IN6**: XOR Input 6 (ANY_BIT data type)

### **Data Outputs**
- **OUT**: XOR Result (ANY_BIT Data Type)

### **Adapter**
No adapter interfaces are available.

## Functionality
The XOR_6 block performs a bitwise XOR operation on all six inputs. When the REQ event is triggered, the values at IN1 to IN6 are processed, and the result is output to OUT. The operation follows the mathematical definition of the XOR function, where the result is true for each bit if an odd number of the corresponding input bits are true.


The calculation is performed according to the formula: OUT = IN1 ⊕ IN2 ⊕ IN3 ⊕ IN4 ⊕ IN5 ⊕ IN6

## Technical Features
- **Generic Data Type**: Uses ANY_BIT, enabling compatibility with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)

- **Six Inputs**: Offers extended functionality compared to standard XOR blocks with fewer inputs

- **Event-Driven Execution**: Follows the 4diac execution model with REQ/CNF event pairs

## State Overview
The function block has a simple state machine:

1. **Wait State**: Block waits for a REQ event

2. **Calculate State**: Processes the inputs when a REQ event is triggered

3. **Output State**: Sends a CNF event with the calculated result

## Application Scenarios

- **Parity Check**: Checks the Data integrity through XOR operation of multiple data words
- **Data encryption**: Simple cryptographic operations
- **Error detection**: Generation of checksums in communication protocols
- **Control engineering**: Logical operations in automation applications

## ⚖️ Comparison with similar blocks
Compared to standard two-input XOR blocks, XOR_6 offers:

- Enhanced functionality with six direct inputs
- Elimination of the need to cascade multiple XOR blocks
- More compact implementation for complex XOR operations

## Conclusion
The XOR_6 function block provides a powerful and flexible solution for bitwise XOR operations with multiple inputs. Its generic nature allows for broad applicability in various automation projects, while its six-input functionality supports efficient implementations of complex logical operations.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```