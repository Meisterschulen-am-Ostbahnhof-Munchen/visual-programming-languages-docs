# F_INT_TO_WORD

<img width="1221" height="183" alt="F_INT_TO_WORD" src="https://github.com/user-attachments/assets/0fd8962d-cbc1-47ea-828f-2286fc7e411b" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_WORD` converts an integer value (INT) into a 16-bit word value (WORD). This conversion is particularly useful in scenarios where data needs to be exchanged between systems with different data types.
![F_INT_TO_WORD](F_INT_TO_WORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. Simultaneously, the converted value is output at data output `OUT`.

### **Data Inputs**

- **IN**: The input for the integer value (INT) to be converted.

### **Data Outputs**

- **OUT**: The output for the converted 16-bit word value (WORD).

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The value at input `IN` is read and converted into a WORD value using the function `INT_TO_WORD`. The result is output at `OUT`, and simultaneously the event `CNF` is triggered to signal the successful completion of the operation.

## Technical Features

- The function block is implemented simply and efficiently, without additional states or complex logic.
- The conversion occurs directly and without delay.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Data conversion in control systems where different data types need to be processed.
- Interfaces between systems that use different data types.
- Logging and monitoring where data in uniform formats is required.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_INT_TO_WORD` specializes in converting INT to WORD and is therefore more efficient at this specific task.
- Other blocks, such as `F_DINT_TO_WORD` or `F_SINT_TO_WORD`, offer similar functionality but for different source data types.

## Conclusion

The `F_INT_TO_WORD` function block is a simple and effective tool for converting integer values to 16-bit word values. Its clear interface and straightforward operation make it a reliable component in control and automation systems.