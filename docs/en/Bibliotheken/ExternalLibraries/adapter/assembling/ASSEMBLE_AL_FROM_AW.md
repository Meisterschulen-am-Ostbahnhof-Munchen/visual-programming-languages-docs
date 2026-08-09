# ASSEMBLE_AL_FROM_AW

![ASSEMBLE_AL_FROM_AW](./ASSEMBLE_AL_FROM_AW.svg)

* * * * * * * * * *
## Introduction

The function block `ASSEMBLE_AL_FROM_AW` combines the data from four **AW (WORD)** adapter interfaces into one **AL (LWORD)** output value. It is used to combine multiple 16-bit words into a 64-bit word and output it via a clocked signal.
## Interface Structure

### **Event Inputs**

None – event control is handled exclusively via the connected adapters (see section Adapters).

### **Event Outputs**

None – event output is provided via the OUT adapter (`OUT.E1`).

### **Data Inputs**

No direct data inputs – the data to be processed is obtained via the four AW sockets.

### **Data Outputs**

No direct data outputs – the result is output via the OUT adapter.

### **Adapters**

| Name | Type | Comment |
|------|-----|-----------|
| **Sockets** | | |
| `WORD_00` | `adapter::types::unidirectional::AW` | Word 0 (least significant 16-bit word) |
| `WORD_01` | `adapter::types::unidirectional::AW` | Word 1 |
| `WORD_02` | `adapter::types::unidirectional::AW` | Word 2 |
| `WORD_03` | `adapter::types::unidirectional::AW` | Word 3 (highest-order 16-bit word) |
| **Plugs** | | |
| `OUT` | `adapter::types::unidirectional::AL` | LWORD output (64-bit) |

## Functionality

The module utilizes an internal network of two function blocks:

1. **`ASSEMBLE_LWORD_FROM_WORDS`** – performs the logical combination of the four 16-bit words (`WORD_00` to `WORD_03`) into a 64-bit LWORD.
2. **`E_D_FF_ANY`** – a clock-edge-triggered D flip-flop that only transmits the combined value to the output adapter `OUT` when a rising edge is present at the clock input.

The events from the four input adapters (`WORD_00.E1` … `WORD_03.E1`) are all connected to the `REQ` event input of `ASSEMBLE_LWORD_FROM_WORDS`. As soon as an event arrives at one of the input adapters, the combination is recalculated. Upon completion (`CNF`), `E_D_FF_ANY` is clocked, which then adopts the calculated value into its internal state and outputs it via `OUT.D1`. The event at the output adapter (`OUT.E1`) signals the availability of the new value.

As soon as an event arrives at one of the input adapters, the combination is recalculated.
## Technical Features

- **Clock Edge Triggered Output** – The use of the `E_D_FF_ANY` prevents unwanted intermediate values and ensures that only fully composed LWORDs are output.
- **Arbitrary Order of Input Events** – Since all four sockets are combined into the same `REQ` input, each incoming event triggers a recalculation. The function block therefore reacts to each partial word, but only updates the output after the complete composition.
- **Adapter-Based Interface** – The use of unidirectional adapters (AW and AL) enables loose coupling and reuse in different contexts.

## State Overview

The function block does not have its own ECC (Execution Control Chart), but consists of a combinational circuit with a downstream flip-flop. The internal state logic is fully implemented by the two sub-modules `ASSEMBLE_LWORD_FROM_WORDS` and `E_D_FF_ANY`.

## Application Scenarios

- **Industrial Data Acquisition** – Combining four 16-bit sensor values (e.g., temperature, pressure, flow rate, level) into a single 64-bit data packet.
- **Communication Interfaces** – Processing separately arriving 16-bit data blocks for a 64-bit interface (e.g., Modbus register → OPC UA).
- **Bit-Parallel Processing** – Combining four microcontroller registers into a single large register for advanced logic applications.

## Comparison with Similar Modules

| Module | Description |
|----------|-------------|
| `ASSEMBLE_AL_FROM_BYTES` | Combines multiple 8-bit values into an LWORD |
| `ASSEMBLE_AL_FROM_DWORDS` | Combines two 32-bit double words into a 64-bit word |
| `ASSEMBLE_AL_FROM_AW` (this one) | Combines four 16-bit words into an LWORD |

All these building blocks follow the same principle but differ in the word width of the input data and the number of sockets required.

## Conclusion

ASSEMBLE_AL_FROM_AW` is a specialized function block for concatenating four 16-bit words into a single 64-bit word. Clocked output via a D flip-flop ensures consistent data transmission. Thanks to its adapter-based interface, it integrates seamlessly into modular 4diac projects and simplifies word-to-long-word conversions.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 MCU vs. MPU Comparison Guide on ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/mikroelektronik/mpu-vs-mcu/mikroprozessor-mpu-vs-mikrocontroller-mcu/)

]
