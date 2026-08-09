# F_BYTE_TO_WORD

<img width="1232" height="182" alt="F_BYTE_TO_WORD" src="https://github.com/user-attachments/assets/895b5f0c-a270-44f1-9dab-26aed65b0089" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_TO_WORD` converts a `BYTE` data type to a `WORD` data type. This conversion is useful when data of different sizes needs to be processed or transferred.
![F_BYTE_TO_WORD](F_BYTE_TO_WORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `BYTE` to be converted.

### **Data Outputs**

- **OUT**: The output of type `WORD`, containing the result of the conversion.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion from `BYTE` to `WORD` as soon as the event `REQ` is received. The conversion is performed using the function ``BYTE_TO_WORD(IN)``, which converts the input value ``IN`` into the corresponding value ``WORD``. The result is output at ``OUT``, and the event ``CNF`` signals the completion of the operation.

## Technical Features

- The function block has a simple structure and contains only one conversion algorithm.
- The conversion is performed directly and without any additional delay.

## State Overview

The function block has no internal states. The conversion is performed on each ``REQ`` event, and the result is output immediately.

## Application Scenarios

- **Data Conversion**: When a `BYTE` value needs to be processed in a system that expects `WORD` values.
- **Interface Adaptation**: For communication between systems that use different data types.

## ⚖️ Comparison with Similar Building Blocks

- **F_WORD_TO_BYTE**: Performs the reverse conversion, from `WORD` to `BYTE`.
- **F_BYTE_TO_INT**: Converts `BYTE` to `INT`, which is another type of data type conversion.

## Conclusion

The `F_BYTE_TO_WORD` function block is a simple and efficient tool for converting `BYTE` values to `WORD` values. Its clear interface structure and direct functionality make it ideal for applications requiring fast and straightforward data type conversions.