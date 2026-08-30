# F_COS

![F_COS](https://user-images.githubusercontent.com/116869307/214145027-b4a8a395-2535-4bd6-853c-644685e13ade.png)

* * * * * * * * * *

## Introduction

The F_COS function block calculates the cosine of an input value in radians. It is a standard function for numerical calculations according to IEC 61131-3.
![F_COS](F_COS.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - triggers the cosine calculation

### **Event Outputs**

- **CNF**: Confirmation of the requested service - signals the completion of the calculation

### **Data Inputs**

- **IN**: Input value in radians (ANY_REAL data type)

### **Data Outputs**

- **OUT**: Calculated cosine value of the input value (ANY_REAL data type)

### **Adapters**

No adapters available.

## Functionality

Upon receiving a REQ event, the F_COS block calculates the cosine of the value passed to IN. The input value is interpreted as an angle in radians. After the calculation is complete, the CNF event is output to OUT along with the result.

## Technical Features

- Supports the ANY_REAL data type for maximum flexibility
- Calculations are performed in radians
- Compliant with the IEC 61131-3 standard
- Part of the iec61131::numerical package

## State Transitions

1. **Wait State**: Block waits for a REQ event
2. **Calculate State**: Cosine is calculated upon a REQ event
3. **Output State**: CNF event with result is output
4. **Return**: Returns to the wait state

## Application Scenarios

- Signal processing in control engineering
- Mathematical calculations in control systems
- Trigonometric functions in technical applications
- Calculations in robotics and motion control

## ⚖️ Comparison with Similar Function Blocks

Compared to other trigonometric functions:

- F_SIN: Calculates sine instead of cosine
- F_TAN: Calculates tangent
- F_ACOS: Calculates Arccosine (Inverse Function)

## Conclusion

The F_COS function block offers a reliable and standards-compliant implementation of the cosine function for industrial control systems. Its simple interface and flexible data type support make it ideal for various automation applications.
