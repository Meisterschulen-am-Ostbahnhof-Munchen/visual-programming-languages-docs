# F_DWORD_TO_ULINT

<img width="1254" height="181" alt="F_DWORD_TO_ULINT" src="https://github.com/user-attachments/assets/e5bbb4d1-3d9a-4a73-b891-646529c28a89" />
* * * * * * * * * *
The function block `F_DWORD_TO_ULINT` converts a `DWORD` value to a `ULINT` value. It is part of the `iec61131::conversion` package and is typically used in automation applications where type conversion between these two data types is required.
![F_DWORD_TO_ULINT](F_DWORD_TO_ULINT.svg)

- **REQ**: This input triggers the execution of the function block. It is linked to the data input `IN`.
- **CNF**: This output signals the successful execution of the function block. It is linked to the data output `OUT`.
- **IN**: The input expects a `DWORD` value, which is to be converted to a `ULINT` value.
- **OUT**: The output provides the converted `ULINT` value.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block does not use any adapters.


The function block performs the conversion from `DWORD` to `ULINT` as soon as the `REQ` event arrives. The algorithm within the function block uses the function `DWORD_TO_ULINT` to carry out the conversion. After successful conversion, the `CNF` event is triggered, and the converted value is available at the `OUT` output.

- The function block is implemented as a simple function block (`SimpleFB`).
- The conversion occurs directly and without any additional delay.
- The function block is licensed under the Eclipse Public License 2.0.

This function block has no internal state. Execution occurs exclusively upon the occurrence of the `REQ` event.

- Type conversion in automation applications where `DWORD` values need to be converted to `ULINT` values.
- Integration into larger control systems that process different data types.
- Similar function blocks such as `F_WORD_TO_UINT` or `F_BYTE_TO_USINT` perform similar conversions, but for different data types.

- `F_DWORD_TO_ULINT` specializes in converting `DWORD` to `ULINT` and offers no additional functionality.

The `F_DWORD_TO_ULINT` function block is a simple and efficient tool for type conversion in IEC 61131-3-based control systems. Its clear interface and direct operation make it a reliable component in automation projects.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
