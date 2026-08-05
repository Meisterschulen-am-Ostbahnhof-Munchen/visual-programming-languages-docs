# AX_OR_3
<img width="963" height="297" alt="image" src="https://github.com/user-attachments/assets/3f0679d7-bd35-40d5-92eb-f7f1122507de" />
* * * * * * * * * *
## Introduction
The AX_OR_3 function block is a generic function block for calculating the logical OR operation with three inputs. It is used to process Boolean signals in control applications and allows the flexible combination of multiple input signals into a single output signal.
![AX_OR_3](AX_OR_3.svg)
## Interface Structure
### **Event Inputs**
No event inputs available.

### **Event Outputs**
No event outputs available.

### **Data Inputs**
No direct data inputs available.

### **Data Outputs**
No direct data outputs available.

### **Adapter**
**Input Adapter:**

- **IN1**: OR Input 1 (Type: adapter::types::unidirectional::AX)
- **IN2**: OR Input 2 (Type: adapter::types::unidirectional::AX)
- **IN3**: OR Input 3 (Type: adapter::types::unidirectional::AX)

**Output Adapter:**

- **OUT**: OR Result (Type: adapter::types::unidirectional::AX)

## Functionality
The function block continuously calculates the logical OR operation of the three input signals. The output signal is true (TRUE) if at least one of the three inputs is true. Only if all three inputs are false (FALSE) will the output also be false.

The logical function can be represented as follows:

OUT = IN1 OR IN2 OR IN3

## Technical Features
- Uses unidirectional adapters for signal transmission
- Implemented as a generic function block with the class 'GEN_AX_OR'
- Operates without event control, computs continuously
- Optimized for use in adapter-based architectures

## State Overview
Since it is a combinational function block without a memory function, AX_OR_3 has no internal states. The output is determined solely by the current input values.

## Application Scenarios
- Safety circuits with multiple emergency stop buttons
- Monitoring systems with multiple sensors
- Control logic with alternative activation conditions
- Linking status messages from various sources

## ⚖️ Comparison with Similar Function Blocks
Compared to standard OR blocks, AX_OR_3 offers the advantage of three inputs in a single block, which simplifies wiring. Compared to function blocks with a variable number of inputs, AX_OR_3 is specifically optimized for triple OR operation.

Comparison with [OR_3](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_3.md)]

## 🛠️ Related Exercises
* [Exercise_002a5_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5_AX.md)]
* [Exercise_002a5b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_002a5b_AX.md)]

## Conclusion
The AX_OR_3 function block provides an efficient solution for three-input OR logic operations. Its adapter-based interface allows for flexible integration into various control architectures and makes it particularly suitable for applications where multiple conditions can be met alternatively.