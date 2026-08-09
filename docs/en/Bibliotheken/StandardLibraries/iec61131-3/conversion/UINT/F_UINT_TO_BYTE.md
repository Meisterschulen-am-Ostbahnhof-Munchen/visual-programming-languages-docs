# F_UINT_TO_BYTE

<img width="1438" height="216" alt="F_UINT_TO_BYTE" src="https://github.com/user-attachments/assets/a8cfd8ac-c7a0-4336-80db-1efc0682ced0" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_BYTE` converts an unsigned 16-bit integer value (UINT) to an 8-bit byte value (BYTE). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_UINT_TO_BYTE](F_UINT_TO_BYTE.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input for the UINT value to be converted.

### **Data Outputs**

- **OUT**: The output for the converted BYTE value.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as an event arrives at input `REQ`. The value at input `IN`, of type UINT, is converted into a BYTE value and output at output `OUT`. The conversion is performed using the function `UINT_TO_BYTE`. After the conversion is complete, event `CNF` is triggered.

## Technical Features

- The conversion is performed without additional parameters or configuration.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios

- Type conversion in communication protocols where BYTE data is expected.
- Data reduction when only the lower 8 bits of a UINT value are relevant.

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, `F_UINT_TO_BYTE` is specialized in converting UINT to BYTE.
- Other blocks might offer additional features such as range checks or scaling, which is not the case here.

## 🛠️ Related Exercises

* [Exercise_12x_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_12x_sub.md)

## Conclusion

The `F_UINT_TO_BYTE` function block is a simple and efficient building block for the specific conversion of UINT to BYTE. It is particularly suitable for applications where fast and direct type conversion is required.