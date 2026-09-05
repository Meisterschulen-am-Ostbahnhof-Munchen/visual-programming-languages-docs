# Exercise_011b4: Numeric Value Input SAFE_ADD

![Uebung_011b4_network](./Uebung_011b4_network.svg)

* * * * * * * * * *
## Introduction

Exercise **Exercise_011b4** performs an addition of two numeric values read from the ISOBUS
network, using
[SAFE_ADD_2](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/SafeArithmetic/arithmetic/SAFE_ADD_2/)
instead of the plain `ADD_2`/`F_ADD`. Unlike the earlier exercises in this series, it exposes a
second output: `SAFE_ADD_2.LIMIT_HIT` is converted to `UDINT` and written to `OutputNumber_N2`,
so an overflow is directly visible on the ISOBUS network as `1` (clamped) or `0` (normal) — not
just silently reflected in a wrapped-around sum on `OutputNumber_N1`.

## Function Blocks (FBs) Used

- **InputNumber_I1** / **InputNumber_I2** (Type: `isobus::UT::io::NumericValue::NumericValue_ID`)
  - Read the current numeric values of the ISOBUS objects "InputNumber_I1"/"InputNumber_I2".
- **F_DWORD_TO_UDINT** / **F_DWORD_TO_UDINT_1** (Type: `iec61131::conversion::F_DWORD_TO_UDINT`)
  - Convert the incoming DWORD values to UDINT.
- **SAFE_ADD_2** (Type: `SafeArithmetic::arithmetic::SAFE_ADD_2`)
  - Data inputs: `IN1`, `IN2` (both UDINT). Data outputs: `OUT` (UDINT, clamped sum),
    `LIMIT_HIT` (BOOL, TRUE if the addition overflowed).
- **Q_NumericValue** (Type: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N1`)
  - Writes `SAFE_ADD_2.OUT` back to the ISOBUS network.
- **F_BOOL_TO_UDINT** (Type: `iec61131::conversion::F_BOOL_TO_UDINT`)
  - Converts `SAFE_ADD_2.LIMIT_HIT` (BOOL) to `UDINT` (`1`/`0`).
- **Q_NumericValue_1** (Type: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N2`)
  - Writes the converted `LIMIT_HIT` back to the ISOBUS network.

## Program Flow and Connections

1. **Event Control**: `InputNumber_I1.IND`/`InputNumber_I2.IND` trigger their converters' `REQ`.
   Both converters' `CNF` outputs trigger `SAFE_ADD_2.REQ`. `SAFE_ADD_2.CNF` triggers both
   `Q_NumericValue.REQ` (the sum) and `F_BOOL_TO_UDINT.REQ` (the limit flag), and
   `F_BOOL_TO_UDINT.CNF` triggers `Q_NumericValue_1.REQ`.
2. **Data Flow**: converted `IN1`/`IN2` (UDINT) go to `SAFE_ADD_2.IN1`/`IN2`. `SAFE_ADD_2.OUT`
   goes to `Q_NumericValue.u32NewValue`. `SAFE_ADD_2.LIMIT_HIT` goes to `F_BOOL_TO_UDINT.IN`,
   whose `OUT` goes to `Q_NumericValue_1.u32NewValue`.

## Expected Behavior

- Normal case (e.g. `InputNumber_I1 = 100`, `InputNumber_I2 = 200`): `OutputNumber_N1 = 300`,
  `OutputNumber_N2 = 0`.
- Overflow case (e.g. `InputNumber_I1 = UDINT#4294967290`, `InputNumber_I2 = 100`): the true sum
  exceeds `UDINT`'s range, so `OutputNumber_N1 = UDINT#4294967295` (clamped to max) and
  `OutputNumber_N2 = 1` — the overflow is now visible, instead of silently wrapping around to a
  small, plausible-looking (but wrong) number.

## Summary

This exercise shows `SAFE_ADD_2` as a drop-in replacement for `ADD_2`/`F_ADD` that turns a
silent, hard-to-notice wraparound into an explicit, observable `LIMIT_HIT` signal.
