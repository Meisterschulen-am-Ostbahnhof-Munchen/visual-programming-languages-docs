# E_RS_SYM_INIT

![E_RS_SYM_INIT_ecc](./E_RS_SYM_INIT_ecc.svg)

* * * * * * * * * *
## Introduction

`E_RS_SYM_INIT` extends [E_RS_SYM](E_RS_SYM.md) with an explicit `INIT`/`INITO` interface: instead of the start value resulting purely from the first `S` or `R` event, it can be initialized (via `INIT`) with a defined value `Q_INIT`, or deinitialized via `QI = FALSE`.

![E_RS_SYM_INIT](E_RS_SYM_INIT.svg)

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

From `START`, `INIT` with `QI = TRUE` leads into state `Init`, which sets `QO := QI` and triggers `INITO`; from there, depending on `Q_INIT`, it moves directly to `SET` (`Q_INIT = TRUE`) or `RESET` (`Q_INIT = FALSE`) — without triggering `EO`. From `SET`/`RESET`, the block behaves like [E_RS_SYM](E_RS_SYM.md): `S` switches to `SET`, `R` to `RESET`, each triggering `EO`. A subsequent `INIT` with `QI = FALSE` leads from `SET` or `RESET` into state `DeInit` (sets `QO := FALSE`, triggers `INITO`) and from there back to `START`.

## Technical Features

- **QI as init/deinit switch**: `QI = TRUE` initializes the block with `Q_INIT`, `QI = FALSE` deinitializes it and returns it to the unconfigured `START` state.
- **Separate event channels**: Initialization (`INIT`/`INITO`) is fully separated from the running set/reset logic (`S`/`R`/`EO`) — an initialization during runtime deliberately resets `Q`, confirmed via `INITO` rather than `EO`.

## State Overview

| State | Meaning |
|---|---|
| START | Unconfigured initial state |
| Init | Initialization in progress, `QO := QI` |
| DeInit | Deinitialization in progress, `QO := FALSE` |
| SET | `Q = TRUE` |
| RESET | `Q = FALSE` |

## Application Scenarios

- **Well-defined startup with a preset value**: The start value of `Q` should come from a configuration variable (`Q_INIT`) at system start, instead of depending on which of `S`/`R` happens to arrive first.
- **Controlled reset of entire subnetworks**: `INIT`/`QI = FALSE` can be used to deliberately deinitialize the block, e.g. when disabling part of an FB network.

## Comparison with similar function blocks

- **[E_RS_SYM](E_RS_SYM.md)**: the same base functionality without an `INIT`/`INITO` interface.
- **[E_SR_SYM_INIT](E_SR_SYM_INIT.md)**: functionally identical, only the order of `S`/`R` in the interface is swapped.
- **[E_T_FF_INIT](../E_T_FF_INIT.md)**: the same INIT/DeInit structure, but with toggle instead of set/reset behaviour during normal operation.

## Conclusion

`E_RS_SYM_INIT` provides a bistable memory element with a deliberately configurable start value, making it suitable for applications where the pure chance of the first set/reset event is not sufficient.
