# SPLIT_WORD_INTO_QUARTERS

## 🎧 Podcast

- [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![SPLIT_WORD_INTO_QUARTERS](https://github.com/user-attachments/assets/f26e7474-c9bf-4fb4-923f-d8c2ad4ac48e)

* * * * * * * * * *
## Introduction

The function block `SPLIT_WORD_INTO_QUARTERS` is used to split a 16-bit word into eight 2-bit quarter bytes. This is particularly useful when processing compressed data or extracting specific bit patterns.

## Interface Structure

### **Event Inputs**

- `REQ`: Starts processing the input word. Linked to the data input `IN`.

### **Event Outputs**

- `CNF`: Signals the completion of processing. It is linked to all eight quarter-byte outputs.

### **Data Inputs**

- `IN` (WORD): The 16-bit input word, which is split into quarter bytes.

### **Data Outputs**

- `QUARTER_BYTE_00` to `QUARTER_BYTE_07` (BYTE): The eight extracted 2-bit quarter bytes. Each output contains one of the quarter bytes of the input word.

### **Adapters**

No adapters are available.

## Operation

The function block uses bitmasks and shift operations to extract the individual 2-bit segments from the input word. Each quarter byte is isolated using a bitwise AND operation with a specific mask and then shifted to the corresponding position to be output as a byte.

## Technical Features

- Uses constants (`quarterconst::WORD_QUARTER_XX` and `quarterconst::SHIFT_QUARTER_XX`) for the masks and shift positions.
- Extraction is performed by combining AND operations and right shifts.

## State Overview

1. **Idle**: Waits for the `REQ` event.
2. **Processing**: Extracts the quarter bytes from the input word.
3. **Completion**: Sends the `CNF` event and outputs the quarter bytes.

## Application Scenarios

- Decoding compressed data.
- Extraction of control bits from a status word.
- Processing of coded sensor data.

## ⚖️ Comparison with similar function blocks

- **SPLIT_WORD_INTO_BYTES**: Splits a word into two bytes, not eight quarter-bytes.
- **BIT_EXTRACT**: Extracts individual bits or groups of bits, but is less specialized for quarter-bytes.

## Conclusion

The `SPLIT_WORD_INTO_QUARTERS` function block is a specialized tool for efficiently extracting 2-bit data from a 16-bit word. Its clear interface and efficient implementation make it ideal for applications working with compressed or bit-coded data.
