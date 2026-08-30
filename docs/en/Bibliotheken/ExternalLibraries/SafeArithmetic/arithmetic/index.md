# Arithmetic Functions

Here you will find the SafeArithmetic library's saturating (clamping) arithmetic function
blocks — drop-in, safety-oriented replacements for the standard library's plain arithmetic
blocks that report an overflow/underflow/division-by-zero via `LIMIT_HIT` instead of silently
wrapping around (integers) or producing `INF`/`NaN` (REAL/LREAL).

```{toctree}
:maxdepth: 1

SAFE_ADD_2
SAFE_ADD_3
SAFE_ADD_4
SAFE_DIV
SAFE_MUL_2
SAFE_MUL_3
SAFE_MUL_4
SAFE_SUB
```