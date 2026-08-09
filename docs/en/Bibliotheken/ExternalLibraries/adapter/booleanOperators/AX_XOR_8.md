# AX_XOR_8

<img width="1009" height="465" alt="image" src="https://github.com/user-attachments/assets/360232e2-8dcb-496e-84cf-311179b598af" />
* * * * * * * * * *
## Introduction

The AX_XOR_8 function block is a generic block for calculating Boolean XOR operations with 8 inputs. It enables the processing of logic signals according to the exclusive-OR principle and is designed for use in control applications.
![AX_XOR_8](AX_XOR_8.svg)

## Interface Structure

### **Event Inputs**

No event inputs available

### **Event Outputs**

No event outputs available

### **Data Inputs**

No direct data inputs available

### **Data Outputs**

No direct data outputs available

### **Adapters**

**Plug Adapter:**

- **OUT**: Unidirectional adapter for the XOR result

**Socket Adapter:**

- **IN1**: Unidirectional adapter for XOR input 1
- **IN2**: Unidirectional adapter for XOR input 2
- **IN3**: Unidirectional adapter for XOR input 3
- **IN4**: Unidirectional adapter for XOR input 4
- **IN5**: Unidirectional adapter for XOR input 5
- **IN6**: Unidirectional adapter for XOR input 6
- **IN7**: Unidirectional adapter for XOR input 7
- **IN8**: Unidirectional adapter for XOR input 8

## Functionality

This function block calculates the XOR operation across all 8 inputs. The XOR operation (exclusive OR) returns a TRUE signal if and only if an odd number of inputs are TRUE. If an even number of inputs are TRUE, FALSE is output.

## Technical Features

- Generic function block with the class 'GEN_AX_XOR'
- Uses unidirectional adapters for all inputs and outputs
- No direct event or data interfaces
- Adapter-based architecture for flexible connectivity

## State Overview

Since it is a combinational logic block, AX_XOR_8 has no internal state. The output is determined solely by the current input values.

## Application Scenarios

- Parity checking in data transmission systems
- Safety-critical controllers with multiple redundancy
- Logical operations in automation systems
- Error detection in binary signal chains

## ⚖️ Comparison with similar components

Compared to simple XOR components with fewer inputs, AX_XOR_8 offers the ability to combine up to 8 signals simultaneously. The exclusive use of adapters instead of direct data and event inputs enables greater flexibility in complex system architectures.

Comparison with [XOR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_8.md)]

## Conclusion

The AX_XOR_8 is a specialized logic component for demanding multi-input XOR operations. Its adapter-based interface makes it particularly suitable for modular system designs where flexible connections between functional blocks are required.
