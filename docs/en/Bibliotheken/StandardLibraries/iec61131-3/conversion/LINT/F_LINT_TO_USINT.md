# F_LINT_TO_USINT

<img width="1448" height="214" alt="F_LINT_TO_USINT" src="https://github.com/user-attachments/assets/847133a9-041d-466e-af83-f73ad8337642" />
* * * * * * * * * *
## Introduction

The function block `F_LINT_TO_USINT` converts a 64-bit integer value (`LINT`) into an 8-bit unsigned integer value (`USINT`). This block is part of the IEC 61131 conversion library and is typically used in automation applications where data types of different sizes need to be processed.
![F_LINT_TO_USINT](F_LINT_TO_USINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN** (`LINT`): The 64-bit integer value to be converted.

### **Data Outputs**

- **OUT** (`USINT`): The resulting 8-bit unsigned integer value after the conversion.

### **Adapters**

No adapters are present.

## Operation

The function block performs the conversion when the event `REQ` is triggered. The value of ``IN`` of type ``LINT`` is converted to type ``USINT``, and the result is output to ``OUT``. The conversion is confirmed by the event ``CNF``.

## Technical Features

- The conversion truncates higher-order bits if the value of ``LINT`` is outside the representable range of ``USINT`` (0 to 255).
- The block is deterministic and has no internal state.

## State Overview

The function block has no internal state. Execution occurs immediately after receiving the ``REQ`` event.

## Application Scenarios

- Conversion of sensor values or counters stored as `LINT` for processing in systems that only support `USINT`.
- Use in control systems where memory optimization is crucial.

## ⚖️ Comparison with Similar Blocks

- Similar conversion blocks like `F_INT_TO_USINT` or `F_DINT_TO_USINT` operate with smaller input data types (`INT` and `DINT`, respectively).
- Unlike generic conversion blocks, `F_LINT_TO_USINT` specializes in converting `LINT` to `USINT`.

## Conclusion

The `F_LINT_TO_USINT` function block is a specialized and efficient tool for converting 64-bit integers to 8-bit unsigned values. Its simple and deterministic operation makes it reliable in automation applications.
