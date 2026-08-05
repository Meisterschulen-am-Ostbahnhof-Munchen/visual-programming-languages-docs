# XOR_2
![XOR_2](https://user-images.githubusercontent.com/116869307/214143689-2a5c46a2-8706-400e-9fc7-fc74efa57eea.png)
* * * * * * * * * *
## Introduction
The XOR_2 function block is a generic function block for calculating the bitwise Boolean XOR operation. It performs an exclusive OR operation between two input values and outputs the result. The function block is suitable for all ANY_BIT data types, thus enabling flexible use with different bit lengths.
![XOR_2](XOR_2.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the XOR operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1** (ANY_BIT): XOR input 1 - first operand for the XOR operation
- **IN2** (ANY_BIT): XOR input 2 - second operand for the XOR operation

### **Data Outputs**
- **OUT** (ANY_BIT): XOR result - result of the bitwise XOR operation

### **Adapters**
The function block does not have any adapter interfaces.

## Functionality
Upon receiving the REQ event, the XOR_2 block performs a bitwise XOR operation between the two input values IN1 and IN2. The operation is performed separately for each bit pair of input values:

- If both bits are the same (both 0 or both 1), the result bit is set to 0.
- If the bits are different, the result bit is set to 1.

After the calculation is complete, the result is output via the OUT output, and the CNF event is sent to confirm execution.

- If the bits are different, the result bit is set to 1. ## Technical Features
- **Generic Implementation**: Supports all ANY_BIT data types (BOOL, BYTE, WORD, DWORD, LWORD)
- **Bitwise Operation**: Performs the XOR operation at the bit level
- **Event-Driven Execution**: Synchronization via REQ/CNF events
- **Type Safety**: Guarantees correct operation for all supported data types

## State Transitions
1. **Wait State**: Block waits for REQ event

2. **Compute State**: On REQ event, block performs XOR operation

3. **Output State**: After computation, OUT is set and a CNF event is sent

4. **Return**: Block returns to wait state

## Application Scenarios
- **Bit Manipulation**: Reversing specific bits in data words
- **Parity Checking**: Creating parity bits for error detection
- **Data Encryption**: Simple cryptographic operations
- **Control Engineering**: Logical operations in automation systems
- **Data Comparison**: Detection of differences between data values

## ⚖️ Comparison with similar blocks
Compared to other logical blocks, XOR_2 offers:

- **Flexibility**: Support for various bit lengths through the ANY_BIT type
- **Specific Logic**: Exclusive OR operation as opposed to AND/OR operations
- **Generic Implementation**: Reusability across different data types

## Conclusion
The XOR_2 function block provides an efficient and flexible solution for bitwise XOR operations in 4diac systems. Its generic nature allows for use in a wide range of applications, while its event-driven architecture ensures reliable integration into complex control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
