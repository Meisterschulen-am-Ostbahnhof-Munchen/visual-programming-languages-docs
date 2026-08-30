# AL_TO_ALI

![AL_TO_ALI](./AL_TO_ALI.svg)

* * * * * * * * * *
## Introduction

The function block `AL_TO_ALI` is a composite function block (FB) for converting an AL adapter (LWORD) to an ALI adapter (LINT). It serves as an interface between LWORD-based and LINT-based data communication within the control logic. Internally, the block uses the conversion block `F_LWORD_TO_LINT` to perform the actual type conversion.
## Interface Structure

### **Event Inputs**

*The function block does not have its own event inputs. Event control is handled via the connected adapters.*

### **Event Outputs**

*The function block does not have its own event outputs. Event control is handled via the connected adapters.*

### **Data Inputs**

*This function block does not have its own data inputs. Input data is provided via socket `AL_IN`.*

### **Data Outputs**

*This function block does not have its own data outputs. Output data is provided via plug `ALI_OUT`.*

### **Adapters**

| Type | Name | Direction | Data Type | Description |
|-----|------|----------|-----------|-------------|
| `adapter::types::unidirectional::AL` | `AL_IN` | Socket (Input) | LWORD | LWORD adapter as input interface. Provides the data to be converted. |
| `adapter::types::unidirectional::ALI` | `ALI_OUT` | Plug (Output) | LINT | LINT adapter as output interface. Delivers the converted data. |

## Functionality

1. **Event Triggering:** The `AL_IN` adapter sends a signal via its event output `E1` as soon as new data is available.
2. **Conversion:** This event triggers the internal function block `Convert` (`F_LWORD_TO_LINT`) at its event input `REQ`. Simultaneously, the current data value of `AL_IN.D1` (LWORD) is transferred to the data input `IN` of the conversion module.
3. **Output:** After successful conversion, `Convert` sends an acknowledgment via its event output `CNF` to the `ALI_OUT` adapter (event input `E1`). In parallel, the converted LINT value is forwarded from output `OUT` to the data input `ALI_OUT.D1`.
4. **Result:** The `ALI_OUT` adapter now forwards the new LINT data to the connected function block.

## Technical Features

- **Type Conversion:** This function block converts an LWORD (64-bit sequence) into a LINT (64-bit signed integer). The conversion is bit-for-bit, meaning the binary representation is interpreted as a signed integer.
- **Composition:** This is a composite function block that does not contain its own logic but relies on the standardized conversion function block `iec61131::conversion::F_LWORD_TO_LINT`.
- **Adapter-Based Interface:** Input and output are exclusively via unidirectional adapters (`AL` and `ALI`), enabling a modular and type-checked connection in the 4diac IDE.
- **Adapter-Based Interface:** - **Package Structure:** The FB is located in the package `adapter::conversion::unidirectional`.

## State Overview

Since this is a composite FB, there is no separate state machine. The state logic is entirely determined by the internally used block `F_LWORD_TO_LINT`. This block operates in an event-driven manner:

- **IDLE:** Wait for an event at the `REQ` input.
- **PROCESSING:** Convert the LWORD to LINT (takes one step).
- **FINISHED:** Output the converted value and send the `CNF` event.

## Application Scenarios

- **PLC Data Conversion:** When a control program receives LINT values (e.g., counter readings or times) via an LWORD-based adapter and a LINT interface is required.
- **Communication Adapter:** Used as an intermediary in an adapter chain to translate different data types between various hardware or software modules.
- **Protocol Adaptation:** For example, converting raw LWORD data (e.g., from a bus system) into a LINT representation for further processing in the control logic.

## Comparison with Similar Function Blocks

- **AL_TO_AL (LWORD ↔ LWORD):** Simple pass-through without conversion.
- **ALI_TO_AL (LINT ↔ LWORD):** Performs the reverse conversion.
- **F_LWORD_TO_LINT (direct conversion block):** Offers the same functionality, but without an adapter interface. `AL_TO_ALI` encapsulates this block and adds the adapter connection.

## Conclusion

The `AL_TO_ALI` function block is a simple yet important converter that bridges the gap between LWORD-based and LINT-based adapter interfaces. Its composite structure keeps it clear and allows for flexible integration into existing 4diac projects. The use of standard conversion blocks ensures correct and efficient type conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
