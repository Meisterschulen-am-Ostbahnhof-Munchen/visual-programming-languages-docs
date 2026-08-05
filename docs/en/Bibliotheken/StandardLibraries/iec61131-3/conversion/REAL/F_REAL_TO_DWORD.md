# F_REAL_TO_DWORD
<img width="1453" height="216" alt="F_REAL_TO_DWORD" src="https://github.com/user-attachments/assets/e2620ce1-a635-402f-98c9-6597cf979c6a" />
* * * * * * * * * *
## Introduction
The function block `F_REAL_TO_DWORD` converts a REAL value (floating-point number) to a DWORD value (32-bit unsigned integer). This conversion is particularly useful when floating-point values need to be processed in systems that only support integer operations.
![F_REAL_TO_DWORD](F_REAL_TO_DWORD.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. The value to be converted is provided via the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. The converted value is output via the data output `OUT`.

### **Data Inputs**
- **IN**: REAL value to be converted to a DWORD value.

### **Data Outputs**
- **OUT**: The resulting DWORD value after conversion.

### **Adapters**
This function block does not use any adapters.

## Operation
When an event is received at input `REQ`, the algorithm is executed, converting the REAL value of `IN` to a DWORD value and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

### **Adapters**

# ## Technical Features
- The conversion is performed by the function ``REAL_TO_DWORD``, which directly converts the REAL value into a DWORD value. The floating-point value is rounded to the nearest integer.
- Note that data loss can occur with very large or small values, as the DWORD type offers only limited precision.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios
- Processing sensor data that is in floating-point form but needs to be further processed in integer form.
- Integration into control systems that only support integer operations.
- Data conversion for communication protocols that require DWORD values.

## ⚖️ Comparison with Similar Function Blocks
- **F_REAL_TO_INT**: Converts REAL to INT (signed integer). In contrast, `F_REAL_TO_DWORD` returns an unsigned value.
- **F_REAL_TO_LREAL**: Converts REAL to LREAL (higher precision), while `F_REAL_TO_DWORD` converts the value to an integer type.

## 🛠️ Related Exercises
* [Exercise_126b2_sub](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b2_sub.md)]

## Conclusion
The function block `F_REAL_TO_DWORD` provides a simple and efficient way to convert floating-point values to unsigned integers. It is particularly useful in environments that only support integer operations or when data needs to be processed further in a specific format. However, when using this method, care must be taken to avoid potential data loss during the conversion process.