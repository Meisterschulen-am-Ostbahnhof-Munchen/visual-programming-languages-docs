# F_UINT_TO_ULINT

<img width="1454" height="216" alt="F_UINT_TO_ULINT" src="https://github.com/user-attachments/assets/ac28f9ed-ea55-4491-af81-a80502951c42" />

* * * * * * * * * *
## Introduction
The function block `F_UINT_TO_ULINT` converts an unsigned 16-bit integer value (`UINT`) into an unsigned 64-bit integer value (`ULINT`). This conversion is particularly necessary when exchanging values between systems with different word widths.

![F_UINT_TO_ULINT](F_UINT_TO_ULINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `UINT` to be converted.

### **Data Outputs**

- **OUT**: The converted output value of type `ULINT`.

### **Adapters**
No adapters are available.

## Functionality
This function block performs a direct conversion of the input value `IN` of type `UINT` to the output value `OUT` of type `ULINT`. The conversion occurs without changing the numerical value; only the data type is extended.

## Technical Features

- The conversion is lossless because the `ULINT` type covers a larger range of values than `UINT`.

- The function block is deterministic and has no internal states.

## State Overview

The function block has no internal states. The conversion occurs immediately upon receiving the `REQ` event.


## Application Scenarios

- Integration of systems with different word widths
- Data processing in controllers that need to handle both 16-bit and 64-bit data
- Data extension for subsequent calculations requiring higher precision

## ⚖️ Comparison with similar function blocks

- Unlike `F_INT_TO_LINT`, this function block processes unsigned data types

- Similar conversion function blocks exist for other data type combinations (e.g., `F_BYTE_TO_WORD`)

## Conclusion
The `F_UINT_TO_ULINT` function block offers a simple and efficient way to convert 16-bit unsigned integers to 64-bit unsigned integers. Its simple structure and deterministic operation make it a reliable function block for systems with mixed word widths.