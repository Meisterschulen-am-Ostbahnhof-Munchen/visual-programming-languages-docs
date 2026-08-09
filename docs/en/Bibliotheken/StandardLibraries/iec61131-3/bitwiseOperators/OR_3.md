# OR_3

![OR_3](https://user-images.githubusercontent.com/116869307/214144056-e850a789-92e3-46c0-ba3c-97960b404daa.png)

* * * * * * * * * *
## Introduction

The OR_3 function block is a generic function block for calculating bitwise Boolean OR operations with three inputs. It performs a logical OR operation at the bit level and supports various bit data types according to the IEC 61131-3 standard.
![OR_3](OR_3.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request - triggers the calculation of the OR operation

### **Event Outputs**

- **CNF**: Execution confirmation - signals the completion of the calculation

### **Data Inputs**

- **IN1**: OR input 1 (ANY_BIT data type)
- **IN2**: OR input 2 (ANY_BIT data type)
- **IN3**: OR input 3 (ANY_BIT data type)

### **Data Outputs**

- **OUT**: OR result (ANY_BIT data type)

### **Adapters**

No adapters available.

## Functionality

The OR_3 function block performs a bitwise OR operation on the three input values IN1, IN2, and IN3 upon each REQ event. The result is output at the OUT data output, and simultaneously a CNF event is generated to signal the completion of the operation.

The operation is performed separately for each bit position: OUT[i] = IN1[i] OR IN2[i] OR IN3[i]

## Technical Features

- Supports the generic ANY_BIT data type, enabling its use with various bit data types such as BOOL, BYTE, WORD, DWORD, etc.
- Implemented as a generic function block according to the IEC 61131-3 standard
- Belongs to the "iec61131::bitwiseOperators" package

## State Overview

1. **Wait State**: Block waits for a REQ event
2. **Calculation State**: Inputs are processed upon a REQ event
3. **Output State**: Result is output to OUT and a CNF event is generated

## Application Scenarios

- Combining multiple digital signals in control applications
- Mask operations in data processing
- Parallel processing of multiple conditions
- Signal linking in automation systems

## ⚖️ Comparison with similar building blocks

Compared to simple OR blocks with only two inputs, OR_3 offers the possibility of directly connecting three inputs, simplifying the program structure and avoiding additional chaining. Unlike arithmetic blocks, OR_3 operates exclusively at the bit level.

## 🛠️ Related Exercises

* [Exercise_002a5_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5_AX.md)]
* [Exercise_002a5b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5b_AX.md)]

## Conclusion

The OR_3 function block represents an efficient and flexible solution for bitwise OR operations with three inputs. Its generic nature allows its use in various application areas and with different bit data types, making it a versatile tool in automation technology.
