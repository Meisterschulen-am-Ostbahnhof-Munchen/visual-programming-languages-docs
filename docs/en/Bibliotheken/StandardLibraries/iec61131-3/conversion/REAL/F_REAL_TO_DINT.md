# F_REAL_TO_DINT
<img width="1235" height="175" alt="F_REAL_TO_DINT" src="https://github.com/user-attachments/assets/fd78a595-bfca-47f7-b4d9-acd46bf10b52" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_DINT` converts a REAL value (floating-point number) into a DINT value (32-bit integer). This conversion is performed by rounding the REAL value down to the nearest integer.
![F_REAL_TO_DINT](F_REAL_TO_DINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**
- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**
- **IN**: Input for the REAL value to be converted.

#
## ### **Data Outputs**
- **OUT**: Output for the converted DINT value.

## **Adapters**
No adapters available.

## Functionality
When the `REQ` event is triggered, the algorithm that converts the `IN` value from REAL to DINT is executed. The result is output at `OUT`, and the `CNF` event is triggered.

## Technical Features
- The conversion is performed by rounding down the REAL value.
- The function block is simple and has no internal states.

## State Overview
No states are present, as the block is stateless.

## Application Scenarios
- Conversion of sensor values (floating-point) to integer values for control logic.
- Data processing in control systems where integer values are required.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks might offer other conversion methods, e.g., rounding or rounding up.
- Compared to generic conversion blocks, this one specializes in REAL-to-DINT conversion.

## Conclusion
The `F_REAL_TO_DINT` function block is a simple and efficient building block for converting floating-point numbers to integers. It is particularly useful in scenarios where fast and direct conversion is required.
