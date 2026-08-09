# F_STRING_AS_INT

<img width="1451" height="213" alt="F_STRING_AS_INT" src="https://github.com/user-attachments/assets/ed2bb7a0-e638-438c-92d8-997cb313e3dd" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_INT` converts a `STRING` value to a `INT` value. This functionality is particularly useful when strings representing numeric values need to be converted into integer values.
![F_STRING_AS_INT](F_STRING_AS_INT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event input is triggered, the `STRING` value at the data input `IN` is converted to a `INT` value.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. This event, along with the converted `INT` value, is output at data output `OUT`.

### **Data Inputs**

- **IN**: The `STRING` value to be converted to a `INT` value.

### **Data Outputs**

- **OUT**: The converted `INT` value.

### **Adapters**

No adapters are present.

## Operation

The function block performs the conversion as soon as the `REQ` event is received. The built-in function ``STRING_AS_INT`` is used to convert the ``STRING`` value at input ``IN`` into a ``INT`` value. The result is output at ``OUT`` and confirmed by the ``CNF`` event.

## Technical Features

- The conversion is performed directly without additional parameters.
- The function block is implemented simply and efficiently, without complex state logic.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the ``REQ`` event.

## Application Scenarios

- Processing user input that is in string form but requires numeric values.
- Conversion of data from text files or communication protocols into numeric values.
- Integration into systems that use string-based data sources but require numerical processing.

## ⚖️ Comparison with similar building blocks

- Compared to generic conversion building blocks, `F_STRING_AS_INT` specializes in converting `STRING` to `INT`.
- Other building blocks might offer additional features such as error handling or support for various numeric formats, which is not the case here.

## Conclusion

The `F_STRING_AS_INT` function block is a simple and effective tool for converting strings to integer values. Its strength lies in its simplicity and direct applicability, without added complexity. This building block is ideal for applications that require fast and straightforward conversion.