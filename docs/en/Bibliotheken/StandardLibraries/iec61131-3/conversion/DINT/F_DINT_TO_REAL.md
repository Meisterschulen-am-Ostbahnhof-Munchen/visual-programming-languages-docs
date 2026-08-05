# F_DINT_TO_REAL
<img width="1437" height="217" alt="F_DINT_TO_REAL" src="https://github.com/user-attachments/assets/9a171061-0724-4ae7-ae31-84f0ef970859" />
* * * * * * * * * *
## Introduction
The function block `F_DINT_TO_REAL` converts an integer value of type `DINT` into a floating-point value of type `REAL`. This conversion is necessary in many control and automation applications when data needs to be exchanged between different systems or components.
![F_DINT_TO_REAL](F_DINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN**: The input value of type `DINT`, which is to be converted to a `REAL` value.

### **Data Outputs**
- **OUT**: The converted output value of type `REAL`.

#### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is triggered. The algorithm `REQ` converts the input value `IN` of type `DINT` into a `REAL` value and stores the result in `OUT`. The event `CNF` is then triggered to signal the completion of the conversion.

## Technical Features
- The function block is implemented simply and efficiently, without additional states or complex logic.
- The conversion is performed directly by the function `DINT_TO_REAL`.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios
- Conversion of integer sensor values to floating-point values for further calculations.
- Data conversion between systems that use different data types.
- Integration into control algorithms that require floating-point values.

## ⚖️ Comparison with Similar Function Blocks
- **F_INT_TO_REAL**: Converts `INT` to `REAL`, but has a smaller input range compared to `DINT`.
- **F_LINT_TO_REAL**: Converts `LINT` to `REAL`, has a larger input range, but is unnecessary in most cases if `DINT` is sufficient.

## Conclusion

The function block `F_DINT_TO_REAL` is a simple and efficient tool for converting `DINT` values to `REAL` values. It is particularly useful in applications where data with different data types needs to be exchanged between different systems or components. Its direct and stateless implementation makes it reliable and easy to integrate.