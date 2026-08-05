# SPLIT_LWORD_INTO_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![SPLIT_LWORD_INTO_QUARTERS](https://github.com/user-attachments/assets/673b8e11-a630-41ed-ab74-5c16e3fe349b)
* * * * * * * * * *
## Introduction
The function block `SPLIT_LWORD_INTO_QUARTERS` extracts the 32 quarter bytes (8 bits each) from a 64-bit LWORD. This allows for the targeted processing of individual byte segments within a long word.

## Interface Structure

### **Event Inputs**
- `REQ`: Starts processing the input value `IN`.

### **Event Outputs**
- `CNF`: Confirms successful processing and returns all 32 quarter bytes.

### **Data Inputs**
- `IN` (LWORD): The 64-bit input word to be split into quarter bytes.

### **Data Outputs**

32 outputs of type BYTE:

- `QUARTER_BYTE_00` to `QUARTER_BYTE_31`: The extracted 8-bit segments of the input word.

### **Adapters**
No adapters available.

#
## **Adapters** ## Functionality

The function block uses bitwise operations (AND and right shift) in combination with constants (`quarterconst::LWORD_QUARTER_xx` and `quarterconst::SHIFT_QUARTER_xx`) to isolate each of the 32 quarter bytes from the input LWORD. Each quarter byte is then written to a separate BYTE output.

```
## Technical Features
- Uses special bitmasks and shift constants for precise extraction
- Works with the largest IEC data type, LWORD (64-bit)
- Delivers all 32 quarter bytes in parallel in a single pass

## State Overview
1. **Idle**: Waits for REQ event
2. **Processing**: Extracts all quarter bytes
3. **Output**: Triggers CNF event with all output values

## Application Scenarios
- Processing long data words in communication protocols
- Extracting individual parameters from packed data structures
- Bitwise analysis of sensor or control data

## ⚖️ Comparison with Similar Function Blocks
- Unlike simple BYTE extraction blocks, this function block can process all 32 segments simultaneously
- More efficient than multiple cascaded extraction blocks
- Specialized in processing LWORD data types

## Conclusion
The The `SPLIT_LWORD_INTO_QUARTERS` function block offers a highly optimized solution for splitting 64-bit words into their individual byte components. Its parallel processing of all segments makes it particularly suitable for applications requiring efficient processing of large data words.
