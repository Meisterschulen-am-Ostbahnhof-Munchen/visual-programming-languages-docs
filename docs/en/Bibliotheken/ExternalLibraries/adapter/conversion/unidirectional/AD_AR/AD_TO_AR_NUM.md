# AD_TO_AR_NUM

![AD_TO_AR_NUM](./AD_TO_AR_NUM.svg)

* * * * * * * * * *
## Introduction

The function block **AD_TO_AR_NUM** is the numerically correct alternative to [`AD_TO_AR`](./AD_TO_AR.md): it converts a DWORD value from a unidirectional AD adapter (socket) into a REAL value output via an AR adapter (plug), via an internal UDINT step — an **actual value conversion**, not a bit-reinterpretation.

## Why not just use AD_TO_AR?

`AD_TO_AR` internally uses `F_DWORD_TO_REAL`, which in the FORTE core is a pure IEEE754 bit-reinterpretation for bit-string source types (BYTE/WORD/DWORD/LWORD), not a numeric cast. A raw counter or analog value such as `DWORD#2048` would therefore **not** become `REAL#2048.0`, but a meaningless value near zero (see [`AD_TO_AR`](./AD_TO_AR.md) and `AD_TO_AR_TODO.md` for the derivation).

## Interface Structure

The function block has no direct (individual) event or data inputs/outputs. All communication takes place via two adapter interfaces:

### **Adapters**

| Name | Type | Direction | Description |
|--------|--------------------------------------------|----------|----------------------------------------------------------------------------|
| AD_IN | `adapter::types::unidirectional::AD` | Socket | Receives an event (E1) and a DWORD raw value (D1) for conversion. |
| AR_OUT | `adapter::types::unidirectional::AR` | Plug | Sends an event (E1) with the numerically converted REAL value (D1). |

## Functionality

The function block works in two stages instead of a single (dangerous) one:

1. An incoming event at socket **AD_IN.E1** triggers the conversion.
2. The data value **AD_IN.D1** (DWORD) is passed to `ToUDINT` (`F_DWORD_TO_UDINT`) — a bit-reinterpretation DWORD→UDINT that is **valid** here, since both types share the same 32-bit unsigned-integer representation.
3. `ToUDINT.CNF` triggers `ToREAL` (`F_UDINT_TO_REAL`) — a **real numeric cast** that correctly converts the UDINT numeric value to REAL.
4. The result is output via plug **AR_OUT.E1**/**AR_OUT.D1**.

## Technical Features

- **Identical interface to `AD_TO_AR`**: `AD_TO_AR_NUM` is a drop-in replacement — same socket/plug types (`AD`/`AR`), easily swapped in once it's clear a numeric value (not a bit pattern) is intended.
- **Two-stage DWORD→UDINT→REAL chain**: the same chain already wired by hand in several exercises (`Uebung_028a_AR` and others), packaged here as a single block.
- **No precision loss in the relevant value range**: `UDINT` (32 bit, max. 4,294,967,295) transfers into `REAL` (IEEE754 single precision, 24-bit mantissa) without loss as long as the value stays within the exactly representable integers (up to 2²⁴ = 16,777,216) — not an issue for typical analog/counter raw values (e.g. 0–64255 or 0–4095).

## Application Scenarios

- **Raw analog values**: An analog input or counter delivers a DWORD raw value (e.g. 0–4095, 0–64255) that should be further processed as an actual numeric value in REAL (scaling, display, OPC-UA publish).
- **Replacement for the manual `AD_TO_AUDI` + `AUDI_TO_AR` chain**: where two separate adapter instances were previously needed in the SubApp network, one now suffices.

## Comparison with Similar Function Blocks

- **[`AD_TO_AR`](./AD_TO_AR.md)**: the bit-reinterpretation variant — use only when `AD_IN` is already a bit pattern meant to be interpreted as REAL.
- **`AI_TO_AR`/`ADI_TO_AR`/`AUDI_TO_AR`**: already numerically correct, since their source types are `ANY_INT` — if the raw value is already available as an INT/DINT/UDINT adapter, no `_NUM` variant is needed.

## Conclusion

**AD_TO_AR_NUM** closes the gap between the tempting-but-dangerous `AD_TO_AR` and the actually needed numeric DWORD→REAL conversion — as a single, drop-in-compatible block instead of a manually wired two-block chain.

---

### 📖 Background

* [Numeric vs. bitwise: the FORTE conversion trap](../Numeric_vs_Bitwise.md)

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
