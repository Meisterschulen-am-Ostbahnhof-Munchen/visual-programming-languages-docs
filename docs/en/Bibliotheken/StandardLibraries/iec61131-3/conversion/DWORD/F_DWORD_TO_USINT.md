# F_DWORD_TO_USINT

<img width="1255" height="182" alt="F_DWORD_TO_USINT" src="https://github.com/user-attachments/assets/4cdaf96f-2ab8-4655-8fed-b81775155fae" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_USINT` converts a 32-bit value (DWORD) to an 8-bit unsigned integer (USINT). This conversion is particularly useful when data needs to be exchanged between systems with different word lengths.

![F_DWORD_TO_USINT](F_DWORD_TO_USINT.svg)

## Interface Structure
### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN** (DWORD): The 32-bit value to be converted to an 8-bit unsigned integer.

### **Data Outputs**

- **OUT** (USINT): The resulting 8-bit unsigned integer after conversion.

### **Adapters**
This function block does not have any adapter interfaces.

## Operation
The function block performs the conversion by transforming the 32-bit value at input `IN` into an 8-bit unsigned integer. The conversion is performed by the function `DWORD_TO_USINT`, which converts the value accordingly. During the conversion, only the least significant byte of the DWORD value is considered, while the higher-order bytes are ignored.

## Technical Features
- The conversion truncates the higher-order bytes, which can lead to data loss if the original DWORD value is greater than 255.

- The function block is deterministic and performs the conversion in a single execution step.

## State Overview

The function block has no internal state. The conversion is performed anew each time the `REQ` event is triggered.

## Application Scenarios
- Data reduction in communication protocols where only 8-bit values can be transmitted.

- Adapting data formats between different system components.

- Use in controllers where specific hardware can only process 8-bit data.


## ⚖️ Comparison with Similar Function Blocks

- **F_WORD_TO_USINT**: Converts a 16-bit value (WORD) to an 8-bit unsigned integer. In contrast, `F_DWORD_TO_USINT` processes 32-bit values.

- **F_DWORD_TO_BYTE**: Similar in functionality, but the output type is BYTE, which is also 8 bits, but unsigned.

## Conclusion
The function block `F_DWORD_TO_USINT` is a simple and efficient tool for converting 32-bit values to 8-bit unsigned integers. It is particularly suitable for applications where data needs to be reduced to a smaller word width. However, due to the potential for data loss with large input values, its use should be carefully planned.