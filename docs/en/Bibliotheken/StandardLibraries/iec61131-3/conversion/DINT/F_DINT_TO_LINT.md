# F_DINT_TO_LINT
<img width="1434" height="212" alt="F_DINT_TO_LINT" src="https://github.com/user-attachments/assets/cf39f6ad-2d08-456e-ae6b-1a02e87a6f50" />
* * * * * * * * * *
## Introduction
The function block `F_DINT_TO_LINT` converts a 32-bit integer value (DINT) to a 64-bit integer value (LINT). This block is particularly useful in scenarios where extending the value range or changing the type is required for subsequent processing steps.
![F_DINT_TO_LINT](F_DINT_TO_LINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals successful completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (DINT): The 32-bit integer value to be converted.

### **Data Outputs**
- **OUT** (LINT): The resulting 64-bit integer value after conversion.

#### **Adapters**
This function block does not use any adapters.

## Operation
When the `REQ` event is triggered, the value of the `IN` input is copied to the `OUT` output. An automatic type conversion from DINT to LINT occurs, preserving the numeric value.

#
## Technical Features
- The conversion is performed without data loss, as the LINT type supports a larger range of values than DINT.
- The algorithm is implemented in Structured Text (ST) and consists of a simple assignment.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Extending the value range for subsequent calculations
- Type adaptation in heterogeneous systems
- Data preparation for interfaces with varying requirements

## ⚖️ Comparison with Similar Function Blocks
Compared to generic conversion blocks, `F_DINT_TO_LINT` offers a specialized and type-safe solution for the specific conversion between DINT and LINT. Other blocks might offer more general conversion options, but may be less efficient or require additional configuration.

## Conclusion

The `F_DINT_TO_LINT` function block provides a simple and efficient solution for converting 32-bit to 64-bit integers. Its clear interface and direct functionality make it a reliable component in control systems where such type conversions are required.
