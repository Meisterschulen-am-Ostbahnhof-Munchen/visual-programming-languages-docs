# E_SR_SYM_INIT

![E_SR_SYM_INIT_ecc](./E_SR_SYM_INIT_ecc.svg)

* * * * * * * * * *
## Introduction

`E_SR_SYM_INIT` is functionally identical to [E_RS_SYM_INIT](E_RS_SYM_INIT.md) — analogous to [E_SR_SYM](E_SR_SYM.md)/[E_RS_SYM](E_RS_SYM.md), it exists purely to preserve the `SR` naming convention (set listed first) and extends [E_SR_SYM](E_SR_SYM.md) with an `INIT`/`INITO` interface.

![E_SR_SYM_INIT](E_SR_SYM_INIT.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization request, carries `QI` and `Q_INIT`.
- **S (Set)**: Sets output `Q` to `TRUE`.
- **R (Reset)**: Sets output `Q` to `FALSE`.

### **Event Outputs**

- **INITO**: Confirms (de-)initialization, carries `QO`.
- **EO**: Triggered after every `S` or `R` event, carries `Q`.

### **Data Inputs**

- **QI** (BOOL): Input event qualifier — `TRUE` initializes, `FALSE` deinitializes.
- **Q_INIT** (BOOL): The value `Q` is set to during initialization.

### **Data Outputs**

- **QO** (BOOL): Output event qualifier, mirrors `QI`.
- **Q** (BOOL): The current state of the flip-flop.

## Functionality

Identical to [E_RS_SYM_INIT](E_RS_SYM_INIT.md): `INIT` with `QI = TRUE` initializes `Q` via `Q_INIT`, `INIT` with `QI = FALSE` deinitializes the block back to state `START`. During normal operation, `S`/`R` switch between `SET` and `RESET`, each confirmed via `EO`.

## Technical Features

See [E_RS_SYM_INIT](E_RS_SYM_INIT.md) — identical behaviour, only the `S`/`R` order in the symbol is swapped.

## State Overview

| State | Meaning |
|---|---|
| START | Unconfigured initial state |
| Init | Initialization in progress, `QO := QI` |
| DeInit | Deinitialization in progress, `QO := FALSE` |
| SET | `Q = TRUE` |
| RESET | `Q = FALSE` |

## Application Scenarios

See [E_RS_SYM_INIT](E_RS_SYM_INIT.md).

## Comparison with similar function blocks

- **[E_RS_SYM_INIT](E_RS_SYM_INIT.md)**: functionally identical, swapped `S`/`R` order.
- **[E_SR_SYM](E_SR_SYM.md)**: the same base functionality without `INIT`/`INITO`.

## Conclusion

`E_SR_SYM_INIT` is the naming-convention counterpart of `E_RS_SYM_INIT` and functionally identical variant with a configurable start value.
