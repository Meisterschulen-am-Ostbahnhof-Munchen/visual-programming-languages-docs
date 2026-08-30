# F_UDINT_TO_UINT

<img width="1450" height="216" alt="F_UDINT_TO_UINT" src="https://github.com/user-attachments/assets/9ee78872-0f37-4ed5-be3e-2592ac760277" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_UINT` converts a 32-bit unsigned integer value (UDINT) to a 16-bit unsigned integer value (UINT). This block is part of the `iec61131::conversion` package.
![F_UDINT_TO_UINT](F_UDINT_TO_UINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion of the input value. The input value `IN` is passed with this event.

### **Event Outputs**

- **CNF**: Signals successful conversion and outputs the converted value `OUT`.

### **Data Inputs**

- **IN** (UDINT): The 32-bit unsigned integer value to be converted.

### **Data Outputs**

- **OUT** (UINT): The converted 16-bit unsigned integer value.

### **Adapters**

This function block does not have any adapters.

## Operation

Upon receiving the event `REQ`, the input value `IN` of type UDINT is converted to type UINT and output via `OUT`. Simultaneously, the event `CNF` is triggered to signal the successful completion of the conversion.

## Technical Features

- The conversion is performed by direct type conversion, whereby the higher-order bits of the UDINT value are truncated if the value is outside the representable range of UINT.
- The block is suitable for use in real-time systems.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Conversion of 32-bit values to 16-bit values in control applications.
- Use in systems that need to work with different integer sizes.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_UDINT_TO_UINT` is specialized for converting UDINT to UINT and is therefore more efficient in execution.
- Similar blocks like `F_DINT_TO_INT` convert between other integer types.

## 🛠️ Related Exercises

- [Exercise_103](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_103.md)

## Conclusion

The `F_UDINT_TO_UINT` function block is a specialized and efficient building block for converting 32-bit to 16-bit unsigned integer values. It is particularly suitable for applications where fast and direct type conversion is required.
