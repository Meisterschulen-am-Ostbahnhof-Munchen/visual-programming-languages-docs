# ASSEMBLE_BYTE_FROM_QUARTERS

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

----

![ASSEMBLE_BYTE_FROM_QUARTERS](https://github.com/user-attachments/assets/0c4e652e-a741-472a-b8d9-d7721c16cc9a)

* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_BYTE_FROM_QUARTERS` combines four individual quarter bytes into a complete byte. This is particularly useful in scenarios where data needs to be transmitted or processed in parts and then reassembled.

## Interface Structure

### **Event Inputs**

- `REQ`: Starts combining the quarter bytes into one byte. It is linked to the four quarter bytes (`QUARTER_BYTE_00` to `QUARTER_BYTE_03`).


### **Event Outputs**

- `CNF`: Signals successful concatenation of the quarter bytes into a single byte.

### **Data Inputs**

- `QUARTER_BYTE_00`: First quarter byte (least significant bits).

- `QUARTER_BYTE_01`: Second quarter byte.

- `QUARTER_BYTE_02`: Third quarter byte.

- `QUARTER_BYTE_03`: Fourth quarter byte (most significant bits).

### **Data Outputs**

- `BYTE`: The concatenated byte resulting from the combination of the four quarter bytes.

### **Adapters**
No adapters available.


### ## Functionality

The function block accepts four quarter bytes and combines them into a complete byte. The individual quarter bytes are shifted to the correct position in the resulting byte using bit shift operations (`SHL`) and joined together using logical OR operations (`OR`). The precise shifts are defined by constants (`quarterconst::SHIFT_QUARTER_00` to `quarterconst::SHIFT_QUARTER_03`).

## Technical Features
- Uses bit shift operations (`SHL`) and logical OR operations (`OR`) to combine the quarter bytes.

- The shift positions are defined as constants, allowing for flexible adjustment.


## State Overview

1. **Initialization**: The function block is initialized and waits for the `REQ` event.

2. **Processing**: Upon receiving `REQ`, the four quarter bytes are processed and combined into the resulting byte.

3. **Acknowledgement**: After successful combination, the `CNF` event is triggered, and the resulting byte is output.

## Application Scenarios

- **Data Communication**: Combining partially transmitted data into a complete byte.

- **Data Processing**: Processing data that exists in smaller units but is required as a whole.


## ⚖️ Comparison with Similar Blocks
- Compared to generic bit manipulation function blocks, `ASSEMBLE_BYTE_FROM_QUARTERS` offers a specialized and optimized solution for combining quarter bytes.

- Other blocks may offer similar functionality, but are often less specific and require more configuration.

## 🛠️ Related Exercises

* [Exercise_056](../../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)]

## Conclusion
The `ASSEMBLE_BYTE_FROM_QUARTERS` function block is an efficient and specialized solution for combining four quarter bytes into a complete byte. By using bit-shift and logical operations, it offers a high-performance and flexible way to process data in relevant application scenarios.