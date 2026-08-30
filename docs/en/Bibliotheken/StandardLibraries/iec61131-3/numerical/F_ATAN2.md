# F_ATAN2

![F_ATAN2](F_ATAN2.svg)

* * * * * * * * * *

## Introduction

`F_ATAN2` computes the principal value of the arc tangent of `Y/X`, taking into account the signs of both arguments (two-parameter arc tangent). Unlike the plain `ATAN` function (which takes only one argument), `F_ATAN2` returns the angle in the correct quadrant across the full angular range from `-π` to `+π`.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the calculation, carries `Y` and `X`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **Y** (ANY_REAL): Ordinate (Y coordinate).
- **X** (ANY_REAL): Abscissa (X coordinate).

### **Data Outputs**

- **OUT** (ANY_REAL): The computed angle in radians, in the range `(-π, π]`.

## Functionality

On `REQ`, the block computes the angle between the positive X axis and the point `(X, Y)` — equivalent to `ATAN(Y/X)`, but evaluating the signs of `X` and `Y` individually to determine the correct quadrant (including the special case `X = 0`). The result is output via `OUT`, then `CNF` is triggered.

## Technical Features

- **Quadrant correctness**: Unlike `ATAN(Y/X)`, `F_ATAN2` returns the correct angle even for negative `X` (2nd and 3rd quadrant), without the caller having to manually correct for the quadrant.
- **`ANY_REAL` typing**: Accepts both `REAL` and `LREAL` for `Y`, `X`, and `OUT`.
- **Special case `X = 0`**: Returns `+π/2` or `-π/2` depending on the sign of `Y`, instead of a division by zero as with directly using `ATAN(Y/X)`.

## State Overview

Stateless: every `REQ` immediately results in the calculation and `CNF`.

## Application Scenarios

- **Angle calculation from Cartesian coordinates**: e.g. determining the heading or orientation of an object from its X/Y position relative to a reference point.
- **Control engineering**: Computing phase angles or steering angles from two component signals.
- **Navigation**: Course calculation from velocity components.

## Comparison with similar function blocks

- **`F_ATAN`**: computes the arc tangent of a single value, only returns angles in the range `(-π/2, π/2)`, and requires manual quadrant correction.

## Conclusion

`F_ATAN2` provides quadrant-correct angle calculation from two Cartesian components and is the standard block for angle/direction calculations where `ATAN` alone is insufficient.
