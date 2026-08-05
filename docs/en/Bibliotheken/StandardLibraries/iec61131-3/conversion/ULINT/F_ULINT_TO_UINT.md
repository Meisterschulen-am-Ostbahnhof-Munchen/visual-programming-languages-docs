# F_ULINT_TO_UINT
<img width="1453" height="214" alt="F_ULINT_TO_UINT" src="https://github.com/user-attachments/assets/398715a7-1e03-490c-83c0-41f0f4d745ed" />
* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_UINT` converts a 64-bit unsigned integer value (ULINT) to a 16-bit unsigned integer value (UINT). This block is part of the `iec61131::conversion` package and implements a simple type conversion.
![F_ULINT_TO_UINT](F_ULINT_TO_UINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion process. This input is connected to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.

### **Data Inputs**
- **IN**: ULINT (64-bit unsigned integer) - The input value to be converted.

### **Data Outputs**
- **OUT**: UINT (16-bit unsigned integer) - The result of the conversion.

#### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion from ULINT to UINT when the `REQ` event occurs. The conversion is carried out using the function `ULINT_TO_UINT`. After the conversion is complete, the `CNF` event is triggered.

### **Adapters**

#
## Technical Features
- The function block performs a direct type conversion, truncating the higher-order bits of the ULINT value if the value is outside the UINT range.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Type conversion in control applications where ULINT values need to be reduced to UINT.
- Data processing in embedded systems with limited memory capacity.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion function blocks, `F_ULINT_TO_UINT` is specialized and optimized for the specific conversion of ULINT to UINT.

Other function blocks might offer additional functionalities such as range checks or scaling, which is not the case here.

## Conclusion
The `F_ULINT_TO_UINT` function block is a simple and efficient building block for converting 64-bit unsigned integer values to 16-bit unsigned integer values. It is particularly useful in applications where direct and fast type conversion is required.
