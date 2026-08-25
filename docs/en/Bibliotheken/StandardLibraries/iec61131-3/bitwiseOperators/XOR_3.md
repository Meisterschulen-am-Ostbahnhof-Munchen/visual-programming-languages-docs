# XOR_3

![XOR_3](https://user-images.githubusercontent.com/116869307/214143735-3c0a538b-d39a-47e0-9cd3-1602d3640896.png)

* * * * * * * * * *
## Introduction

The XOR_3 function block is a generic function block for calculating bitwise XOR operations with three inputs. It implements the logical exclusive OR operation at the bit level according to the IEC 61131-3 standard and can be used with various bit data types.
![XOR_3](XOR_3.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request - triggers the calculation of the XOR operation

### **Event Outputs**

- **CNF**: Execution Acknowledgement - signals the completion of the calculation

### **Data Inputs**

- **IN1**: XOR Input 1 (ANY_BIT data type)
- **IN2**: XOR Input 2 (ANY_BIT data type)
- **IN3**: XOR Input 3 (ANY_BIT data type)

### **Data Outputs**

- **OUT**: XOR Result (ANY_BIT data type)

### **Adapters**

The function block does not use adapters.

## Functionality

Upon arrival of the REQ event, the function block performs a bitwise XOR operation on the three input values IN1, IN2, and IN3. The operation is executed separately for each bit position and corresponds to the logical function: OUT = IN1 XOR IN2 XOR IN3. After completion of the calculation, the CNF event is output along with the result value.

## Technical Features

- Uses the generic data type ANY_BIT, which is compatible with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)
- Implemented as a generic function block with the class 'GEN_XOR'
- Supports exactly three inputs for the XOR operation
- Conforms to the IEC 61131-3 classification for standardized bitwise Boolean functions

## State Overview

The function block operates statelessly:

1. Wait state: No active calculation
2. Calculation state: The XOR operation is executed upon a REQ event
3. Output state: A CNF event with the result is output

## Application Scenarios

- Bitwise encryption operations
- Parity checks in communication protocols
- Error detection in digital systems
- Control logic with multiple conditions
- Data processing in industrial automation systems

## ⚖️ Comparison with Similar Function Blocks

Compared to XOR_3 offers the ability to process three inputs simultaneously, unlike standard two-input XOR blocks. Compared to AND/OR operations, XOR delivers an exclusive result where the output bit is only 1 if an odd number of the input bits are 1.

## 🛠️ Related Exercises

* [Exercise_002a7_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a7_AX.md)

## Conclusion

The XOR_3 function block provides an efficient and flexible solution for bitwise XOR operations with three inputs in 4diac systems. Its generic nature allows its use with various bit data types, making it versatile for industrial automation applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
