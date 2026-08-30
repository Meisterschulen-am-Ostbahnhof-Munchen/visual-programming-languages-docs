# AD_TO_AR

![AD_TO_AR](./AD_TO_AR.svg)

* * * * * * * * * *

## Introduction

The **AD_TO_AR** function block is a composite function block that maps a DWORD value from a unidirectional AD adapter (socket) onto a REAL value at an AR adapter (plug).

> **⚠️ Warning — not a numeric value conversion:** `AD_TO_AR` internally uses `F_DWORD_TO_REAL`, which in the FORTE core is a pure IEEE754 **bit-reinterpretation** for bit-string source types (BYTE/WORD/DWORD/LWORD), not a numeric cast. A raw counter or analog value such as `DWORD#2048` will therefore **not** become `REAL#2048.0`, but a meaningless value near zero. For an actual numeric DWORD→REAL conversion, see [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md) (via UDINT). `AD_TO_AR` is only correct when `AD_IN` is already a bit pattern meant to be interpreted as REAL (e.g. the result of `F_REAL_TO_DWORD`).
## Interface Structure

The function block has no direct (individual) event or data inputs/outputs. All communication takes place via two adapter interfaces:

### **Event Inputs**

- *No direct event inputs* – event control is handled via the incoming adapter.

### **Event Outputs**

- *No direct event outputs* – event output is handled via the outgoing adapter.

### **Data Inputs**

- *No direct data inputs* – data is received via the incoming adapter.

### **Data Outputs**

- *No direct data outputs* – data is output via the outgoing adapter.

### **Adapters**

| Name | Type | Direction | Description |
| -------- | -------------------------------------------- | ---------- | ---------------------------------------------------------------------------- |
| AD_IN | `adapter::types::unidirectional::AD` | Socket | Receives an event (E1) and a DWORD value (D1) for conversion. |
| AR_OUT | `adapter::types::unidirectional::AR` | Plug | Sends an event (E1) with the converted REAL value (D1). |

## Functionality

The function block operates as an event-driven pipeline:

1. An incoming event at socket **AD_IN.E1** triggers the conversion.
2. The data value **AD_IN.D1** (DWORD) is passed to the internal function block `F_DWORD_TO_REAL`.
3. After successful conversion, the internal function block signals an output event (**CNF**).
4. This event is forwarded to plug **AR_OUT.E1**, and simultaneously, the converted REAL value is output via **AR_OUT.D1**.

`F_DWORD_TO_REAL` merely reinterprets the DWORD's 32-bit pattern as an IEEE754 `REAL` (a bit copy) — **no** numeric value conversion takes place.

## Technical Features

- **⚠️ Bit-reinterpretation, not numeric conversion**: See the warning in the introduction. This affects all bit-string source types (`AB`/BYTE, `AW`/WORD, `AD`/DWORD, `AL`/LWORD) converting to `AR`/REAL or `ALR`/LREAL — the only other instance in this library is [`AL_TO_ALR`](../AL_ALR/AL_TO_ALR.md) (LWORD→LREAL).
- **Composite Function Block**: The conversion logic is implemented entirely within an internal network consisting of a single function block.
- **Type Conversion via Adapter**: This function block enables the connection of components that communicate exclusively via adapter interfaces, eliminating the need for additional manual conversions.
- **Standard Compliance**: Utilizes the IEC 61131 library function `F_DWORD_TO_REAL`, making it portable and well-tested.
- **Unidirectional Adapters**: Both input and output adapters are unidirectional, meaning data flows in only one direction.

## State Overview

The function block does not have its own state machine. Processing is strictly causal: An event at the input immediately triggers the conversion and output. There are no delays or intermediate states.

## Application Scenarios

- **Bit pattern pass-through**: `AD_IN` already carries a bit pattern meant to be interpreted as REAL (e.g. the result of an `F_REAL_TO_DWORD` elsewhere in the network, or deserialized raw float data from a fieldbus/protocol).
- **NOT suitable** for raw counter, analog, or other integer values meant to carry the same numeric value as REAL — use [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md) for that.

## Comparison with Similar Function Blocks

- **`AD_TO_AR_NUM`** (numeric, DWORD→UDINT→REAL): the safe replacement when an actual numeric value is meant.
- **`AI_TO_AR`/`ADI_TO_AR`/`AUDI_TO_AR`** (INT/DINT/UDINT→REAL): already numerically correct, since their source types are `ANY_INT` (not `ANY_BIT`) — no trap.
- **`AL_TO_ALR`** (LWORD→LREAL): the same bit-reinterpretation trap, just with the 64-bit counterparts.

## Conclusion

The **AD_TO_AR** block offers a compact way to expose a DWORD bit pattern as REAL via adapter interfaces — **but not a numeric value conversion**. For raw counter or analog values meant to carry the same numeric value in REAL, use [`AD_TO_AR_NUM`](./AD_TO_AR_NUM.md).

---

### 📖 Background

* [Numeric vs. bitwise: the FORTE conversion trap](../Numeric_vs_Bitwise.md)

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
