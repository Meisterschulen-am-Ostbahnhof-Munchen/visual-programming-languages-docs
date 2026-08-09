# F_USINT_TO_REAL

<img width="1451" height="214" alt="F_USINT_TO_REAL" src="https://github.com/user-attachments/assets/f1f498f3-f7f6-48bb-9136-b03a341a2ec4" />
* * * * * * * * * *
The function block `F_USINT_TO_REAL` converts an unsigned 8-bit integer value (USINT) into a 32-bit floating-point value (REAL). This conversion is particularly necessary in scenarios where numeric values of different data types need to be processed or used further.
![F_USINT_TO_REAL](F_USINT_TO_REAL.svg)

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.
- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.
- **IN**: An unsigned 8-bit integer value (USINT) to be converted to a REAL value.
- **OUT**: The resulting 32-bit floating-point value (REAL) after the conversion.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

#### **Adapters**

This function block does not use any adapters.

The function block performs the conversion by directly converting the USINT value from `IN` to the REAL data type and outputting it to `OUT`. The conversion occurs synchronously upon receiving the `REQ` event and is confirmed by the `CNF` event.

- The conversion is performed without additional scaling or rounding.
- The block is optimized for simple conversions and does not provide error handling for invalid values.
1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Completed**: Sends the `CNF` event and outputs the converted value.
- Conversion of sensor values (e.g., raw ADC data) into floating-point values for further calculations.
- Compared to generic conversion blocks, `F_USINT_TO_REAL` is specialized and therefore more efficient for this specific conversion.
- Other blocks, such as `F_INT_TO_REAL` or `F_DINT_TO_REAL`, are designed for other integer data types.

The `F_USINT_TO_REAL` function block is a simple and efficient function block for converting unsigned 8-bit integers to floating-point values. Its simplicity and direct operation make it ideal for applications requiring fast and reliable type conversion.
## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion