# F_REAL_TO_USINT

<img width="1450" height="213" alt="F_REAL_TO_USINT" src="https://github.com/user-attachments/assets/16d6af79-f844-41ac-bebb-55fd87c4d950" />
* * * * * * * * * *
## Introduction

The function block `F_REAL_TO_USINT` converts a REAL value (floating-point number) to a USINT value (unsigned 8-bit integer). This conversion is particularly useful when floating-point numbers need to be processed in a range that only accepts integer values.
![F_REAL_TO_USINT](F_REAL_TO_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is processed.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. Triggered as soon as the converted value is available at data output `OUT`.

### **Data Inputs**

- **IN**: REAL value to be converted to a USINT value.

### **Data Outputs**

- **OUT**: The converted USINT value.

#### **Adapters**

This function block has no adapters.

## Functionality

The function block performs a direct conversion of the REAL value at input `IN` to a USINT value. The conversion is performed by calling the internal function `REAL_TO_USINT`. Once the conversion is complete, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features

- The conversion truncates the decimal portion (no rounding).
- The input value should be in the range of 0 to 255, as USINT can only represent values within this range. Values outside this range will result in undefined behavior or an overflow.

## State Overview

1. **Idle**: Waits for the event `REQ`.
2. **Processing**: Performs the conversion.
3. **Completed**: Sends the event `CNF` and provides the converted value.

## Application Scenarios

- Conversion of sensor values (e.g., temperature, pressure) into integer values for further processing.
- Preprocessing of data for systems that can only process integers.

## ⚖️ Comparison with Similar Function Blocks

- **F_REAL_TO_INT**: Converts REAL to INT (signed 16-bit integer count).
- **F_REAL_TO_UINT**: Converts REAL to UINT (unsigned 16-bit integer count).
- **F_REAL_TO_ULINT**: Converts REAL to ULINT (unsigned 64-bit integer count).

## Conclusion

The function block `F_REAL_TO_USINT` is a simple and efficient tool for converting floating-point numbers to unsigned 8-bit integers. It is particularly suitable for applications where memory or processing resources are limited.
