# F_LREAL_TO_SINT
<img width="1453" height="214" alt="F_LREAL_TO_SINT" src="https://github.com/user-attachments/assets/033b49c4-f1c6-452a-a19e-2b4e91b60282" />
* * * * * * * * * *
## Introduction
The function block `F_LREAL_TO_SINT` converts a `LREAL` value (64-bit floating-point number) to a `SINT` value (8-bit integer count). This conversion is useful when floating-point numbers need to be converted into a compact integer representation, for example, for storage or transmission in systems with limited bandwidth.
![F_LREAL_TO_SINT](F_LREAL_TO_SINT.svg)
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**
- **IN** (`LREAL`): The input value to be converted.

### **Data Outputs**
- **OUT** (`SINT`): The converted output value.

### **Adapters**
No adapters are present.

## Functionality
The function block performs the conversion as soon as the event `REQ` is received. The `LREAL` value at input `IN` is converted into a `SINT` value and output as `OUT`. The `CNF` event signals the completion of the conversion.

## Technical Features
- The conversion is performed by the function `LREAL_TO_SINT`, which converts the `LREAL` value into a `SINT` value.
- This is a simple function block without state management or complex logic.

## State Overview

The function block has no internal states. The conversion is re-executed with each `REQ` event.

## Application Scenarios
- Conversion of floating-point numbers to integers for storage in limited memory areas.
- Use in control systems where floating-point numbers need to be converted into compact integer formats.
- Integration into data processing chains where data width reduction is required.

## ⚖️ Comparison with Similar Function Blocks
- **F_REAL_TO_SINT**: Converts `REAL` (32-bit floating-point number) to `SINT`. Compared to `F_LREAL_TO_SINT`, this method processes input data with lower precision.
- **F_LREAL_TO_INT**: Converts `LREAL` to `INT` (16-bit integer). Offers a wider output width compared to `F_LREAL_TO_SINT`.

## Conclusion
The `F_LREAL_TO_SINT` function block is a simple and efficient tool for converting 64-bit floating-point numbers to 8-bit integers. Its simple interface and direct operation make it ideal for applications where space or bandwidth limitations are a concern.