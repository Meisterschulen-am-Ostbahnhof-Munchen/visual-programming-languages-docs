# F_UDINT_TO_DWORD

<img width="1464" height="212" alt="F_UDINT_TO_DWORD" src="https://github.com/user-attachments/assets/2a17af0b-98a8-4d4b-ac10-de4278c1451a" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_DWORD` converts a `UDINT` value (32-bit unsigned integer) into a `DWORD` value (32-bit data word). This conversion is particularly useful in scenarios where numeric values need to be further processed or transmitted as bit patterns.
![F_UDINT_TO_DWORD](F_UDINT_TO_DWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`UDINT`): The 32-bit unsigned integer value to be converted.

### **Data Outputs**

- **OUT** (`DWORD`): The result of the conversion as a 32-bit data word.

### **Adapters**

No adapters available.

## Functionality

When the `REQ` event is triggered, the input value `IN` of type `UDINT` is converted to a `DWORD` value and output `OUT`. The `CNF` event signals the successful completion of the conversion.

The underlying algorithm is implemented in Structured Text (ST):

ALGORITHM REQ
OUT := UDINT_TO_DWORD(IN);
END_ALGORITHM
## Technical Features

- The conversion is performed directly through type conversion, without changing the bit representation.
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of numeric values for bitwise processing.
- Compatibility with systems that expect `DWORD` data.
- Data preparation for communication protocols or hardware registers.

## ⚖️ Comparison with Similar Function Blocks

- Unlike arithmetic function blocks, `F_UDINT_TO_DWORD` does not change the value, but only the data type.

Similar conversion blocks exist for other data types (e.g., `INT_TO_DINT`), but with different source and target types.

## 🛠️ Related Exercises

* [Exercise_034b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034b.md)
* [Exercise_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Exercise_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion

F_UDINT_TO_DWORD` is a simple yet essential function block for type conversions in IEC 61499-based control systems. Its deterministic operation and clear interface make it a reliable tool for data transformations.
