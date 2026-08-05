# E_SR_SYM_INIT
![E_SR_SYM_INIT](./E_SR_SYM_INIT.svg)

* * * * * * * * * *
## Introduction
The function block `E_SR_SYM_INIT` implements an event-driven, bistable flip-flop with symmetric startup behavior and an INIT interface. It extends a simple SR flip-flop by adding the ability to set the output `Q` to a predefined value (`Q_INIT`) and perform deinitialization during the INIT event. The input qualification `QI` controls whether the operations (S, R, INIT) actually affect `Q`.
## Interface Structure
### **Event Inputs**

| Event | Type | Comment |

|-------|-----|-----------|

| `INIT` | EInit | Initialization request; evaluated with `QI` and `Q_INIT` |

| `S` | Event | Set output `Q` to `TRUE` (only effective if `QI = TRUE`) |

| `R` | Event | Set output `Q` to `FALSE` (only effective if `QI = TRUE`) |

### **Event Outputs**

| Event | Type | Comment |

|-------|-----|-----------|

| `INITO` | EInit | Initialization/Deinitialization Confirmation |

| `EO` | Event | Triggered when `Q` has changed (by S or R) |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| `QI` | BOOL | Input Qualifier; controls whether the operations (S, R, INIT) affect `Q` |
| `Q_INIT` | BOOL | Value that `Q` should assume upon successful initialization (`INIT` with `QI = TRUE`) |

### **Data Outputs**

| Variable | Type | Comment |

|----------|-----|-----------|

| `QO` | BOOL | Output qualifier; returns the value of `QI` during the last action (`FALSE` upon deinitialization) |

| `Q` | BOOL | Value of the flip-flop (bistable output) |

### **Adapter**
None.

## Functionality
The function block has five states: `START`, `Init`, `DeInit`, `SET`, and `RESET`.

- **START**: Idle state after initialization.
- **INIT**: Achieved by `INIT` with `QI = TRUE`. The algorithm `initialize` sets `QO := QI`. The system then switches to state `SET` (if `Q_INIT = TRUE`) or `RESET` (if `Q_INIT = FALSE`), depending on `Q_INIT`. During this process, `Q` is set to the value of `Q_INIT` (via the algorithms `SET` and `RESET`, respectively), and `EO` is triggered.

Q ...8qz is then set to the value of `Q_INIT` (via the algorithms `SET` and `RESET`, respectively). - **DeInit**: This is achieved by `INIT` with `QI = FALSE` from the states `SET` or `RESET`. The algorithm `deInitialize` sets `QO := FALSE`. The function block then automatically returns to the state `START`.

- **SET** and **RESET**: Normal operating states of the flip-flop. On a `S` event, the algorithm `SET` is executed: `QO := QI`, and if `QI = TRUE`, `Q := TRUE` is set; `EO` is triggered. On a `R` event, the algorithm `Q := FALSE` is executed analogously. A `INIT` event with `QI = FALSE` returns to `DeInit`. The output `INIT` with `QI = TRUE` would only be possible from the state `START`.

The qualification `QI` acts as an enable signal: Only if `QI = TRUE` is active do `S`, `R`, and the initialization affect the output `Q`. The output `QO` reflects the last valid value of `QI` (except after `DeInit`, in which case it is `QO = FALSE`).

The qualification `QI` acts as an enable signal: `S`, `R`, and the initialization only affect the output `Q`. The output `QO` reflects the last valid value of `QI` (except after `DeInit`, in which case it is `QO = FALSE`).
## Technical Features

- **Symmetrical Start-up**: After initialization, the value of `Q` is determined solely by `Q_INIT` – regardless of the previous state. This enables deterministic behavior after startup.
- **Qualified Operations**: All actions (S, R, INIT) are only executed if `QI = TRUE` is active. This allows the function block to be switched on and off, for example, via a higher-level controller.
- **Deinitialization**: A `INIT` followed by `QI = FALSE` puts the function block into a defined deinitialization state (`DeInit`), which prevents any further actions until a subsequent `INIT` followed by `QI = TRUE` occurs.
- **No QO Storage**: `QO` is reset with each transition; no separate storage occurs.

## State Overview

START
│
│ INIT[QI = TRUE]
▼
Init ─────────────────────────────────┐
│                                    │
│ [Q_INIT = TRUE]  [Q_INIT = FALSE] │
▼                    ▼               │
SET                 RESET             │
│                    │               │
│ R                  │ S             │
└───────→ RESET      │               │
←───────────┘                │
│                    │               │
│ INIT[QI = FALSE]  │ INIT[QI=FALSE]│
└────────────────────┴───────────────┘
▼
DeInit
│
│ 1 (immer)
▼
START
## Application Scenarios
- **Controllers that require a defined output state after power-up** (e.g., machines: valve closed or open).
- **Systems with safety-critical initialization**, where the output may only be set after authorization by a qualifier (`QI`).
- **Block chains**, where deinitialization (e.g., during a system reset) should return the function block to a default state without the actual set/reset signals still being active.

## Comparison with Similar Function Blocks
- **E_SR** (Standard SR Flip-Flop): Has no initialization behavior; it starts undefined or with the last value. `E_SR_SYM_INIT` extends this with defined initialization and deinitialization.
- **E_RS**: Swaps set/reset priority, but without an initialization mechanism.
- **E_SR_SYM**: Symmetric SR flip-flop without an INIT interface; `E_SR_SYM_INIT` adds the INIT startup logic.

The advantage of `E_SR_SYM_INIT` lies in the combination of qualified initialization with an explicit deinitialization path.

## Conclusion
The function block `E_SR_SYM_INIT` offers a robust, qualified flip-flop with a defined startup state. Its symmetric startup logic and deinitialization capability make it ideal for applications requiring reproducible behavior after system startup or reset. The separation of events and qualification allows for flexible integration into higher-level control structures.
