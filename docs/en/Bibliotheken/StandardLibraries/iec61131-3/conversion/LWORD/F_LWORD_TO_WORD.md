# F_LWORD_TO_WORD

<img width="1454" height="214" alt="F_LWORD_TO_WORD" src="https://github.com/user-attachments/assets/eeb29887-0982-497c-bd0d-0bac534c0573" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_WORD` is used to convert a 64-bit value (LWORD) to a 16-bit value (WORD). This conversion is particularly necessary in scenarios where data needs to be exchanged or processed between systems with different word widths.
![F_LWORD_TO_WORD](F_LWORD_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Signals the start of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: LWORD (64-bit) – The input value to be converted.

### **Data Outputs**

- **OUT**: WORD (16-bit) – The converted output value.

#### **Adapters**

No adapters available.

## Functionality

This function block performs the conversion from a 64-bit value (LWORD) to a 16-bit value (WORD). During the conversion, the lower 16 bits of the input value are retained, while the upper 48 bits are discarded. The conversion occurs synchronously with the `REQ` event, and the result is confirmed with the `CNF` event.

## Technical Features

- The conversion is performed without rounding or scaling, as it is a direct bit conversion.
- No check is performed to prevent potential data loss due to word width reduction. The user must ensure that the input value is within the permissible range.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Communication between systems with different word widths.
- Processing data originating from 64-bit sources but intended for use in 16-bit systems.
- Reducing the data width to optimize storage space when the higher-order bits are not required.

## ⚖️ Comparison with Similar Function Blocks

- **F_LWORD_TO_DWORD**: Converts LWORD to DWORD (32-bit), retaining more data bits.
- **F_LWORD_TO_BYTE**: Converts LWORD to BYTE (8-bit), reducing the data width even further.
- **F_LWORD_TO_<any>**: Similar function blocks for other target data types, each with a different bit width as a result.

## Conclusion

The `F_LWORD_TO_WORD` function block offers a simple and efficient way to reduce 64-bit data to 16-bit data. It is particularly useful in heterogeneous system environments where data needs to be exchanged between components with different word widths. However, due to the lack of data loss checks, users should ensure that the conversion is appropriate and safe.
