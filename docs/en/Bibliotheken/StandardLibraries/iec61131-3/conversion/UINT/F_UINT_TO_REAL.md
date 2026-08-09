# F_UINT_TO_REAL

<img width="1441" height="216" alt="F_UINT_TO_REAL" src="https://github.com/user-attachments/assets/4cb48960-25c6-479d-9c4c-636b5a546a0c" />
* * * * * * * * * *
## Introduction

The function block `F_UINT_TO_REAL` converts an unsigned integer value (`UINT`) into a floating-point number (`REAL`). This functionality is particularly useful when exchanging data between systems that use different data types.
![F_UINT_TO_REAL](F_UINT_TO_REAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `UINT`, which is to be converted to a `REAL` value.

### **Data Outputs**

- **OUT**: The output value of type `REAL`, which represents the result of the conversion.

### **Adapters**

This function block has no adapters.

## Operation

The function block performs the conversion as soon as the event `REQ` is triggered. The algorithm within the block directly assigns the value of `IN` to `OUT`, performing an implicit type conversion from `UINT` to `REAL`. Upon completion of the conversion, the event `CNF` is triggered.

## Technical Features

- The conversion is performed without any additional parameters or settings.
- The block is part of the package `iec61131::conversion`.

## State Overview

The function block has no internal state. The conversion occurs immediately upon the triggering of `REQ`.

## Application Scenarios

- Conversion of sensor values stored as `UINT` to `REAL` for further calculations.
- Compatibility between systems using different data types.

## ⚖️ Comparison with Similar Blocks

- Unlike more complex conversion blocks, `F_UINT_TO_REAL` offers a simple, direct conversion without additional functionality.
- Similar blocks might offer additional features such as scaling or range checks, which is not the case here.

## 🛠️ Related Exercises

* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)

## Conclusion

The `F_UINT_TO_REAL` function block is a simple and efficient tool for converting the type from `UINT` to `REAL`. Its strength lies in its simplicity and direct applicability, without the overhead of additional functions.