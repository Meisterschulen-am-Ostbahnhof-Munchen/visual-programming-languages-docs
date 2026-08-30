# F_ULINT_TO_UDINT

<img width="1462" height="214" alt="F_ULINT_TO_UDINT" src="https://github.com/user-attachments/assets/15f7dfad-1b32-45df-af59-bbad295a6c11" />
* * * * * * * * * *
## Introduction

The function block `F_ULINT_TO_UDINT` converts a 64-bit unsigned integer value (ULINT) to a 32-bit unsigned integer value (UDINT). This conversion is useful when exchanging data between systems or components that use different data types.
![F_ULINT_TO_UDINT](F_ULINT_TO_UDINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. It is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. Linked to the data output `OUT`.

### **Data Inputs**

- **IN**: ULINT (64-bit unsigned integer) - The input value to be converted.

### **Data Outputs**

- **OUT**: UDINT (32-bit unsigned integer) - The converted output value.

#### **Adapters**

No adapters are available.

## Functionality

This function block performs a direct conversion of a ULINT value to a UDINT value. The conversion is carried out by calling the function `ULINT_TO_UDINT` within the algorithm `REQ`. During the conversion, the 64-bit value is truncated to 32 bits. Note that data loss can occur if the original value is greater than the maximum value of a UDINT.

## Technical Features

- The function block is simple and has no internal states.
- The conversion is performed by a single algorithm (`REQ`) that is executed with each call to the `REQ` event.
- There is no overflow error handling. The user must ensure that the input value is within the valid range for UDINT.

## State Overview

Since the function block is stateless, there are no state transitions or internal states.

## Application Scenarios

- Data conversion in control systems where different data types are used.
- Reduced memory requirements when 64-bit values are not needed.
- Compatibility with older systems that only support 32-bit values.

## ⚖️ Comparison with Similar Function Blocks

- **F_ULINT_TO_INT**: Converts ULINT to INT (signed integer), taking the sign into account.
- **F_ULINT_TO_LINT**: Converts ULINT to LINT (64-bit signed integer), which does not reduce the data size but does change the sign.
- **F_UDINT_TO_ULINT**: Reverse conversion from UDINT to ULINT, which does not result in any data loss.

## Conclusion

The `F_ULINT_TO_UDINT` function block is a simple and efficient tool for converting 64-bit unsigned integer values to 32-bit unsigned integer values. It is particularly useful in scenarios where memory efficiency or compatibility with older systems is required. However, users should be careful to avoid overflows, as the function block does not offer automatic error handling.
