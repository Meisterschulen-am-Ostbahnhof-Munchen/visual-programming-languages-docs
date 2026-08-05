# DWORDS_TO_ARR08B
![DWORDS_TO_ARR08B](./DWORDS_TO_ARR08B.svg)
* * * * * * * * * *
## Introduction
The function block **DWORDS_TO_ARR08B** converts two 32-bit DWORD values into an eight-byte array (BYTE). The conversion is performed in little-endian format (Intel standard), meaning the least significant byte of a DWORD is written to the lowest index position of the output array. The function block is optimized for use on PC-based controllers (e.g., Beckhoff, Wago, B&R, Raspberry Pi).
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Starts the conversion. The current values of `IN_00` and `IN_01` are read. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Sent as soon as the output `OUT` has been updated. |

### **Data Inputs**

| Variable | Type | Description |

|----------|--------|-------------------|

| `IN_00` | DWORD | First 32-bit word (lower order). |

| `IN_01` | DWORD | Second 32-bit word (higher order). |

### **Data Outputs**

| Variable | Type | Description |

|----------|-------------------|-------------------------------------------------------|

| `OUT` | ARRAY[0..7] OF BYTE| Output array with 8 bytes (bytes 0–3 from `IN_00`, bytes 4–7 from `IN_01`). |

### **Adapters**
No adapters available.

## Functionality
When a rising edge is detected at the event input `REQ`, the following logic is executed:

1. The two input DWORDs `IN_00` and `IN_01` are read byte by byte.

2. The system's internal byte accesses (e.g., `IN_00.%B0` for the least significant byte) are used.

3. The bytes are copied into the output array `OUT` in **little-endian order**:

- `OUT[0]` ← least significant byte of `IN_00`
- `OUT[1]` ← second byte of `IN_00`
- `OUT[2]` ← third byte of `IN_00`
- `OUT[3]` ← most significant byte of `IN_00`
- `OUT[4]` ← least significant byte of `IN_01`
- `OUT[5]` ← second byte of `IN_01`
- `OUT[6]` ← third byte of `IN_01`
- `OUT[7]` ← most significant byte of `IN_01`

4. After the assignments are complete, the event `CNF` is sent.

## Technical Details
- The byte order follows the **Little-Endian format** (Intel standard), which is natively used on most PC-based controllers (Windows-based systems, Raspberry Pi).
- The function block is implemented as **structured text (ST)** and does not require a state machine – processing occurs linearly with each `REQ` event.
- The package `logiBUS::utils::conversion::arr::reversing` used in the ST code indicates a reusable library for conversions.

## State Overview
The function block does not have its own state machine. It performs a single, deterministic calculation with each `REQ` event and signals completion with `CNF`. There are no internal memory states that persist across multiple calls.

## Application Scenarios
- **Data Protocol Preparation**: Conversion of control data (e.g., position values, timer counters) stored as two DWORDs into a byte array for serial transmission (RS-232, CAN, Ethernet).
- **Communication with Endian-Sensitive Devices**: Ensuring the correct byte order when exchanging data with sensors or actuators that expect little-endian.
- **Memory Mapping / Union Replacement**: In languages without union types, this function block serves as a portable method for decomposing DWORD values byte by byte.

## Comparison with Similar Function Blocks
- **WORD_TO_ARR04B**: Converts a WORD into a 4-byte array – here, the same approach is extended to two DWORDs.
- **DWORDS_TO_ARR08B_BIGENDIAN**: Alternative function block for big-endian systems (Motorola standard) with reversed byte order.
- **SWAP_BYTES**: Swaps the bytes of a DWORD, but does not return an array. This function block directly creates the complete 8-byte array.

## Conclusion
The function block `DWORDS_TO_ARR08B` offers a simple and efficient way to combine two little-endian DWORDs into a byte array. Its consistent focus on PC-based controllers and its clear, maintainable ST implementation make it a reliable tool for data conversion in automation technology.
