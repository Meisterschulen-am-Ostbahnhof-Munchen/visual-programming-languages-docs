# F_BOOL_TO_UINT

<img width="1230" height="183" alt="F_BOOL_TO_UINT" src="https://github.com/user-attachments/assets/0ed51abc-df99-4646-bb36-6243ba00a996" />
* * * * * * * * * *
## Introduction

The function block `F_BOOL_TO_UINT` converts a Boolean value (`BOOL`) into an unsigned integer value (`UINT`). This conversion is particularly useful when Boolean signals need to be converted into numerical values, for example, for further calculations or control purposes.
![F_BOOL_TO_UINT](F_BOOL_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The Boolean input value (`BOOL`) to be converted.

### **Data Outputs**

- **OUT**: The converted unsigned integer value (`UINT`).

### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion by transforming the Boolean value `IN` into an unsigned integer value `OUT`. The conversion is performed according to the following rule:

- `FALSE` becomes `0`
- `TRUE` becomes `1`

The conversion is triggered by the event `REQ` and confirmed by the event `CNF`.

## Technical Features

- The function block is a simple function block (`SimpleFB`) and performs the conversion in a single algorithm.
- The conversion is performed directly and without delay.

## State Overview

The function block has no internal states. The conversion is performed anew with each `REQ` event.

## Application Scenarios

- Conversion of Boolean sensor data into numerical values for further processing.
- Integration into control systems that require numerical values instead of Boolean values.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_BOOL_TO_INT` or `F_BOOL_TO_REAL` offer conversions to other data types, but `F_BOOL_TO_UINT` is specifically optimized for unsigned integer values.

## 🛠️ Related Exercises

- [Exercise_087](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087.md)
- [Exercise_087a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_087a1.md)
- [Exercise_090a1](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a1.md)
- [Exercise_090a1_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a1_AX.md)
- [Exercise_090a2](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_090a2.md)
- [Exercise_090a2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_090a2_AX.md)

## Conclusion

The `F_BOOL_TO_UINT` function block is a simple and efficient tool for converting Boolean values to unsigned integers. Its clear interface and direct functionality make it a reliable component in control and automation systems.
