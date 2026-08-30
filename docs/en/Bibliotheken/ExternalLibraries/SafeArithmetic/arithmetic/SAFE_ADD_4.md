# SAFE_ADD_4

![SAFE_ADD_4](SAFE_ADD_4.svg)

* * * * * * * * * *
## Introduction

**SAFE_ADD_4** is part of the **SafeArithmetic** library (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). It is a generic, 4-input addition function block that behaves like the
standard library's `ADD_4`, but never lets an overflow pass silently: on overflow the
result is **clamped** (saturated) into the valid range of the result type, and `LIMIT_HIT`
reports that clamping happened.

This library exists because plain IEC 61131-3 arithmetic function blocks (like `ADD_4`
itself, for integer types) compute the standard's specified two's-complement wraparound on
overflow — correct per the standard, but dangerous for real measurement values. `Uebung_011b3`
demonstrates this on real hardware: plain `F_SUB` computes `UDINT#1 - UDINT#12 = UDINT#4294967285`,
a silent underflow wraparound.

## Interface Structure

### **Event Inputs**

- `REQ`: Normal Execution Request

### **Event Outputs**

- `CNF`: Execution Confirmation

### **Data Inputs**

- `IN1` (ANY_MAGNITUDE): first summand
- `IN2` (ANY_MAGNITUDE): second summand
- `IN3` (ANY_MAGNITUDE): third summand
- `IN4` (ANY_MAGNITUDE): fourth summand

### **Data Outputs**

- `OUT` (ANY_MAGNITUDE): ADD result, clamped to the valid range of the result type
- `LIMIT_HIT` (BOOL): TRUE if the result was clamped due to overflow

## Functionality

1. **Calculation Request**: `REQ` event with values for IN1, IN2, IN3, IN4.
2. **Calculation**: computes `IN1 + IN2 + IN3 + IN4` left-to-right, one pairwise step at a time. Each step
   checks for overflow; if a step overflows, its result is clamped into the result type's valid
   range and `LIMIT_HIT` is set (sticky — once set by any step, it stays set for the rest of the
   fold).
3. **Result Output**: `CNF` event with the calculated `OUT` and `LIMIT_HIT`.

## Overflow / Saturation Behavior

- **Signed integer** types: on overflow, clamps to `numeric_limits::max()` or `::min()`,
  direction determined by the operand signs of the step that overflowed.
- **Unsigned integer** types: on overflow, clamps to `numeric_limits::max()`.
- **REAL/LREAL**: a non-finite intermediate or final result is always caught, regardless of
  whether the *inputs* to that step were already non-finite — `+INF`/`-INF` clamp to
  `numeric_limits::max()`/`::lowest()`, and `NaN` (e.g. from a prior step going non-finite and
  combining in a way that produces `NaN`) becomes a deterministic `0`. `LIMIT_HIT` is set in
  every case.
- **Incompatible types** (e.g. mixing a magnitude type with an unrelated type where no `ADD`
  is defined): the offending step is skipped (logged as an error), `OUT` keeps whatever value
  the fold had accumulated so far, and `LIMIT_HIT` is **not** set for this case — it is a type
  error, not a numeric limit event.

## Known Limitation for Chained (Arity ≥ 3) addition With SIGNED Types

`SAFE_ADD_4` evaluates as a strict left-to-right pairwise fold: `((IN1 + IN2) + IN3) + ...`,
clamping after every step. For **signed** integer types (and REAL/LREAL, which have no unsigned
notion) this means a transient intermediate overflow that a later input would otherwise cancel
back into range gets permanently baked into `OUT`, together with a `LIMIT_HIT` that no longer
reflects the true total.

Example (INT, IN1=20000, IN2=20000, IN3=-30000, IN4=0): the true result is `10000`, well within INT's range, but
the fold clamps after the second step and never recovers.

This is **not** a bug being silently patched — it is documented, intentional behavior: the fold
evaluates as a real chain of fixed-width operations, exactly like the plain (non-safe) `ADD_4`
does, and reports a genuine intermediate limit condition rather than silently reordering the
computation.

**Unsigned** chains of any arity are unaffected and always report a true overflow:
for addition, a later non-negative term can never bring an already-overflowed running total back in range (the total only grows).

`SAFE_ADD_2` (single pairwise operation, no chaining) always reports a true, correct
overflow regardless of signedness — the ambiguity only exists for arity ≥ 3.

## Related Function Blocks

- [ADD_4](../../../StandardLibraries/iec61131-3/arithmetic/ADD_4.md) — the
  plain, non-saturating standard-library equivalent (silent wraparound/`INF` on overflow instead
  of clamping and reporting).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — the hardware finding
  that motivated this library.

## Conclusion

SAFE_ADD_4 gives you the same 4-input addition as `ADD_4`, but with an explicit,
type-range-aware limit signal instead of a silent wraparound (integers) or a silently-corrupted
result (floats) — at the cost of the arity-≥-3/signed chaining caveat documented above, which is
a deliberate design trade-off, not an oversight.
