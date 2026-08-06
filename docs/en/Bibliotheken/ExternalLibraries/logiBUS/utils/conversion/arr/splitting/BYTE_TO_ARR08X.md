# BYTE_TO_ARR08X
<img width="1315" height="219" alt="image" src="https://github.com/user-attachments/assets/9af3b849-ed33-437d-9688-1de0bee2a1f9" />
![BYTE_TO_ARR08X](./BYTE_TO_ARR08X.svg)

* * * * * * * * * *
## Introduction
The function block `BYTE_TO_ARR08X` converts a single byte value into an array of eight Boolean values (BOOL). Each bit of the input byte is assigned to a separate element in the output array. This block is particularly useful for breaking down compact digital information stored in a byte for individual processing or visualization.
## Interface Structure

### **Event Inputs**
* `REQ` (Request): This event triggers the conversion function. Upon its arrival, the current value at data input `IN` is processed.

### **Event Outputs**
* `CNF` (Confirm): This event signals the completion of the conversion. It is output along with the calculated data at output `OUT`.

### **Data Inputs**
* `IN` (BYTE): The input for the byte value to be decomposed into Boolean bits.

### **Data Outputs**
* `OUT` (ARRAY[0..7] OF BOOL): The output array with eight BOOL elements. Element `OUT[0]` corresponds to the least significant bit (LSB, bit 0) of the input byte, and `OUT[7]` corresponds to the most significant bit (MSB, bit 7).

### **Adapter**

This function block has no adapter interfaces.

## Functionality
When triggered by the `REQ` event, the block reads the value at the `IN` input. Then, each individual bit (0 to 7) of the BYTE data type is extracted and assigned to the corresponding index in the BOOL array `OUT`. The assignment is performed directly:

* `OUT[0]` receives the value of `IN.0` (bit 0)
* `OUT[1]` receives the value of `IN.1` (bit 1)
* ...
* `OUT[7]` receives the value of `IN.7` (bit 7)

After these assignments are complete, the `CNF` event is output along with the populated array `OUT`.

* `OUT[7]` receives the value of `IN.7` (bit 7)

After these assignments are complete, the `CNF` event is output along with the populated array `OUT`.

* `OUT[0]` receives the value of `IN.0`
* `OUT[1]` receives the value of `IN.1`
* `OUT[1]` receives the value of IN.1 ...
## Technical Features
* **Direct Bit Access:** The implementation uses the direct bit addressing common in IEC 61131-3 ST (Structured Text) syntax (e.g., `IN.0`), enabling efficient and readable operation.
* **Fixed Array Size:** The output array is defined with the fixed size `[0..7]`, which corresponds exactly to the bit length of a byte (8 bits).
* **Real-Time Capable:** The block performs a deterministic, stateless operation and is therefore suitable for real-time applications.

## State Overview

The function block is stateless. Its behavior is identical for every `REQ` event and depends solely on the current value at the data input `IN`. There are no internal variables stored between calls.

## Application Scenarios
* **Control Byte Unpacking:** Processing a status or control byte received from a field device or higher-level controller to evaluate individual status bits (e.g., "Motor on," "Valve open," "Fault active") separately.
* **Visualization:** Preparing data for visualization systems (HMIs), which often display individual switching states as separate Boolean lamps or indicators.
* **Interface to Bit-Oriented Logic:** Providing individual bits for subsequent function blocks that operate with Boolean logic (AND, OR, NOT, flip-flops) instead of entire bytes.

## ⚖️ Comparison with Similar Blocks
* **`BYTE_TO_BOOL` (or similarly named blocks):** Many libraries offer blocks that convert one byte into eight separate BOOL outputs. `BYTE_TO_ARR08X` differs in that it outputs the bits in a structured **array**, which simplifies the wiring in the 4diac IDE, as only one data output is required. Handling in ST code is also more compact.
* **Bitwise reading using `AND` & comparisons:** The same functionality could be achieved through a series of comparisons (`(IN AND 16#01) = 1`, etc.). The `BYTE_TO_ARR08X` block encapsulates this logic in a reusable, easy-to-understand block.
* **Counterpart `ARR08X_TO_BYTE`:** A complementary block that combines an array of eight BOOLs into one byte would perform the reverse operation.

## Conclusion

The `BYTE_TO_ARR08X` function block is a simple, specialized, and highly practical conversion module. It elegantly solves a common problem in automation technology by abstracting bit extraction from a byte and providing the results in a manageable array. Its deterministic and stateless nature makes it a reliable and high-performance component for applications where digital bit information needs to be transferred compactly and then processed decentrally.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
