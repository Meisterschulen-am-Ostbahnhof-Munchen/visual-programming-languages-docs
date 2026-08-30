# F_REAL_AS_STRING

<img width="1256" height="180" alt="F_REAL_AS_STRING" src="https://github.com/user-attachments/assets/7ac6c577-f078-4c20-a63e-216db88cf2e7" />
* * * * * * * * * *
The function block `F_REAL_AS_STRING` converts a REAL value to a STRING value. It is part of the package `iec61131::conversion` and enables the easy conversion of numeric values to a string.
![F_REAL_AS_STRING](F_REAL_AS_STRING.svg)
- **REQ**: Starts the conversion of the REAL value to a STRING. This input is linked to the data input `IN`.
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.
- **IN**: The REAL value to be converted to a STRING.
- **OUT**: The converted STRING value of input `IN`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

This function block has no adapters.

## Functionality

When an event is present at input `REQ`, the algorithm is executed, converting the REAL value of `IN` to a STRING and outputting the result to `OUT`. The event `CNF` is then triggered to signal the successful completion of the conversion.

- The function block uses the function `REAL_AS_STRING` for conversion.
- It is a simple function block without a state machine.

Since it is a simple function block, there are no state transitions. The conversion occurs directly upon triggering the `REQ` event.

- Conversion of sensor values for display on an HMI.
- Conversion of numerical values for logging in text files.
- Integration into systems that require string-based communication.
- Compared to other conversion blocks such as `F_INT_AS_STRING` or `F_BOOL_AS_STRING`, this one is specifically designed for real values.
- Simpler and more direct than universal conversion blocks, which may require additional parameters.

The `F_REAL_AS_STRING` function block offers an efficient and straightforward way to convert REAL values to STRINGs. Its simple interface and direct functionality make it ideal for applications where numeric values need to be processed as strings.

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
