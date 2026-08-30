# AND_AUF

![AND_AUF_network](./AND_AUF_network.svg)

* * * * * * * * * *
## Introduction

`AND_AUF` computes the logical `IN1 AND IN2` and provides the enable condition for an "OPEN" movement (e.g. opening a valve/flap): both conditions must be true at the same time. For the complementary "CLOSE" condition, see [`AND_ZU`](./AND_ZU.md).

## Function Blocks Used

### Sub-blocks: AND_AUF

- **Type**: SubAppType
- **Internal FBs used**:
    - **AND_2**: `iec61131::bitwiseOperators::AND_2` — bitwise AND, used here at BOOL level as a logical AND.
- **Operation**: `REQ` triggers `AND_2`; `IN1` and `IN2` are ANDed and returned as `OUT` and `CNF`.

## Program Flow and Connections

1. `REQ` → `AND_2.REQ`.
2. `IN1` → `AND_2.IN1`; `IN2` → `AND_2.IN2`.
3. `AND_2.OUT` → `OUT`; `AND_2.CNF` → `CNF`.

## Application Scenarios

- Enable logic for opening movements where two independent conditions (e.g. CLOSE limit switch not active AND enable button) must be true simultaneously.

## Summary

Simple, reusable AND block, meaningfully named for the OPEN condition of a valve/flap control.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
