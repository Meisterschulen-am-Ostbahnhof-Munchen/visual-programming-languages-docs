# AUDI_TO_AW

![AUDI_TO_AW](./AUDI_TO_AW.svg)

* * * * * * * * * *
## Introduction

The **AUDI_TO_AW** function block is a composite function block for converting an **AUDI adapter** (UDINT) to an **AW adapter** (WORD). It serves as a unidirectional bridge between different data types and enables the seamless integration of components based on different adapter interfaces.
The block encapsulates the conversion logic and is typically used in automation projects according to IEC 61499 that require the adaptation of data types between adapters.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|---------------|
| (via AUDI_IN.E1) | EVENT | Event that triggers the conversion (provided by the connected AUDI adapter) |

### **Event Outputs**

| Name | Type | Description |
|------|-----|--------------|
| (via AW_OUT.E1) | EVENT | Output event after successful conversion (provided by the AW adapter) |

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| (via AUDI_IN.D1) | UDINT | 32-bit unsigned integer to be converted (provided by the AUDI adapter) |

### **Data Outputs**

| Name | Type | Description |
|------|-----|--------------|
| (via AW_OUT.D1) | WORD | 16-bit unsigned integer (result of the conversion, provided by the AW adapter) |

### **Adapter**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| AUDI_IN | adapter::types::unidirectional::AUDI | Socket (Input) | Receives the UDINT signal and its associated event |
| AW_OUT | adapter::types::unidirectional::AW | Plug (Output) | Passes on the converted WORD signal and its output event |

## Functionality

The function block operates as a **Composite FB** containing a single IEC 61131 conversion block `F_UDINT_TO_WORD`. Processing proceeds as follows:

1. The socket `AUDI_IN` receives an event at its event input `E1` and the corresponding data value `D1` (UDINT).
2. This event is internally forwarded to the `REQ` input of the conversion block, while the UDINT value is passed to the `IN` input.
3. The conversion block converts the UDINT value into a WORD and signals completion via its `CNF` output. 4. The `CNF` event is passed to the event output `E1` of plug `AW_OUT`, and the converted WORD is output to its data output `D1`.

The entire process is **event-driven** and takes place within a single execution step.

## Technical Features

- **Unidirectional Data Flow**: The function block converts exclusively from AUDI (UDINT) to AW (WORD); reverse conversion is not supported.
- **Composite Architecture**: The internal logic is fully implemented by a single standard conversion block, making the function block easy to understand and maintain.
- **Use of IEC 61131 libraries**: The function block `F_UDINT_TO_WORD` is derived from the `iec61131::conversion` library, ensuring high portability and standards compliance.
- **No dedicated state machine**: The function block does not have an ECC (Execution Control Chart) and operates purely in a data flow-oriented manner.

## State overview

The function block does **not have a state machine**. Processing is event-driven and deterministic according to the internal wiring. There are no internal states or latencies.

## Application scenarios

- **Interface adaptation**: A system provides data via an AUDI adapter (UDINT), but a subsequent function block expects an AW adapter (WORD). The AUDI_TO_AW adapter converts the data without manual programming.
- **Data consolidation**: In a controller, multiple sensor data from different adapter types need to be combined. This function block serves as a conversion element.
- **Legacy Integration**: Older components based on UDINT are to be integrated into a modern WORD-based architecture.

## Comparison with Similar Function Blocks

- **F_WORD_TO_UDINT** (analogous, but in reverse): Converts WORD to UDINT and expects an AW input and an AUDI output.
- **General Conversion Function Blocks** such as `F_UDINT_TO_DINT` or `F_UDINT_TO_REAL` offer similar functionality but work with different data types and without adapter connections.
- **Custom Adapter Converters** can be implemented by combining several conversion function blocks and adapters, but are less encapsulated than this composite function block.

## Conclusion

The **AUDI_TO_AW** is a specialized but essential component for adapter-based communication in IEC 61499 systems. By using a standardized conversion block and encapsulating it in a composite function block, it offers a clean, reusable, and testable solution for converting UDINT to WORD data within a unidirectional adapter path.
