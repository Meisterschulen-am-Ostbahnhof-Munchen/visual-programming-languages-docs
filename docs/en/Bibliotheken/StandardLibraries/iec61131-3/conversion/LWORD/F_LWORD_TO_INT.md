# F_LWORD_TO_INT

<img width="1434" height="211" alt="F_LWORD_TO_INT" src="https://github.com/user-attachments/assets/1edfb2cc-ce64-4ed3-9668-580b531f4b11" />
* * * * * * * * * *
The function block `F_LWORD_TO_INT` converts a `LWORD` value (64-bit unsigned integer) to a `INT` value (16-bit signed integer). This conversion is useful when data needs to be exchanged or processed between systems with different word lengths.
![F_LWORD_TO_INT](F_LWORD_TO_INT.svg)

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.
- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.
- **IN**: The input value of type `LWORD` (64-bit unsigned integer) to be converted.
- **OUT**: The output value of type `INT` (16-bit signed integer) containing the result of the conversion.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- No adapters are available.


The function block performs the conversion by transforming the `LWORD` value at input `IN` into a `INT` value and outputting it at output `OUT`. The conversion occurs upon an event at input `REQ` and is confirmed by an event at output `CNF`.

- Converting a 64-bit value to a 16-bit value can result in data loss if the original value is outside the representable range of `INT`.
- Converting from a 64-bit value to a 16-bit value can lead to data loss if the original value is outside the representable range of `INT`.

`` - The function block is implemented as a simple function block (`SimpleFB`) and uses an ST algorithm for conversion.

The function block has no internal states. The conversion occurs immediately upon an event at the input `REQ`.

- Conversion of 64-bit data values for systems that can only process 16-bit data.
- Data reduction when only the lower 16-bit portion of a 64-bit value is relevant.
- `F_DWORD_TO_INT`: Converts a 32-bit value to a 16-bit value.
- `F_LWORD_TO_DINT`: Converts a 64-bit value to a 32-bit value.
- `F_LWORD_TO_SINT`: Converts a 64-bit value to an 8-bit value.

The function block `F_LWORD_TO_INT` provides a simple and efficient way to convert 64-bit data values to 16-bit data values. However, when using it, be aware of the potential data loss if the original value is outside the representable range of `INT`.

## Functionality

## Application Scenarios

## State Overview

## Technical Features

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion