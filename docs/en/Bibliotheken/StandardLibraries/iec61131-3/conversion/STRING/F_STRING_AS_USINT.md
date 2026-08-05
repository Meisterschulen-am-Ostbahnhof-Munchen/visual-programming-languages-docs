# F_STRING_AS_USINT

<img width="1480" height="212" alt="F_STRING_AS_USINT" src="https://github.com/user-attachments/assets/70362b16-1ffa-4281-8a03-3acb4f428c33" />

* * * * * * * * * *
## Introduction
The function block `F_STRING_AS_USINT` converts a `STRING` value to a `USINT` value (Unsigned Short Integer). This block is part of the `iec61131::conversion` package and enables the easy conversion of strings to numeric values.

![F_STRING_AS_USINT](F_STRING_AS_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: This input expects a `STRING` value, which is to be converted to a `USINT` value.

### **Data Outputs**

- **OUT**: Outputs the converted `USINT` value.

### **Adapters**
This function block does not have any adapters.


### ## Functionality
When the `REQ` event is triggered, the algorithm is executed, converting the `STRING` value at the `IN` input into a `USINT` value. The result is output at `OUT`, and the `CNF` event signals the completion of the conversion.

## Technical Features
- The block uses the `STRING_AS_USINT` function for the conversion.

- The conversion occurs synchronously with the triggering of the `REQ` event.

## State Overview
The function block has no internal states. The conversion occurs immediately after the `REQ` event is triggered.

## Application Scenarios

- Conversion of user input or communication data into numeric values.

- Use in control logic where strings need to be converted into numeric values.

## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks such as `F_STRING_AS_INT` or `F_STRING_AS_UINT`, this block is specifically optimized for conversion to `USINT` values.

## Conclusion
The `F_STRING_AS_USINT` function block provides a simple and efficient way to convert `STRING` values to `USINT` values. It is particularly useful in applications where strings need to be converted into numeric values.