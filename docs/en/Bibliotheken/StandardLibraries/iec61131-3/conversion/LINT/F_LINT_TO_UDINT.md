# F_LINT_TO_UDINT
<img width="1448" height="214" alt="F_LINT_TO_UDINT" src="https://github.com/user-attachments/assets/9e88f669-c0d5-4acd-a01f-4274a376f3f3" />
* * * * * * * * * *
## Introduction
The function block `F_LINT_TO_UDINT` converts a 64-bit signed integer value (`LINT`) to a 32-bit unsigned integer value (`UDINT`). This block is part of the `iec61131::conversion` library and is suitable for applications requiring type conversion.
![F_LINT_TO_UDINT](F_LINT_TO_UDINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`LINT`): The 64-bit signed integer value to be converted.

### **Data Outputs**
- **OUT** (`UDINT`): The resulting 32-bit unsigned integer value after the conversion.

### **Adapters**
No adapters available.

### ## Functionality
When the event `REQ` is triggered, the algorithm is executed, converting the value of `IN` from `LINT` to `UDINT` and outputting the result to `OUT`. The event `CNF` is then triggered to signal the completion of the operation.

## Technical Features
- The block uses the built-in function `LINT_TO_UDINT` for the conversion.
- It is a simple function block without state machines or complex logic.

## State Overview
The block has no internal states. The conversion occurs immediately upon triggering `REQ`.

## Application Scenarios
- Type conversion in control applications where 64-bit values need to be converted to 32-bit values.
- Use in data processing chains where different data types need to be made compatible.

## ⚖️ Comparison with Similar Blocks
- Similar blocks like `F_DINT_TO_UDINT` or `F_INT_TO_UINT` offer conversions between other integer types, but not for `LINT` to `UDINT`.
- Unlike generic conversion blocks, `F_LINT_TO_UDINT` is specialized and optimized for this specific conversion.

## Conclusion

The `F_LINT_TO_UDINT` block is an efficient tool for converting 64-bit signed integer values to 32-bit unsigned integer values. Its simplicity and direct operation make it a reliable component in control applications.