# ASSEMBLE_LWORD_FROM_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![ASSEMBLE_LWORD_FROM_QUARTERS](https://github.com/user-attachments/assets/c6bc85a7-e9e1-4464-b725-6d168027e7af)
* * * * * * * * *
## Introduction
The function block `ASSEMBLE_LWORD_FROM_QUARTERS` combines 32 byte values (QUARTER_BYTE_00 to QUARTER_BYTE_31) into a 64-bit LWORD value. This is particularly useful when data is in smaller units and needs to be combined into a larger data word.

## Interface Structure
### **Event Inputs**
- `REQ`: Starts the processing and combines the 32 byte inputs into an LWORD.

### **Event Outputs**
- `CNF`: Signals the successful merging of the bytes into an LWORD.

### **Data Inputs**
- `QUARTER_BYTE_00` to `QUARTER_BYTE_31` (32 inputs of type `BYTE`): The individual byte values that are combined into an LWORD.

### **Data Outputs**
- (Unnamed, type `LWORD`): The combined 64-bit value that is created from the 32 byte inputs.

### **Adapters**
No adapters are present.

## Functionality
The function block receives the 32 byte inputs and combines them into a 64-bit LWORD. Each byte value is shifted to a specific position in the LWORD (using the ``SHL`` operation) and then logically combined with the current LWORD value (``OR`` operation). The shifting is performed according to predefined constants (``quarterconst::SHIFT_QUARTER_XX``) that define the exact position of each byte in the LWORD.

## Technical Features
- Uses bitwise operations (``SHL``, ``OR``) for efficient byte combination.
- The combination order ranges from ``QUARTER_BYTE_31`` (most significant byte) to ``QUARTER_BYTE_00`` (least significant byte).

``` - The function block is implemented in ST (Structured Text) and uses a library (`quarterconst`) for the shift constants.

## State Overview
The function block has no internal states. Processing occurs directly upon receiving the `REQ` event, and the result is immediately output via `CNF`.

## Application Scenarios
- Reassembling data that has been transmitted or stored in smaller units (bytes).
- Processing protocols or data formats that transmit large values in segmented form.
- Use in systems that work with 64-bit data but only have 8-bit interfaces available.

## ⚖️ Comparison with Similar Blocks
- Similar function blocks could be... For example, `ASSEMBLE_DWORD_FROM_BYTES`, which only combines 32-bit values.
- Unlike manual implementations, this function block offers a standardized and optimized solution for combining 32 bytes into a 64-bit LWORD.

## Conclusion
The `ASSEMBLE_LWORD_FROM_QUARTERS` function block provides an efficient and reliable method for combining 32-byte values into a 64-bit LWORD. By using bitwise operations and predefined shift constants, the solution is performant and easily integrated into existing systems. Ideal for applications that work with large, segmented datasets.