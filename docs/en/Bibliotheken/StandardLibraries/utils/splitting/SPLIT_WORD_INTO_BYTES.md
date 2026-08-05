# SPLIT_WORD_INTO_BYTES
![SPLIT_WORD_INTO_BYTES](https://github.com/user-attachments/assets/5c99635d-3f7d-4266-a108-12d075d58313)

* * * * * * * * * *
## Introduction
The function block `SPLIT_WORD_INTO_BYTES` is used to split a 16-bit word (WORD) into its two 8-bit bytes. This is particularly useful when working with data that is transmitted as a WORD but needs to be processed byte by byte.
## Interface Structure
### **Event Inputs**
- **REQ**: Starts the execution of the function block. When this event input is triggered, processing of the input value `IN` begins.

### **Event Outputs**
- **CNF**: Signals the successful completion of processing. This event is triggered along with the two output bytes `BYTE_00` and `BYTE_01`.

### **Data Inputs**
- **IN**: The 16-bit word (WORD) to be split into two bytes.

### **Data Outputs**
- **BYTE_00**: The least significant byte (bits 0 to 7) of the input word `IN`.
- **BYTE_01**: The most significant byte (bits 8 to 15) of the input word `IN`.

### **Adapters**
No adapters available.

#
## **Adapters** ## Functionality

The function block extracts the two bytes from the input word `IN` and outputs them via the outputs `BYTE_00` (lower-order byte) and `BYTE_01` (higher-order byte). Extraction is performed by direct access to the bytes of the WORD data type (`IN.%B0` for the lower-order byte and `IN.%B1` for the higher-order byte).

## Technical Features
- The function block is implemented in the ST (Structured Text) programming language.
- Processing occurs synchronously with the triggering of the `REQ` event.
- The bytes are output along with the `CNF` event.

## State Overview

1. **Idle State**: Waiting for the `REQ` event.

2. **Processing State**: When `REQ` is triggered, the bytes are extracted.

3. **Output State**: The extracted bytes are output with the `CNF` event, and the block returns to the idle state.

## Application Scenarios
- **Data Communication**: When processing network data transmitted as WORDs but requiring byte-by-byte interpretation.
- **Low-Hardware Programming**: When working with register contents read as WORDs but containing individual bytes.
- **Data Conversion**: When converting WORD data into two separate BYTE data for further processing.

## ⚖️ Comparison with Similar Building Blocks
- Compared to generic extraction functions, `SPLIT_WORD_INTO_BYTES` offers a specialized and optimized solution for splitting WORD data into bytes.
- Other building blocks might offer additional features such as sign handling or bit extraction, but are less efficient for this specific task.

## Conclusion
The `SPLIT_WORD_INTO_BYTES` function block is a simple yet effective building block for splitting 16-bit words into their individual bytes. Its clear interface and efficient implementation make it ideal for applications requiring this functionality.
