# F_SINT_TO_LINT

<img width="1434" height="213" alt="F_SINT_TO_LINT" src="https://github.com/user-attachments/assets/87eb573f-d686-40fb-aa1e-1a3c3c21f187" />
* * * * * * * * * *
## Introduction

The function block `F_SINT_TO_LINT` converts a `SINT` value (8-bit integer) to a `LINT` value (64-bit integer). This conversion is useful when processing data with different bit widths.
![F_SINT_TO_LINT](F_SINT_TO_LINT.svg)
## Interface Structure

### **Event Inputs**

- `REQ`: Starts the conversion. This input is connected to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of the conversion. This output is connected to the data output `OUT`.

### **Data Inputs**

- `IN` (`SINT`): The 8-bit integer value to be converted.

### **Data Outputs**

- `OUT` (`LINT`): The converted 64-bit integer value.

### **Adapters**

No adapters are available.

## Functionality

The function block performs a direct assignment of the input value `IN` to the output value `OUT`. Since `LINT` has a larger bit width than `SINT`, the conversion is lossless.

## Technical Features

- The conversion is lossless because the `LINT` data type can represent all possible values of the `SINT` data type.
- The function block is deterministic and has no internal state.

## State Overview

The function block has no internal state. Execution occurs immediately upon receiving the `REQ` event.

## Application Scenarios

- Processing 8-bit sensor data in 64-bit systems
- Compatibility between systems with different bit widths
- Data conversion in automation systems

## ⚖️ Comparison with similar modules

- Compared to other conversion modules (e.g., `F_INT_TO_LINT`), this module specifically works with 8-bit input data.
- Similar to `F_BYTE_TO_LWORD`, but for signed integers.

## Conclusion

The `F_SINT_TO_LINT` function module offers a simple and efficient way to convert 8-bit integers to 64-bit integers. Its simple structure and deterministic operation make it a reliable module in automation solutions.