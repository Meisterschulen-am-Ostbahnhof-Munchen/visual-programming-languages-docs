# F_LWORD_TO_LREAL

<img width="1464" height="211" alt="F_LWORD_TO_LREAL" src="https://github.com/user-attachments/assets/89f93d44-7207-4ef1-ba65-ed61f446770f" />
* * * * * * * * * *
## Introduction

The function block `F_LWORD_TO_LREAL` converts an LWORD data value (64-bit unsigned integer) to an LREAL data value (64-bit floating-point number according to IEEE 754). This block is particularly useful in applications where direct type conversion between these two data types is required.
![F_LWORD_TO_LREAL](F_LWORD_TO_LREAL.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. The input value `IN` is processed upon this event.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion and outputs the converted value `OUT`.

### **Data Inputs**

- **IN** (LWORD): The input value to be converted.

### **Data Outputs**

- **OUT** (LREAL): The result of the conversion.

### **Adapters**

This function block has no adapters.

## Operation

When the `REQ` event is triggered, the algorithm that converts the `IN` value of type LWORD to an LREAL value is executed. The result is output via the `OUT` output, and the `CNF` event signals successful conversion.

## Technical Features

- The conversion is performed directly without additional parameters.
- The function block is optimized for use in real-time systems.

## State Overview

The function block has a simple state machine:

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Performs the conversion.
3. **Complete**: Sends the `CNF` event with the result.

## Application Scenarios

- Data processing in control systems where LWORD values need to be converted to floating-point numbers.
- Integration into larger function block networks that process mixed data types.

## ⚖️ Comparison with similar blocks

- Similar blocks such as `F_DWORD_TO_REAL` or `F_WORD_TO_REAL` offer conversions for smaller data types.
- `F_LWORD_TO_LREAL` is specifically optimized for 64-bit conversions.

## Conclusion

The `F_LWORD_TO_LREAL` function block is an efficient tool for directly converting 64-bit integers to floating-point numbers. Its simple interface and reliable operation make it ideal for use in complex automation solutions.