# F_BYTE_TO_UDINT

<img width="1245" height="183" alt="F_BYTE_TO_UDINT" src="https://github.com/user-attachments/assets/34a2230f-154d-4bae-ac66-db0481be7d57" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_TO_UDINT` is used to convert a BYTE value to a UDINT value. This function block is particularly useful in scenarios where a type conversion between these two data types is required.
![F_BYTE_TO_UDINT](F_BYTE_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: This event input triggers the conversion. The input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: This event output signals the successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `BYTE`, containing the value to be converted.

### **Data Outputs**

- **OUT**: The output of type `UDINT`, containing the result of the conversion.

#### **Adapters**

This function block has no adapters.

## Functionality

When the event input `REQ` is triggered, the algorithm is executed, converting the value at input `IN` (of type `BYTE`) into a `UDINT` value and outputting the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features

- The function block uses the built-in function `BYTE_TO_UDINT` for the conversion.
- The conversion is performed without additional parameters or configuration.

## State Overview

The function block has no internal states. Execution occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Type conversion in control applications where BYTE values need to be converted to UDINT values.
- Integration into larger control systems that require uniform data processing.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other conversion blocks such as `F_WORD_TO_UDINT` or `F_DWORD_TO_UDINT`, this block is specifically optimized for converting `BYTE` to `UDINT`.
- Similar blocks can process different input data types but are otherwise comparable in their functionality.

## 🛠️ Related Exercises

* [Exercise_011a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a.md)]

## Conclusion

The `F_BYTE_TO_UDINT` function block offers a simple and efficient way to convert BYTE values to UDINT values. Its clear interface structure and direct functionality make it ideal for applications requiring fast and reliable type conversion.