# F_UDINT_TO_BYTE

<img width="1454" height="212" alt="F_UDINT_TO_BYTE" src="https://github.com/user-attachments/assets/55120ea3-8221-4095-8f59-51cc6eb4207a" />
* * * * * * * * * *
The function block `F_UDINT_TO_BYTE` converts a 32-bit unsigned integer (UDINT) value to an 8-bit unsigned integer (BYTE) value. This conversion is useful when data needs to be exchanged between systems with different word lengths or when memory space needs to be optimized.
![F_UDINT_TO_BYTE](F_UDINT_TO_BYTE.svg)
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.
- **IN**: The 32-bit unsigned integer value (UDINT) to be converted.
- **OUT**: The resulting 8-bit unsigned integer value (BYTE) after the conversion.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion when the event `REQ` is received. The value at input `IN`, of type UDINT, is converted to a BYTE value and output at `OUT`. The event `CNF` signals the successful completion of the conversion.

- The conversion is performed by the function `UDINT_TO_BYTE`, which maps the UDINT value to a BYTE value. Data loss can occur if the original value is outside the representable range of a BYTE (0 to 255).
- The function block is implemented as a simple function block (SimpleFB) and uses an ST algorithm for the conversion.
1. **Idle State**: The function block waits for the event `REQ`.
2. **Conversion State**: Upon receiving `REQ`, the conversion is performed, and `CNF` is triggered.
- **Data Reduction**: When only the lower 8 bits of a 32-bit value are relevant.
- **Interface Adaptation**: For communication with systems that can only process BYTE data.
- **Memory Optimization**: In environments with limited memory.
- **F_DINT_TO_BYTE**: Converts a 32-bit signed integer (DINT) to a BYTE value.
- **F_INT_TO_BYTE**: Converts a 16-bit signed integer (INT) to a BYTE value.
- **F_UDINT_TO_WORD**: Converts a 32-bit unsigned integer (UDINT) to a 16-bit unsigned integer (WORD).

The function block `F_UDINT_TO_BYTE` provides a simple and efficient way to convert 32-bit unsigned integer values to 8-bit unsigned integer values. It is particularly useful in scenarios where memory or communication bandwidth needs to be optimized. However, be aware of the potential data loss with values outside the byte range.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion