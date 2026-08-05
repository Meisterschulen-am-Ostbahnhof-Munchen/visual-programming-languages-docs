# AX_RS_SYM_INIT

![AX_RS_SYM_INIT](./AX_RS_SYM_INIT.svg)

* * * * * * * * * *

## Introduction

The function block **AX_RS_SYM_INIT** implements an event-driven, bistable flip-flop (RS flip-flop) with symmetrical startup behavior and an explicit initialization mechanism. It extends a simple RS flip-flop by adding the ability to assume a predefined state at startup (INIT) and to control both initialization and deinitialization via the INIT event input. The actual state of the flip-flop is provided via an adapter, while the data outputs QO and the adapter output Q.D1 are synchronized.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|-------|-------|---------------------------------------------|

| INIT | EInit | Initialization Request (with QI, Q_INIT) |

| R | Event | Reset Signal (resets Q) |

| S | Event | Set Signal (sets Q) |

### **Event Outputs**

| Name | Type | Comment |

|-------|-------|---------------------------------------------|

| INITO | EInit | Initialization Acknowledgement (with QO) |

### **Data Inputs**

| Name | Type | Comment |

|--------|------|-----------------------------------------------|

| QI | BOOL | Event Qualifier – Controls Execution |

| Q_INIT | BOOL | Desired Value of Q at Initialization |

### **Data Outputs**

| Name | Type | Comment |

|------|------|------------------------------------------|

| QO | BOOL | Event Qualifier – passes QI to INITO or on S/R |

### **Adapter**

| Name | Type | Comment |

|------|------------------------------------|------------------------------------------|

| Q | adapter::types::unidirectional::AX | Adapter for the value of the flip-flop (D1) |

## Functionality

The function block cycles through various states, controlled by the INIT, S, and R events.

- In the **START** state, it waits for an INIT event.

- When INIT is received with `QI = TRUE`, it switches to the **INIT** state. The action ``initialize`` sets ``QO := QI``.

- Depending on the value of ``Q_INIT``:

- If ``Q_INIT = TRUE`` → transition to the **SET** state.

- If ``Q_INIT = FALSE`` → transition to the **RESET** state.

- After the action, ``INITO`` is triggered.

- If INIT is received with ``QI = FALSE`` (regardless of whether it's from **SET** or **RESET**), it transitions to the **DeInit** state. The action ``deInitialize`` sets ``QO := FALSE``. Then, `INITO` is triggered, and the function block (FB) returns to **START**.

- In the **SET** and **RESET** states, the FB behaves like a conventional RS flip-flop:

- On **S** event, the action `SET` is executed: `QO := QI`; if `QI = TRUE`, `Q.D1 := TRUE` is also set (adapter output).

- On **R** event, the action `RESET` is executed: `QO := QI`; if `QI = TRUE`, `Q.D1 := FALSE` is set.

- The event at `Q.E1` is sent after each action.

The `QI` variable acts as a qualifier: Only if `QI = TRUE` is present are the operations on the adapter (setting/resetting `Q.D1`) actually performed. Otherwise, only `QO` is passed on.

## Technical Features

- **Symmetrical Startup Behavior**: Initialization takes the value of `Q_INIT` into account, allowing the flip-flop to start in either the SET or RESET state. The behavior is symmetrical because both possibilities are explicitly implemented.

- **Adapter Coupling**: The flip-flop's state is not directly output as a data output, but is provided via a **unidirectional adapter** (`Q`) with output `D1`. This enables loose coupling with other function blocks.

- **Deinitialization**: INIT with `QI = FALSE` resets the function block and returns it to the START state. All internal variables are set to their defined values (`QO = FALSE`).

- **Event Qualifiers**: `QI` and `QO` control event propagation and provide an additional conditional level.

## State Overview

| State | Description |

|---------|---------------------------------------------------|

| START | Wait for INIT event |

| INIT | Initialization: Sets QO and selects target state |

| DEINIT | Deinitialization: Sets QO = FALSE |

| SET | Active set state (Q.D1 = TRUE) |

| RESET | Active reset state (Q.D1 = FALSE) |


**Important Transitions:**

- START → Initialize on INIT with QI = TRUE

- Initialize → SET on Q_INIT = TRUE

- Initialize → RESET on Q_INIT = FALSE

- SET → RESET on R
- RESET → SET on S

- SET/RESET → DeInit on INIT with QI = FALSE

- DeInit → START (automatic after completion)

## Application Scenarios

- **Startup Control**: A flip-flop that should assume a defined initial state after a start or reset (e.g., a machine starts in the "Ready" state).

- **Safe Initialization**: In safety-critical systems where the start state must be explicitly specified.

- **Modular Design**: Used as a fundamental storage element in an adapter-based architecture where the state is passed to other components via the adapter.


## Comparison with Similar Function Blocks

- **Standard RS (e.g., RS Flip-Flop)**: Simple RS flip-flop without INIT and without an adapter. `AX_RS_SYM_INIT` extends this with initialization logic and an adapter interface.

- **Bistable Flip-Flops with Reset**: Many function blocks only offer asynchronous reset. This function block integrates the reset into the event-driven behavior and allows for symmetrical target setting.

- **SR Latch with INIT**: Similar function blocks exist, but usually without the qualifier `QI` and the deinitialization option.

## Conclusion

The function block `AX_RS_SYM_INIT` combines classic RS flip-flop behavior with flexible initialization logic that allows both setting and resetting at startup. The use of an adapter for the state value and the inclusion of qualifiers (`QI`, `QO`) make it a robust and versatile building block for event-driven automation applications that require a defined and resettable initial state.