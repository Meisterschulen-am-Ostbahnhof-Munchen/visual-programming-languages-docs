# F_REAL_TO_UINT
<img width="1440" height="213" alt="F_REAL_TO_UINT" src="https://github.com/user-attachments/assets/c70dcb74-21d4-4caa-8404-2518a95ca3b4" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_UINT` converts a REAL value (floating-point number) to a UINT value (unsigned integer). This conversion is particularly useful when exchanging data between systems that use different data types or when an explicit type conversion is required.
![F_REAL_TO_UINT](F_REAL_TO_UINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this event input is triggered, the algorithm for converting the REAL value to a UINT value is executed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This event is triggered as soon as the algorithm has been successfully executed.

#
## ### **Data Inputs**
- **IN**: The REAL input value to be converted to a UINT value.

### **Data Outputs**
- **OUT**: The UINT output value representing the result of the conversion.

### **Adapters**
This function block has no adapter interfaces.

## Functionality
When the `F_REAL_TO_UINT` event is triggered, the function block `F_REAL_TO_UINT` converts the REAL value at input `IN` to a UINT value. The result is output at `OUT`, and the `CNF` event signals the successful completion of the operation.

The underlying algorithm is:

```ST
ALGORITHM REQ
OUT := REAL_TO_UINT(IN);
END_ALGORITHM
## Technical Features
- The conversion is performed using the standard function `REAL_TO_UINT`, which rounds the REAL value to the nearest UINT value.
- Note that undefined behavior may occur with values outside the representable range of UINT (0 to 65535).

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Type conversion in control applications where floating-point values need to be converted to integers.
- Data preparation for systems that can only process unsigned integers.
- Interfaces between different system components with different data types.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks like `F_REAL_TO_INT` or `F_REAL_TO_UDINT`, this function block specializes in converting to unsigned 16-bit integers (UINT).
- Similar blocks might offer additional parameters such as rounding modes or range checks, which is not the case here.

## Conclusion
The `F_REAL_TO_UINT` function block provides a simple and efficient way to convert floating-point numbers to unsigned integers. Its clear interface structure and direct functionality make it ideal for applications requiring fast and straightforward type conversion. However, when using it, care must be taken to ensure the valid range of values is observed to avoid unexpected behavior.
