# F_BOOL_TO_ULINT

<img width="1242" height="183" alt="F_BOOL_TO_ULINT" src="https://github.com/user-attachments/assets/b10992cb-8e8e-46fe-85a0-f9372e711d1c" />
* * * * * * * * * *
The function block `F_BOOL_TO_ULINT` converts a Boolean value (`BOOL`) into an unsigned 64-bit integer value (`ULINT`). This conversion is particularly useful in scenarios where Boolean states need to be converted into numerical values, for example, for processing in mathematical operations or for storage in databases.
![F_BOOL_TO_ULINT](F_BOOL_TO_ULINT.svg)
- **REQ**: Normal execution request. Triggers the conversion. Linked to the data input `IN`.
- **CNF**: Execution Confirmation. Triggered after successful conversion. Linked to the data output `OUT`.
- **IN**: Input for the Boolean value (`BOOL`) to be converted.
- **OUT**: Output for the converted unsigned 64-bit integer value (`ULINT`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

No adapters available.

## Functionality

This function block performs the conversion from `BOOL` to `ULINT` when the event `REQ` is received. The Boolean value `IN` is converted to a value `ULINT`, with `FALSE` becoming `0` and `TRUE` becoming `1`. The result is output at `OUT`, and the event `CNF` is triggered.

- The function block is a simple function block (`SimpleFB`) and uses an ST algorithm for the conversion.

- The conversion is performed using the function ``BOOL_TO_ULINT``, which directly converts the Boolean value into a ``ULINT`` value.

The function block has no internal states. The conversion occurs immediately upon receiving the ``REQ`` event.

- Conversion of Boolean switching states into numerical values for further calculations.
- Integration into control systems that need to store Boolean signals in numerical databases.
- Use in data processing chains that require type conversion.
- Similar function blocks like `F_BOOL_TO_INT` or `F_BOOL_TO_DINT` convert Boolean values to other numeric types, but not to `ULINT`.
- `F_BOOL_TO_ULINT` is specific to converting to the unsigned 64-bit type and is therefore suitable for applications requiring a large range of values.

The function block `F_BOOL_TO_ULINT` provides a simple and efficient way to convert Boolean values to unsigned 64-bit integers. Its clear interface and direct operation make it ideal for applications requiring high-precision type conversion with a large range of values.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion