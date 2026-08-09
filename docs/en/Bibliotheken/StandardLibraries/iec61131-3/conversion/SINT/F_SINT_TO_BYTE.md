# F_SINT_TO_BYTE

<img width="1439" height="213" alt="F_SINT_TO_BYTE" src="https://github.com/user-attachments/assets/af182d96-472c-4593-8202-182a67b19c5a" />
* * * * * * * * * *
## Introduction

The function block `F_SINT_TO_BYTE` converts a signed 8-bit integer value (SINT) to an unsigned 8-bit integer value (BYTE). This conversion is useful when exchanging data between systems that use different representations for 8-bit values.
![F_SINT_TO_BYTE](F_SINT_TO_BYTE.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at data output `OUT`.

### **Data Inputs**

- **IN** (SINT): The signed 8-bit integer value to be converted.

### **Data Outputs**

- **OUT** (BYTE): The unsigned 8-bit integer value representing the result of the conversion.

#### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion as soon as the event `REQ` is triggered. The value at input `IN`, of type SINT, is converted to a BYTE value and output at `OUT`. The event `CNF` signals the successful completion of the conversion.

## Technical Features

- The conversion is performed directly by the function `SINT_TO_BYTE`.
- The block is simple and deterministic, without internal states or complex logic.

## State Overview

The function block has no internal states. The conversion occurs immediately after `REQ` is triggered, followed by the output of the result and confirmation by `CNF`.

## Application Scenarios

- Communication between systems that use signed and unsigned 8-bit values.
- Data processing in control systems where type conversion is required.
- Integration into larger function block networks that process different data types.

## ⚖️ Comparison with Similar Building Blocks

- Compared to generic conversion blocks, `F_SINT_TO_BYTE` specializes in converting SINT to BYTE and is therefore more efficient for this specific use case.
- Other blocks, such as `F_INT_TO_BYTE` or `F_DINT_TO_BYTE`, are designed for larger integer types.

## Conclusion

The `F_SINT_TO_BYTE` function block is a simple yet effective tool for converting between signed and unsigned 8-bit integers. Its simplicity and determinism make it reliable for applications that require such type conversions.