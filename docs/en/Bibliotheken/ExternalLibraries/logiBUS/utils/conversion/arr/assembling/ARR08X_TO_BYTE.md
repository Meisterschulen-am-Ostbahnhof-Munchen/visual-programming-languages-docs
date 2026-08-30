# ARR08X_TO_BYTE

<img width="1176" height="217" alt="image" src="https://github.com/user-attachments/assets/7e2d9580-9a80-4dea-ad4f-4100a7186544" />
![ARR08X_TO_BYTE](./ARR08X_TO_BYTE.svg)

* * * * * * * * * *
## Introduction

The function block `ARR08X_TO_BYTE` converts an array of eight Boolean values (`BOOL`) into a single byte value (`BYTE`). Each bit in the resulting byte corresponds to an element of the input array. This operation is useful for bundling multiple binary signals (e.g., switch states or error flags) to save space and preparing them for further processing or communication.
## Interface Structure

### **Event Inputs**

- `REQ` (Request): Triggers the conversion operation. Upon receiving an event at this input, the current value of the input array `IN` is read and converted into a byte.

### **Event Outputs**

- `CNF` (Confirm): Triggered as soon as the conversion is complete. This event signals that the output value (the byte) is valid and current.

### **Data Inputs**

- `IN` (Array[0..7] of BOOL): The input array containing the eight Boolean values to be converted. The index `0` corresponds to the least significant bit (LSB, bit 0) of the resulting byte, and the index `7` corresponds to the most significant bit (MSB, bit 7).

### **Data Outputs**

- `OUT` (BYTE): The output value composed of the eight Boolean inputs. The data output is not explicitly named (empty name in the interface) but is accompanied by the event output `CNF`.

### **Adapters**

This function block does not use any adapters.

## Operation

Upon receiving a `REQ` event, the block performs a bitwise assignment. Each bit of the internal result byte (`ARR08X_TO_BYTE`) is directly assigned to the corresponding element of the input array `IN`. After these assignments are complete, the `CNF` event is generated, and the calculated byte value is available at the output.

The underlying ST code logic is:

ARR08X_TO_BYTE.0 := IN[0];
ARR08X_TO_BYTE.1 := IN[1];
...
ARR08X_TO_BYTE.7 := IN[7];
## Technical Features

- **Hard-wired size:** This block is specifically designed for converting exactly 8 Boolean values. Different blocks are required for other array sizes.
- **Direct bit mapping:** The mapping is deterministic and performed without any arithmetic operations, enabling very fast and resource-efficient execution.
- **Index bit mapping:** It is critical to observe the mapping of array index to bit position in the byte: `IN[0]` → Bit 0 (LSB), `IN[7]` → Bit 7 (MSB).

## State overview

This function block is stateless. It has no internal memory between calls. Its output at any given time is solely a direct function of the current input values when the `REQ` event occurs.

## Application Scenarios

- **Communication Protocols:** Bundling multiple binary device statuses into a single data byte for transmission via serial interfaces or fieldbuses (e.g., PROFIBUS, CANopen).
- **Memory Optimization:** More compact storage of up to 8 switching states or alarm conditions in a single byte variable.
- **PLC Internal Data Handling:** Preparing data for blocks or functions that expect byte or word data types instead of individual Boolean values.

## ⚖️ Comparison with Similar Building Blocks

- **`BOOL_TO_BYTE` blocks:** Many libraries offer blocks that combine eight individual `BOOL` inputs (e.g., `IN0`...`IN7`) into a `BYTE`. `ARR08X_TO_BYTE`, on the other hand, uses an array as its input, which often makes wiring clearer when dealing with many signals from a common source (e.g., a previous array output).
- **`MERGE`/`PACK` blocks:** More general blocks can combine different data types. `ARR08X_TO_BYTE` is more specialized, simpler, and more efficient for its specific purpose.
- **Bitwise Shifting (`SHL`, `OR`):** The same function could be implemented using a loop and bitwise operations in ST. This pre-built block offers a standardized, ready-to-use, and less error-prone solution.

## Conclusion

The `ARR08X_TO_BYTE` function block is a simple yet extremely useful tool for signal processing in IEC 61499 systems. It provides an elegant and efficient method for converting eight Boolean values from an array into a compact byte. Its clear interface and deterministic operation make it a reliable component for automation applications, especially where data needs to be prepared for communication or space-optimized storage.
