# ASSEMBLE_WORD_FROM_BOOLS
![ASSEMBLE_WORD_FROM_BOOLS](https://github.com/user-attachments/assets/0f9e88ae-3645-4364-a8e7-183caf4f1bb0)
* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_WORD_FROM_BOOLS` combines 16 Boolean input values into a single WORD output value. Each Boolean input represents a single bit in the resulting WORD.
## Interface Structure
### **Event Inputs**
- `REQ`: Starts processing and takes all current values from the Boolean inputs.

### **Event Outputs**
- `CNF`: Signals the successful combination of the Boolean values into a WORD.

### **Data Inputs**

16 Boolean inputs (BIT_00 to BIT_15), each corresponding to one bit in the resulting WORD:

- `BIT_00` to `BIT_15` (BOOL): Individual bits for the WORD to be assembled

### **Data Outputs**
- `(Unbenannt)` (WORD): The resulting WORD, assembled from the 16 Boolean inputs.

### **Adapters**
No adapters are available.

## Operation
When the `REQ` event is triggered, all 16 Boolean input values are read and combined into a 16-bit WORD. Here, the following correspond to:

- `BIT_00` corresponds to bit 0 (LSB)
- `BIT_15` corresponds to bit 15 (MSB)

The assignment is performed directly via bitwise operations, where each Boolean input value is mapped to the corresponding bit in the WORD.

## Technical Features
- The bit order is fixed (BIT_00 = LSB, BIT_15 = MSB)
- The block does not perform any additional calculations or transformations
- The operation is atomic and occurs in one step

## State Overview
1. **Idle**: Waits for the `REQ` event
2. **Processing**: Processes the inputs and assembles the WORD
3. **Output**: Sends `CNF` with the resulting WORD

## Application Scenarios
- Combining individual switching states into a compact data word
- Preparing data for communication with devices that expect WORD data
- Bitwise control of hardware registers

## ⚖️ Comparison with Similar Function Blocks
- Unlike general combination blocks, this function block is specifically optimized for converting BOOL to WORD
- Offers a more direct and efficient Solution than using multiple individual blocks
- Similar to BIT_TO_* blocks, but with a fixed 16-bit WORD output

## Conclusion
The `ASSEMBLE_WORD_FROM_BOOLS` function block provides an efficient and direct method to convert 16 Boolean signals into a single WORD. Its simple and deterministic operation makes it particularly suitable for applications where individual bits need to be combined into compact data words.