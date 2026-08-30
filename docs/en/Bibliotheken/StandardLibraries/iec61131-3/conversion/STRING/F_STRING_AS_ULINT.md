# F_STRING_AS_ULINT

<img width="1480" height="212" alt="F_STRING_AS_ULINT" src="https://github.com/user-attachments/assets/42f8c0fa-f5ad-4f51-9d6b-3c35653b6782" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_ULINT` converts a `STRING` value to a `ULINT` value (unsigned 64-bit integer). This block is particularly useful when strings need to be converted to numeric values, for example, when processing user input or parsing data from external sources.
![F_STRING_AS_ULINT](F_STRING_AS_ULINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `STRING`, containing the string to be converted.

### **Data Outputs**

- **OUT**: The output of type `ULINT`, containing the result of the conversion.

### **Adapters**

No adapters are present.

## Operation

The function block performs the conversion as soon as the event `REQ` is triggered. The built-in function ``STRING_AS_ULINT`` is used to convert the input ``STRING`` into a value ``IN``. The result is output at ``OUT``, and the event ``CNF`` signals the successful completion of the operation.

## Technical Features

- The function block is part of the package ``iec61131::conversion``.
- The conversion is performed directly without any additional parameters or settings.

## State Overview

The function block has no internal states. The conversion is re-executed with each ``REQ`` event.

## Application Scenarios

- **Data Processing**: Converting strings to numeric values for calculations or storage.
- **User Input**: Processing input that is in string form but should be interpreted as numbers.
- **Logging**: Converting logical or textual data to numeric formats for further analysis.

## ⚖️ Comparison with Similar Building Blocks

- **F_STRING_AS_INT**: Converts a `STRING` to a `INT` (signed 32-bit integer). In contrast, `F_STRING_AS_ULINT` works with a larger range of values and without a sign.
- **F_STRING_AS_LINT**: Similar, but for `LINT` (signed 64-bit integer). `F_STRING_AS_ULINT` is optimized for unsigned values.

## Conclusion

The function block `F_STRING_AS_ULINT` provides a simple and efficient way to convert strings to unsigned 64-bit integer values. Its clear interface and direct functionality make it ideal for applications requiring fast and reliable conversion.
