# ARR08B_TO_WORDS

![ARR08B_TO_WORDS](./ARR08B_TO_WORDS.svg)

* * * * * * * * * *
## Introduction
The function block **ARR08B_TO_WORDS** is used to divide an 8-byte array into four 16-bit words (WORDs). It is typically used in data preprocessing when raw byte data from sensors or communication interfaces needs to be converted into integer values. The conversion is performed byte-wise, taking the little-endian byte order into account.

## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Trigger the conversion; The function block processes the current value of `IN` and outputs the results. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirmation that the conversion is complete and the output values are valid. |

### **Data Inputs**

| Name | Type | Array Size | Description |

|------|-------|-------------|--------------|

| IN | BYTE | 0…7 | Input array of 8 bytes, which is split into four words. |

### **Data Outputs**

| Name | Type | Description |

|---------|------|--------------|

| OUT_00 | WORD | Word formed from bytes IN[0] and IN[1] (least significant). |

| OUT_01 | WORD | Word formed from bytes IN[2] and IN[3]. |

| OUT_02 | WORD | Word formed from bytes IN[4] and IN[5]. |

| OUT_03 | WORD | Word formed from bytes IN[6] and IN[7] (most significant). |

### **Adapter**
No adapters available.

## Functionality
When the event `REQ` is triggered, the 8-byte array `IN` is processed sequentially. Each pair of consecutive bytes is combined into a 16-bit word, with the first byte (`IN[0]`) being the least significant byte (`%B0`) and the second byte (`IN[1]`) being the most significant byte (`%B1`) of the word (little-endian format). The resulting four words are made available at outputs `OUT_00` to `OUT_03`. The event `CNF` is then sent.



## Technical Features

- **Byte Order:** Conversion always occurs in little-endian format, meaning the first byte in the array becomes the least significant part of the word.

- **No Buffering:** The function block is purely combinational and does not store any states. Each `REQ` call processes the current input value.

- **Typing:** Inputs are defined as an array of `BYTE` (0 indexing), outputs as `WORD`. The function block does not require any further type conversions.

## State Overview

The function block does not have an internal state machine. Processing is strictly event-driven:

1. Wait for `REQ`.

2. For `REQ`: Copy the bytes into the output words.

3. Send `CNF` and return to wait mode.

## Application Scenarios

- **Sensor Readout:** A temperature sensor provides 8 raw bytes, which must be split into four 16-bit measured values (e.g., two channels with one word each).

- **Protocol Decoding:** A serial protocol transmits user data as a byte array; the function block extracts four 16-bit register values from it.

- **Data Preprocessing in PLC Systems:** Combine multiple byte-oriented interfaces (e.g., Profibus, CAN) into uniform word signals for further processing.


## Comparison with Similar Function Blocks

- **`BYTE_TO_WORD`:** Converts only two bytes into a single word; requires four calls for 8 bytes.

- **`ARRAY_TO_WORD` (general):** Usually configurable, e.g., with start index and number of words – `ARR08B_TO_WORDS`, on the other hand, is fixed to 8 bytes and 4 words and is therefore simpler and more performant in this specific case.

- **`WORD_TO_ARR08B` (if present):** The inverse function that packs four words back into an 8-byte array.

## Conclusion
The function block **ARR08B_TO_WORDS** offers a lean, specialized solution for decomposing an 8-byte array into four 16-bit words. The hardwired byte mapping ensures high execution speed and ease of use, especially in time-critical environments or for recurring conversion tasks. Little-endian interpretation is the standard for many industrial and embedded systems, so the component requires no additional parameters.