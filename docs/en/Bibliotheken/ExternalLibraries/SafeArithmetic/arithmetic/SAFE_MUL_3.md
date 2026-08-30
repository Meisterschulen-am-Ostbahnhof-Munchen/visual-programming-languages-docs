# SAFE_MUL_3

![SAFE_MUL_3](SAFE_MUL_3.svg)

* * * * * * * * * *
## Introduction

**SAFE_MUL_3** is part of the **SafeArithmetic** library (`SafeArithmetic::arithmetic`, EPL-2.0,
HR Agrartechnik GmbH). It is a generic, 3-input multiplication function block that extends the
standard library's fixed 2-input `F_MUL` pattern to 3 inputs (the standard library has no
generic multi-input `MUL_n` yet, unlike `ADD_2/3/4`), and never lets an overflow pass silently:
on overflow the result is **clamped** (saturated) into the valid range of the result type, and
`LIMIT_HIT` reports that clamping happened.

This library exists because plain IEC 61131-3 arithmetic function blocks (like `F_MUL`
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

- `IN1` (ANY_NUM): first factor
- `IN2` (ANY_NUM): second factor
- `IN3` (ANY_NUM): third factor

### **Data Outputs**

- `OUT` (ANY_NUM): MUL result, clamped to the valid range of the result type
- `LIMIT_HIT` (BOOL): TRUE if the result was clamped due to overflow

## Functionality

1. **Calculation Request**: `REQ` event with values for IN1, IN2, IN3.
2. **Calculation**: computes `IN1 * IN2 * IN3` left-to-right, one pairwise step at a time. Each step
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
- **Incompatible types** (e.g. mixing a magnitude type with an unrelated type where no `MUL`
  is defined): the offending step is skipped (logged as an error), `OUT` keeps whatever value
  the fold had accumulated so far, and `LIMIT_HIT` is **not** set for this case — it is a type
  error, not a numeric limit event.

## Known Limitation for Chained (Arity ≥ 3) multiplication With SIGNED Types

`SAFE_MUL_3` evaluates as a strict left-to-right pairwise fold: `((IN1 * IN2) * IN3) * ...`,
clamping after every step. For **signed** integer types (and REAL/LREAL, which have no unsigned
notion) this means a transient intermediate overflow that a later input would otherwise cancel
back into range gets permanently baked into `OUT`, together with a `LIMIT_HIT` that no longer
reflects the true total.

Example (INT, IN1=40000, IN2=40000, IN3=0): the true result is `0`, well within INT's range, but
the fold clamps after the second step and never recovers.

This is **not** a bug being silently patched — it is documented, intentional behavior: the fold
evaluates as a real chain of fixed-width operations, exactly like the plain (non-safe) `F_MUL`
does, and reports a genuine intermediate limit condition rather than silently reordering the
computation.

**Unsigned** chains of any arity are unaffected and always report a true overflow:
a later factor is either 0 (collapses the result cleanly to 0 regardless of any prior clamping) or ≥ 1 (keeps the product non-decreasing), so an unsigned chain's intermediate clamp can never diverge from the true total.

`SAFE_MUL_2` (single pairwise operation, no chaining) always reports a true, correct
overflow regardless of signedness — the ambiguity only exists for arity ≥ 3.

## Related Function Blocks

- [F_MUL](../../../StandardLibraries/iec61131-3/arithmetic/F_MUL.md) — the fixed 2-input,
  non-saturating standard-library block this pattern extends (silent wraparound/`INF` on
  overflow instead of clamping and reporting; no 3-input standard equivalent exists).
- [Uebung_011b3](../../../../Uebungen/test_B/Uebungen_doc/Uebung_011b3.md) — the hardware finding
  that motivated this library.

## Conclusion

SAFE_MUL_3 extends `F_MUL`'s multiplication to 3 inputs, with an explicit,
type-range-aware limit signal instead of a silent wraparound (integers) or a silently-corrupted
result (floats) — at the cost of the arity-≥-3/signed chaining caveat documented above, which is
a deliberate design trade-off, not an oversight.
