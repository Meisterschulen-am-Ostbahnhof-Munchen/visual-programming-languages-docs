# F_UDINT_TO_USINT
<img width="1470" height="216" alt="F_UDINT_TO_USINT" src="https://github.com/user-attachments/assets/1e0f089e-de96-4e75-91cb-739ff8cf6842" />
* * * * * * * * * *
## Introduction
The function block `F_UDINT_TO_USINT` converts a 32-bit unsigned integer value (UDINT) to an 8-bit unsigned integer value (USINT). This block is particularly useful in scenarios where type conversion between numerical values of different sizes is required.
![F_UDINT_TO_USINT](F_UDINT_TO_USINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: The input expects a 32-bit unsigned integer value (UDINT) to be converted.

### **Data Outputs**
- **OUT**: The output provides the converted 8-bit unsigned integer value (USINT).

#### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The algorithm converts the value of `IN` (UDINT) to the corresponding `OUT` (USINT) value. After successful conversion, the event `CNF` is triggered.

### **Adapters**

#
## Technical Features
- The conversion is performed by the built-in function `UDINT_TO_USINT`.
- No range check is performed. Values outside the USINT range (0 to 255) may produce unexpected results.

## State Overview

The function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios
- Type conversion in control applications where memory optimization is crucial.
- Communication between systems using different data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion blocks, `F_UDINT_TO_USINT` is specialized and therefore more efficient in execution.
- Other blocks might offer additional functionalities such as range checks, which is not the case here.

## Conclusion

The `F_UDINT_TO_USINT` function block is a simple and efficient building block for the specific conversion of UDINT to USINT values. It is particularly suitable for applications where fast and direct type conversion is required.
