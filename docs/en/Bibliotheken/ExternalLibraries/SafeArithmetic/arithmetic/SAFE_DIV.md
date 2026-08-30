# SAFE_DIV

![SAFE_DIV](SAFE_DIV.svg)

* * * * * * * * * *
## Introduction

**SAFE_DIV** is part of the **SafeArithmetic** library (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). It is a fixed 2-input division function block that behaves like the
standard library's `F_DIV`, but never traps, produces `INF`/`NaN`, or lets an overflow pass
silently: division by zero and overflow are treated as **clamp** conditions, and `LIMIT_HIT`
reports that clamping happened.

Like `SAFE_SUB`, `SAFE_DIV` is **not** generic-arity: division is neither associative nor
commutative, so a "chained" division has no well-defined meaning the way extensible ADD/MUL do.

## Interface Structure

### **Event Inputs**

- `REQ`: Normal Execution Request

### **Event Outputs**

- `CNF`: Execution Confirmation

### **Data Inputs**

- `IN1` (ANY_NUM): dividend
- `IN2` (ANY_NUM): divisor

### **Data Outputs**

- `OUT` (ANY_NUM): IN1 divided by IN2; 0 if IN2 is 0
- `LIMIT_HIT` (BOOL): TRUE if the result was clamped due to overflow or division by zero

## Functionality

1. **Calculation Request**: `REQ` event with values for IN1 and IN2.
2. **Division**: computes `IN1 / IN2`.
3. **Result Output**: `CNF` event with the calculated `OUT` and `LIMIT_HIT`.

## Overflow / Division-by-Zero Behavior

- **Any integer** type, `IN2 == 0`: clamps to `0` with `LIMIT_HIT = TRUE`, instead of trapping
  (integer division by zero is undefined behavior in plain C++ and would crash `F_DIV`).
- **Signed integer** types: the one remaining case that can overflow, `INT_MIN / -1`, clamps to
  `numeric_limits::max()`.
- **REAL/LREAL**, `IN2 == 0.0`: clamps to `0` with `LIMIT_HIT = TRUE`, instead of producing
  IEEE-754 `+INF`/`-INF`/`NaN` (`0.0 / 0.0`).
- **REAL/LREAL**, `IN2 != 0.0`: a non-finite intermediate or final result is always caught,
  regardless of whether the *inputs* were already non-finite — `+INF`/`-INF` clamp to
  `numeric_limits::max()`/`::lowest()`, and `NaN` becomes a deterministic `0`. `LIMIT_HIT` is set
  in every case.
- **Incompatible types** (e.g. mixing a numeric type with an unrelated type where no division is
  defined): the result is undefined by this operation (logged as an error), `OUT` is left
  unchanged, and `LIMIT_HIT` is **not** set for this case — it is a type error, not a numeric
  limit event.

## Related Function Blocks

- [F_DIV](../../../StandardLibraries/iec61131-3/arithmetic/F_DIV.md) — the plain, non-saturating
  standard-library equivalent (undefined behavior on integer division by zero, `INF`/`NaN` on
  float division by/of zero, instead of clamping and reporting).
- [Uebung_011b7](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b7.md) — a division-by-zero
  demo with `SAFE_DIV`, `LIMIT_HIT` wired to a second output so the clamping is visible on
  hardware.

## Conclusion

SAFE_DIV gives you the same division as `F_DIV`, but with an explicit, type-range-aware limit
signal instead of undefined behavior (integer division by zero) or a silently-corrupted result
(float overflow/`NaN`).
