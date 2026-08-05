# ASSEMBLE_DWORD_FROM_BYTES
![ASSEMBLE_DWORD_FROM_BYTES](https://github.com/user-attachments/assets/818dd9ca-040d-43e5-a631-b8206ec1ed5d)

* * * * * * * * * *
## Introduction
The function block `ASSEMBLE_DWORD_FROM_BYTES` combines four BYTE values into a single DWORD value. This is particularly useful when data from multiple sources needs to be merged for processing or storage as a single unit.
## Interface Structure
### **Event Inputs**
- **REQ**: Initiates the combination of the BYTE values into a DWORD. This is linked to the data inputs `BYTE_00`, `BYTE_01`, `BYTE_02`, and `BYTE_03`.

### **Event Outputs**
- **CNF**: Signals the successful combination of the BYTE values into a DWORD. The combined DWORD value is available at the data output.

### **Data Inputs**
- **BYTE_00**: First byte of the DWORD to be combined.
- **BYTE_01**: Second byte of the DWORD to be combined.
- **BYTE_02**: Third byte of the DWORD to be combined.
- **BYTE_03**: Fourth byte of the DWORD to be combined.

### **Data Outputs**
- **(unnamed)**: The combined DWORD value created from the four input bytes.

### **Adapters**
No adapters available.

## Functionality
The function block accepts four BYTE values and combines them into a single DWORD value. The combination is achieved by directly assigning the individual bytes to the corresponding positions in the DWORD:

- `BYTE_00` is assigned to the least significant byte (B0) of the DWORD.
- `BYTE_01` is assigned to the next byte (B1).
- `BYTE_02` is assigned to the next byte (B2).
- `BYTE_03` is assigned to the most significant byte (B3).

## Technical Features
- The function block is implemented in the ST (Structured Text) language.
- The bytes are assigned directly using the `%B0` to `%B3` syntax, which accesses the individual bytes of the DWORD.

## State Overview

1. **Idle**: Waits for the `REQ` event.

2. **Processing**: Upon receiving `REQ`, the input bytes are combined and the DWORD value is calculated.

3. **Completed**: Sends the `CNF` event with the combined DWORD value.

## Application Scenarios
- Combining data from multiple sensors or sources into a single value.
- Preprocessing data for transmission or storage.
- Use in protocol implementations where data needs to be segmented into bytes and later reassembled.

## ⚖️ Comparison with Similar Building Blocks
- Similar function blocks might combine individual bytes into other data types (e.g., WORD).

Unlike manual combinations in ST code, this block offers a predefined and reusable solution.

## Conclusion
The `ASSEMBLE_DWORD_FROM_BYTES` function block provides a simple and efficient way to combine four byte values into a DWORD. Its clear interface and direct implementation make it a useful tool in various use cases.
