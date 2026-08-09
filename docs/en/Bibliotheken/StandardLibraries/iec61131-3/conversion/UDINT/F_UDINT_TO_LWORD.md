# F_UDINT_TO_LWORD

<img width="1462" height="216" alt="F_UDINT_TO_LWORD" src="https://github.com/user-attachments/assets/b952fbc8-443f-43ff-9840-5f002a169f93" />
* * * * * * * * * *
## Introduction

The function block `F_UDINT_TO_LWORD` converts a 32-bit unsigned integer value (UDINT) to a 64-bit unsigned integer value (LWORD). This block is particularly useful in scenarios where an extension of the data bit width is required.
![F_UDINT_TO_LWORD](F_UDINT_TO_LWORD.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- **IN**: The input for the UDINT value to be converted.

### **Data Outputs**

- **OUT**: The output for the converted LWORD value.

#### **Adapters**

No adapters are present.

## Functionality

The function block performs the UDINT to LWORD conversion by expanding the incoming 32-bit value to a 64-bit value. The conversion occurs each time the `REQ` event occurs and is confirmed by the `CNF` event.

## Technical Features

- The function block uses the built-in function `UDINT_TO_LWORD` for the conversion.
- This is a simple function block without a state machine or complex logic.

## State Overview

Because it is a simple function block, there are no state transitions or internal states.

## Application Scenarios

- Extending data widths in control systems.
- Compatibility with systems that use different bit widths.
- Data processing in industrial automation solutions.

## ⚖️ Comparison with Similar Blocks

Compared to other conversion blocks such as `F_DINT_TO_LWORD` or `F_UINT_TO_LWORD`, this one is specifically optimized for converting UDINT to LWORD. It offers a direct and efficient solution for this specific conversion.

## Conclusion

The `F_UDINT_TO_LWORD` function block is a simple and efficient building block for converting 32-bit unsigned integer values to 64-bit unsigned integer values. Its clear interface structure and simple functionality make it a reliable component in industrial automation solutions.