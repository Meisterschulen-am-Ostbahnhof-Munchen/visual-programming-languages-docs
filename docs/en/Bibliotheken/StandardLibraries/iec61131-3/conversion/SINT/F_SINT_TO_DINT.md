# F_SINT_TO_DINT
<img width="1439" height="213" alt="F_SINT_TO_DINT" src="https://github.com/user-attachments/assets/82945116-960d-4bc1-bc3c-40a845897785" />
* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_DINT` converts a `SINT` value (8-bit signed count) to a `DINT` value (32-bit signed count). This block is particularly useful in scenarios where type conversion is required to prepare data for further processing.
![F_SINT_TO_DINT](F_SINT_TO_DINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `SINT` to be converted.

### **Data Outputs**
- **OUT**: The converted output value of type `DINT`.

### **Adapters**
This function block has no adapters.

## Operation
When the event input `REQ` is triggered, the value at the data input `IN` is read and converted to type `DINT`. The result is output at data output `OUT`, and the event `CNF` signals the successful completion of the conversion.

## Technical Features
- The conversion is performed directly by assignment (`OUT := IN`), as `SINT` is automatically converted to `DINT`.
- The function block is simple and efficient because it does not perform any complex calculations.

## State Overview
1. **Idle State**: Waits for the event `REQ`.

2. **Conversion State**: Upon receiving `REQ`, the conversion is performed, and `CNF` is triggered.

## Application Scenarios
- Type conversion in control applications where `SINT` data needs to be converted to `DINT`.
- Preparing data for further processing steps that require `DINT`.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_INT_TO_DINT` or `F_USINT_TO_UDINT` perform similar conversions, but with different output and input types, respectively.
- `F_SINT_TO_DINT` is specifically for converting `SINT` to `DINT`.

## Conclusion

The `F_SINT_TO_DINT` function block is a simple and efficient building block for type conversion from `SINT` to `DINT`. Its clear interface structure and simple functionality make it a reliable component in control applications.