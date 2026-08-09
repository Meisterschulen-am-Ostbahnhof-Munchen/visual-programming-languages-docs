# F_ULINT_TO_WORD

<img width="1448" height="214" alt="F_ULINT_TO_WORD" src="https://github.com/user-attachments/assets/8be2ddee-0d88-4c60-98ec-e97dc61f329c" />
* * * * * * * * * *
The function block `F_ULINT_TO_WORD` converts a 64-bit unsigned integer value (ULINT) to a 16-bit unsigned integer value (WORD). This block is part of the `iec61131::conversion` package and implements a simple type conversion.
![F_ULINT_TO_WORD](F_ULINT_TO_WORD.svg)

- **REQ**: Starts the conversion process. This input is connected to the data input `IN`.
- **CNF**: Signals successful completion of the conversion. The output is connected to the data output `OUT`.
- **IN**: ULINT (64-bit unsigned integer) - The input value to be converted.
- **OUT**: WORD (16-bit unsigned integer) - The result of the conversion.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

No adapters are available.

## Functionality

This function block performs the conversion from ULINT to WORD when the `REQ` event occurs. The conversion is carried out using the built-in function `ULINT_TO_WORD`. After successful conversion, the `CNF` event is triggered.

- The block does not support overflow error handling (since ULINT has a larger value range than WORD).
- The conversion is instantaneous and without any additional delay.

The block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

- Type conversion in control applications where ULINT values need to be converted to WORD values.
- Data reduction when only the lower 16 bits of a ULINT value are relevant.
- Similar blocks such as `F_DINT_TO_WORD` or `F_LINT_TO_WORD` offer conversions from other integer types to WORD, but with different value ranges and precision.

The `F_ULINT_TO_WORD` function block is a simple and efficient tool for converting ULINT to WORD values. It is particularly useful in scenarios where data width reduction is required. However, be aware of the potential data loss when converting from larger to smaller data types.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion