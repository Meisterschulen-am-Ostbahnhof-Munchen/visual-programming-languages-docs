# ASSEMBLE_WORD_FROM_QUARTERS
## 🎧 Podcast
* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
----
![ASSEMBLE_WORD_FROM_QUARTERS](https://github.com/user-attachments/assets/6677028d-5ee1-4e7f-80d6-df3177ab9181)

* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_WORD_FROM_QUARTERS` combines 8 quarter bytes into a WORD. This is particularly useful when data is in smaller units and needs to be combined into a larger unit.

## Interface Structure

### **Event Inputs**
- `REQ`: Starts the processing and combines the 8 quarter bytes into a WORD.

#### **Event Outputs**
- `CNF`: Signals the successful combination of the quarter bytes into a WORD.

### **Data Inputs**
- `QUARTER_BYTE_00` to `QUARTER_BYTE_07` (Type: `BYTE`): The 8 quarter bytes that are combined to form a WORD.

### **Data Outputs**
- `OUT` (Type: `WORD`): The resulting WORD composed of the 8 quarter bytes.

### **Adapters**
No adapters are available.

## Functionality
The function block receives 8 quarter bytes and combines them into a WORD. Each quarter byte is moved to a specific position within the WORD and concatenated using logical OR operations. The exact shifts are defined by constants (`quarterconst::SHIFT_QUARTER_00` to `quarterconst::SHIFT_QUARTER_07`).

## Technical Features
- Uses bitwise operations (SHL and OR) to combine the bytes.
- The shift positions are defined by constants, allowing for flexible adjustment.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Combines the quarter bytes into a WORD.

3. **Complete**: Sends the `CNF` event along with the resulting WORD.

## Application Scenarios
- Data compression: Combining smaller data units into larger ones.
- Communication protocols: Composing data packets from individual bytes.
- Signal processing: Combining signal segments into a complete signal.

## ⚖️ Comparison with similar function blocks
- Similar function blocks could be `BYTE_TO_WORD` or `SHL`; however, `ASSEMBLE_WORD_FROM_QUARTERS` offers a specialized function for combining eight quarter bytes into a WORD.
- Unlike generic combination function blocks, this function block is optimized for the specific requirement of combining quarter bytes.

## Conclusion
The `ASSEMBLE_WORD_FROM_QUARTERS` function block is an efficient tool for combining eight quarter bytes into a WORD. By using bitwise operations and defined shift positions, it provides a reliable and flexible solution for this specific task.
