# F_UDINT_TO_USINT

<img width="1470" height="216" alt="F_UDINT_TO_USINT" src="https://github.com/user-attachments/assets/1e0f089e-de96-4e75-91cb-739ff8cf6842" />
* * * * * * * * * *
The function block `F_UDINT_TO_USINT` converts a 32-bit unsigned integer value (UDINT) to an 8-bit unsigned integer value (USINT). This block is particularly useful in scenarios where type conversion between numerical values of different sizes is required.
![F_UDINT_TO_USINT](F_UDINT_TO_USINT.svg)

- **REQ**: Starts the conversion. This input is connected to the data input `IN`.
- **CNF**: Signals the completion of the conversion. The output is connected to the data output `OUT`.
- **IN**: The input expects a 32-bit unsigned integer value (UDINT) to be converted.
- **OUT**: The output provides the converted 8-bit unsigned integer value (USINT).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the conversion as soon as the event `REQ` is received. The algorithm converts the value of `IN` (UDINT) to the corresponding `OUT` (USINT) value. After successful conversion, the event `CNF` is triggered.

- The conversion is performed by the built-in function `UDINT_TO_USINT`.
- No range check is performed. Values outside the USINT range (0 to 255) may produce unexpected results.

The function block has no internal states. The conversion is performed anew with each `REQ` event.

- Type conversion in control applications where memory optimization is crucial.
- Communication between systems using different data types.
- Compared to generic conversion blocks, `F_UDINT_TO_USINT` is specialized and therefore more efficient in execution.
- Other blocks might offer additional functionalities such as range checks, which is not the case here.

The `F_UDINT_TO_USINT` function block is a simple and efficient building block for the specific conversion of UDINT to USINT values. It is particularly suitable for applications where fast and direct type conversion is required.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
