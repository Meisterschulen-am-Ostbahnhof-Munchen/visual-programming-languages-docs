# F_BYTE_BCD_TO_USINT
<img width="1290" height="182" alt="F_BYTE_BCD_TO_USINT" src="https://github.com/user-attachments/assets/1877ce9e-1601-4cea-921e-6a7288e635b6" />
* * * * * * * * * *
## Introduction
The function block `F_BYTE_BCD_TO_USINT` converts a BCD-encoded BYTE value to a USINT value. BCD (Binary Coded Decimal) is an encoding in which each digit of a decimal number is represented by 4 bits. This function block is particularly useful in applications that need to process BCD-encoded data.
![F_BYTE_BCD_TO_USINT](F_BYTE_BCD_TO_USINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the algorithm for converting the BCD-encoded BYTE value to a USINT value is executed.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is activated once the conversion is complete.

### **Data Inputs**
- **IN**: The BCD-encoded BYTE value to be converted to a USINT value.

### **Data Outputs**
- **OUT**: The resulting USINT value after the conversion.

### **Adapters**
- This function block has no adapters.

## Functionality
The function block performs the conversion of a BCD-encoded BYTE value to a USINT value as soon as the event `REQ` is triggered. The conversion is performed using the built-in function `BYTE_BCD_TO_USINT`. After successful conversion, the event `CNF` is triggered to signal the completion of the operation.

## Technical Features
- Conversion occurs directly and without any additional delay.
- The function block is optimized for processing BCD-encoded data.

## State Overview

1. **Idle State**: The function block waits for the `REQ` event.

2. **Conversion State**: Conversion is performed when `REQ` is triggered.

3. **Completion State**: After successful conversion, `CNF` is triggered, and the function block returns to the idle state.

## Application Scenarios
- Processing of BCD-encoded data in industrial control systems.
- Conversion of BCD-encoded sensor data into numerical values.
- Integration into control logic that needs to process BCD data.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic conversion function blocks, `F_BYTE_BCD_TO_USINT` specializes in converting BCD-encoded BYTE values to USINT values.
- Other function blocks might offer additional conversion options, but they may be less efficient for this specific use case.

## Conclusion
The `F_BYTE_BCD_TO_USINT` function block provides an efficient and specialized solution for converting BCD-encoded BYTE values to USINT values. Its simple and straightforward operation makes it ideal for applications requiring fast and reliable conversion.