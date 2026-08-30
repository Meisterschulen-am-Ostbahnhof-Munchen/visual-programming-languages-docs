# SPLIT_WORD_INTO_BOOLS

![SPLIT_WORD_INTO_BOOLS](https://github.com/user-attachments/assets/dc1abe89-3f91-409f-815b-858dcd48d035)

* * * * * * * * * *
The function block `SPLIT_WORD_INTO_BOOLS` is used to decompose a 16-bit word into its individual bits. Each bit of the input word is mapped to a separate BOOL output. This is particularly useful when individual bits of a word need to be further processed or monitored.

- `REQ` (Normal Execution Request): Starts the decomposition of the input word. It is linked to the data input `IN`.
- `CNF` (Execution Confirmation): Confirms successful word decomposition. Linked to all 16 BOOL outputs.
- `IN` (WORD): The 16-bit word to be decomposed into individual bits.
- `BIT_00` to `BIT_15` (BOOL): The individual bits of the input word, where `BIT_00` represents the least significant bit (LSB) and `BIT_15` represents the most significant bit (MSB).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- No adapters available.


The function block parses the input word `IN` into its 16 individual bits and assigns them to the corresponding BOOL outputs. The assignment is done directly via the bit addressing of the WORD data type (e.g., `IN.%X0` for the first bit). When the `REQ` event is triggered, all bits are extracted, and the `CNF` event confirms successful execution.

- Bit extraction is performed directly via low-level hardware bit addressing, enabling efficient processing.
- The function block is deterministic and has no internal states.
- **Idle**: Waiting for the `REQ` event.
- **Processing**: Parses the word and updates the outputs.
- **Complete`: Löst das `CNF` event and returns to the idle state.
- Processing of digital input signals transmitted as WORDs.
- Decoding of status or control words in control systems.
- Interface between word-based and bit-based system components.
- Compared to generic bit manipulation functions, this block offers a specialized and simple interface for decomposing words.
- Similar blocks might support a flexible number of bits, which is not the case here.

The `SPLIT_WORD_INTO_BOOLS` function block is a simple and efficient block for decomposing 16-bit words into individual bits. It is particularly suitable for applications where clear and direct bit extraction is required.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion
