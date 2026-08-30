# AND_ZU

![AND_ZU_network](./AND_ZU_network.svg)

* * * * * * * * * *
## Introduction

`AND_ZU` computes the logical `IN1 AND NOT IN2` and provides the enable condition for a "CLOSE" movement (e.g. closing a valve/flap): `IN1` must be true and `IN2` must be false. Complementary to [`AND_AUF`](./AND_AUF.md).

## Function Blocks Used

### Sub-blocks: AND_ZU

- **Type**: SubAppType
- **Internal FBs used**:
    - **F_NOT** (`F_NOT`): `iec61131::booleanOperators::F_NOT_BOOL_INIT` — negates `IN2` before the AND is computed.
    - **AND_3** (type `AND_2`): `iec61131::bitwiseOperators::AND_2` — ANDs `IN1` with the negated `IN2`.
- **Operation**: `REQ` first triggers `F_NOT`, whose `CNF` in turn triggers `AND_3` — the negation happens before the AND, both in data flow and in event sequencing.

## Program Flow and Connections

1. `REQ` → `F_NOT.REQ`; `IN2` → `F_NOT.IN`.
2. `F_NOT.CNF` → `AND_3.REQ` (event chain).
3. `IN1` → `AND_3.IN1`; `F_NOT.OUT` → `AND_3.IN2`.
4. `AND_3.OUT` → `OUT`; `AND_3.CNF` → `CNF`.

## Application Scenarios

- Enable logic for closing movements where one condition must be true and a second must explicitly be *false* (e.g. enable button AND OPEN limit switch not active).

## Summary

Extends `AND_AUF` with a negation of `IN2` — the matching counterpart logic for the CLOSE condition of a valve/flap control.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
