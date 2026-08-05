# SPLIT_BYTE_INTO_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![SPLIT_BYTE_INTO_QUARTERS](https://github.com/user-attachments/assets/9cbf32e0-f8c2-437f-88d3-8e29db1731dd)
* * * * * * * * * *
## Introduction
The function block `SPLIT_BYTE_INTO_QUARTERS` is used to split a byte into four quarter bytes. This function is particularly useful when individual parts of a byte need to be processed separately, for example, when decoding data or manipulating bits.

## Interface Structure

### **Event Inputs**
- `REQ`: Starts the processing of the input byte. It is linked to the data input `IN`.

### **Event Outputs**
- `CNF`: Signals the completion of processing and provides the four quarter bytes. It is linked to the data outputs `QUARTER_BYTE_00`, `QUARTER_BYTE_01`, `QUARTER_BYTE_02`, and `QUARTER_BYTE_03`.

### **Data Inputs**
- `IN` (BYTE): The input byte to be split into four quarter bytes.

### **Data Outputs**
- `QUARTER_BYTE_00` (BYTE): The first quarter byte (bits 0-1).
- `QUARTER_BYTE_01` (BYTE): The second quarter byte (bits 2-3).
- `QUARTER_BYTE_02` (BYTE): The third quarter byte (bits 4-5).
- `QUARTER_BYTE_03` (BYTE): The fourth quarter byte (bits 6-7).

### **Adapters**
No adapters are used.

## Functionality
The function block extracts the four quarter bytes from the input byte `IN` using bitwise operations:

1. Each quarter byte is isolated using a bitwise AND operation with a corresponding mask.

2. The result is then shifted into the correct position using a right shift (`SHR`).

3. The masks and shift values used are defined in the constant file `quarterconst`.

## Technical Features
- The bitwise operations are efficient and fast because they are performed directly at the processor level.
- The use of constants (`quarterconst`) allows for flexible adjustment of masks and shift values.

## State Overview
The function block has no internal state. Processing occurs exclusively when the `REQ` event occurs.

## Application Scenarios
- Decoding data packed into a byte.
- Extracting individual control bits from a status byte.
- Processing data in communication protocols where information is encoded in quarter bytes.

## ⚖️ Comparison with Similar Function Blocks
- Compared to generic bit manipulation function blocks, `SPLIT_BYTE_INTO_QUARTERS` offers a specialized and optimized solution for splitting a byte into four parts.

Other blocks, such as `EXTRACT_BITS` or `BIT_SLICE`, are more general but require more configuration and may be less efficient.

## 🛠️ Related Exercises
* [Exercise_056](../../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)

## Conclusion
The `SPLIT_BYTE_INTO_QUARTERS` function block is an efficient and specialized solution for splitting a byte into four quarter bytes. Its use of bitwise operations and constants makes it fast and flexible. It is ideal for applications where data is in a compact form and needs to be processed separately.