# AX_XOR_5

<img width="1009" height="366" alt="image" src="https://github.com/user-attachments/assets/cb5ecc68-f421-4466-a82b-f877edbb13f0" />
* * * * * * * * * *
## Introduction

The AX_XOR_5 is a generic function block for calculating the Boolean XOR operation with five inputs. The block implements the exclusive OR operation for up to five input signals and outputs the result via an adapter output.
![AX_XOR_5](AX_XOR_5.svg)

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No direct data inputs available.

### **Data Outputs**

No direct data outputs available.

### **Adapters**

**Input Adapters:**

- **IN1**: XOR Input 1 (unidirectional AX adapter)
- **IN2**: XOR Input 2 (unidirectional AX adapter)
- **IN3**: XOR Input 3 (unidirectional AX adapter)
- **IN4**: XOR Input 4 (unidirectional AX adapter)
- **IN5**: XOR Input 5 (unidirectional AX adapter)

**Output Adapters:**

- **OUT**: XOR Result (unidirectional AX adapter)

## Functionality

This function block calculates the XOR operation across all five inputs. The XOR operation (exclusive OR) returns a "true" signal if and only if an odd number of inputs are active. With an even number of active inputs, it returns "false".

The mathematical formula is:

OUT = IN1 XOR IN2 XOR IN3 XOR IN4 XOR IN5
## Technical Features

- Uses unidirectional AX adapters for all interfaces
- Implemented as a generic function block named 'GEN_AX_XOR'
- Supports up to five independent input signals
- No event control - operates continuously based on the adapter inputs

## State Overview

Since it is a combinational logic block without memory, the AX_XOR_5 has no internal states. The output is determined solely by the current input values.

## Application Scenarios

- Parity checking in digital circuits
- Fault detection in safety systems
- Control logic with multiple conditions
- Distributed decision-making in automation systems
- Safety-critical applications with redundant sensors

## ⚖️ Comparison with Similar Blocks

Compared to standard XOR blocks with fewer inputs, the AX_XOR_5 offers the ability to process up to five signals simultaneously. While simple XOR blocks typically have only two inputs, this function block enables more complex logical operations without additional nesting.

Comparison with [XOR_5](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_5.md)]

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The AX_XOR_5 function block provides a flexible solution for multi-input XOR operations. Its adapter-based interface allows for easy integration into existing control systems, while its generic implementation ensures reusability and extensibility.