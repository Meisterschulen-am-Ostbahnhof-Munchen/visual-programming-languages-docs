# F_STRING_AS_LINT

<img width="1463" height="213" alt="F_STRING_AS_LINT" src="https://github.com/user-attachments/assets/e550d809-5da9-4c01-b2c4-0041510891ef" />
* * * * * * * * * *
## Introduction

The function block `F_STRING_AS_LINT` converts a `STRING` value to a `LINT` value. This functionality is particularly useful when strings need to be converted into numeric values for use in further calculations or control logic.
![F_STRING_AS_LINT](F_STRING_AS_LINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the `STRING` value to a `LINT` value. This event input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input for the `STRING` value, which is to be converted to a `LINT` value.

### **Data Outputs**

- **OUT**: The output for the converted `LINT` value.

### **Adapters**

No adapters are available.

## Functionality

The function block converts the `STRING` value to a `LINT` value as soon as the `REQ` event is triggered. The conversion is performed using the function `STRING_AS_LINT()`. After successful conversion, the `CNF` event is triggered, and the converted value is available at the `OUT` output.

## Technical Features

- The function block is a simple function block (SimpleFB) and performs the conversion in a single algorithm.
- The conversion is performed directly without additional state management.

## State Overview

Because it is a simple function block, there are no complex state transitions. The block performs the conversion on each `REQ` event and signals completion with the `CNF` event.

## Application Scenarios

- Conversion of user input to numeric values.
- Processing of strings containing numeric data in control systems.
- Integration into larger control logics that require numeric calculations.

## ⚖️ Comparison with Similar Blocks

- **F_STRING_AS_INT**: Converts a `STRING` value to a `INT` value, but is limited to smaller numeric ranges.
- **F_STRING_AS_REAL**: Converts a `STRING` value to a `REAL` value; suitable for floating-point numbers.
- **F_LINT_AS_STRING**: Performs the reverse conversion, i.e., from `LINT` to `STRING`.

## Conclusion

The function block `F_STRING_AS_LINT` offers a simple and efficient way to convert strings into large numeric values (`LINT`). Its direct functionality and clear interface structure make it ideal for use in control systems that require such conversion.
