# F_UDINT_TO_LINT

<img width="1451" height="212" alt="F_UDINT_TO_LINT" src="https://github.com/user-attachments/assets/bdc7f6e4-7460-464c-8c40-94f9399b9c0e" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_LINT` converts a 32-bit unsigned integer value (UDINT) to a 64-bit signed integer value (LINT). This block is part of the `iec61131::conversion` package and enables simple and efficient type conversion between these two data types.
![F_UDINT_TO_LINT](F_UDINT_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (UDINT): The 32-bit unsigned integer value to be converted.

### **Data Outputs**

- **OUT** (LINT): The resulting 64-bit signed integer value after the conversion.

### **Adapters**

This function block does not use adapters.

## Operation

When the event input `REQ` is triggered, the value of the data input `IN` (UDINT) is copied to the data output `OUT` (LINT). The conversion is performed directly because LINT covers a larger range of values than UDINT and can therefore represent all possible UDINT values without data loss. After the conversion is complete, the event `CNF` is triggered.

## Technical Features

- **Algorithm**: The function block uses a simple ST algorithm that directly assigns the input value to the output value.
- **Data Loss**: Since LINT has a larger range of values than UDINT, there is no data loss during this conversion.
- **Performance**: The conversion is very efficient and takes place in constant time.

## State Overview

The function block has no internal states. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- **Type Conversion**: In scenarios where an unsigned 32-bit value needs to be converted to a signed 64-bit value, e.g., when processing sensor data or in mathematical calculations.
- **Data Compatibility**: When integrating systems that use different integer types.

## ⚖️ Comparison with Similar Components

- **F_UDINT_TO_DINT**: Converts UDINT to DINT (32-bit signed), but can cause overflow because DINT has a smaller range of values.
- **F_UDINT_TO_ULINT**: Converts UDINT to ULINT (64-bit unsigned), but retains the unsigned nature.

## 🛠️ Related Exercises

* [Exercise_072c](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_072c.md)

## Conclusion

The `F_UDINT_TO_LINT` function block provides a simple and efficient way to convert unsigned 32-bit integer values to signed 64-bit integer values. Its direct and lossless conversion makes it ideal for applications that require an extended range of values.