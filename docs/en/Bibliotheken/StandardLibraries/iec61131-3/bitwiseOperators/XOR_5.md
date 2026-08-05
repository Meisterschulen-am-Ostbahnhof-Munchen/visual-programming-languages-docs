# XOR_5
![XOR_5](https://user-images.githubusercontent.com/116869307/214144268-b188a2d3-cbc1-48b6-a90d-300b875efdc0.png)
* * * * * * * * * *
## Introduction
The XOR_5 function block is a generic function block for calculating the bitwise Boolean XOR operation with five inputs. It implements the exclusive OR operation for arbitrary bit data types according to the IEC 61131-3 standard.
![XOR_5](XOR_5.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Normal Execution Request - triggers the calculation of the XOR operation

### **Event Outputs**
- **CNF**: Execution Confirmation - signals the completion of the calculation

### **Data Inputs**
- **IN1**: XOR Input 1 (ANY_BIT data type)
- **IN2**: XOR Input 2 (ANY_BIT data type)
- **IN3**: XOR Input 3 (ANY_BIT data type)
- **IN4**: XOR Input 4 (ANY_BIT data type)
- **IN5**: XOR Input 5 (ANY_BIT data type)

### **Data Outputs**
- **OUT**: XOR Result (ANY_BIT data type)

### **Adapters**
No adapter interfaces are available.

## Functionality
Upon arrival of the REQ event, the function block performs a bitwise XOR operation on all five input values. The result is output to the OUT output, and simultaneously, the CNF event is generated to confirm the completion of the calculation.

``` The XOR operation is performed according to the following principle:

- Each bit position is processed individually.
- The result bit is 1 if an odd number of input bits at that position are 1.
- The result bit is 0 if an even number of input bits at that position are 1.

## Technical Features
- Uses the generic ANY_BIT data type, which is compatible with various bit data types (BOOL, BYTE, WORD, DWORD, LWORD).
- Supports the processing of five input values.
- Implemented as a generic function block according to the IEC 61131-3 standard.
- Package mapping: iec61131::bitwiseOperators

## State Overview
The function block has a simple state machine:

1. **Wait State**: Waiting for a REQ event.

2. **Compute State**: Processing the XOR operation.

3. **Output State**: Setting the OUT value and triggering the CNF Event

## Application Scenarios
- Bitwise data processing in control systems
- Parity checks and error detection
- Cryptographic operations
- Data manipulation and transformation
- Signal processing with multiple input signals

## ⚖️ Comparison with similar components
Compared to standard XOR components with fewer inputs, XOR_5 offers:

- Extended functionality with five inputs instead of two
- Greater flexibility for more complex logical operations
- Reduced chaining depth compared to serial XOR operations

## Conclusion
The XOR_5 function block provides a powerful and flexible solution for bitwise XOR operations with five inputs. Its generic implementation allows its use with various bit data types, making it a versatile tool for diverse applications in automation technology.