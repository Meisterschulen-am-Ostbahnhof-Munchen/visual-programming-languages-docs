# WORDS_TO_ARR08B
![WORDS_TO_ARR08B](./WORDS_TO_ARR08B.svg)

* * * * * * * * * *
## Introduction
The function block **WORDS_TO_ARR08B** is used to concatenate four 16-bit words (type `WORD`) into a byte array of length 8 (type `ARRAY[0..7] OF BYTE`). It uses the little-endian format (Intel standard), which stores the least significant bytes first. The block is controlled via an event input and is particularly suitable for PC-based controllers (e.g., Beckhoff, Wago, B&R, Raspberry Pi).
## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|--------------|

| `REQ` | Event | Triggers the conversion; all input variables are read and the result is calculated. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|--------------|

| `CNF` | Event | Sent after successful calculation, indicating that valid data is present at output `OUT`. |

### **Data Inputs**

| Name | Type | Description |

|--------|------|----------------------------------|

| `IN_00` | WORD | First Word (Bytes 0 and 1) |

| `IN_01` | WORD | Second Word (Bytes 2 and 3) |

| `IN_02` | WORD | Third Word (Bytes 4 and 5) |

| `IN_03` | WORD | Fourth Word (Bytes 6 and 7) |

### **Data Outputs**

| Name | Type | Description |

|------|--------------------|---------------------------------------------------|

| `OUT` | ARRAY[0..7] OF BYTE | Result array, containing the 8 bytes in little-endian order. |

### **Adapters**

No adapters defined.

## Functionality

When a rising edge is detected at the event input `REQ`, the function block performs the following mapping (described in the Structured Text Implementation):

| Index `OUT` | Source | Meaning |

|-------------|-----------------|-------------------------------------|

| `OUT[0]` | `IN_00.%B0` | Low-order byte of word 0 |

| `OUT[1]` | `IN_00.%B1` | High-order byte of word 0 |

| `OUT[2]` | `IN_01.%B0` | Low-order byte of word 1 |

| `OUT[3]` | `IN_01.%B1` | Higher-order byte of word 1 |

| `OUT[4]` | `IN_02.%B0` | Low-order byte of word 2 |

| `OUT[5]` | `IN_02.%B1` | Higher-order byte of word 2 |

| `OUT[6]    | `IN_03.%B0` | Low-order byte of word 3 |

| `OUT[7]` | `IN_03.%B1` | Higher-order byte of word 3 |

After the assignments are complete, the output pulse `CNF` is generated.

## Technical Features
- **Little-Endian Format**: The bytes of each word are stored in ascending memory address order, with the least significant byte first. This corresponds to the Intel byte order and is common for many PC-based controllers and communication protocols (e.g., Modbus, CANopen, serial interfaces).
- **No Reversal of Overall Order**: The words themselves are inserted into the array in the order `IN_00` to `IN_03`; only within each word is the byte order reversed. If a different implementation is required to also reverse the word order (e.g., Big-Endian at the word level), this is necessary.
- **Immediate Execution**: The function block is purely combinatorial – after the event `REQ`, the result is available in the next execution cycle. No internal state is stored.

## State Overview

The function block does not have an explicit state machine. Its behavior is purely event-driven:

1. **Idle**: Waiting for `REQ`.

2. **Processing**: Upon `REQ`, the input values are read and the output calculation is performed.

3. **Complete**: `CNF` is sent; the function block returns to the idle state.

The implementation is deterministic and requires only one execution step.

## Application Scenarios
- **Communication with Peripherals**: A microcontroller or IPC sends 16-bit sensor data (e.g., analog-to-digital converter, encoder) via a byte-oriented serial bus. The device packs the words into a byte array that can be transmitted directly.
- **Data Logging**: Combining multiple 16-bit measurements into a buffer for storage or transmission (e.g., CSV, binary format).
- **Protocol Conversion**: Adapting data to the byte order required by a specific protocol (e.g., OPC UA, MQTT binary payload).

## Comparison with Similar Function Blocks
- **WORDS_TO_ARR08B** expects exactly four words and creates an array of length 8. For other word/byte counts, related function blocks exist, such as `WORDS_TO_ARR04B`, `WORDS_TO_ARR16B`, or for big-endian.
- Unlike a general-purpose block like `MERGE`, which concatenates arbitrary data types, this function block is specifically optimized for 2-byte-per-word conversion and guarantees the correct byte order.
- Compared to simple variable assignment using `MOVE` or a pure function like `WORD_TO_BYTE`, this block avoids manual index calculations and improves readability.

## Conclusion

The function block **WORDS_TO_ARR08B** is a compact, specialized module for converting four 16-bit words into a little-endian byte array. Its clear, event-driven interface and simple implementation make it ideal for use in control applications where data needs to be prepared at the byte level for communication or storage. It belongs to the `logiBUS::utils::conversion::arr::reversing` package family and adds a useful conversion capability to the 4diac toolbox.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 MCU vs. MPU Comparison Guide on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]
