# ASSEMBLE_WORD_FROM_BYTES

![ASSEMBLE_WORD_FROM_BYTES](https://github.com/user-attachments/assets/7ddc020d-4826-42e2-8447-7ba0fcfd215a)

* * * * * * * * * *
## Introduction

The function block `ASSEMBLE_WORD_FROM_BYTES` combines two byte values into a single word (WORD). This is particularly useful when data from two separate byte sources needs to be concatenated into a single 16-bit value.
## Interface Structure

### **Event Inputs**

- **REQ**: Starts processing. The input data `BYTE_00` and `BYTE_01` are passed with this event.

### **Event Outputs**

- **CNF**: Signals successful merging of the bytes into a WORD.

### **Data Inputs**

- **BYTE_00**: The least significant byte (LSB) of the resulting WORD.
- **BYTE_01**: The most significant byte (MSB) of the resulting WORD.

### **Data Outputs**

- **(no name)**: The resulting WORD, composed of `BYTE_00` (LSB) and `BYTE_01` (MSB).

### **Adapters**

No adapters are used.

## Functionality

The function block combines the two input bytes `BYTE_00` and `BYTE_01` into a 16-bit WORD. The least significant byte (LSB) is `BYTE_00` and the most significant byte (MSB) is `BYTE_01`. The operation occurs immediately after the `REQ` event arrives, and the result is output with the `CNF` event.

## Technical Features

- The concatenation is performed directly by assigning the bytes to the corresponding positions in the WORD.
- The block is optimized for use in real-time systems and has a deterministic runtime.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Processes the input data and creates the WORD.
3. **Output**: Sends the `CNF` event along with the resulting WORD.

## Application Scenarios

- Combining sensor values stored as separate bytes.
- Processing communication protocols where data is transmitted in byte pairs.
- General data manipulation in control systems.

## ⚖️ Comparison with Similar Blocks

- Compared to generic computing blocks, `ASSEMBLE_WORD_FROM_BYTES` is specialized and more efficient for this specific task.
- Similar blocks might offer additional features such as byte swapping or error handling, but they are more complex.

## Conclusion

The `ASSEMBLE_WORD_FROM_BYTES` function block is a simple and efficient block for combining two bytes into a WORD. It is particularly suitable for applications where performance and simplicity are paramount.
