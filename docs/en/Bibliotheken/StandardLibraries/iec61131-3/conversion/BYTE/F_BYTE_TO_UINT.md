# F_BYTE_TO_UINT
<img width="1436" height="212" alt="F_BYTE_TO_UINT" src="https://github.com/user-attachments/assets/8cb462ae-eb4e-4fd2-8556-33ab2b4fa9f3" />
* * * * * * * * * *
## Introduction
The function block `F_BYTE_TO_UINT` converts a `BYTE` value to a `UINT` value. This is particularly useful when data of different types needs to be processed in a system and type conversion is required.
![F_BYTE_TO_UINT](F_BYTE_TO_UINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Confirms the successful execution of the function block. The output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input of type `BYTE`, which is to be converted to a `UINT` value.

### **Data Outputs**
- **OUT**: The output of type `UINT`, which contains the result of the conversion.

#### **Adapters**
- No adapters are present.

## Functionality
The function block performs the conversion of the `BYTE` value at the input `IN` to a `UINT` value as soon as the event `REQ` is triggered. The result is output at `OUT`, and the event `CNF` signals successful execution.

## Technical Features
- The function block has a simple structure and contains only one algorithm that performs the conversion.
- The conversion is performed using the function `BYTE_TO_UINT`, which converts the `BYTE` value into a `UINT` value.

## State Overview

The function block has no internal state. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Type conversion in control and automation systems.
- Data processing in systems that use different data types.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks like `F_WORD_TO_UINT` or `F_DWORD_TO_UINT` perform similar conversions, but with different input types.
- `F_BYTE_TO_UINT` specializes in converting `BYTE` to `UINT` and is therefore more efficient for this specific use case.

## 🛠️ Related Exercises
* [Exercise_006c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_006c.md)

## Conclusion
The function block `F_BYTE_TO_UINT` is a simple and efficient tool for converting `BYTE` values to `UINT` values. Its clear interface structure and direct functionality make it ideal for applications requiring such type conversions.