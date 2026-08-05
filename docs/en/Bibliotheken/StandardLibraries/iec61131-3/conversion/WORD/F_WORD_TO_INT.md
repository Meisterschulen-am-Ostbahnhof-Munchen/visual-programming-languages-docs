# F_WORD_TO_INT

<img width="1423" height="214" alt="F_WORD_TO_INT" src="https://github.com/user-attachments/assets/49dc7b5b-d691-45f0-963a-7e6af1509e72" />

* * * * * * * * * *
## Introduction
The function block `F_WORD_TO_INT` converts a `WORD` data type to a `INT` data type. It is part of the `iec61131::conversion` package and enables simple and efficient type conversion within IEC 61131-3-based control systems.

![F_WORD_TO_INT](F_WORD_TO_INT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the conversion. This event input is linked to the data input `IN`.


### **Event Outputs**

- **CNF**: Signals the completion of the conversion. This event output is linked to the data output `OUT`.

### **Data Inputs**

- **IN**: The input of type `WORD`, which is to be converted to a `INT` value.

### **Data Outputs**

- **OUT**: The output of type `INT`, which contains the result of the conversion.

### **Adapters**

- No adapters are present.

## Operation
The function block performs the conversion as soon as the event `REQ` is triggered. The conversion is performed using the function ``WORD_TO_INT``, which converts the value of input ``IN`` to a value of ``INT`` and passes the result to output ``OUT``. Upon completion of the conversion, the event ``CNF`` is triggered.

## Technical Features
- The function block is a simple function block (``SimpleFB``) and uses an ST algorithm for the conversion.

- The conversion is performed directly and without any additional delay.

## State Overview

The function block has no internal states. The conversion is re-executed with each ``REQ`` event.


## Application Scenarios

- Type conversion in control applications where `WORD` data needs to be converted to `INT` data.

- Integration into larger control systems that require type compatibility.

## ⚖️ Comparison with Similar Blocks

- Similar function blocks could be `F_BYTE_TO_INT` or `F_DWORD_TO_INT`, but these convert different data types.

- Unlike more complex conversion blocks, `F_WORD_TO_INT` offers a simple and direct solution for the specific conversion of `WORD` to `INT`.


## Conclusion

The `F_WORD_TO_INT` function block is an efficient and easy-to-use tool for type conversion in IEC 61131-3-based systems. Its clear interface and direct operation make it ideal for applications requiring fast and reliable conversion.