# ALR_TO_AI

![ALR_TO_AI](./ALR_TO_AI.svg)

* * * * * * * * * *
The **ALR_TO_AI** function block is a composite block that converts an ALR (LREAL data) adapter to an AI (INT data) adapter. It is used to convert signals from agricultural technology (e.g., sensor values) to a standardized integer-based adapter interface. The block encapsulates the conversion and event forwarding, thus simplifying integration into existing 4diac applications.

The function block does not have its own top-level event inputs. Event control is handled via the connected socket `ALR_IN`:

| Input | Type | Description |
| `ALR_IN` | ALR (Socket) | Adapter that triggers the conversion via its event (`E1`) |

The FB does not have any independent event outputs at the top level. Event feedback is provided via the connected plug `AI_OUT`:

| Output | Type | Description |
|---------|-----|---------------|
| `AI_OUT` | AI (Plug) | Adapter that outputs the converted event (`E1`) after successful conversion |

The **data input signal** is provided via socket `ALR_IN`:

| Adapter Input | Data Type | Description |
-----------------|----------|--------------|
| `ALR_IN.D1` | LREAL | The floating-point value to be converted |

The **data output signal** is provided via plug `AI_OUT`:

| Adapter Output | Data Type | Description |
-----------------|----------|--------------|
| `AI_OUT.D1` | INT | The converted integer value |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

The function block has two adapter interfaces:

- **Socket (Input)**: `ALR_IN` – Adapter for unidirectional LREAL data (Type `adapter::types::unidirectional::ALR`)
- **Plug (Output)**: `AI_OUT` – Adapter for unidirectional INT data (Type `adapter::types::unidirectional::AI`)

## Functionality

The **ALR_TO_AI** function block contains an internal conversion block `F_LREAL_TO_INT` from the IEC 61131 library.

1. When socket `ALR_IN` sends an event at its output `E1`, it is forwarded to the input `REQ` of the internal converter.
2. The converter transforms the incoming LREAL value (`ALR_IN.D1`) into an INT value and outputs the result via its output `OUT`, along with an acknowledgment event `CNF`.
3. The `CNF` event is passed to plug `AI_OUT.E1`, informing the downstream component about data availability.
4. In parallel, the converted INT value is applied to the data output `AI_OUT.D1`.

The entire process is synchronous and performed in a single step.

- The function block (FB) is a **composite function block** – it does not have its own state machine (ECC) but implements the logic via an internal subnetwork.
- The conversion follows the IEC 61131-3 function `LREAL_TO_INT`: decimal places are truncated (truncation to zero), and overflows or underflows are implementation-dependent.
- The function block is designed as a unidirectional adapter coupling – no feedback channels are supported.

As a composite FB, **ALR_TO_AI** does not have its own state diagram. The internal converter `F_LREAL_TO_INT` operates in an event-driven manner: An event at input `REQ` triggers the conversion, and output `CNF` signals the end of the operation. The function block behaves like a transparent block for event and data forwarding.

- **Sensor Value Processing**: Conversion of an LREAL signal (e.g., from an analog sensor adapter) into an INT signal, which is then processed by a PLC or a controller with integer-based adapters.
- **Adapter Bridge**: Connecting adapter types of different physical units when only the data type, not the scaling, needs to be changed.
- **Interface Adaptation**: Used in agricultural control systems (e.g., HR Agricultural Technology – general), where LREAL values from sensors are mapped to a CAN-based INT adapter interface.

| FB | Function | Difference |
|----|----------|-------------|
| **ALR_TO_AI** | Converts LREAL → INT via adapter | Composite, no dedicated state machine; uses IEC 61131 converter |
| `F_LREAL_TO_INT` | Pure data conversion without adapter | Direct FB, requires separate adapter connection |
| `AI_TO_ALR` | Reverse direction INT → LREAL | Different data type and conversion direction |

The **ALR_TO_AI** function block simplifies reuse by encapsulating the adapter logic and conversion in a single block.

The **ALR_TO_AI** is a practical composite function block for the standardized conversion of LREAL-based to INT-based adapter interfaces. It allows for a clean separation of data conversion and adapter logic and facilitates integration into larger automation projects. Thanks to its clear event forwarding and the use of an IEC 61131 basic function, it is reliable and easy to use.

---

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
