# SafeArithmetic

Saturating (clamping) arithmetic function blocks, developed under the EPL-2.0 license by
HR Agrartechnik GmbH. Motivated by a real hardware finding (`Uebung_011b3`): plain IEC 61131-3
arithmetic silently wraps around on overflow/underflow for integer types, and produces `INF`/`NaN`
for REAL/LREAL — both dangerous for real measurement values. Every block in this library instead
clamps the result into the valid range and reports the limit condition via a `LIMIT_HIT` output.

- [Arithmetic Functions](arithmetic/index.md)
