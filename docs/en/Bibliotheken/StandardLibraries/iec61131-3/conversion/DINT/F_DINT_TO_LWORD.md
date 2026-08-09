# F_DINT_TO_LWORD

<img width="1454" height="217" alt="F_DINT_TO_LWORD" src="https://github.com/user-attachments/assets/2b51d495-a600-44ab-afbf-3f6e94586a86" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_LWORD` converts a 32-bit integer value (DINT) to a 64-bit unsigned integer value (LWORD). This block is particularly useful in scenarios where extending the value range or changing the type is required for subsequent processing steps.
![F_DINT_TO_LWORD](F_DINT_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the function block reads the value at the data input `IN` and performs the conversion.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. Simultaneously, the converted value is output at data output `OUT`.

### **Data Inputs**

- **IN** (DINT): The 32-bit integer value to be converted to a 64-bit unsigned integer value.

### **Data Outputs**

- **OUT** (LWORD): The resulting 64-bit unsigned integer value after the conversion.

### **Adapters**

This function block does not have any adapter interfaces.

## Operation

When event input `REQ` is triggered, the function block's algorithm is activated. This function reads the value at input `IN`, converts it from DINT to LWORD, and stores the result at output `OUT`. The event `CNF` is then triggered to signal the successful completion of the operation.

## Technical Features

- The conversion is performed by directly assigning the DINT value to an LWORD, with the value being extended accordingly.
- The function block is deterministic and performs no additional calculations or checks.

## State Overview

The function block has no internal states. The operation is re-executed with each `REQ` event.

## Application Scenarios

- Extending the value range for subsequent operations that require 64-bit values.
- Type conversion in heterogeneous systems where different data types need to be processed.
- Use in control systems where higher precision or a larger value range is required.

## ⚖️ Comparison with similar function blocks

- Unlike generic conversion function blocks, `F_DINT_TO_LWORD` specializes in converting DINT to LWORD.
- Similar function blocks such as `F_INT_TO_DINT` or `F_LINT_TO_LWORD` offer conversions between other integer types.

## Conclusion

The `F_DINT_TO_LWORD` function block is a simple yet effective function block for converting 32-bit to 64-bit integer values. Its deterministic operation and clear interface make it a reliable component in control and automation solutions.