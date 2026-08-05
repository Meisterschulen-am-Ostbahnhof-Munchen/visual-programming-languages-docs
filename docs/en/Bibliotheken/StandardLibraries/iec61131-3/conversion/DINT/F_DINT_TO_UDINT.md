# F_DINT_TO_UDINT
<img width="1454" height="217" alt="F_DINT_TO_UDINT" src="https://github.com/user-attachments/assets/1f958f49-ab73-4ac0-a2dd-fd1379a3cc6e" />
* * * * * * * * * *
## Introduction
The function block `F_DINT_TO_UDINT` converts a 32-bit signed integer value (DINT) to a 32-bit unsigned integer value (UDINT). This conversion is useful when exchanging data between systems that use different data types.
![F_DINT_TO_UDINT](F_DINT_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**
- **IN**: The DINT value to be converted (32-bit signed integer).

### **Data Outputs**
- **OUT**: The converted UDINT value (32-bit unsigned integer).

#### **Adapters**
No adapters are supported.

## Functionality
When the event input `REQ` is triggered, the function block's algorithm is executed. The value at input `IN`, of type `DINT`, is converted to a `UDINT` value and output at `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

## Technical Features
- The conversion is performed directly by the function `DINT_TO_UDINT`.
- There is no additional error handling for overflows or invalid values.

## State Overview
The function block has no internal states. The conversion occurs immediately upon triggering `REQ`.

## Application Scenarios
- Conversion of sensor values that are in the form of signed integers for systems that expect unsigned values.
- Data preparation for communication protocols that use unsigned integers.

## ⚖️ Comparison with Similar Function Blocks
- **F_INT_TO_UINT**: Converts 16-bit signed integers to unsigned integers.
- **F_LINT_TO_ULINT**: Converts 64-bit signed integers to unsigned integers.
- **F_SINT_TO_USINT**: Converts 8-bit signed integers to unsigned integers.

## 🛠️ Related Exercises
* [Exercise_009a](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)

## Conclusion
The function block `F_DINT_TO_UDINT` provides a simple and efficient way to convert signed 32-bit integers to unsigned 32-bit integers. It is particularly useful in scenarios where data needs to be exchanged between systems with different data type requirements.