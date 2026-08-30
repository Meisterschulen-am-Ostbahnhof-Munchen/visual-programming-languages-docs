# F_STRING_AS_DINT

<img width="1464" height="213" alt="F_STRING_AS_DINT" src="https://github.com/user-attachments/assets/cbb2bda3-8b1f-45cd-a56f-e4a1958ac543" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_DINT` converts a `STRING` value to a `DINT` value. This function is particularly useful when strings need to be converted into numeric values, for example, when processing user input or interpreting text data.
![F_STRING_AS_DINT](F_STRING_AS_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`STRING`): The string value to be converted.

### **Data Outputs**

- **OUT** (`DINT`): The result of the conversion as a 32-bit integer.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The `STRING` value at input `IN` is converted into a `DINT` value and output at `OUT`. The conversion is performed using the function ``STRING_AS_DINT``. Upon completion of the conversion, the event ``CNF`` is triggered.

## Technical Details

- The conversion can fail if the value of ``STRING`` does not contain a valid numeric representation. In such cases, the output ``OUT`` may be undefined.
- The function block is part of the package ``iec61131::conversion``.

## State Overview

The function block has no internal state. The conversion occurs immediately upon triggering the ``REQ`` event.

## Application Scenarios

- Processing user input in the form of strings.
- Interpreting text data from files or network sources.
- Conversion of configurable parameters stored as strings.

## ⚖️ Comparison with similar function blocks

- Unlike `F_STRING_TO_*` function blocks, which perform explicit type conversions, `F_STRING_AS_DINT` directly interprets the `STRING` value as `DINT`.
- Similar function blocks like `F_STRING_TO_DINT` might offer additional formatting parameters, but they are not included in the standard library.

## Conclusion

The `F_STRING_AS_DINT` function block provides a simple and efficient way to convert strings to 32-bit integers. Its use is particularly useful in scenarios where direct interpretation of the string as a numeric value is required.
