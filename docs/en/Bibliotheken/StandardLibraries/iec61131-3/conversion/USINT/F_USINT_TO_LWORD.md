# F_USINT_TO_LWORD

<img width="1466" height="214" alt="F_USINT_TO_LWORD" src="https://github.com/user-attachments/assets/1a7fa270-9594-45e3-be4d-fb8e84a64db2" />
* * * * * * * * * *
## Introduction

The function block `F_USINT_TO_LWORD` converts a `USINT` value (8-bit unsigned integer) to a `LWORD` value (64-bit unsigned integer). This conversion is useful when processing data with different bit lengths, especially in systems that require a uniform data width.
![F_USINT_TO_LWORD](F_USINT_TO_LWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. When this input is triggered, the value at the data input `IN` is read and converted.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. The converted value is available at the data output `OUT`.

### **Data Inputs**

- **IN**: Expects a `USINT` value (8-bit unsigned integer) to be converted.

### **Data Outputs**

- **OUT**: Returns the converted `LWORD` value (64-bit unsigned integer).

### **Adapters**

This function block has no adapter interfaces.

## Operation

The function block performs the conversion as soon as the `REQ` event is triggered. The algorithm reads the value of ``IN``, converts it from ``USINT`` to ``LWORD``, and provides the result to ``OUT``. The ``CNF`` event is then triggered to signal the successful completion of the operation.

## Technical Features

- The conversion is lossless because the ``USINT`` value is converted to the larger ``LWORD`` type.
- The function block is deterministic and has no internal state.

## State Overview

The function block has no internal state. Execution is purely event-driven, triggered by the ``REQ`` event.

## Application Scenarios

- Data conversion in control systems where different data widths need to be processed.
- Integration into larger function block networks that require a uniform data width.

## ⚖️ Comparison with Similar Blocks

- Compared to other conversion blocks (e.g., `F_INT_TO_LWORD`), this one is specifically optimized for converting 8-bit unsigned integers.
- Similar blocks might offer additional features such as scaling or error handling, but this block is limited to pure conversion.

## Conclusion

The `F_USINT_TO_LWORD` function block is a simple and efficient block for converting 8-bit unsigned integers to 64-bit unsigned integers. Its simplicity and determinism make it a reliable component in control systems.
