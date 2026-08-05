# ASSEMBLE_DWORD_FROM_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![ASSEMBLE_DWORD_FROM_QUARTERS](https://github.com/user-attachments/assets/b87a9cb4-49aa-4375-be7f-c4e32422490e)
* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_DWORD_FROM_QUARTERS` combines 16 quarter bytes (4 bits each) into a DWORD (32 bits). This is particularly useful when data exists in smaller units and needs to be combined into a larger unit.

## Interface Structure

### **Event Inputs**
- `REQ`: Starts combining the quarter bytes into a DWORD. All 16 quarter bytes are combined.

### **Event Outputs**
- `CNF`: Signals the successful combination of the quarter bytes into a DWORD.

### **Data Inputs**
- `QUARTER_BYTE_00` to `QUARTER_BYTE_15`: 16 inputs of type `BYTE`, each containing one quarter byte (4 bits).

### **Data Outputs**
- (Unnamed): One output of type `DWORD` containing the combined result.

### **Adapters**
No adapters are present.

## Operation
The function block accepts 16 quarter bytes and combines them into a 32-bit DWORD. Each quarter byte is shifted according to its position in the DWORD and then concatenated with the others. The shifting is performed using constants (`quarterconst::SHIFT_QUARTER_XX`) that define the position of each quarter byte in the DWORD.

## Technical Features
- Uses bit shifts (`SHL`) and logical OR operations (`OR`) to correctly combine the quarter bytes.
- The conversion from `BYTE` to `DWORD` is performed using `BYTE_TO_DWORD`.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Processes the quarter bytes and combines them into a DWORD.

3. **Complete**: Sends the `CNF` event and provides the combined DWORD.

## Application Scenarios
- Data compression: Combining multiple small data packets into one larger one.
- Communication protocols: Processing data transmitted in smaller units.
- Signal processing: Summarizing parts of a signal into a complete value.

## ⚖️ Comparison with similar building blocks
- Similar building blocks could be `BYTE_TO_WORD` or `WORD_TO_DWORD`, but these offer less flexibility as they only combine fixed values.
- `ASSEMBLE_DWORD_FROM_QUARTERS` offers more control over the position of each individual bit in the resulting DWORD.

## 🛠️ Related Exercises
* [Exercise_060](../../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion
The `ASSEMBLE_DWORD_FROM_QUARTERS` function block is a powerful tool for combining 16 quarter-bytes into a DWORD. Its flexible and precise operation makes it ideal for applications where data exists in smaller units and needs to be combined into a larger unit.