# OR_2
![OR_2](https://user-images.githubusercontent.com/116869307/214144026-378fb776-128a-41b0-ad4c-4d23d70d12d0.png)
A common use case is a soft AI and an AUX button.
TRUE dominates, so as soon as an input is TRUE, the output is set to TRUE.
![](https://user-images.githubusercontent.com/113907580/227976949-e73303db-993f-431e-b679-477dd9ad877e.png)

* * * * * * * * * *

## Introduction
The OR_2 function block is a generic function block for calculating bitwise Boolean OR operations. It performs a logical OR operation on two input values and outputs the result. The function block is classified according to the IEC 61131-3 standard and supports generic data types for maximum flexibility.

![OR_2](OR_2.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the OR operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1**: OR input 1 (Type: ANY_BIT) - first operand for the OR operation
- **IN2**: OR input 2 (Type: ANY_BIT) - second operand for the OR operation

### **Data Outputs**
- **OUT**: OR result (Type: ANY_BIT) - result of the bitwise OR operation

### **Adapters**
This function block does not use adapters.

## Functionality

Upon arrival of the REQ event, the OR_2 block performs a bitwise OR operation between the two input values IN1 and IN2. The result is output at the OUT data output, and simultaneously, the CNF event is generated to confirm successful calculation.

The OR operation is performed at the bit level, with each bit of the input values being processed separately. The result bit is 1 if at least one of the corresponding input bits is 1.

## Technical Features
- **Generic Type Support**: Uses the ANY_BIT data type, meaning the block can work with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)
- **Standard-Compliant Implementation**: Conforms to the IEC 61131-3 standard for bitwise Boolean functions
- **Event-Driven Execution**: The calculation is only performed when a REQ event is active

## State Transitions
1. **Wait State**: Block waits for a REQ event

2. **Calculation State**: Upon a REQ event, IN1 and IN2 are processed

3. **Output State**: Result is output to OUT and a CNF event is generated

4. **Return**: Block returns to the wait state

## Application Scenarios
- Bitwise mask operations in control applications
- Combining status flags in process control systems
- Logical operations in digital circuits
- Data manipulation in Communication Protocols

## ⚖️ Comparison with Similar Building Blocks
Compared to other Boolean operations like AND or XOR, OR_2 offers the specific property that the result is true if at least one of the operands is true. Unlike simple Boolean OR blocks, OR_2 supports generic bit data types, thus enabling the processing of various data widths.

## 🛠️ Related exercises
* [Uebung_002a3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a3.md)
* [Uebung_002a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a3_AX.md)
* [Uebung_002b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)
* [Uebung_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Uebung_035a](../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a.md)
* [Uebung_035a2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a2.md)
* [Uebung_035a2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a2_AX.md)
* [Uebung_035a3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_035a3.md)
* [Exercise_035a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a3_AX.md)
* [Exercise_039_sub_Outputs](../../../../Uebungen/test_B/Uebungen_doc/Uebung_039_sub_Outputs.md)
* [Exercise_089](../../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)
* [Exercise_160_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160_AX.md)
* [Exercise_160b2_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)
* [Exercise_160b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b_AX.md)

## Conclusion
The OR_2 function block provides a flexible and standards-compliant solution for bitwise OR operations in automation systems. Its generic nature allows for use in various application contexts with different data types, while the event-driven architecture ensures efficient resource utilization.
