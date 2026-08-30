# AW_TO_AL

![AW_TO_AL](./AW_TO_AL.svg)

* * * * * * * * * *
## Introduction

The AW_TO_AL function block is a composite block for converting a WORD adapter (AW) to an LWORD adapter (AL). It is used to convert data from a 16-bit format to a 64-bit format, typically in control and automation systems. The block forwards events and data directly from the input side to the output side, ensuring the data type conversion.
## Interface Structure

### **Event Inputs**

None (Events are transmitted exclusively via the AW_IN adapter)
### **Event Outputs**

None (Events are output exclusively via the AL_OUT adapter)
### **Data Inputs**

None (Data is received exclusively via the AW_IN adapter)
### **Data Outputs**

None (Data is sent exclusively via the AL_OUT adapter)
### **Adapters**

- **AW_IN** (Socket): Adapter type `adapter::types::unidirectional::AW` – WORD input (16-bit) with event and data channels (E1, D1).
- **AL_OUT** (Plug): Adapter type `adapter::types::unidirectional::AL` – LWORD output (64-bit) with event and data channels (E1, D1).

## Functionality

The function block implements a simple passthrough function: The event (E1) received by the AW_IN adapter is directly forwarded to the event output AL_OUT.E1. Simultaneously, the 16-bit data signal from AW_IN.D1 is transferred to the 64-bit data output AL_OUT.D1. Since the AL adapter expects LWORD, the WORD value is implicitly converted to an LWORD (by zero expansion or explicit type conversion according to the runtime environment used). The function block does not perform any further operations.

## Technical Features

- **Bit-reinterpretation** (structural copy between bit-string types; truncates on narrowing, zero-extends on widening).

- The function block is implemented as a composite function block, meaning it contains an internal network that connects the adapters.
- The type conversion from WORD to LWORD occurs automatically through the concatenation of the data lines (implicit type conversion).
- The event and data paths are synchronized: Each incoming event triggers an outgoing event, accompanied by the current data value.

- The function block is unidirectional and does not support reverse communication.

## State Overview

Since the function block does not have its own state logic but only implements pass-through, there are no explicit states. Its function is purely combinatorial or event-driven without memory behavior.

## Application Scenarios

- **Format Adaptation**: If a sensor or controller only delivers WORD data (16 bits), but the downstream system expects LWORD data (64 bits), this function block can be used for adaptation.
- **Adapter Bridge**: In communication chains where different adapter types are used, the function block enables seamless integration.
- **Protocol Conversion**: As part of a larger adapter chain for converting from 16-bit to 64-bit data buses.

## Comparison with Similar Function Blocks

- **AW_TO_AW**: Identical type, no conversion.
- **AL_TO_AW**: Reverse conversion from LWORD to WORD (potentially resulting in data loss).
- **Direct connection without conversion**: If the systems use the same adapter type, no conversion module is required.
- The AW_TO_AL function block is characterized by its simplicity and specific type adaptation.

## Conclusion

The AW_TO_AL function block offers a straightforward way to convert WORD data to an LWORD format. It is particularly suitable for scenarios where pure type adaptation without additional logic is required. Its implementation as a composite function block ensures transparent and efficient data transfer.
