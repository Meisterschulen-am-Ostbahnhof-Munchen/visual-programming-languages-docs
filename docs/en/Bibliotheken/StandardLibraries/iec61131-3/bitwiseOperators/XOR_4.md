# XOR_4
![XOR_4](https://user-images.githubusercontent.com/116869307/214143769-c8306099-6b4d-4e74-ad33-3cd11198e36d.png)
* * * * * * * * * *
## Introduction
The XOR_4 function block is a generic function block for calculating bitwise XOR operations with four inputs. It implements the exclusive OR operation at the bit level according to the IEC 61131-3 standard and can work with various bit data types.
![XOR_4](XOR_4.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the XOR operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1**: XOR input 1 (ANY_BIT data type)
- **IN2**: XOR input 2 (ANY_BIT data type)
- **IN3**: XOR input 3 (ANY_BIT data type)
- **IN4**: XOR input 4 (ANY_BIT data type)

### **Data Outputs**
- **OUT**: XOR result (ANY_BIT data type)

### **Adapters**
The function block does not use adapters.

## Functionality
Upon arrival of the REQ event, the XOR_4 block performs a bitwise XOR operation on all four inputs. The operation is executed according to the following logic:

OUT = IN1 XOR IN2 XOR IN3 XOR IN4
Once the calculation is complete, the CNF event, along with the result, is output to OUT.
... ## Technical Features
- **Generic Data Type**: Uses ANY_BIT, enabling use with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)
- **Four-Input XOR Operation**: Processes four inputs in a single operation
- **Event-Driven**: Execution is triggered by the REQ event
- **Standard-Compliant**: Conforms to the IEC 61131-3 standard for bitwise Boolean functions

## State Transitions
1. **Wait State**: Block waits for REQ event

2. **Compute State**: All inputs are processed upon REQ event

3. **Output State**: CNF event is output with the computed result

4. Returns to Wait State

## Application Scenarios
- **Bit Manipulation**: Used in control applications for bitwise operations
- **Parity Checking**: Implementation of parity bits or error detection
- **Data Encryption**: Simple cryptographic operations
- **Signal Processing**: Combining multiple digital signals

## ⚖️ Comparison with Similar Blocks
- **AND/OR Blocks**: Process logical AND/OR operations instead of exclusive OR
- **XOR with Fewer Inputs**: This block offers four inputs compared to standard XOR blocks, which typically have two inputs
- **Generic vs. Specific Blocks**: Can process various bit data types, while specific blocks are limited to one data type

## Conclusion
The XOR_4 function block offers a flexible and standards-compliant solution for four-input bitwise XOR operations. Its generic nature allows for use in various application areas, while its event-driven architecture ensures efficient integration into control systems.