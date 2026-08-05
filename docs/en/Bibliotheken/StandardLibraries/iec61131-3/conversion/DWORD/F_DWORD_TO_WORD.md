# F_DWORD_TO_WORD

<img width="1244" height="182" alt="F_DWORD_TO_WORD" src="https://github.com/user-attachments/assets/eeb53dda-9cf9-4235-91ac-ad7b17de8da7" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_WORD` converts a 32-bit DWORD value to a 16-bit WORD value. This conversion is useful when data needs to be exchanged between systems with different word lengths or when memory space needs to be optimized.

![F_DWORD_TO_WORD](F_DWORD_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (DWORD): The 32-bit input value to be converted.

### **Data Outputs**

- **OUT** (WORD): The converted 16-bit output value.

#### **Adapters**
This function block does not use adapters.

## Operation
When the `REQ` event is triggered, the algorithm is executed that converts the DWORD value at the input `IN` to a WORD value and outputs the result to `OUT`. The `CNF` event is then triggered to signal the completion of the conversion.

## Technical Features
- The conversion is performed by truncating the 16 most significant bits of the DWORD value.

- No check is performed to prevent potential data loss during this conversion.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Communication between systems with different word widths
- Memory optimization in embedded systems
- Data preprocessing in control systems

## ⚖️ Comparison with Similar Function Blocks
- Unlike `F_DWORD_TO_BYTE`, this function block converts to a WORD value instead of a BYTE.

- Similar to `F_WORD_TO_BYTE`, but with different data types.


## Conclusion

The `F_DWORD_TO_WORD` function block offers a simple and efficient way to convert DWORD values to WORD values. It is particularly useful in systems that need to handle different word widths. However, be aware of the potential for data loss during the conversion.