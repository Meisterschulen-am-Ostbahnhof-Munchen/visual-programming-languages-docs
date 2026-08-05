# ASSEMBLE_LWORD_FROM_BOOLS
![ASSEMBLE_LWORD_FROM_BOOLS](https://github.com/user-attachments/assets/9df93a68-feb4-4868-8fbd-9aecbaab21a2)
* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_LWORD_FROM_BOOLS` combines 64 individual BOOL values into a single LWORD data type. This is particularly useful when multiple binary states need to be processed or transmitted in a compact form.
## Interface Structure
### **Event Inputs**
- `REQ`: Starts combining the 64 BOOL inputs into an LWORD.

### **Event Outputs**
- `CNF`: Signals the successful combination of the BOOL values into an LWORD.

### **Data Inputs**

64 BOOL inputs (`BIT_00` to `BIT_63`), each representing one bit in the resulting LWORD.

### **Data Outputs**
- One LWORD composed of the 64 BOOL inputs.

### **Adapters**
No adapters included.

## Operation
The function block assigns each of the 64 bits of the LWORD output to a corresponding BOOL input. Upon triggering the `REQ` event, all BOOL inputs are read and inserted into the LWORD. The `CNF` event signals the completion of this process.

## Technical Features
- Processes 64 BOOL inputs in parallel.
- Direct bit mapping without additional calculations.
- Efficient implementation through direct bit assignment.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Combines the BOOL values into an LWORD.

3. **Complete**: Sends the `CNF` event and outputs the combined LWORD.

## Application Scenarios
- Compressing multiple binary signals for transmission.
- Processing bitmasks in control applications.
- Efficient storage of binary states.

## ⚖️ Comparison with Similar Function Blocks
- Similar to `BOOL_TO_*` function blocks, but optimized for 64 bits.
- Offers more flexibility than hard-coded bit operations.

## Conclusion

The `ASSEMBLE_LWORD_FROM_BOOLS` function block is an efficient tool for combining multiple BOOL values into a single LWORD data type, ideal for applications with high bit density.