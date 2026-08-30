# F_BYTE_TO_LWORD

<img width="1245" height="182" alt="F_BYTE_TO_LWORD" src="https://github.com/user-attachments/assets/c56c9f09-1174-475c-ad6f-123ba7f3aa49" />
* * * * * * * * * *
## Introduction

The function block `F_BYTE_TO_LWORD` converts a `BYTE` value to a `LWORD` value. It is part of the `iec61131::conversion` library and enables simple and efficient type conversion.
![F_BYTE_TO_LWORD](F_BYTE_TO_LWORD.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. This input is linked to the data input `IN`.

### **Event Outputs**

- **CNF**: Signals the successful completion of the conversion. The output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input value of type `BYTE` to be converted.

### **Data Outputs**

- **OUT**: The output value of type `LWORD`, containing the result of the conversion.

#### **Adapters**

- No adapters are available.

## Functionality

Upon receiving an incoming `REQ` event, the function block converts the `BYTE` value at input `IN` to a `LWORD` value. The result is output at `OUT` and confirmed by a `CNF` event.

## Technical Features

- The function block uses the `BYTE_TO_LWORD` function for conversion.
- It is a simple function block without a state machine.

## State Overview

Since it is a simple function block, there are no state transitions. The conversion occurs directly upon a `REQ` event.

## Application Scenarios

- Type conversion in control applications where `BYTE` values need to be converted to `LWORD` values.
- Use in data processing chains where different data types are processed.

## ⚖️ Comparison with Similar Function Blocks

- Similar function blocks are `F_WORD_TO_LWORD` or `F_DWORD_TO_LWORD`, which convert other data types.
- Unlike more complex conversion blocks, `F_BYTE_TO_LWORD` offers a simple and direct solution for the specific conversion of `BYTE` to `LWORD`.

## Conclusion

The `F_BYTE_TO_LWORD` function block is an efficient and simple solution for converting `BYTE` to `LWORD` values. Its clear interface structure and direct functionality make it ideal for use in control applications.
