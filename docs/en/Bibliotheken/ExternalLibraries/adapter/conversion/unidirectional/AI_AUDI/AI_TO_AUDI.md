# AI_TO_AUDI

![AI_TO_AUDI](./AI_TO_AUDI.svg)

* * * * * * * * * *
## Introduction

The function block `AI_TO_AUDI` is a composite module that converts an **AI adapter** (data of type `INT`) into an **AUDI adapter** (data of type `UDINT`). It serves as a unidirectional interface between different adapter types and enables seamless data conversion within the 4diac IDE.
## Interface Structure

The module does not have traditional event and data inputs/outputs, but instead implements its inputs and outputs via **adapter interfaces**. The following ports are available via the internal adapters:

### Event Inputs

| Port | Adapter | Description |
|--------|---------|-------------------------------------------|
| `E1` | `AI_IN` | Starts the conversion of the INT value. |

### Event Outputs

| Port | Adapter | Description |
|--------|-----------|-------------------------------------------|
| `E1` | `AUDI_OUT`| Signals completion of the conversion. |

### Data Inputs

| Port | Adapter | Data Type | Description |
|--------|---------|----------|----------------------------------|
| `D1` | `AI_IN` | `INT` | Integer value to be converted. |

### Data Outputs

| Port | Adapter | Data Type | Description |
|--------|-----------|----------|--------------------------------|
| `D1` | `AUDI_OUT`| `UDINT` | Converted unsigned integer. |

### Adapter

| Direction | Name | Type | Description |
|----------|------------|------------------------------|-----------------------------|
| Socket | `AI_IN` | `adapter::types::unidirectional::AI` | Input adapter (INT). |
| Plug | `AUDI_OUT` | `adapter::types::unidirectional::AUDI` | Output adapter (UDINT). |

## Functionality

The function block is implemented as a composite function block. Internally, it uses the standard conversion function block `iec61131::conversion::F_INT_TO_UDINT`.

**Process:**

1. An event arrives at the input `E1` of socket `AI_IN`, accompanied by an INT value at `D1`.
2. This event is forwarded to the internal function block `Convert` (type `F_INT_TO_UDINT`).
3. The internal function block performs the type conversion from `INT` to `UDINT` (according to IEC 61131-3).
4. After successful conversion, an event is generated at the output `CNF` of the internal function block.
5. This event is passed to plug `AUDI_OUT` (event output `E1`), and simultaneously the converted UDINT value is available at data output `D1`.

This event is passed to plug `AUDI_OUT` (event output `E1`), and the converted UDINT value is simultaneously available at data output `D1`.

... The connections in the FBNetwork are:

- `AI_IN.E1` → `Convert.REQ`
- `Convert.CNF` → `AUDI_OUT.E1`
- `AI_IN.D1` → `Convert.IN`
- `Convert.OUT` → `AUDI_OUT.D1`

## Technical Features

- **Composite Block:** Simplifies the reuse and encapsulation of the conversion logic.
- **Standard Conversion:** Uses the IEC 61131-3 block `F_INT_TO_UDINT`, which ensures clean and portable type conversion.
- **Unidirectional Adapters:** Both the input and output adapters are implemented as unidirectional interfaces (socket and plug, respectively) – data flows in only one direction.
- **Event-driven:** The conversion is triggered by an event at the input adapter and acknowledged by an event at the output adapter (handshake principle).

## State Overview

The function block itself does not have its own state machine, as it consists solely of a direct chain of adapter ports and the internal conversion block. The internal function block `F_INT_TO_UDINT` performs the conversion in one step – therefore, a state overview is not required.

## Application Scenarios

- **Data Bridge Between Different Adapter Types:** When a higher-level system or library provides adapters of type `AI` (with INT data), but downstream components expect a `AUDI` adapter (with UDINT data).
- **Signal Conversion in Automation Solutions:** For example, when processing counter values or position data that arrive as signed 16-bit values but must be passed on as unsigned 32-bit values.
- **Modular Adapter Conversion:** Easily replace or extend the conversion logic by replacing the internal function block.

## Comparison with Similar Function Blocks

Other adapter conversion function blocks exist in the library, e.g. B.:

- `AI_TO_AI` – forwarding without conversion
- `AUDI_TO_AI` – reverse direction (UDINT → INT)
- Direct use of the `F_INT_TO_UDINT` block with manual adapter wiring

The `AI_TO_AUDI` block not only encapsulates the type conversion but also the complete adapter connection, making the design clearer and preventing errors due to incorrect wiring.

## Conclusion

The `AI_TO_AUDI` composite block offers a simple yet clean solution for converting an INT-based adapter protocol to a UDINT-based protocol. Thanks to the use of the standardized IEC block and event-driven coupling, it is reliable and easily integrated into larger 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
