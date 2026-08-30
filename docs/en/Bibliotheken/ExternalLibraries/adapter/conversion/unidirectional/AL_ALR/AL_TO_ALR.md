# AL_TO_ALR

![AL_TO_ALR](./AL_TO_ALR.svg)

* * * * * * * * * *

## Introduction

The function block **AL_TO_ALR** is a composite function block (FB) that maps a unidirectional AL adapter (LWORD) onto a unidirectional ALR adapter (LREAL). Internally, it uses the block `F_LWORD_TO_LREAL`.

> **⚠️ Warning — not a numeric value conversion:** `LWORD` is a bit-string type (not a signed integer), and `F_LWORD_TO_LREAL` in the FORTE core merely reinterprets the 64-bit pattern as an IEEE754 `LREAL` (a bit copy) — the same trap as [`AD_TO_AR`](../AD_AR/AD_TO_AR.md) (DWORD→REAL), just with the 64-bit counterparts. A raw counter or analog value will therefore **not** become the corresponding LREAL number, but a meaningless value. For an actual numeric conversion: chain `AL_TO_AULI` (bit-reinterpretation LWORD→ULINT, valid here since both share the same 64-bit unsigned-integer representation) followed by `AULI_TO_ALR` (a real numeric cast) — the same pattern as [`AD_TO_AR_NUM`](../AD_AR/AD_TO_AR_NUM.md) for the 32-bit case.
## Interface Structure

### **Event Inputs**

The FB does not have direct event inputs. The event required to trigger the conversion is provided via the socket **AL_IN** (type `AL`). This event (E1) is internally connected to the `REQ` input of the conversion block.

### **Event Outputs**

The function block (FB) does not have direct event outputs. The conversion completion event is output via the plug **ALR_OUT** (type `ALR`). The event (E1) of the internal block (`CNF`) is forwarded to the output adapter.

### **Data Inputs**

The function block (FB) does not have direct data inputs. The LWORD value to be converted is provided via the **AL_IN** socket (data signal D1) and passed to the `IN` input of the conversion block.

### **Data Outputs**

The function block has no direct data outputs. The converted LREAL value is output via the **ALR_OUT** plug (data signal D1); it originates from the `OUT` output of the internal block.

### **Adapters**

| Adapter | Direction | Type | Description |
| --------- | ---------- | ----- | -------------- |
| **AL_IN** | Socket (Input) | `adapter::types::unidirectional::AL` | LWORD adapter that provides the input signal (LWORD) and a trigger event. |
| **ALR_OUT** | Plug (Output) | `adapter::types::unidirectional::ALR` | LREAL adapter that outputs the converted signal (LREAL) and an acknowledgment event. |

## Functionality

`F_LWORD_TO_LREAL` reinterprets the LWORD's 64-bit pattern as an IEEE754 `LREAL` (a bit copy) — **no** numeric value conversion takes place. The function block operates in a simple event-driven sequence:

1. An incoming event at socket **AL_IN.E1** is forwarded to the `REQ` input of the internal function block `F_LWORD_TO_LREAL`.
2. Simultaneously, the data value from **AL_IN.D1** (LWORD) is passed to the `IN` input of the converter.

3. The internal function block (FB) performs the conversion `LWORD → LREAL`.

4. After the conversion is complete, the event `CNF` is sent to the plug **ALR_OUT.E1**.
5. The converted LREAL value is output to **ALR_OUT.D1**.

The entire processing takes place within one clock cycle (no blocking).

## Technical Features

- **Adapter-based interface**: The FB uses only unidirectional adapters (`AL` and `ALR`). This enables loose coupling between sender and receiver and easy reuse in different system architectures.
- **⚠️ Bit-reinterpretation, not numeric conversion**: See the warning in the introduction — affects all bit-string source types converting to `AR`/REAL or `ALR`/LREAL; the only other instance in this library is [`AD_TO_AR`](../AD_AR/AD_TO_AR.md) (DWORD→REAL).
- **Pass-Through Event Control**: The function block does not execute any internal state logic; it transparently forwards events and data. The call time corresponds to the execution time of the internal converter.

## State Overview

The assembled function block itself has **no states of its own**. The processing is entirely controlled by the internally used function block `F_LWORD_TO_LREAL`, which exhibits the following minimal state behavior:

- **IDLE**: Waiting for a `REQ` event.
- **CONVERT**: Executing the conversion (immediately after `REQ`).
- **SEND**: Outputting the `CNF` event and the converted value.

Since the internal function block operates in a single execution step, the states are not externally observable.

## Application Scenarios

- **Bit pattern pass-through**: `AL_IN` already carries a bit pattern meant to be interpreted as LREAL (e.g. serialized raw double data from a fieldbus/protocol).
- **NOT suitable** for raw counter, analog, or other integer values meant to carry the same numeric value as LREAL — use `AL_TO_AULI` + `AULI_TO_ALR` for that.

## Comparison with Similar Function Blocks

- **`AL_TO_AULI` + `AULI_TO_ALR`** (numeric, LWORD→ULINT→LREAL): the safe replacement when an actual numeric value is meant.
- **`ALI_TO_ALR`/`AULI_TO_ALR`** (LINT/ULINT→LREAL): already numerically correct, since their source types are `ANY_INT` (not `ANY_BIT`) — no trap.
- **[`AD_TO_AR`](../AD_AR/AD_TO_AR.md)** (DWORD→REAL): the same bit-reinterpretation trap, just with the 32-bit counterparts.

## Conclusion

`AL_TO_ALR` offers a compact way to expose an LWORD bit pattern as LREAL via adapter interfaces — **but not a numeric value conversion**. For raw counter or analog values meant to carry the same numeric value in LREAL, use `AL_TO_AULI` + `AULI_TO_ALR`.

---

### 📖 Background

* [Numeric vs. bitwise: the FORTE conversion trap](../Numeric_vs_Bitwise.md)
