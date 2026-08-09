# E_T_FF_SR_SYM_INIT

![E_T_FF_SR_SYM_INIT](./E_T_FF_SR_SYM_INIT.svg)
**Image of the function block:** (not available)

* * * * * * * * * *
## Introduction

The function block `E_T_FF_SR_SYM_INIT` implements an event-driven, bistable flip-flop with set, reset, and toggle functionality. It features symmetrical startup behavior: Upon the initialization event (`INIT`), the output `Q` is set to the value specified at the input `Q_INIT`, provided the qualifier `QI` is active. The block combines the properties of an SR flip-flop and a toggle flip-flop in a single unit.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|--------|------------------------------------------|
| INIT | EInit | Initialization Request |
| S | Event | Sets output Q (set) |
| R | Event | Resets output Q |
| CLK | Event | Clock for toggling Q |

### **Event Outputs**

| Name | Type | Comment |
|-------|--------|------------------------------------------|
| INITO | EInit | Initialization Acknowledgement |
| EO | Event | Signals a change in Q |

### **Data Inputs**

| Name | Type | Comment |
|---------|-------|----------------------------------------------|
| QI | BOOL | Event qualifier (controls execution) |
| Q_INIT | BOOL | Value that Q should assume at INIT |

### **Data Outputs**

| Name | Type | Comment |
|------|-------|------------------------------------------|
| QO | BOOL | Output qualifier (mirror of QI) |
| Q | BOOL | Flip-flop value |

### **Adapters**

None.

## Functionality

The function block traverses a finite state machine with five states: `START`, `Init`, `DeInit`, `SET`, and `RESET`.

- **Initialization (`INIT`)**

If a signal is present at the event input `INIT`, the function block distinguishes between the following states depending on the state of the qualifier `QI`:

- If `QI = TRUE`, the function block transitions to state `Init`. There, the output qualifier `QO` is set to the value of `QI` (i.e., `TRUE`), and the output `INITO` is triggered. Subsequently, the automaton—again depending on `Q_INIT`—enters state `SET` (if `Q_INIT = TRUE`) or state `RESET` (if `Q_INIT = FALSE`). Thus, `Q` receives the desired starting value.

If `QI = FALSE`, the function block transitions to state `DeInit`. There, `QO` is set to `FALSE`, and `INITO` is triggered. The machine then returns to its initial state.

- **Setting (`S`)**

When an event occurs at `S`, the algorithm `SET` is executed:

QO` receives the value of `QI`. If `QI = TRUE` is present, `Q` is set to `TRUE`. The output `EO` is triggered to signal a change in `Q`.

- **Reset (`R`)**

When an event occurs at `R`, the algorithm `RESET` is executed:

QO` receives the value of `QI`. If `QI = TRUE` is present, `Q` is set to `FALSE`. In this case, `EO` is also triggered.

QI = TRUE` is set to `Q`. `EO` is also triggered in this case. - **Toggle (`CLK`)**

An event at `CLK` always causes a state change:

If the automaton is in state `SET`, it switches to `RESET` and vice versa. The respective algorithm (`SET` or `RESET`) is executed with the current evaluation from `QI`. The output `Q` is therefore toggled at every clock cycle, provided `QI = TRUE` is in state.

## Technical Features

- **Symmetrical Start-up Behavior**: The initial value of `Q` is determined by the configurable input `Q_INIT` and is not set to a fixed default. This allows the system to start reproducibly in a defined state.
- **Event Qualifier `QI`**: All actions (`SET`, `RESET`) are only executed if `QI = TRUE` is present. For `QI = FALSE`, the output qualifier `QO` is simply set to `FALSE`; the value of `Q` remains unchanged. This enables conditional control by upstream function blocks.
- **Deinitialization**: If a `INIT` event with `QI = FALSE` is received during runtime, the function block is deinitialized and enters its idle state (`START`). In this state, it does not respond to any further events until it is reinitialized.

## State Overview

| State | Description | Action on Occurrence |
|---------|----------------------------------------------|---------------------------------------------|
| START | Waiting for initialization | – |
| Init | Initializing QO | `QO := QI`; Triggering `INITO` |
| DeInit | Deinitializing (if QI=false) | `QO := FALSE`; Triggering `INITO` |
| SET | Q is set (`TRUE`) | `Q := TRUE` (only if QI=true); Triggering `EO` |
| RESET | Q is reset (`FALSE`) | `Q := FALSE` (only if QI=true); Trigger `EO` |

Q is reset (`FALSE`) | `Q := FALSE` (only if QI=true);

Q is reset (`EO`) ...80qz) |
Q is reset (`Q := FALSE`) |

Q is reset (q Transitions:

- `START` → `Init`: at `INIT` and `QI = TRUE`
- `START` → `DeInit`: at `INIT` and `QI = FALSE`
- `Init` → `SET`: when `Q_INIT = TRUE`
- `Init` → `RESET`: when `Q_INIT = FALSE`
- `SET` ⇄ `RESET` : via `S`, `R` or `CLK` (each taking QI into account)
- `SET` → `DeInit` : if `INIT` is reused with `QI = FALSE`
- `RESET` → `DeInit` : if `INIT` is reused with `QI = FALSE`
- `DeInit` → `START` : always (transition with condition `1`)

## Application Scenarios

- **Control with defined start state**: In safety controllers or systems that require a specific initial state after a restart, `Q_INIT` can be set accordingly.
- **Toggle function for command switches**: A single push button (connected to `CLK`)) switches an output with each press – e.g., for lighting controls.
- **Conditional Set/Reset Logic**: The qualifier `QI` allows actions to be made dependent on higher-level conditions without losing the flip-flop's state.

## Comparison with Similar Components

- **Standard SR Flip-Flop (`E_SR`)**: Offers only set and reset functionality, no toggle function, and no adjustable initial value.
- **Toggle Flip-Flop (`E_TOGGLE`)**: Only toggles on each clock cycle; no separate set/reset functionality and no defined initial value.
- **SR Flip-Flop with Initialization (`E_SR_INIT`)**: Similar, but without a toggle function.

This function block combines all three functions (Set, Reset, Toggle) with flexible initialization behavior – a comprehensive solution for many event-driven control tasks.

## Conclusion

E_T_FF_SR_SYM_INIT` is a versatile function block for IEC 61499-based event-driven automation. By combining Set, Reset, and Toggle functions with configurable initialization, it covers a wide range of requirements. Using the qualifier `QI` increases flexibility and enables secure integration into complex sequence control systems.
