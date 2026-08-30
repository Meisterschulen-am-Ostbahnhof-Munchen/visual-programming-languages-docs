# SPLIT_BYTE_INTO_BOOLS

![SPLIT_BYTE_INTO_BOOLS](https://github.com/user-attachments/assets/666a1be8-3ac9-4da7-b5ab-b11513e98c9c)

* * * * * * * * * *
## Introduction

The function block `SPLIT_BYTE_INTO_BOOLS` is used to split a byte into its individual bits and output them as separate BOOL values. This is particularly useful when working with hardware that evaluates or sets individual bits of a byte.
## Interface Structure

### **Event Inputs**

- **REQ**: Starts the execution of the function block. When this event is triggered, the bits of the current byte value are evaluated at `IN`.

### **Event Outputs**

- **CNF**: Confirms the execution of the function block. This event is triggered after all bits have been evaluated and forwarded to the corresponding outputs.

### **Data Inputs**

- **IN**: The byte to be split into its individual bits. The data type is `BYTE`.

### **Data Outputs**

- **BIT_00** to **BIT_07**: The individual bits of the byte, where `BIT_00` represents the least significant bit (LSB) and `BIT_07` represents the most significant bit (MSB). The data type of all outputs is `BOOL`.

### **Adapters**

This function block does not use adapters.

## Operation

This function block splits the incoming byte `IN` into its 8 bits and assigns them to the corresponding BOOL outputs. Each bit is extracted directly from the byte and output as a separate BOOL value. Evaluation occurs with each `REQ` event.

## Technical Features

- Bit extraction is performed directly via the access notation `IN.%X0` to `IN.%X7`, enabling efficient and fast processing.
- The function block is implemented in the ST (Structured Text) programming language.

## State Overview

The function block has no internal states. Execution occurs immediately upon receiving the `REQ` event, and the results are immediately available via the `CNF` event and the data outputs.

## Application Scenarios

- **Hardware Control**: When controlling digital inputs and outputs organized as bytes, individual bits can be easily evaluated.
- **Data Processing**: When processing byte data where individual bits have a specific meaning (e.g., status flags).

## ⚖️ Comparison with Similar Blocks

- Compared to generic bit manipulation functions, this block offers a specialized and simple solution for decomposing a byte into bits.
- Other blocks might require more complex operations such as bit shifts or masks, while this block enables direct bit extraction.

## 🛠️ Related Exercises

- [Exercise_053](../../../../Uebungen/test_B/Uebungen_doc/Uebung_053.md)

## Conclusion

The `SPLIT_BYTE_INTO_BOOLS` function block is a simple and efficient tool for decomposing a byte into its individual bits. It is particularly suitable for applications requiring fast and direct bit extraction. Its clear interface and simple operation make it easy to integrate into existing systems.
