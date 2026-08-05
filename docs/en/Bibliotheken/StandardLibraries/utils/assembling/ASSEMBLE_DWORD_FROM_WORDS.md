# ASSEMBLE_DWORD_FROM_WORDS

![ASSEMBLE_DWORD_FROM_WORDS](https://github.com/user-attachments/assets/6e0070a6-ac74-4370-9657-7d0fdd5e02cf)

* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_DWORD_FROM_WORDS` combines two 16-bit words (WORD) into a 32-bit double word (DWORD). This functionality is particularly useful when data from two separate sources needs to be merged.

## Interface Structure

### **Event Inputs**

- `REQ`: Starts the processing of the function block. Must be linked to the data inputs `WORD_00` and `WORD_01`.


### **Event Outputs**

- `CNF`: Signals successful processing and output of the combined DWORD.

### **Data Inputs**

- `WORD_00`: First 16-bit word (WORD) inserted into the resulting DWORD.

- `WORD_01`: Second 16-bit word (WORD) inserted into the resulting DWORD.

### **Data Outputs**

- (no name): The combined 32-bit double word (DWORD) consisting of the two input words.

### **Adapters**
This function block does not use adapters.


### ## Functionality

The function block receives the two 16-bit input words (`WORD_00` and `WORD_01`) and combines them into a single 32-bit double word (DWORD). `WORD_00` is placed in the lower 16 bits and `WORD_01` in the upper 16 bits of the resulting DWORD.

## Technical Details
- The implementation is in Structured Text (ST).

- The function block is part of the `eclipse4diac::utils::assembling` package.

## State Overview
1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Processes the input words and creates the DWORD.

3. **Complete**: Sends the `CNF` event with the combined DWORD.

## Application Scenarios

- Combining two 16-bit sensor data points into a 32-bit value.

- Processing data from two separate communication channels.

- Extending 16-bit data to 32 bits for further processing.

## ⚖️ Comparison with Similar Blocks
- Unlike simple bit operations, this function block offers a clearly defined interface and is integrated into the 4diac IDE.

- Similar functionality could be achieved with basic operations, but this block simplifies handling.

## Conclusion
The `ASSEMBLE_DWORD_FROM_WORDS` function block provides a simple and efficient way to combine two 16-bit words into a 32-bit double word. Its clear interface and direct integration with 4diac make it particularly useful for applications that work with combined word data.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]