# ARR08X_TO_BOOLS

<img width="1076" height="362" alt="image" src="https://github.com/user-attachments/assets/d607edb8-cbf2-4776-a5f2-cc8022ad9574" />
![ARR08X_TO_BOOLS](./ARR08X_TO_BOOLS.svg)

* * * * * * * * * *

## Introduction

The **ARR08X_TO_BOOLS** function block converts an 8-element BOOL array into eight individual BOOL signals. It extracts each bit from the input array and makes it available via its own named data output. This block is particularly useful for breaking down compact array data from higher-level systems or communication interfaces into individual, easily processed logical signals.

## Interface Structure

The block has a simple, unidirectional interface with a request/acknowledgment event pair.

## **Event Inputs**

**REQ**: This event triggers the processing. Upon its arrival, the values of the input array `IN` are read and distributed to the individual outputs `OUT_00` to `OUT_07`.

### **Event Outputs**

- **CNF**: This event is triggered as soon as the extraction of the Boolean values is complete. It confirms the execution of the function block and transmits the new values to all eight data outputs (`OUT_00` to `OUT_07`).

### **Data Inputs**

- **IN** (ARRAY[0..7] OF BOOL): The input array containing the eight Boolean values to be extracted. Index 0 corresponds to the least significant bit (LSB) and is mapped to `OUT_00`.

### **Data Outputs**

- **OUT_00** (BOOL): Extracted bit 0 (LSB) of input array `IN`.
- **OUT_01** (BOOL): Extracted bit 1 of input array `IN`.
- **OUT_02** (BOOL): Extracted bit 2 of input array `IN`.
- **OUT_03** (BOOL): Extracted bit 3 of input array `IN`.
- **OUT_04** (BOOL): Extracted bit 4 of input array `IN`.
- **OUT_05** (BOOL): Extracted bit 5 of the input array `IN`.
- **OUT_06** (BOOL): Extracted bit 6 of the input array `IN`.
- **OUT_07** (BOOL): Extracted bit 7 (MSB) of the input array `IN`.

### **Adapters**

This function block does not use any adapters.

## Operation

The operation is deterministic and stateless. Upon each occurrence of the `REQ` event, the function block performs a direct assignment. Each element of the input array `IN` is assigned to its corresponding, individually named output variable. The logic corresponds to the following ST assignment:

``iec61131-3
OUT_00 := IN[0];
OUT_01 := IN[1];
OUT_02 := IN[2];
OUT_03 := IN[3];
OUT_04 := IN[4];
OUT_05 := IN[5];
OUT_06 := IN[6];
OUT_07 := IN[7];
Immediately after this operation is completed, the ``CNF`` event is generated with the new values.

## Technical Features

- **Real-time behavior:** The function block only performs assignments and causes no significant latency. Execution is completed in one cycle.
- **Memory:** No internal state is stored between calls. The output is a pure function of the current input.
- **Array limits:** The function block is specifically defined for arrays of a fixed size of 8 (indices 0 to 7). Using an array of a different size will result in a compilation error.

## State overview

The function block has no internal state (stateless). Its behavior is identical for each call and depends solely on the current values at the data input ``IN``.

## Application Scenarios

- **Bus Telegram Unpacking:** Extracting individual status or control bits from a byte received via fieldbuses (e.g., CAN, PROFIBUS) or industrial networks.
- **Interface to Bit-Oriented Components:** Preparing array data for controlling individual lamps, valves, or relays addressed via discrete BOOL outputs.
- **Simplified Visualization:** Providing individually addressable signals for HMIs or alarm systems instead of having to work with array indices.
- **Decoding:** Converting a simple 8-bit binary number into its individual logical values.

## ⚖️ Comparison with Similar Function Blocks

- **`SEL` / `MUX` Function Blocks:** These select a single element from an array based on an index. `ARR08X_TO_BOOLS`, on the other hand, extracts **all** elements simultaneously and in parallel.
- **`BYTE_TO_BOOLS` / `WORD_TO_BOOLS`:** These building blocks decompose a byte or word data element into its individual bits. `ARR08X_TO_BOOLS` operates directly on an array of BOOLs, which is semantically clearer if the source is already a BOOL array. However, the functional effect on the bits is equivalent.
- **Manual Indexing:** Instead of using this building block, one could directly access `IN[0]`, `IN[1]`, etc., in the surrounding algorithm. However, the function block provides a clearer interface description, improves the readability of the FBD network, and encapsulates the functionality.

## 🛠️ Related Exercises

- [Exercise_054](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_054.md)

## Conclusion

The `ARR08X_TO_BOOLS` is a specialized, yet very useful conversion module. It provides a simple and efficient method for unpacking a compact 8-bit BOOL array into eight discrete signals. Its clear, stateless operation and the explicit labeling of all outputs significantly improve the readability and maintainability of control applications that use array-based data structures.
