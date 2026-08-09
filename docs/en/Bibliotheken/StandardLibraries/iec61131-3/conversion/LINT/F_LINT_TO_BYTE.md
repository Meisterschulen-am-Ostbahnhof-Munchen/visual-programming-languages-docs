# F_LINT_TO_BYTE

<img width="1230" height="183" alt="F_LINT_TO_BYTE" src="https://github.com/user-attachments/assets/31f5aea5-3ee0-4d1d-83d9-c7897fad2fe4" />
* * * * * * * * * *
## Introduction

The function block `F_LINT_TO_BYTE` converts a LINT data type (64-bit integer) to a BYTE data type (8-bit integer). This block is particularly useful in scenarios where type conversion between these two data types is required.
![F_LINT_TO_BYTE](F_LINT_TO_BYTE.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: Input for the LINT value to be converted.

### **Data Outputs**

- **OUT**: Output for the converted BYTE value.

#### **Adapters**

- No adapters available.

## Functionality

This function block performs the conversion from LINT to BYTE as soon as the event `REQ` is triggered. The conversion is carried out using the function `LINT_TO_BYTE(IN)`, where the value from `IN` is converted to the BYTE type and output to `OUT`. After successful conversion, the event `CNF` is triggered.

## Technical Features

- The function block is a simple algorithm (SimpleFB) and does not perform any complex state transitions.
- Data loss can occur during conversion if the LINT value is outside the representable range of a BYTE (0 to 255).

## State Overview

Since this is a simple function block, there are no state transitions. Execution occurs directly upon triggering `REQ`.

## Application Scenarios

- Type conversion in control applications where LINT data needs to be converted to BYTE data.
- Use in data processing chains where different data types need to be made compatible.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks such as `F_INT_TO_BYTE` or `F_DINT_TO_BYTE` perform similar conversions, but with different output data types.
- `F_LINT_TO_BYTE` is specifically for converting 64-bit to 8-bit integers.

## Conclusion

The `F_LINT_TO_BYTE` function block provides a simple and efficient way to convert LINT data to BYTE data. Its use is essential in type conversion scenarios; however, potential data loss with large values should be considered.