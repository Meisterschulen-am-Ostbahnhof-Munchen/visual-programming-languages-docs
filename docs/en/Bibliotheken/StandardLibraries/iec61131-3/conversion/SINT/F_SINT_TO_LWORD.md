# F_SINT_TO_LWORD
<img width="1448" height="213" alt="F_SINT_TO_LWORD" src="https://github.com/user-attachments/assets/97fc01cb-6efa-4b3f-9184-c61d04ddc8f4" />
* * * * * * * * * *
## Introduction
The function block `F_SINT_TO_LWORD` converts a signed 8-bit integer value (`SINT`) to an unsigned 64-bit integer value (`LWORD`). This block is part of the `iec61131::conversion` package and is typically used in automation applications where data type conversions are required.
![F_SINT_TO_LWORD](F_SINT_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**
- **REQ** (Normal Execution Request): Starts the execution of the function block. Linked to data input `IN`.

### **Event Outputs**
- **CNF** (Execution Confirmation): Signals completion of the conversion. Linked to data output `OUT`.

### **Data Inputs**
- **IN** (`SINT`): The signed 8-bit integer value to be converted.

### **Data Outputs**
- **OUT** (`LWORD`): The resulting unsigned 64-bit integer value after conversion.

### **Adapters**
This function block does not use adapters.

### **Adapters** ## Functionality

This function block performs the conversion from `SINT` to `LWORD` as soon as the event `REQ` is triggered. The conversion is carried out using the integrated function `SINT_TO_LWORD`. After successful conversion, the event `CNF` is triggered, and the converted value is available at output `OUT`.

## Technical Features
- The conversion is performed without additional parameters or configuration.
- The function block is deterministic and has no internal states.

## State Overview
Since this is a simple function block, there are no state transitions or internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios
- Type conversion in control applications where different data types need to be processed.
- Integration into larger function block networks where data needs to be converted from a lower to a higher precision format.

## ⚖️ Comparison with Similar Function Blocks
- Similar function blocks such as `F_INT_TO_LWORD` or `F_DINT_TO_LWORD` perform conversions from other integer types to `LWORD`. `F_SINT_TO_LWORD` is specifically for converting 8-bit integers.
- Unlike generic conversion blocks, this function block offers a type-safe and optimized solution for this specific conversion.

## Conclusion

The `F_SINT_TO_LWORD` function block offers an efficient and simple way to convert `SINT` values to `LWORD` values. Its deterministic operation and clear interfaces make it ideal for use in automation projects where such type conversions are regularly required.