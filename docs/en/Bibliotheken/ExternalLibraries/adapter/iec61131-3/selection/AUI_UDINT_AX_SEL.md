# AUI_UDINT_AX_SEL

![AUI_UDINT_AX_SEL](./AUI_UDINT_AX_SEL.svg)

* * * * * * * * * *
## Introduction

The function block **AUI_UDINT_AX_SEL** performs a binary selection between two input values. It is implemented as a combination of an internal IEC 61131 function block `F_SEL` and a unidirectional adapter `AX`. The selector provided by the adapter determines which of the two data inputs is passed to the output. The function block is suitable for simple switching logic where the choice between two signals depends on an external criterion (e.g., coupled in via an adapter).
## Interface Structure

### **Event Inputs**

| Event | Data Type | Comment |
|----------|----------|-----------|
| `EI0` | Event | Sets the value of `IN0` and triggers a selection. |
| `EI1` | Event | Sets the value of `IN1` and triggers a selection. |

### **Event Outputs**

| Event | Data Type | Comment |
|----------|-----------|-----------|
| `CNF` | Event | Confirmation of successful selection and update of `OUT`. |

### **Data Inputs**

| Variable | Data Type | Comment |
|----------|-----------------|-----------|
| `IN0` | `UINT` | Selectable input value (first alternative). |
| `IN1` | `ANY_ELEMENTARY`| Selectable input value (second alternative). |

*Note:* `IN1` is declared as an arbitrary elementary data type (`ANY_ELEMENTARY`). Actual compatibility with the output type `UINT` depends on the elementary type used (implicit or explicit conversion is required depending on the target system).

### **Data Outputs**

| Variable | Data Type | Comment |
|----------|----------|-----------|
| `OUT` | `UINT` | The selected input value (either `IN0` or `IN1`). |

### **Adapters**

| Adapter | Type | Comment |
|---------|-----------------------------------------|-----------|
| `G` | `adapter::types::unidirectional::AX` | Returns the selection criterion (e.g., a Boolean signal or a numeric value). |

## Functionality

This function block encapsulates the IEC 61131 function block `F_SEL` (binary selection). The selection occurs synchronously with the events `EI0` or `EI1`:

1. When either `EI0` or `EI1` is triggered, the corresponding data input is updated simultaneously, and the event `REQ` of the internal `F_SEL` is triggered.

`` 2. The internal function `F_SEL` checks the signal `G.D1` provided via the adapter `G`:

- If `G.D1 = 0` is false (i.e., logically incorrect), the value of `IN0` is passed to `OUT`.
- If `G.D1 ≠ 0` is true (i.e., logically correct), the value of `IN1` is passed to `OUT`.
3. After the selection is complete, `F_SEL` confirms with the event `CNF`, which is then forwarded as the output event of the entire function block.

`` The adapter `G` is connected to the application as a unidirectional socket and continuously provides the selection signal.

## Technical Features

- The function block (FB) is implemented as a **composition** (internal FB network), therefore its behavior cannot be adjusted at the ECC level.
- The input type `IN1` is declared as `ANY_ELEMENTARY` – this allows the use of various elementary data types, but requires type-safe wiring at the application level.
- The output `OUT` is permanently declared as `UINT`. If `IN1` has a different elementary type, either an implicit conversion must be performed in the target system or an explicit adjustment must be made.

`` - The function block requires a connected adapter of type `AX`. If this adapter is missing, the internal `F_SEL` is not wired correctly, and the behavior is undefined.

## State Overview

The function block does not have an explicit state machine. Its behavior is defined solely by the internal `F_SEL`:

- Waiting for an event (`EI0` or `EI1`).
- Upon arrival of an event: Read the associated data and the selector signal from the adapter.
- Output the signal via `CNF` and update `OUT`.

There are no internal states that persist beyond the response time of an event.

## Application Scenarios

- **Switching between two sensor data points** in agricultural technology, depending on an operating mode (e.g., speed vs. torque).
- **Signal Redundancy**: Selection between a primary and a backup signal, controlled by an error status (e.g., via an adapter).
- **Configurable Constants**: A parameter (e.g., `IN0`) is replaced by a value selected via the adapter (e.g., `IN1`).

## Comparison with Similar Function Blocks

- **EtherNet/IP & PROFINET Function Blocks**: Often implemented as function blocks or blocks with state machines. In contrast, `AUI_UDINT_AX_SEL` is component-based and uses the standardized IEC 61131 function block `F_SEL`.

**EtherNet/IP & PROFINET Function Blocks**: Often implemented as function blocks or blocks with state machines. - **`SEL` (Standard IEC 61499 Block)**: Usually available as an ECC variant. The function block described here offers decoupled input of the selector via the adapter, which simplifies reuse in different contexts.

- **Custom Selection Blocks**: Can support multiple channels or other data types. `AUI_UDINT_AX_SEL` is specialized for two inputs and the output type `UINT`.

## Conclusion

The function block `AUI_UDINT_AX_SEL` represents a simple, adapter-controlled binary selection. It is particularly suitable for applications where a selection signal is provided externally (e.g., via a sensor or bus adapter). Thanks to the encapsulation of the proven `F_SEL` from IEC 61131, the selection behavior is deterministic and reliable. Limitations regarding the data type compatibility of `IN1` must be considered during wiring. Overall, a useful, clearly structured basic building block for switching logic in IEC 61499 applications.
