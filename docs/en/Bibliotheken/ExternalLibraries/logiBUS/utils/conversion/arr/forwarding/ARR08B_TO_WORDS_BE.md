# ARR08B_TO_WORDS_BE
![ARR08B_TO_WORDS_BE](./ARR08B_TO_WORDS_BE.svg)

* * * * * * * * * *
## Introduction
The function block `ARR08B_TO_WORDS_BE` extracts four 16-bit words (WORD) from an 8-byte array (big-endian). It is primarily used to convert binary data streams stored in an ascending byte array and interpret them as an ordered word sequence. This block belongs to the package group `logiBUS::utils::conversion::arr::forwarding`.
## Interface Structure

### **Event Inputs**

| Event | Description |
|---------|-------------|
| `REQ` | Starts the conversion: The incoming byte array `IN` is converted into the four output words. |

### **Event Outputs**

| Event | Description |
|---------|-------------|
| `CNF` | Confirms successful conversion and indicates that the output values are valid. |

### **Data Inputs**

| Name | Type | Array Size | Description |
|------|-----|--------------|-------------|
| `IN` | `BYTE` | `0..7` (8 bytes) | Input array – the raw data from which the words are extracted. |

### **Data Outputs**

| Name | Type | Description |
|------|-----|--------------|
| `OUT_00` | `WORD` | Word from byte 0 (high) and byte 1 (low) |
| `OUT_01` | `WORD` | Word from byte 2 (high) and byte 3 (low) |
| `OUT_02` | `WORD` | Word consisting of byte 4 (high) and byte 5 (low) |
| `OUT_03` | `WORD` | Word consisting of byte 6 (high) and byte 7 (low) |

### **Adapter**

No adapters available.

## Functionality

Upon arrival of a `REQ` event, the eight bytes of the input array `IN` are encoded into four 16-bit words in strict **big-endian order**:

- `OUT_00` = `(IN[0] << 8) | IN[1]`
- `OUT_01` = `(IN[2] << 8) | IN[3]`
- `OUT_02` = `(IN[4] << 8) | IN[5]`
- `OUT_03` = `(IN[6] << 8) | IN[7]`

The output event is then The event ``CNF`` is triggered, indicating the validity of all output values. This is implemented directly in the structured text portion of the function block, without an internal state machine.

## Technical Features
- **Big-Endian Convention:** The first byte of a word (`IN[0]`, `IN[2]`, …) is the higher-order byte (`%B1`), and the second byte (`IN[1]`, `IN[3]`, …) is the lower-order byte (`%B0`).
- **Fixed Array Size:** Exactly 8 bytes are expected; the array is declared as ``ARRAY[0..7] OF BYTE``.
- **No side effects:** The function block is purely combinatorial – it requires no internal state and operates within a single event cycle.
- **Typical use:** Converting data from binary protocols (e.g., CAN messages, Modbus registers, or serial streams) that are stored as byte arrays.

## State overview

The function block does not have its own state machine. It is triggered by the **event `REQ`** and outputs **`CNF`** after data processing. Execution occurs within a single cycle.

| State | Description |
|---------|-------------|
| *Idle* | Waiting for `REQ`; outputs retain the last value. |
| *Processing* | `REQ` received – data is being processed. |
*Completed* | `CNF` is being sent, outputs are valid. The module immediately returns to idle state. |

## Application Scenarios

1. **Modbus Communication:** An 8-byte register block (e.g., holding register) is received as a byte array and must be split into four 16-bit values.

2. **CAN Messages:** An 8-byte CAN frame contains multiple 16-bit sensor values transmitted in big-endian format.

3. **Serial Data Analysis:** Summarizing consecutive bytes from a serial interface into usable WORD sizes for further processing.

4. **Gateway Functions:** Conversion of binary to general-purpose data in automation processes based on IEC 61499.

## Comparison with Similar Building Blocks

| Building Block | Difference |
|----------|-------------|
| `ARR08B_TO_WORDS_LE` | Uses little-endian order (Byte[0] = low byte). |
| `ARR04B_TO_WORD` | Works with a 4-byte array and creates only one WORD. |
| `BYTE_TO_WORD` | Converts two individual bytes into one WORD; requires separate concatenation. |

ARR08B_TO_WORDS_BE` focuses on the efficient, predefined partitioning of an 8-byte array into four words in big-endian order – ideal for standardized protocols.

## Conclusion

The `ARR08B_TO_WORDS_BE` function block offers a simple and reliable method for converting an 8-byte array into four big-endian words. Its compact interface (`REQ`/`CNF` + one input, four outputs) allows for easy integration into existing IEC 61499 applications. Thanks to its direct ST implementation, there are no latencies from state machines, making it particularly suitable for time-critical applications in automation technology.
