# WORDS_TO_ARR08B_BE
<br>
![WORDS_TO_ARR08B_BE](./WORDS_TO_ARR08B_BE.svg)
* * * * * * * * * *
## Introduction
The function block **WORDS_TO_ARR08B_BE** combines four 16-bit words (WORD) into an 8-byte array. The conversion is performed in **Big-Endian format** (Network Byte Order), where the most significant byte is stored first in the output array. This corresponds to the standard representation in network protocols such as Modbus TCP, Siemens S7 communication, or Ethernet headers.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Starts the conversion of all four input words. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Sent once the output array has been fully calculated. |

### **Data Inputs**

| Name | Type | Comment |

|---------|-------|-----------|

| `IN_00` | WORD | Word 00 (first word) |

| `IN_01` | WORD | Word 01 (second word) |

| `IN_02` | WORD | Word 02 (third word) |

| `IN_03` | WORD | Word 03 (fourth word) |

### **Data Outputs**

| Name | Type | Comment |

|------|-----------------|-----------|

| `OUT`| ARRAY[0..7] OF BYTE | 8-byte array in big-endian format |

### **Adapters**
No adapters available.

## Functionality
After receiving the event `REQ`, the values of the four inputs `IN_00` to `IN_03` are read. For each word, the **high byte** (BYTE 1) and then the **low byte** (BYTE 0) are written to the output array. The order in the array is:

- `OUT[0]` = High byte of `IN_00`
- `OUT[1]` = Low byte of `IN_00`
- `OUT[2]` = High byte of `IN_01`
- `OUT[3]` = Low byte of `IN_01`
- `OUT[4]` = High byte of `IN_02`
- `OUT[5]` = Low byte of `IN_02`
- `OUT[6]` = High byte of `IN_03`
- `OUT[7]` = Low byte of `IN_03`

The event `CNF` is then triggered.

## Technical Features
- **Big-Endian Format** (Network Byte Order) – the bytes are stored in order, with the most significant byte first. This is required for many industrial communication protocols and network stacks.
- The function block operates **event-driven**: The conversion is only performed when a `REQ` event occurs, so no cyclical calculation takes place.
- The internal implementation uses **Structured Text (ST)** with direct bit element access (`%B1` and `%B0`), ensuring efficient and deterministic conversion.

## State Overview
The function block has no explicit internal state (stateless). It immediately performs the calculation upon each `REQ` and signals completion with `CNF`. No blocking is expected during the calculation.

## Application Scenarios
- **Network Communication**: Preparation of data for protocols that expect big-endian, e.g., Modbus TCP, Siemens S7 over Industrial Ethernet, or raw Ethernet frames.
- **Data Preprocessing**: Conversion of sensor values or control commands stored as WORD registers into a byte-oriented format.
- **Gateway Functions**: Translation between little-endian controllers and big-endian networks.

## Comparison with Similar Components

| Component | Special Feature |

-----------------------------|---------------|

| WORDS_TO_ARR08B_BE | Big-endian, 4 WORDS → 8 bytes |

| WORDS_TO_ARR08B_LE | Little-endian (low byte first) |

| BYTES_TO_WORDS_BE / LE | Reverse conversion |

| WORDS_TO_ARR16B_BE | Big-Endian, 8 WORDS → 16 Bytes |

| WORDS_TO_ARR08N | Possibly unspecified endianness |

This function block is specifically optimized for big-endian applications and is kept compact.

## Conclusion

`WORDS_TO_ARR08B_BE` is a precise, event-driven function block for the big-endian conversion of four WORDS into an 8-byte array. It is ideally suited for all applications that require byte-wise representation in Network Byte Order and simplifies the interface between control logic and communication protocols.