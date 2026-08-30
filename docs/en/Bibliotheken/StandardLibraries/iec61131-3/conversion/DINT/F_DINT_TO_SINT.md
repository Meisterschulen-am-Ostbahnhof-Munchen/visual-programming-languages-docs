# F_DINT_TO_SINT

<img width="1437" height="217" alt="F_DINT_TO_SINT" src="https://github.com/user-attachments/assets/a19ea1e6-6fc7-492c-8a92-09e3466d0f6c" />
* * * * * * * * * *
## Introduction

The function block `F_DINT_TO_SINT` converts a 32-bit integer value (DINT) to an 8-bit integer value (SINT). This block is particularly useful in scenarios where type conversion between integer data types of different sizes is required.
![F_DINT_TO_SINT](F_DINT_TO_SINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the conversion. It is associated with the input value `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. Returns the converted value via `OUT`.

### **Data Inputs**

- **IN** (DINT): The 32-bit integer value to be converted.

### **Data Outputs**

- **OUT** (SINT): The resulting 8-bit integer value after conversion.

#### **Adapters**

- No adapters available.

## Functionality

This function block performs the conversion from `DINT` to `SINT` as soon as the event `REQ` is triggered. The algorithm uses the built-in function `DINT_TO_SINT` to perform the conversion. After successful conversion, the event `CNF` is output with the result `OUT`.

## Technical Features

- **Type Conversion**: Conversion can lead to data loss if the original `DINT` value is outside the representable range of `SINT` (-128 to 127).
- **Simple Implementation**: The function block is implemented as a simple function block (SimpleFB) without internal states.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- **Data Reduction**: When only the lower 8 bits of a 32-bit value are relevant.
- **Compatibility**: Adapting values for systems or components that can only process `SINT`.
- **Logging**: Memory-optimized storage of values where the higher bits are not needed.

## ⚖️ Comparison with similar function blocks

- **F_INT_TO_SINT**: Similar function block, but for 16-bit to 8-bit conversion.
- **F_ANY_TO_<Typ>**: Generic conversion function blocks that are more flexible but potentially less efficient.

## Conclusion

The `F_DINT_TO_SINT` function block provides a simple and efficient way to convert 32-bit integers to 8-bit integers. Its use is particularly useful in resource-constrained environments or when adapting data types between different system components. However, be aware of the potential for data loss with large input values.
