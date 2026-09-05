# F_AI_RAW_TO_PERCENT

![F_AI_RAW_TO_PERCENT_network](./F_AI_RAW_TO_PERCENT_network.svg)

* * * * * * * * * *

## Introduction

`F_AI_RAW_TO_PERCENT` converts the raw analog value from `logiBUS_AI_ID`/`logiBUS_AI_IDA` (DWORD, 0-4095, 12-bit ESP32-P4 ADC full scale) **linearly** into percent (REAL 0.0-100.0) — no physical calibration (planned as a later step). Data-based variant; the fully adapter-based alternative is [`F_AI_RAW_TO_PERCENT_AD`](./F_AI_RAW_TO_PERCENT_AD.md).

## Function Blocks (FBs) Used

### Sub-blocks: F_AI_RAW_TO_PERCENT

- **Type**: SubAppType
- **Internal FBs used**:
    - **F_DWORD_TO_UDINT**: `iec61131::conversion::F_DWORD_TO_UDINT` — bit-reinterpretation DWORD→UDINT, valid here (same 32-bit unsigned-integer representation).
    - **F_UDINT_TO_REAL**: `iec61131::conversion::F_UDINT_TO_REAL` — a real numeric cast UDINT→REAL.
    - **F_MUL_TO_PERCENT**: `iec61131::arithmetic::F_MUL` — multiplication by `REAL#0.0244200244` (= 100/4095).
- **Functionality**: `IN` (raw value 0-4095) → UDINT → REAL → ×(100/4095) = percent.

## Program Flow and Connections

1. `IN` → `F_DWORD_TO_UDINT.IN` → `F_UDINT_TO_REAL.IN` → `F_MUL_TO_PERCENT.IN1`.
2. `F_MUL_TO_PERCENT.IN2 = REAL#0.0244200244` (parameter, = 100/4095).
3. `F_MUL_TO_PERCENT.OUT` → `OUT` (percent 0.0-100.0).

## Technical Details

- **Numerically correct chain**: DWORD→UDINT is a valid bit-reinterpretation (see [Numeric vs. bitwise](../../../../Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/Numeric_vs_Bitwise.md)), UDINT→REAL is a real numeric cast — together they form a correct DWORD→REAL conversion, avoiding the bit-reinterpretation trap of `F_DWORD_TO_REAL`.
- **No physical calibration**: The factor 100/4095 only yields the linear percentage of ADC full scale, not a physical unit (volts, bar, etc.) — per the source comment, that's a later extension step.

## Application Scenarios

- Displaying/processing a raw analog input value as a percentage, e.g. for an AI training example.

## Summary

`F_AI_RAW_TO_PERCENT` demonstrates the numerically correct DWORD→REAL chain (via UDINT) on a concrete analog raw value example — data-based variant; see [`F_AI_RAW_TO_PERCENT_AD`](./F_AI_RAW_TO_PERCENT_AD.md) for the adapter-based alternative.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
