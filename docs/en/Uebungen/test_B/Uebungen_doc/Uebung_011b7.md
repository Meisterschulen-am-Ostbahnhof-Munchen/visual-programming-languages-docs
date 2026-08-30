# Exercise_011b7: Numeric Value Input SAFE_DIV

![Uebung_011b7_network](./Uebung_011b7_network.svg)

* * * * * * * * * *
## Introduction

Exercise **Exercise_011b7** performs a division of two numeric values read from the ISOBUS
network, using
[SAFE_DIV](../../../Bibliotheken/ExternalLibraries/SafeArithmetic/arithmetic/SAFE_DIV.md). There
is no plain, non-safe `F_DIV` predecessor exercise in this series — integer division by zero is
undefined behavior in plain C++ and would crash a native `F_DIV`, so this exercise exists purely
to demonstrate `SAFE_DIV`'s division-by-zero handling directly. `SAFE_DIV.LIMIT_HIT` is
converted to `UDINT` and written to `OutputNumber_N2`.

## Function Blocks (FBs) Used

- **InputNumber_I1** / **InputNumber_I2** (Type: `isobus::UT::io::NumericValue::NumericValue_ID`)
  - Read the current numeric values of the ISOBUS objects "InputNumber_I1"/"InputNumber_I2".
- **F_DWORD_TO_UDINT** / **F_DWORD_TO_UDINT_1** (Type: `iec61131::conversion::F_DWORD_TO_UDINT`)
  - Convert the incoming DWORD values to UDINT.
- **SAFE_DIV** (Type: `SafeArithmetic::arithmetic::SAFE_DIV`)
  - Data inputs: `IN1` (dividend), `IN2` (divisor), both UDINT. Data outputs: `OUT` (UDINT,
    quotient, `0` if `IN2` is `0`), `LIMIT_HIT` (BOOL, TRUE on overflow or division by zero).
- **Q_NumericValue** (Type: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N1`)
  - Writes `SAFE_DIV.OUT` back to the ISOBUS network.
- **F_BOOL_TO_UDINT** (Type: `iec61131::conversion::F_BOOL_TO_UDINT`)
  - Converts `SAFE_DIV.LIMIT_HIT` (BOOL) to `UDINT` (`1`/`0`).
- **Q_NumericValue_1** (Type: `isobus::UT::Q::Q_NumericValue`, `u16ObjId` = `OutputNumber_N2`)
  - Writes the converted `LIMIT_HIT` back to the ISOBUS network.

## Program Flow and Connections

1. **Event Control**: `InputNumber_I1.IND`/`InputNumber_I2.IND` trigger their converters' `REQ`.
   Both converters' `CNF` outputs trigger `SAFE_DIV.REQ`. `SAFE_DIV.CNF` triggers both
   `Q_NumericValue.REQ` (the quotient) and `F_BOOL_TO_UDINT.REQ` (the limit flag), and
   `F_BOOL_TO_UDINT.CNF` triggers `Q_NumericValue_1.REQ`.
2. **Data Flow**: converted `IN1`/`IN2` (UDINT) go to `SAFE_DIV.IN1`/`IN2`. `SAFE_DIV.OUT`
   goes to `Q_NumericValue.u32NewValue`. `SAFE_DIV.LIMIT_HIT` goes to `F_BOOL_TO_UDINT.IN`,
   whose `OUT` goes to `Q_NumericValue_1.u32NewValue`.

## Hardware Result

`InputNumber_I1 = UDINT#12`, `InputNumber_I2 = UDINT#0`:

```
SAFE_DIV.OUT = 0           (clamped: division by zero, instead of trapping)
SAFE_DIV.LIMIT_HIT = TRUE  ->  OutputNumber_N1 = 0, OutputNumber_N2 = 1
```

`InputNumber_I1 = UDINT#12`, `InputNumber_I2 = UDINT#4` (normal case):

```
SAFE_DIV.OUT = 3, SAFE_DIV.LIMIT_HIT = FALSE  ->  OutputNumber_N1 = 3, OutputNumber_N2 = 0
```

## Summary

This exercise shows `SAFE_DIV` handling division by zero as an explicit, observable clamp
condition rather than the undefined behavior a native integer division by zero would otherwise
be.
