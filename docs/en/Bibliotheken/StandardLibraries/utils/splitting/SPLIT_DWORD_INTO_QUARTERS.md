# SPLIT_DWORD_INTO_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![SPLIT_DWORD_INTO_QUARTERS](https://github.com/user-attachments/assets/140e8baa-2ae9-4977-91b3-1a7b608f9f12)

* * * * * * * * * *
## Introduction
The function block `SPLIT_DWORD_INTO_QUARTERS` is used to split a 32-bit word (DWORD) into its 16 individual 4-bit blocks (QUARTER_BYTE). Each of these 4-bit blocks is output as a separate BYTE variable. This block is particularly useful when individual parts of a DWORD need to be processed or analyzed separately.

## Interface Structure
### **Event Inputs**
- `REQ`: Starts processing the input DWORD.

### **Event Outputs**
- `CNF`: Signals successful processing and provision of all 16 QUARTER_BYTE outputs.

### **Data Inputs**
- `IN`: The input DWORD, which is split into 16 QUARTER_BYTE.

### **Data Outputs**
- `QUARTER_BYTE_00` to `QUARTER_BYTE_15`: The 16 individual 4-bit blocks of the input DWORD, each output as a BYTE.

### **Adapters**
No adapters are available.

## Functionality
The function block extracts the 16 QUARTER_BYTE from the input DWORD using bitwise operations. Each QUARTER_BYTE is isolated using a combination of bitwise AND operation and right shift, and then converted into a BYTE value. The constants used (`DWORD_QUARTER_XX` and `SHIFT_QUARTER_XX`) are defined in a separate constant file (`quarterconst`).

## Technical Features
- The block uses bitwise operations to isolate the individual 4-bit blocks.
- The output values are defined as BYTES, even though they only contain 4 bits. Therefore, the upper 4 bits of each BYTE are always 0.
- The use of predefined constants (`quarterconst`) allows for flexible adjustment of the bit positions.

## State Overview

The function block has no internal state. Processing is repeated with each `REQ` event.

## Application Scenarios
- Processing data packets where individual 4-bit blocks of a DWORD need to be evaluated.
- Decoding status or control information encoded in a DWORD.
- Splitting data for further processing in downstream systems.

## ⚖️ Comparison with Similar Blocks
- Compared to generic bit manipulation blocks, `SPLIT_DWORD_INTO_QUARTERS` offers specialized functionality for splitting a DWORD into 4-bit blocks.
- Other blocks, such as `SPLIT_DWORD_INTO_BYTES`, split a DWORD into 8-bit blocks, while this block offers finer granularity.

## 🛠️ Related Exercises
* [Exercise_060](../../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion
The `SPLIT_DWORD_INTO_QUARTERS` function block is a specialized tool for splitting a 32-bit word into 16 individual 4-bit blocks. Its simple and efficient implementation makes it ideal for applications requiring detailed analysis or processing of DWORD data.
