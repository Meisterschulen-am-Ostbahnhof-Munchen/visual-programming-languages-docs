# F_USINT_TO_WORD

<img width="1454" height="214" alt="F_USINT_TO_WORD" src="https://github.com/user-attachments/assets/a587789a-c16b-4b4c-a09f-643a2e300dcf" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_WORD` converts an unsigned 8-bit integer value (USINT) into a 16-bit word value (WORD). This conversion is particularly necessary in scenarios where data with different bit widths needs to be processed or transmitted.
![F_USINT_TO_WORD](F_USINT_TO_WORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (USINT): The unsigned 8-bit integer value to be converted.

### **Data Outputs**

- **OUT** (WORD): The resulting 16-bit word value after conversion.

#### **Adapters**

- No adapters are present.

## Functionality

The function block performs the conversion by taking the USINT value from `IN` and converting it to a WORD value. This is done by direct assignment using the function `USINT_TO_WORD(IN)`. The conversion is triggered by the event `REQ` and acknowledged by `CNF`.

## Technical Features

- The conversion is lossless, as a USINT (0-255) can be easily converted into a WORD (0-65535).
- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. Execution is purely event-driven:

1. The conversion is performed upon receipt of `REQ`.
2. Upon completion, `CNF` is triggered.

## Application Scenarios

- Data preparation for communication protocols that expect WORD data.
- Integration of sensor data in USINT format into systems that process WORD.
- General type conversion in automation applications.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_USINT_TO_WORD` is specialized and optimized for the specific conversion of USINT to WORD.
- Other blocks might offer additional features such as scaling or error handling, but they are more complex.

## Conclusion

The `F_USINT_TO_WORD` function block is a simple and efficient building block for the specific conversion of USINT to WORD. Its simplicity and determinism make it a reliable choice in scenarios that require this conversion.
