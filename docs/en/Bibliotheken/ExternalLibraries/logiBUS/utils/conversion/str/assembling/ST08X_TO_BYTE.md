# ST08X_TO_BYTE

<img width="1075" height="213" alt="image" src="https://github.com/user-attachments/assets/006152fd-288f-460f-9c7b-723922245e8e" />
![ST08X_TO_BYTE](./ST08X_TO_BYTE.svg)

* * * * * * * * * *
## Introduction

The function block `ST08X_TO_BYTE` converts a special data structure containing eight individual Boolean values (BOOL) into a single byte value (BYTE). This operation is useful for bundling compact digital signals for transmission or storage, or for connecting them to systems that expect data in byte format.
## Interface Structure

### **Event Inputs**

- **REQ**: This event triggers the conversion function. Upon its arrival, the current values at the data input `IN` are read and converted to the byte output `OUT`.

### **Event Outputs**

- **CNF**: This event signals the successful completion of the conversion. It is generated simultaneously with the output of the calculated byte value at data output `OUT`.

### **Data Inputs**

- **IN** (Type: `ST08X`): The input for the data structure to be converted. Type `ST08X` is a user-defined structure type (STRUCT) containing eight individual BOOL elements named `X_00` through `X_07`.

### **Data Outputs**

- **OUT** (Type: `BYTE`): The output where the result of the conversion is provided. The eight bits of the byte (bits 0 to 7) directly correspond to the eight BOOL values of the input structure.

### **Adapter**

This function block has no adapter interfaces.

## Functionality

When triggered by the `REQ` event, the block performs a bitwise assignment. Each bit of the output byte `OUT` is set to the value of the corresponding Boolean element in the input structure `IN`. The assignment follows the following predefined scheme:

- `OUT`.0 (least significant bit, LSB) = `IN`.`X_00`
- `OUT`.1 = `IN`.`X_01`
- `OUT`.2 = `IN`.`X_02`
- `OUT`.3 = `IN`.`X_03`
- `OUT`.4 = `IN`.`X_04`
- `OUT`.5 = `IN`.`X_05`
- `OUT`.6 = `IN`.`X_06`
- `OUT`.7 (most significant bit, MSB) = `IN`.`X_07`

After these assignments are complete, the `CNF` event is output along with the new value of `OUT`.

## Technical Features

- **Deterministic Mapping**: The assignment of individual BOOL elements to specific bit positions in the byte is hardcoded and not configurable.
- **Simple Logic**: The block contains no state machines or complex algorithms. Its functionality is limited to direct, parallel assignment.
- **Type Dependency**: The block is specific to the user-defined data type `ST08X`. Different blocks may be required for other structures or a different number of bits.

## State Overview

The function block does not have an internal state in the sense of a state machine. It behaves purely combinatorially with respect to the data and sequentially with respect to event handling: An incoming `REQ` is always followed by an outgoing `CNF`.

## Application Scenarios

- **Communication with Byte-Oriented Interfaces**: Preparing data for transmission via serial bus systems (e.g., Modbus, Profibus), networks, or communication protocols that expect data in byte blocks.
- **Compact Storage**: Bundling multiple digital switching states (e.g., from limit switches, machine states) into a single byte to optimize storage space.
- **Data Preparation for Visualization or Logging**: Converting structured BOOL signals into a byte format that is easier for display systems or data storage to handle.
*
## ⚖️ Comparison with Similar Blocks

- **`BOOL_TO_BYTE` (or similar blocks from standard libraries)**: Many IEC 61499 or IEC 61131-3 libraries offer blocks that directly convert eight separate `BOOL` inputs into a single `BYTE`. `ST08X_TO_BYTE` differs in that the input values are already bundled into a structured variable (`ST08X`), which can simplify wiring in the application diagram.
- **`PACK` / `UNPACK` blocks**: More general blocks for packing and unpacking data. `ST08X_TO_BYTE` is a specialized and type-safe implementation for precisely this one use case.
- **Manual Bit Operations**: The function could also be implemented through direct assignments in Structured Text (ST). The function block encapsulates this logic and provides a standardized, reusable interface with clear event handling.

## Conclusion

The `ST08X_TO_BYTE` function block is a specialized and efficient tool for converting a structured group of eight Boolean signals into a compact byte. Its clear, well-defined interface and simple operation make it ideal for applications where digital signals need to be bundled for efficient communication or storage. Its use promotes the reusability and readability of control programs compared to manually implemented bit operations.
