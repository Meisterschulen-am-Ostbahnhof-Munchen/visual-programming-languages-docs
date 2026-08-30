# SAFE_SUB

![SAFE_SUB](SAFE_SUB.svg)

* * * * * * * * * *
## Introduction

**SAFE_SUB** is part of the **SafeArithmetic** library (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). It is a fixed 2-input subtraction function block that behaves like the
standard library's `F_SUB`, but never lets an underflow/overflow pass silently: on a limit
violation the result is **clamped** (saturated) into the valid range of the result type, and
`LIMIT_HIT` reports that clamping happened.

This is the block that motivated the whole library: `Uebung_011b3` demonstrates on real ESP32-P4
hardware that plain `F_SUB` computes `UDINT#1 - UDINT#12 = UDINT#4294967285` — exactly the
IEC 61131-3-specified two's-complement wraparound for unsigned types, but dangerous for real
measurement values (setpoint differences, remaining-distance calculations). `SAFE_SUB` computes
the same subtraction instead as `UDINT#0` with `LIMIT_HIT = TRUE`.

Unlike `SAFE_ADD_2/3/4`/`SAFE_MUL_2/3/4`, `SAFE_SUB` is **not** generic-arity: subtraction is
neither associative nor commutative, so an N-ary "extensible" `SAFE_SUB_n` would not have a
well-defined meaning the way extensible ADD/MUL do.

## Interface Structure

### **Event Inputs**

- `REQ`: Normal Execution Request

### **Event Outputs**

- `CNF`: Execution Confirmation

### **Data Inputs**

- `IN1` (ANY_MAGNITUDE): minuend
- `IN2` (ANY_MAGNITUDE): subtrahend

### **Data Outputs**

- `OUT` (ANY_MAGNITUDE): IN2 subtracted from IN1, clamped to the valid range of the result type
- `LIMIT_HIT` (BOOL): TRUE if the result was clamped due to underflow/overflow

## Functionality

1. **Calculation Request**: `REQ` event with values for IN1 and IN2.
2. **Subtraction**: computes `IN1 - IN2`.
3. **Result Output**: `CNF` event with the calculated `OUT` and `LIMIT_HIT`.

## Overflow / Underflow Behavior

- **Signed integer** types: on overflow/underflow, clamps to `numeric_limits::min()` or
  `::max()`, direction determined by the sign of `IN2`.
- **Unsigned integer** types: subtraction can only ever underflow (go below 0), so it always
  clamps to `0` — this is exactly the `Uebung_011b3` case: `UDINT#1 - UDINT#12` clamps to
  `UDINT#0` with `LIMIT_HIT = TRUE` instead of wrapping to `UDINT#4294967285`.
- **REAL/LREAL**: a non-finite intermediate or final result is always caught, regardless of
  whether the *inputs* were already non-finite — `+INF`/`-INF` clamp to
  `numeric_limits::max()`/`::lowest()`, and `NaN` (e.g. `INF - INF`) becomes a deterministic `0`.
  `LIMIT_HIT` is set in every case.
- **Incompatible types** (e.g. mixing a magnitude type with an unrelated type where no
  subtraction is defined): the result is undefined by this operation (logged as an error), `OUT`
  is left unchanged, and `LIMIT_HIT` is **not** set for this case — it is a type error, not a
  numeric limit event.

## Related Function Blocks

- [F_SUB](../../../StandardLibraries/iec61131-3/arithmetic/F_SUB.md) — the plain, non-saturating
  standard-library equivalent (silent wraparound/`INF` on overflow instead of clamping and
  reporting).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — the hardware finding
  that motivated this library.
- [Uebung_011b5](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b5.md) — the same `1 - 12`
  scenario re-run with `SAFE_SUB`, with `LIMIT_HIT` wired to a second output so the clamping is
  visible on hardware.

## Conclusion

SAFE_SUB gives you the same subtraction as `F_SUB`, but with an explicit, type-range-aware limit
signal instead of a silent wraparound (integers) or a silently-corrupted result (floats) —
directly closing the gap `Uebung_011b3` found in the standard library.
