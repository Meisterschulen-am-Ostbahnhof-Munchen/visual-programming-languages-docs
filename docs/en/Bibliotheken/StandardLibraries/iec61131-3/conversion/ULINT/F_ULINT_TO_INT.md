# F_ULINT_TO_INT

<img width="1442" height="214" alt="F_ULINT_TO_INT" src="https://github.com/user-attachments/assets/ef9d1612-2e7c-4316-b959-f3ed32453d61" />

* * * * * * * * * *
## Introduction
The function block `F_ULINT_TO_INT` converts a 64-bit unsigned integer value (ULINT) into a 16-bit signed integer value (INT). This conversion is particularly necessary when data needs to be exchanged between systems with different data types.

![F_ULINT_TO_INT](F_ULINT_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: This input triggers the conversion. Upon arrival of this event, the value at the data input `IN` is read and converted.

### **Event Outputs**

- **CNF**: This event signals the completion of the conversion. It is output along with the converted value at data output `OUT`.

### **Data Inputs**

- **IN** (ULINT): This input provides the 64-bit unsigned integer value to be converted.

### **Data Outputs**

- **OUT** (INT): This output provides the converted 16-bit signed integer value.

#### **Adapters**
This function block does not have any adapters.

## Functionality
The function block performs the conversion from ULINT to INT as soon as the event `REQ` occurs. The conversion is performed using the function ``ULINT_TO_INT(IN)``, which converts the value of ``IN`` to the target type ``INT``. After successful conversion, the event ``CNF`` is triggered, and the converted value is output to ``OUT``.

## Technical Features

- **Data Type Conversion**: Converting ULINT (64-bit) to INT (16-bit) can result in data loss if the original value is outside the representable range of INT (i.e., greater than 32767 or less than -32768).

- **Simple Implementation**: The function block is implemented as a SimpleFB and uses a simple ST algorithm for the conversion.


## State Overview

1. **Idle State**: The function block waits for the event `REQ`.

2. **Conversion State**: The conversion is performed upon receipt of `REQ`.

3. **Acknowledge State**: After the conversion, `CNF` is triggered, and the function block returns to the idle state.

## Application Scenarios

- **Data Compatibility**: Used when systems need to communicate with different data types.

- **Data Reduction**: Can be used to save memory when the higher precision of ULINT is not required.

## ⚖️ Comparison with Similar Blocks

- **F_ULINT_TO_DINT**: Converts ULINT to DINT (32-bit), offering a larger value range than INT.

- **F_ULINT_TO_LINT**: Converts ULINT to LINT (64-bit), maintaining full precision.

## Conclusion
The function block `F_ULINT_TO_INT` is a simple yet effective tool for converting 64-bit unsigned integer values to 16-bit signed integer values. It is particularly useful in scenarios where memory efficiency or compatibility with older systems is required. However, be aware of potential data loss when converting large values.