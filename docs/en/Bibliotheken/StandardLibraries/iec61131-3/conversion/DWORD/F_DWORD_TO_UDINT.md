# F_DWORD_TO_UDINT
<img width="1253" height="181" alt="F_DWORD_TO_UDINT" src="https://github.com/user-attachments/assets/0b023d3e-49d2-41d3-a6b3-db4d5f1970f8" />
* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_UDINT` converts a `DWORD` value to a `UDINT` value. This block is part of the `iec61131::conversion` package and enables simple and efficient type conversion.
![F_DWORD_TO_UDINT](F_DWORD_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `DWORD`, containing the value to be converted.

### **Data Outputs**
- **OUT**: The output of type `UDINT`, providing the result of the conversion.

### **Adapters**
- This function block does not use any adapters.

## Functionality
The function block performs the conversion from `DWORD` to `UDINT` as soon as the `REQ` event is triggered. The conversion is performed using the built-in function `DWORD_TO_UDINT`. After the conversion is complete, the `CNF` event is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The function block has a simple structure and contains only one algorithm (`REQ`) that performs the conversion.
- The conversion is performed directly and without any additional delay.

## State Overview

The function block has no internal state. The conversion is re-executed with each `REQ` event.

## Application Scenarios
- Type conversion in control applications where `DWORD` values need to be converted to `UDINT` values.
- Integration into larger control systems that require type compatibility between different data formats.

## ⚖️ Comparison with similar blocks
- Similar function blocks such as `F_WORD_TO_UINT` or `F_BYTE_TO_USINT` perform similar type conversions, but for different data types.
- Unlike generic conversion blocks, `F_DWORD_TO_UDINT` is specialized and optimized for converting `DWORD` to `UDINT`.

## 🛠️ Related exercises
* [Uebung_011](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011.md)
* [Uebung_011a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_011a2.md)
* [Uebung_012](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012.md)
* [Uebung_012a_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012a_sub.md)
* [Uebung_012b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012b.md)
* [Uebung_012c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_012c.md)
* [Uebung_020c2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_020c2_sub.md)
* [Uebung_028](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_028.md)
* [Uebung_034](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034.md)
* [Uebung_034a1_Q1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q1.md)
* [Uebung_034a1_Q2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q2.md)
* [Uebung_034a1_Q4](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_034a1_Q4.md)
* [Uebung_103](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)
* [Uebung_151](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_151.md)
* [Uebung_151_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_151_AX.md)
* [Uebung_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion
The `F_DWORD_TO_UDINT` function block provides a simple and efficient solution for converting `DWORD` values to `UDINT` values. Its clear interface structure and direct functionality make it a reliable component in control applications.