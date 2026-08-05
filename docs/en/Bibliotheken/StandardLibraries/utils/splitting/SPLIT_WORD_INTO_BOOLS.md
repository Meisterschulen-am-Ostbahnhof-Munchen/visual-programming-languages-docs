# SPLIT_WORD_INTO_BOOLS
![SPLIT_WORD_INTO_BOOLS](https://github.com/user-attachments/assets/dc1abe89-3f91-409f-815b-858dcd48d035)
* * * * * * * * * *
## Introduction
The function block `SPLIT_WORD_INTO_BOOLS` is used to decompose a 16-bit word into its individual bits. Each bit of the input word is mapped to a separate BOOL output. This is particularly useful when individual bits of a word need to be further processed or monitored.
## Interface Structure
### **Event Inputs**
- `REQ` (Normal Execution Request): Starts the decomposition of the input word. It is linked to the data input `IN`.

### **Event Outputs**
- `CNF` (Execution Confirmation): Confirms successful word decomposition. Linked to all 16 BOOL outputs.

### **Data Inputs**
- `IN` (WORD): The 16-bit word to be decomposed into individual bits.

### **Data Outputs**
- `BIT_00` to `BIT_15` (BOOL): The individual bits of the input word, where `BIT_00` represents the least significant bit (LSB) and `BIT_15` represents the most significant bit (MSB).

### **Adapters**
- No adapters available.

### **Adapters**

### ## Functionality

The function block parses the input word `IN` into its 16 individual bits and assigns them to the corresponding BOOL outputs. The assignment is done directly via the bit addressing of the WORD data type (e.g., `IN.%X0` for the first bit). When the `REQ` event is triggered, all bits are extracted, and the `CNF` event confirms successful execution.

## Technical Features
- Bit extraction is performed directly via low-level hardware bit addressing, enabling efficient processing.
- The function block is deterministic and has no internal states.

## State Overview
- **Idle**: Waiting for the `REQ` event.
- **Processing**: Parses the word and updates the outputs.
- **Complete`: Löst das `CNF` event and returns to the idle state.

## Application Scenarios
- Processing of digital input signals transmitted as WORDs.
- Decoding of status or control words in control systems.
- Interface between word-based and bit-based system components.

## ⚖️ Comparison with Similar Blocks
- Compared to generic bit manipulation functions, this block offers a specialized and simple interface for decomposing words.
- Similar blocks might support a flexible number of bits, which is not the case here.

## Conclusion
The `SPLIT_WORD_INTO_BOOLS` function block is a simple and efficient block for decomposing 16-bit words into individual bits. It is particularly suitable for applications where clear and direct bit extraction is required.