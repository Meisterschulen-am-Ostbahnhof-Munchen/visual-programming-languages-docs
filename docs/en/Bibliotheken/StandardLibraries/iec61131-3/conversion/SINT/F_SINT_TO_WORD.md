# F_SINT_TO_WORD
<img width="1437" height="213" alt="F_SINT_TO_WORD" src="https://github.com/user-attachments/assets/91a7e9f0-a0c6-4151-a15e-61432acf0f37" />
* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_WORD` converts a SINT value (8-bit signed integer count) to a WORD value (16-bit unsigned integer count). This block is particularly useful in scenarios where type conversion between different integer formats is required.
![F_SINT_TO_WORD](F_SINT_TO_WORD.svg)
## Interface Structure

### **Event Inputs**
- `REQ` (Normal Execution Request): Starts the execution of the conversion. It is associated with the input value `IN`.

### **Event Outputs**
- `CNF` (Execution Confirmation): Signals the completion of the conversion. Returns the converted value via `OUT`.

### **Data Inputs**
- `IN` (SINT): The input value to be converted from SINT to WORD.

### **Data Outputs**
- `OUT` (WORD): The converted WORD value.

### **Adapters**
This function block does not use adapters.

## Operation
When the `REQ` event is triggered, the algorithm that converts the `IN` value from SINT to WORD is executed. The result is output via `OUT`, and the `CNF` event signals successful conversion.

## Technical Features
- The conversion is performed directly by the function `SINT_TO_WORD(IN)`.
- No additional error handling is required for overflow or underflow, as SINT (8-bit) is converted to WORD (16-bit), and therefore no values are lost.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering `REQ`.

## Application Scenarios
- Type conversion in control applications where different integer formats need to be processed.
- Data preprocessing for communication protocols or sensor data.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks like `F_INT_TO_WORD` or `F_DINT_TO_WORD` offer conversions from other integer types to WORD.
- `F_SINT_TO_WORD` is specifically optimized for converting 8-bit signed integers to 16-bit unsigned integers.

## Conclusion
The `F_SINT_TO_WORD` function block is a simple and efficient building block for type conversion from SINT to WORD. Its clear interface and direct functionality make it ideal for applications requiring fast and reliable conversion.