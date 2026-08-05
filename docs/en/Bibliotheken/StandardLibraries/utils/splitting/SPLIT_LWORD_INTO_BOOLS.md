# SPLIT_LWORD_INTO_BOOLS
![SPLIT_LWORD_INTO_BOOLS](https://github.com/user-attachments/assets/1049fa17-3495-4ca5-8e03-ae09e81b47d5)

* * * * * * * * * *
## Introduction
The function block `SPLIT_LWORD_INTO_BOOLS` is used to decompose a 64-bit LWORD data type into its individual bits. Each bit is provided as a separate BOOL output. This block is particularly useful when individual bits of a long word need to be evaluated or processed.
## Interface Structure
### **Event Inputs**
- `REQ` (Event): Starts the decomposition of the LWORD into individual bits. It is linked to the input `IN`.

### **Event Outputs**
- `CNF` (Event): Confirms the successful decomposition of the LWORD. Linked to all 64 BOOL outputs.

### **Data Inputs**
- `IN` (LWORD): The 64-bit word to be split into individual bits.

### **Data Outputs**
- `BIT_00` to `BIT_63` (BOOL): The individual bits of the input LWORD, where `BIT_00` is the least significant bit (LSB) and `BIT_63` is the most significant bit (MSB).

### **Adapters**
No adapters are included.

## Functionality
The function block extracts each bit of the input LWORD (`IN`) and assigns it to the corresponding BOOL outputs. Extraction is performed via direct bit accesses (`IN.%X0` to `IN.%X63`). Upon triggering the `REQ` event, all bits are updated, and the `CNF` event confirms successful processing.

## Technical Features
- Processes 64-bit data (LWORD).
- Each bit is output individually as a BOOL.
- No additional logic or filtering – direct bit mapping.

## State Overview

The block has no internal state. The decomposition is performed anew with each `REQ` event.

## Application Scenarios
- Evaluation of bitmasks or status registers.
- Processing of digital signals encoded as LWORDs.
- Debugging or monitoring individual bits in long data words.

## ⚖️ Comparison with similar blocks
- Similar blocks like `SPLIT_WORD_INTO_BOOLS` or `SPLIT_DWORD_INTO_BOOLS` work with shorter data types (WORD and DWORD, respectively).
- This block is specifically optimized for 64-bit data.

## Conclusion
The `SPLIT_LWORD_INTO_BOOLS` block is an efficient tool for decomposing 64-bit data into individual bits. Its simple and direct operation makes it ideal for applications requiring detailed bit analysis.
