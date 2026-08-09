# ALR_TO_AULI

![ALR_TO_AULI](./ALR_TO_AULI.svg)

* * * * * * * * * *
## Introduction

The function block **ALR_TO_AULI** is a **composite FB** for the unidirectional conversion of an **LREAL adapter signal** (type `ALR`) into a **ULINT adapter signal** (type `AULI`). By internally using the IEC 61131 standard FB `F_LREAL_TO_ULINT`, the floating-point number (LREAL) is converted into an unsigned integer (ULINT) and provided via an output adapter. This block is particularly suitable for integrating floating-point data sources into systems that expect an integer adapter interface.
## Interface Structure

The FB has **no direct** event or data inputs/outputs. Communication takes place exclusively via the two **adapters** (socket & plug). The following tables describe the signals provided via the adapters.

### **Event Inputs**

| Signal | Source | Data Type | Description |
|--------|--------|----------|-------------|
| E1 | via Socket `ALR_IN` | (Event) | Starts the conversion of an incoming LREAL value. |

### **Event Outputs**

| Signal | Destination | Data Type | Description |
|--------|------|-----------|--------------|
| E1 | via Plug `AULI_OUT` | (Event) | Signals that the converted ULINT value is present at the output. |

### **Data Inputs**

| Signal | Source | Data Type | Description |
|--------|--------|----------|-------------|
| D1 | via Socket `ALR_IN` | LREAL | The floating-point value to be converted. |

### **Data Outputs**

| Signal | Destination | Data Type | Description |
|--------|------|----------|--------------|
| D1 | via Plug `AULI_OUT` | ULINT | The converted unsigned integer value. |

### **Adapter**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| `ALR_IN` | `adapter::types::unidirectional::ALR` | Socket (Input) | Receives the LREAL value and its associated event. |
| `AULI_OUT` | `adapter::types::unidirectional::AULI` | Plug (Output) | Outputs the converted ULINT value with an acknowledgment event. |

## Functionality

The FB operates according to the **gearbox principle** of a composite block:

1. An incoming **event E1** at socket `ALR_IN` activates the internal FB `F_LREAL_TO_ULINT` (type `iec61131::conversion::F_LREAL_TO_ULINT`).
2. Simultaneously, the **data value D1** (LREAL) present at socket `ALR_IN` is forwarded to the input `IN` of the internal FB.
3. The internal FB immediately performs the conversion from LREAL to ULINT and outputs the result at its output `OUT`.
4. The event `CNF` of the internal function block triggers the **output event E1** at plug `AULI_OUT`.
5. The converted ULINT value is simultaneously applied to the data output `D1` of plug `AULI_OUT`.

The entire conversion is **event-driven** and without its own state logic.

## Technical Features

- **License**: The function block is provided under the **Eclipse Public License 2.0** (see copyright notice).
- **Standard Compliance**: The internally used conversion block `F_LREAL_TO_ULINT` complies with the IEC 61131-3 standard.
- **No State Machine**: As a composite function block (FB), this block has no inherent state logic – the conversion is purely combinatorial.
- **Unidirectional Adapters**: Input and output are separate adapter types that define a clear signal direction.

## State Overview

Since this is a **composite FB without its own state machine**, there is no explicit state overview. The functionality is event-triggered and behaves like a **combinatorial function**: An event at the input, after internal processing, results in exactly one event at the output.

## Application Scenarios

- **Connecting floating-point sensors** to a controller that only processes integer adapter signals (e.g., in agricultural technology).
- **Data processing** in an adapter-based communication chain when the source delivers LREAL, but the destination expects ULINT.
- **Replacement of manual type conversions** in systems that rely on the standardized IEC 61131 functions.

## Comparison with similar function blocks

Other conversion adapters (e.g., `REAL_TO_DINT`, `LREAL_TO_LINT`) follow the same pattern: They use an internal IEC function block and encapsulate the type conversion in an adapter interface. The advantage of `ALR_TO_AULI` lies in the **targeted combination of LREAL and ULINT** – a type combination that is not offered as a ready-made adapter in many standard libraries.

## Conclusion

ALR_TO_AULI` is a specialized **composite adapter function block** for lossy conversion of floating-point numbers to integers. Thanks to the use of a standardized IEC function block, the conversion is deterministic and easily testable. The function block is ideally suited for creating a clean adapter interface between LREAL and ULINT domains in heterogeneous automation systems.
