# AX_T_FF_SR_SYM_INIT
![AX_T_FF_SR_SYM_INIT](./AX_T_FF_SR_SYM_INIT.svg)
* * * * * * * * * *
## Introduction
The function block **AX_T_FF_SR_SYM_INIT** implements an event-driven bistable flip-flop with **Set**, **Reset**, and **Toggle** functionality. It features **symmetrical start-up behavior**, where the output state after the INIT event can be defined via the parameter `Q_INIT`. The block is designed according to IEC 61499-1 Annex A and is suitable for applications requiring a resettable, set, or toggleable binary state with an initializable preset.
## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|-------|---------|-----------------------------------------------|

| INIT | EInit | Initialization Request |

| S | Event | Set output Q (dependent on QI) |

| R | Event | Reset output Q (dependent on QI) |

| CLK | Event | Clock to toggle Q |

### **Event Outputs**

| Event | Type | Comment |

|--------|---------|-----------------------------------------|

| INITO | EInit | Initialization Confirmation |

### **Data Inputs**

| Variable | Type | Comment |

|-----------|--------|------------------------------------------------|

| QI | BOOL | Event Qualifier (Enable Actions) |

| Q_INIT | BOOL | Value of Q on the INIT event |

### **Data Outputs**

| Variable | Type | Comment |

|----------|--------|-------------------------------------------------|

| QO | BOOL | Output Event Qualifier |

### **Adapters**

| Adapter | Type | Comment |

|---------|-------------------------------------|-----------------------------|

| Q | adapter::types::unidirectional::AX | Value of the flip-flop (D1) |

## Functionality

The component has a finite state machine with five states: **START**, **INIT**, **DEINIT**, **SET**, and **RESET**.

- **START** is the initial state after power-on.
- An **INIT** event initiates the initialization:
- When `QI = TRUE` occurs, the system switches to the **Init** state. The algorithms `initialize` set `QO := QI`.
- Subsequently, based on `Q_INIT`, a decision is made whether to transition to the **SET** state (`Q_INIT = TRUE`) or the **RESET** state (`Q_INIT = FALSE`).

``` - During operation, **S**, **R**, or **CLK** can be processed:

- With **S** (Set), the adapter output `Q.D1` is set to `TRUE` in the algorithm `QI = TRUE`. `QO` receives the value of `QI`.
- With **R** (Reset), `Q.D1` is set to `FALSE`, also only if `QI` is active.
- With **CLK** (Toggle), the state is toggled: If the FB is in the **SET** state, a CLK event leads to the **RESET** state; if it is in **RESET**, it leads to **SET**. Does the toggle function operate independently of `QI`? *Note:* The transitions `SET—CLK→RESET` and `RESET—CLK→SET` are defined without further conditions; however, in the algorithms, `Q.D1` is only changed at `QI = TRUE`. If `QI = FALSE`, the adapter value remains unchanged, but the state transition still occurs. The internal state (SET/RESET) is always toggled, but the actual output to `Q.D1` only occurs if `QI` is true.
- A subsequent **INIT** event with `QI = FALSE` leads to the **DeInit** state, in which `QO := FALSE` is set. Afterward, the function block returns to the **START** state.

The output `QO` is set to the current value of `QI` with each executed algorithm. It serves as an event qualifier for the INITO output.

```
## Technical Features

- **Symmetrical Start-up Behavior**: The initial value of the output is set via `Q_INIT`, allowing for both set and reset start states.
- **Event Qualifier QI**: The actual change to the adapter `Q.D1` (i.e., the flip-flop output) is only executed if `QI` = `TRUE`. With `QI = FALSE`, the events S, R, and CLK are processed (state change), but the adapter value remains unchanged.
- **Toggle Functionality**: The CLK event allows the output to be switched between 0 and 1, enabling simple square wave generation or state transitions in many applications.
- **INIT Handling**: The INIT event can be used for both initialization (`QI = TRUE`) and deinitialization (`QI = FALSE`).

## State Overview

| State | Action | Output/Event | Description |

|---|---|---|---|

| **START** | – | – | Waits for first INIT event. |

| **Init** | `initialize` | INITO | Sets `QO := QI`; Then switch to SET or RESET depending on `Q_INIT`. |

**DeInit** | `deInitialize` | INITO | Sets `QO := FALSE`; then returns to START. |

**SET** | `SET` | Q.E1 | Sets `Q.D1 := TRUE` (if QI = TRUE) and `QO := QI`. |

**RESET** | `RESET` | Q.E1 | Sets `Q.D1 := FALSE` (if QI = TRUE) and `QO := QI`. |

**DeInit** | `RESET` | Q.E1 | Sets `Q.D1 := FALSE` (if QI = TRUE) and `QO := QI`. |

**DeInit** | `Q_INIT = FALSE` | INITO | Sets `QO := FALSE` (if QI = TRUE) and `QO := QI`. |

**Set** | `SET` | Q.E1 | Sets `Q.D1 := FALSE` (if QI = TRUE) and `QO := QI`. |

**Set** | `Q_INIT = FALSE` | Q.E1 | **Transitions** (excerpt):

- START → Init: `INIT[QI = TRUE]`
- Init → SET: `Q_INIT = TRUE`
- Init → RESET: `Q_INIT = FALSE`
- SET → RESET: `R` or `CLK`
- RESET → SET: `S` or `CLK`
- SET → DeInit: `INIT[QI = FALSE]`
- RESET → DeInit: `INIT[QI = FALSE]`
- DeInit → START: (always, condition = 1)

## Application Scenarios
- **Machine Control**: Defined start state after power-up (e.g., Valve Closed = `Q_INIT = FALSE`).
- **State Change with Toggle**: Switches a light or drive with each CLK pulse.
- **Safe Initialization**: The action can be made conditional via `QI` (e.g., enabling by a higher-level controller).
- **Fault Reset**: A RESET event resets the output, while setting is possible via S.

## Comparison with Similar Function Blocks

| Function Block | Special Feature |

|---|---|

| `E_SR` (Standard IEC 61499) | Pure set/reset flip-flop without toggle and without INIT symmetry. |

| `E_RS` | Like E_SR, but Reset takes precedence. |

| `E_Toggle` | Toggle function only, no Set/Reset, no Initialization. |

| `AX_T_FF_SR_SYM_INIT` | Combines Set, Reset, **Toggle**, **Symmetric INIT Preset**, and Event Qualifier `QI`. |

The function block described here thus offers greater flexibility for applications requiring multiple operating modes and a defined initial state.

## Conclusion

The **AX_T_FF_SR_SYM_INIT** is a versatile and robust function block for binary state control in IEC 61499 systems. Its combination of Set, Reset, and Toggle functions, coupled with a freely configurable start state via `Q_INIT` and the qualifier `QI`, enables a compact and reliable implementation of many automation requirements. Thanks to its well-designed INIT handling, it is particularly suitable for applications requiring defined and reproducible start-up behavior.
