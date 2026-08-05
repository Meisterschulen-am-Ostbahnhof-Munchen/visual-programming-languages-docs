# F_DWORD_TO_LWORD

<img width="1255" height="181" alt="F_DWORD_TO_LWORD" src="https://github.com/user-attachments/assets/8b697d39-33ef-445c-8626-4e4ece73fda6" />

* * * * * * * * * *
## Introduction
The function block `F_DWORD_TO_LWORD` converts a 32-bit data value (DWORD) to a 64-bit data value (LWORD). This conversion is particularly useful in scenarios where an increase in data width is required to ensure compatibility with subsequent processing steps.

![F_DWORD_TO_LWORD](F_DWORD_TO_LWORD.svg)

## Interface Structure
### **Event Inputs**

- **REQ** (Type: Event): Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF** (Type: Event): Signals the successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (Type: DWORD): The 32-bit input value to be converted to a 64-bit value.

### **Data Outputs**

- **OUT** (Type: LWORD): The resulting 64-bit output value after conversion.

#### **Adapters**
This function block does not have any adapters.

## Functionality
This function block performs the DWORD to LWORD conversion by converting the 32-bit input value (`IN`) to a 64-bit value (`OUT`). The conversion occurs automatically upon receiving an event at input `REQ`. After successful conversion, the event `CNF` is triggered.

## Technical Features
- The function block is implemented as a simple FB (SimpleFB) and uses an ST algorithm for the conversion.

- The conversion is performed without data loss, as the 32-bit value is embedded into the 64-bit value.

## State Overview

The function block has no internal state. The conversion occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Extending the data width for subsequent processing steps.

- Ensuring compatibility between systems that use different data widths.


## ⚖️ Comparison with Similar Function Blocks
- Compared to other conversion blocks (e.g., `F_WORD_TO_DWORD`), this function block is specifically optimized for converting 32-bit to 64-bit values.

- Similar blocks might offer additional features such as scaling or offset adjustment, which is not the case here.

## Conclusion
The `F_DWORD_TO_LWORD` function block is a simple and efficient tool for converting 32-bit to 64-bit values. Its clear interface structure and direct functionality make it ideal for applications that only require data width extension.