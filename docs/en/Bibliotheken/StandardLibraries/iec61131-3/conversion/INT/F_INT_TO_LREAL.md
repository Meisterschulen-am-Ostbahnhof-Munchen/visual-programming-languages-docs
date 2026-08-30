# F_INT_TO_LREAL

<img width="1232" height="182" alt="F_INT_TO_LREAL" src="https://github.com/user-attachments/assets/c99ad1d4-dafe-40fc-9bc4-7515768ec888" />
* * * * * * * * * *
## Introduction

The function block `F_INT_TO_LREAL` converts an integer value (INT) into a 64-bit floating-point number (LREAL). This block is particularly useful in applications where type conversion between these two data types is required.
![F_INT_TO_LREAL](F_INT_TO_LREAL.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `INT`, which is to be converted to a value of `LREAL`.

### **Data Outputs**

- **OUT**: The output value of type `LREAL`, which contains the result of the conversion.

### **Adapters**

- No adapters are available.

## Functionality

The function block performs the conversion by directly assigning the integer input value `IN` to the floating-point output value `OUT`. The conversion occurs automatically when an event arrives at the `REQ` input. After the conversion is complete, the `CNF` event is triggered.

## Technical Features

- The conversion is performed without additional parameters or configuration.
- The function block is optimized for use in the 4diac IDE and supports real-time processing.

## State Overview

1. **Idle State**: Waits for a `REQ` event.
2. **Conversion State**: Performs the type conversion.
3. **Acknowledge State**: Sends the `CNF` event and returns to the idle state.

## Application Scenarios

- Type conversion in control applications requiring floating-point operations.
- Integration into larger control systems that process mixed data types.

## ⚖️ Comparison with Similar Function Blocks

- Compared to generic conversion blocks, `F_INT_TO_LREAL` specializes in converting `INT` to `LREAL` and is therefore more efficient at this specific task.
- Other function blocks might offer additional features such as scaling or range checking, which is not the case here.

## Conclusion

The `F_INT_TO_LREAL` function block is a simple and efficient building block for converting integer values to floating-point numbers. Its simplicity and direct operation make it a reliable choice for basic type conversions in automation technology.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
