# F_LREAL_TO_UDINT

<img width="1466" height="214" alt="F_LREAL_TO_UDINT" src="https://github.com/user-attachments/assets/8b6d5f6b-1cdf-44b6-a520-33c18fb77913" />
* * * * * * * * * *
## Introduction

The function block `F_LREAL_TO_UDINT` is used to convert a 64-bit floating-point value (LREAL) into a 32-bit unsigned integer value (UDINT). This conversion is useful when floating-point numbers need to be converted into unsigned integers, for example, for specific control or communication applications.
![F_LREAL_TO_UDINT](F_LREAL_TO_UDINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (LREAL): The input value to be converted.

### **Data Outputs**

- **OUT** (UDINT): The converted output value.

#### **Adapters**

This function block does not use any adapters.

## Functionality

The function block performs the conversion from an LREAL value to a UDINT value as soon as the `REQ` event is received. The conversion is performed using the built-in function `LREAL_TO_UDINT`. After the conversion is complete, the `CNF` event is triggered, and the converted value is available at the output `OUT`.

## Technical Features

- The conversion truncates the floating-point value to the nearest integer.
- There is no overflow or underflow check. Values outside the UDINT range (0 to 4,294,967,295) result in undefined behavior.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of sensor data (e.g., temperature measurements) into unsigned integer values for further processing.
- Preparation of floating-point values for communication with systems that only support unsigned integers.

## ⚖️ Comparison with similar components

- **F_REAL_TO_UINT**: Converts 32-bit floating-point values (REAL) to 16-bit unsigned integer values (UINT).
- **F_LREAL_TO_DINT**: Converts 64-bit floating-point values (LREAL) to 32-bit signed integer values (DINT).
- **F_LREAL_TO_UDINT** is specific for converting to unsigned 32-bit integers.

## 🛠️ Related Exercises

* [Exercise_152](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_152.md)
* [Exercise_153](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_153.md)

## Conclusion

The function block `F_LREAL_TO_UDINT` offers a simple and efficient way to convert floating-point values into unsigned integers. However, due to the lack of overflow checking, it should only be used in scenarios where the input values are known and within the valid range.