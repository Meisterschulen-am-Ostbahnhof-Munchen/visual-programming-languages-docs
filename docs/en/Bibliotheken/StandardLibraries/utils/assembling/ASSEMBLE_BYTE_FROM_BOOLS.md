# ASSEMBLE_BYTE_FROM_BOOLS
![ASSEMBLE_BYTE_FROM_BOOLS](https://github.com/user-attachments/assets/4a70532a-aa28-4489-a8b6-5cf357a41460)
* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_BYTE_FROM_BOOLS` combines eight Boolean input values into a single byte. Each Boolean input represents one bit of the resulting byte. This block is particularly useful when individual Boolean signals need to be combined into a compact byte value.
## Interface Structure
### **Event Inputs**
- `REQ`: Starts processing the Boolean inputs and generates the resulting byte.

#### **Event Outputs**
- `CNF`: Signals successful aggregation of the Boolean values into a single byte.

### **Data Inputs**
- `BIT_00` to `BIT_07`: Eight Boolean inputs, each corresponding to one bit of the resulting byte.

### **Data Outputs**
- `BYTE`: The composite byte generated from the eight Boolean inputs.

### **Adapters**
No adapters are included.

## Functionality
This function block combines the eight Boolean inputs (`BIT_00` to `BIT_07`) into a single byte. Each Boolean value is mapped to the corresponding bit of the byte:

- `BIT_00` corresponds to bit 0 (LSB)
- `BIT_01` corresponds to bit 1
- ...
- `BIT_07` corresponds to bit 7 (MSB)

When the event `REQ` is triggered, the current values of the Boolean inputs are read and combined into a byte. The result is output at the data output, and the event `CNF` signals successful processing.

## Technical Features
- The function block is implemented in ST (Structured Text).
- Bit mapping is performed directly by assigning the Boolean values to the corresponding bits of the byte.

## State Overview

1. **Idle State**: Waits for the `REQ` event.

2. **Processing State**: Reads the Boolean inputs and assembles the byte.

3. **Acknowledge State**: Outputs the resulting byte and signals `CNF`.

## Application Scenarios
- Summarizing 8 individual switch states into one byte for communication with other systems.
- Compressing Boolean status information for more efficient data transmission.
- Use in control systems where multiple Boolean signals need to be processed as a single byte.

## ⚖️ Comparison with Similar Function Blocks
- Compared to manual bit operations in ST or other languages, this function block offers a predefined and maintainable solution.

Similar function blocks might have fewer inputs or offer additional features like inverted logic, which is not the case here.

## 🛠️ Related Exercises
* [Exercise_035a1b_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_035a1b_AX.md)]
* [Exercise_053](../../../../Uebungen/test_B/Uebungen_doc/Uebung_053.md)]

## Conclusion
The `ASSEMBLE_BYTE_FROM_BOOLS` function block is a simple and efficient solution for combining eight Boolean values into one byte. Its clear interface and direct implementation make it ideal for applications that require compact processing of Boolean signals.