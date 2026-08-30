# F_LREAL_TO_DINT

<img width="1448" height="210" alt="F_LREAL_TO_DINT" src="https://github.com/user-attachments/assets/ad2c6222-b7c0-4b49-b00b-e1ea330f724f" />
* * * * * * * * * *
## Introduction

The function block `F_LREAL_TO_DINT` converts an LREAL value (64-bit floating-point number) to a DINT value (32-bit integer). This block is part of the `iec61131::conversion` package and implements a simple type conversion.
![F_LREAL_TO_DINT](F_LREAL_TO_DINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion process. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (LREAL): The input value to be converted from LREAL to DINT.

### **Data Outputs**

- **OUT** (DINT): The result of the conversion as a DINT value.

### **Adapters**

This function block does not have any adapters.

## Operation

When the `REQ` event is triggered, the algorithm is executed that converts the `IN` value from LREAL to DINT and outputs the result to `OUT`. The `CNF` event is then triggered to signal the successful completion of the operation.

## Technical Features

- The conversion is performed by the built-in function `LREAL_TO_DINT`.
- This is a simple function block without state management or complex logic.

## State Overview

The function block has no internal states. Execution is purely event-driven and occurs with each `REQ` event.

## Application Scenarios

- Type conversion in control applications where floating-point numbers need to be converted to integers.
- Use in calculations where an integer representation is required.

## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks such as `F_REAL_TO_INT` or `F_LREAL_TO_LINT`, this block offers a specific conversion from LREAL to DINT.

Similar blocks can have different source or target types, such as `F_DINT_TO_LREAL` for reverse conversion.

## Conclusion

The `F_LREAL_TO_DINT` function block is a simple and efficient tool for type conversion in IEC 61499-based control systems. Its clear interface and direct operation make it ideal for applications requiring fast conversion of floating-point numbers to integers.
