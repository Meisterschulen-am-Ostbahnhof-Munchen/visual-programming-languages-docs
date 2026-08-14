# F_IS_VALID

![F_IS_VALID](F_IS_VALID.svg)

* * * * * * * * * *
## Introduction

`F_IS_VALID` checks whether a floating-point value (`REAL`/`LREAL`) is a valid, finite value — i.e. neither `NaN` (Not a Number) nor `+/-Infinity`. It guards numerical calculations against invalid intermediate results.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the check, carries `IN`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **IN** (ANY_REAL): The floating-point value to check.

### **Data Outputs**

- **OUT** (BOOL): `TRUE` if `IN` is a valid, finite value; `FALSE` for `NaN` or `Infinity`.

## Functionality

On `REQ`, the algorithm's ST statement `OUT := IS_VALID(IN)` checks whether `IN` is neither `NaN` nor `+/-Infinity`, and outputs the result via `OUT`. `CNF` is then triggered.

## Technical Features

- **`ANY_REAL` input**: Accepts both `REAL` and `LREAL`.
- **Detects typical error results**: `NaN` arises e.g. from `0.0/0.0`, `Infinity` from division by `0.0` with a nonzero numerator — both classic sources of error in floating-point calculations.

## State Overview

Stateless: every `REQ` immediately results in the check and `CNF`.

## Application Scenarios

- **Guarding calculation chains**: Checking a floating-point result for validity before further processing, to prevent follow-on errors (e.g. `NaN` propagation).
- **Sanity checking sensor data**: Detecting faulty or out-of-range measurements.

## Comparison with similar function blocks

- **[F_IS_VALID_BCD](F_IS_VALID_BCD.md)**: the same basic idea of validity checking, but for BCD-encoded bit strings instead of floating-point numbers.

## Conclusion

`F_IS_VALID` provides a simple, central validity check for floating-point values and helps catch `NaN`/`Infinity`-related follow-on errors in calculation chains early.
