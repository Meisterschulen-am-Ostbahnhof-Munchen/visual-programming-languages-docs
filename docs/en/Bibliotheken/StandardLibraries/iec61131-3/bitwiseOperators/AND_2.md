# AND_2

![AND_2](https://user-images.githubusercontent.com/116869307/214143461-f2104d1b-a147-4a9f-a118-f527fc245b5f.png)

OUT is only switched when a Boolean signal is present at IN1 and IN2, e.g., from a switch.

![](https://user-images.githubusercontent.com/113907580/227966597-94049ae9-429e-49d8-93ca-b46b31b27550.png)

The same principle applies to all other "AND" blocks, except that all IN inputs must always be True.

* * * * * * * * * *

## Introduction
The AND_2 function block is a generic block for calculating the bitwise Boolean AND operation. It implements a standard function according to IEC 61131-3 and can be used with any bit data type.


![AND_2](AND_2.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request - triggers the calculation of the AND operation

### **Event Outputs**
- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1** (ANY_BIT): AND input 1 - first operand for the bitwise AND operation
- **IN2** (ANY_BIT): AND input 2 - second operand for the bitwise AND operation

### **Data Outputs**
- **OUT** (ANY_BIT): AND result - result of the bitwise AND operation

### **Adapters**
No adapter interfaces are available.


## Functionality

Upon arrival of the REQ event, the function block performs a bitwise AND operation between the two input values IN1 and IN2. The result is output at the data output OUT, and simultaneously, the CNF event is generated to confirm execution.


``` The operation is performed separately for each bit of the input values:

- Bit = 1 if both corresponding bits of the inputs are 1

- Bit = 0 if at least one of the corresponding bits of the inputs is 0

## Technical Features
- **Generic Data Type**: Uses ANY_BIT, which allows its use with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD)
- **Bitwise Operation**: Performs the AND operation at the bit level
- **Event-Driven**: Execution is driven by events, not by cycle times

## State Transitions
1. **Wait State**: Block waits for REQ event

2. **Compute State**: Upon REQ event, IN1 and IN2 are processed

3. **Output State**: Result is output to OUT and a CNF event is generated

4. Returns to Wait State

## Application Scenarios

- Bitmask operations in control applications
- Filtering of data by masking unwanted bits

- Logical operations in digital circuits
- Data preprocessing in communication protocols

## ⚖️ Comparison with similar building blocks
Compared to other logical operation blocks:

- AND_2 is generic and supports various bit data types

- Operates bitwise, unlike purely Boolean AND blocks

- Event-driven, unlike cycle-driven blocks

## 🛠️ Related exercises

* [Exercise_002a](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002a.md)
* [Exercise_002a_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a_AX.md)
* [Exercise_002b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_002b2.md)
* [Exercise_002b3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002b3_AX.md)
* [Exercise_006a3_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_006a3_AX.md)

* [Exercise_088](../../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)

## Conclusion
The AND_2 function block offers a flexible and standards-compliant solution for bitwise AND operations in IEC 61131-3 based control systems. Its generic nature allows for use in a wide range of applications, while its event-driven architecture ensures efficient resource utilization.