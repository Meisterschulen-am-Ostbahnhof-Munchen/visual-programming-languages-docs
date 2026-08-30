# F_LINT_TO_LWORD

<img width="1448" height="214" alt="F_LINT_TO_LWORD" src="https://github.com/user-attachments/assets/9a0ef8d1-c702-4743-94c4-d151d7d9dd05" />
* * * * * * * * * *
## Introduction

The function block `F_LINT_TO_LWORD` converts a LINT data type (64-bit signed integer) to an LWORD data type (64-bit bit string). This block is particularly useful in scenarios where numeric values need to be converted to their binary representation.
![F_LINT_TO_LWORD](F_LINT_TO_LWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this event input is triggered, the function block reads the value at the data input `IN` and performs the conversion.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. This event, along with the converted value, is output at the data output `OUT`.

### **Data Inputs**

- **IN**: Expects a value of type `LINT` (64-bit signed integer) to be converted.

### **Data Outputs**

- **OUT**: Outputs the converted value of type `LWORD` (64-bit bit string).

### **Adapters**

This function block has no adapter interfaces.

## Functionality

When the `REQ` event is triggered, the value at input `IN` is read and converted into a `LWORD` value using the function `LINT_TO_LWORD`. The result is provided at output `OUT`, and simultaneously, the `CNF` event is triggered.

## Technical Features

- The conversion occurs directly and without any additional delay.
- The function block is deterministic and has no internal states.

## State Overview

Since this is a simple function block, there are no state transitions or state machines. The conversion occurs immediately upon triggering the `REQ` event.

## Application Scenarios

- Conversion of numeric values into their binary representation for bitwise operations.
- Use in protocol implementations where numeric values must be transmitted as bit strings.
- Integration into systems that perform low-level bit manipulation.

## ⚖️ Comparison with Similar Blocks

- Compared to generic conversion blocks, `F_LINT_TO_LWORD` specializes in converting `LINT` to `LWORD` and therefore offers an optimized and type-safe solution.
- Similar blocks such as `INT_TO_WORD` or `DINT_TO_DWORD` work with smaller data types.

## Conclusion

The `F_LINT_TO_LWORD` function block provides an efficient and reliable method for converting 64-bit integers to 64-bit bit strings. Its simplicity and determinism make it ideal for real-time applications where fast and precise type conversions are required.
