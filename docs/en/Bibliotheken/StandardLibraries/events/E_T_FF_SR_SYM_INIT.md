# E_T_FF_SR_SYM_INIT

![E_T_FF_SR_SYM_INIT_ecc](./E_T_FF_SR_SYM_INIT_ecc.svg)

* * * * * * * * * *

## Introduction

`E_T_FF_SR_SYM_INIT` extends [E_T_FF_SR_SYM](E_T_FF_SR_SYM.md) with an explicit `INIT`/`INITO` interface: the start value of `Q` is not determined by the first `S`, `R`, or `CLK` event, but is set deliberately via `Q_INIT`.

![E_T_FF_SR_SYM_INIT](E_T_FF_SR_SYM_INIT.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization request, carries `QI` and `Q_INIT`.
- **S (Set)**: Sets `Q` to `TRUE`.
- **R (Reset)**: Sets `Q` to `FALSE`.
- **CLK**: Inverts the current state of `Q`.

### **Event Outputs**

- **INITO**: Confirms (de-)initialization, carries `QO`.
- **EO**: Triggered after every `S`, `R`, or `CLK` event, carries `Q`.

### **Data Inputs**

- **QI** (BOOL): Input event qualifier — `TRUE` initializes, `FALSE` deinitializes.
- **Q_INIT** (BOOL): The value `Q` is set to during initialization.

### **Data Outputs**

- **QO** (BOOL): Output event qualifier.
- **Q** (BOOL): The current state.

## Functionality

`INIT` with `QI = TRUE` initializes `Q` via `Q_INIT` (`Init` → `SET`/`RESET`). During normal operation, `S`/`R` switch deliberately, `CLK` toggles between `SET` and `RESET` — identical to [E_T_FF_SR_SYM](E_T_FF_SR_SYM.md), but without its symmetric start-up behaviour from `START`, since the start value instead comes from `INIT`. `INIT` with `QI = FALSE` deinitializes the block back to state `START`.

## Technical Features

- **Combines all three mechanisms**: deliberate set/reset (`S`/`R`), toggle (`CLK`), and configurable initialization (`INIT`/`Q_INIT`) in a single block.
- **Same INIT/DeInit structure** as [E_RS_SYM_INIT](E_RS_SYM_INIT.md), [E_SR_SYM_INIT](E_SR_SYM_INIT.md), and [E_T_FF_INIT](E_T_FF_INIT.md).

## State Overview

| State | Meaning |
| --- | --- |
| START | Unconfigured initial state |
| Init | Initialization in progress, `QO := QI` |
| DeInit | Deinitialization in progress, `QO := FALSE` |
| SET | `Q = TRUE`; `R`/`CLK`→RESET |
| RESET | `Q = FALSE`; `S`/`CLK`→SET |

## Application Scenarios

- **Fully-featured operator/blink element** with a defined start value: combines manual set/reset, clock-driven toggling, and a start state that can be configured at startup.

## Comparison with similar function blocks

- **[E_T_FF_SR_SYM](E_T_FF_SR_SYM.md)**: the same functionality without `INIT`/`INITO`.
- **[E_T_FF_INIT](E_T_FF_INIT.md)**: only toggle + init, without `S`/`R`.
- **[E_RS_SYM_INIT](E_RS_SYM_INIT.md) / [E_SR_SYM_INIT](E_SR_SYM_INIT.md)**: only set/reset + init, without `CLK`.

## Conclusion

`E_T_FF_SR_SYM_INIT` is the functionally most complete block in the `E_*_SYM` family, combining set/reset, toggle, and configurable initialization in a single function block.
