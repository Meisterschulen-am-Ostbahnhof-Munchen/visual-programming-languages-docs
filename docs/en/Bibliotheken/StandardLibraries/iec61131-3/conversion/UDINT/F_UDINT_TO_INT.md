# F_UDINT_TO_INT

<img width="1446" height="212" alt="F_UDINT_TO_INT" src="https://github.com/user-attachments/assets/e374f818-7a4c-400e-8da2-7b27a801baf9" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_INT` converts a `UDINT` value (32-bit unsigned integer) to a `INT` value (16-bit signed integer). This conversion is useful when data needs to be exchanged between systems or components that use different data types.
![F_UDINT_TO_INT](F_UDINT_TO_INT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal execution request. Triggers the conversion.

### **Event Outputs**

- **CNF**: Execution confirmation. Triggered after successful conversion.

### **Data Inputs**

- **IN** (`UDINT`): The input value to be converted.

### **Data Outputs**

- **OUT** (`INT`): The converted output value.

#### **Adapters**

- No adapters available.

## Functionality

This function block performs the conversion from `UDINT` to `INT` when the `REQ` event is received. The algorithm uses the built-in function `UDINT_TO_INT` to perform the conversion. After successful conversion, the `CNF` event is triggered, and the converted value is available at the `OUT` output.

## Technical Features

- Data loss can occur if the `UDINT` value is outside the representable range of `INT` (i.e., greater than 32767 or less than -32768).
- The function block is simple and has no internal states or complex logic.

## State Overview

The function block has no internal state. It responds exclusively to the `REQ` event and performs the conversion immediately.

## Application Scenarios

- Data conversion in control systems where different data types are used.
- Integration of components that expect or deliver different data types.
- Logging or displaying data originally stored as `UDINT` but intended to be displayed as `INT`.

## ⚖️ Comparison with similar building blocks

- **F_DINT_TO_INT**: Converts `DINT` (32-bit signed) to `INT`.
- **F_UDINT_TO_DINT`: Konvertiert `UDINT` zu `DINT` (32-Bit vorzeichenbehaftet), ohne Datenverlust, da der Wertebereich von `DINT` is larger.
- **F_INT_TO_UDINT**: Performs the reverse conversion (`INT` to `UDINT`).

## Conclusion

The `F_UDINT_TO_INT` function block is a simple and efficient tool for converting `UDINT` to `INT` values. It is particularly useful in scenarios where such a type conversion is required; however, potential data loss with large values should be considered.