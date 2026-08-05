# AX_OR_8

<img width="960" height="469" alt="image" src="https://github.com/user-attachments/assets/a5f20ed5-b8ed-4f26-9696-860bc64cfb6f" />

* * * * * * * * * *
## Introduction
The AX_OR_8 function block is a generic function block for calculating an eight-input logical OR operation. It is used to process Boolean signals in control applications and allows the combination of multiple input signals into a single output signal.


![AX_OR_8](AX_OR_8.svg)

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
**Input Adapters:**
- **IN1** - OR input 1 (unidirectional AX adapter)
- **IN2** - OR input 2 (unidirectional AX adapter)
- **IN3** - OR input 3 (unidirectional AX adapter)
- **IN4** - OR input 4 (unidirectional AX adapter)
- **IN5** - OR input 5 (unidirectional AX adapter)
- **IN6** - OR input 6 (unidirectional AX adapter) AX Adapter

- **IN7** - OR input 7 (unidirectional AX adapter)

- **IN8** - OR input 8 (unidirectional AX adapter)

**Output Adapter:**

- **OUT** - OR result (unidirectional AX adapter)

## Functionality
The AX_OR_8 block performs a logical OR operation on all eight inputs. The output signal is set to TRUE if at least one of the eight inputs is TRUE. Only if all inputs are FALSE will the output also be FALSE.


The functionality corresponds to the Boolean equation:

OUT = IN1 ∨ IN2 ∨ IN3 ∨ IN4 ∨ IN5 ∨ IN6 ∨ IN7 ∨ IN8

## Technical Features
- Generic function block with the class name identifier 'GEN_AX_OR'
- Uses unidirectional AX adapters for all interfaces

- No internal states or memory functions
- Immediate processing without delay
- Part of the "adapter::booleanOperators" package

## State Overview
The function block is stateless and performs the OR operation immediately upon any change to the inputs. No internal states are stored.


## Application Scenarios

- Safety circuits with multiple emergency stop buttons
- Monitoring systems with multiple sensors
- Control logic with parallel conditions
- Alarm systems with multiple triggers
- Linking multiple enable signals

## ⚖️ Comparison with similar function blocks

Compared to simple OR function blocks with fewer inputs, AX_OR_8 offers the ability to directly link up to eight signals without additional chaining of multiple function blocks. The use of adapters instead of direct data connections enables more flexible integration into various system architectures.

Comparison with [OR_8](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_8.md)]

## Conclusion
The AX_OR_8 function block represents an efficient solution for complex OR logic operations with up to eight inputs. Due to the use of standard adapters and its generic implementation, it is particularly suitable for reusable control logic in industrial automation applications.