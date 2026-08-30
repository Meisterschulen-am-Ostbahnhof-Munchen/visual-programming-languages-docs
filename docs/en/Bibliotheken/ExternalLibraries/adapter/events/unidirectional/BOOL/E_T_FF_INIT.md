# E_T_FF_INIT

![E_T_FF_INIT](./E_T_FF_INIT.svg)

* * * * * * * * * *
The function block **E_T_FF_INIT** implements a **toggle flip-flop** with integrated initialization logic. It combines the classic behavior of a T flip-flop (switching the output *Q* on each *CLK* event) with targeted output setting during initialization. This block is particularly suitable for applications where a defined initial state is required after startup before normal toggle operation begins.

| Event | Type | With Variables | Description |
| ---------- | -------- | ---------------- | ------------------------------------------------------- |
| **INIT** | EInit | QI, Q_INIT | Initialization request; sets *Q* to *Q_INIT*. |
| **CLK** | Event | – | Clock signal; triggers the toggling of *Q* on each rising edge (if *QI* = TRUE). |
| Event | Type | With Variables | Description |
| ---------- | -------- | --------------- | ------------------------------------------------------- |
| **INITO** | EInit | QO | Initialization confirmation; signals the end of initialization. |
| **EO** | Event | Q | Output event; is output after each state change of *Q*. |
| Variable | Type | Description |
| ---------- | ------- | ------------------------------------------------------------ |
| **QI** | BOOL | Enable signal for the normal toggle function. |
| **Q_INIT** | BOOL | Desired value of *Q* after initialization (if TRUE, *Q* is set). |
| Variable | Type | Description |
| ---------- | ------- | ----------------------------------------------------------- |
| **QO** | BOOL | Output qualifier; set to *QI* on INIT, to FALSE on de-initialization. |
| **Q** | BOOL | Toggle output; toggles with each *CLK* (only if *QI* = TRUE). |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

No adapters available.

## Functionality

The module operates as a **state-controlled machine (ECC)** with five states: `START`, `Init`, `DeInit`, `SET`, and `RESET`.

1. **Initialization (state *Init*)**:

- Triggered by the **INIT** event, provided *QI* = TRUE.
- The algorithm `initialize` sets *QO* to the value of *QI* (here TRUE).
- The transition from *Init* depends on the value of *Q_INIT*:
- *Q_INIT* = TRUE → transition to the **SET** state (*Q* becomes TRUE).
- *Q_INIT* = FALSE → Transition to the **RESET** state (*Q* remains FALSE).
- After the transition, the **INITO** event is output.
1. **De-Initialization (State *DeInit*)**:

- Triggered by an **INIT** event with *QI* = FALSE (from the *SET* or *RESET* states).
- The algorithm `deInitialize` sets *QO* to FALSE.
- Subsequently, the transition back to the **START** start state occurs, and the **INITO** event is output.
1. **Normal Toggle Operation**:

- In the **SET** (*Q* = TRUE) and **RESET** (*Q* = FALSE) states.
- Each **CLK** event toggles between the two states.
- The algorithms `SET` and `RESET` set *QO* to the current value of *QI* and, if *QI* = TRUE, the output *Q* to the corresponding state (TRUE or FALSE).
- After each toggle, the event **EO** is output.

**Important**: The toggle function is only active if *QI* = TRUE. If *QI* = FALSE, *Q* remains unchanged (the IF condition in the algorithms prevents the change).

- **Combined Init/Toggle Logic**: This function block allows the output *Q* to be set to a defined value during initialization (*Q_INIT*). This distinguishes it from a simple T flip-flop, which usually starts in the RESET state.
- **Enable via QI**: The variable *QI* acts as a global enable. Switching occurs only when *QI* = TRUE at *CLK*. When *QI* = FALSE, INIT events can still be processed, but toggle operation is disabled.
- **Output Qualifier QO**: *QO* reflects the enable state – it is set to TRUE upon successful initialization and to FALSE upon de-initialization. This allows for easy monitoring of the block status.

| State | Description | Incoming Transition(s) | Outgoing Action (Algorithm) | Outgoing Event |
| ---------- | ------------------------------------------------------------------------ | ----------------------------------------- | --------------------------------- | ---------------------- |
| START | Idle state after initialization (or after de-initialization). | *DeInit* → START | – | – |
| Init | Initialization phase, sets *QO* and determines *Q*. | START → Init (when INIT & QI = TRUE) | `initialize` | INITO |
| DeInit | De-initialization phase, sets *QO* to FALSE. | SET/RESET → DeInit (when INIT & QI = FALSE) | `deInitialize` | INITO |
| SET | Normal toggle state: *Q* = TRUE. | Init → SET (when Q_INIT = TRUE) <br> RESET → SET (when CLK) | `SET` | EO |
| RESET | Normal toggle state: *Q* = FALSE. | Init → RESET (when Q_INIT = FALSE) <br>SET → RESET (when CLK) | `RESET` | EO |

**Transition conditions** (simplified):

- `START → Init` : `INIT & (QI = TRUE)`
- `Init → SET` : `(Q_INIT = TRUE)`
- `Init → RESET` : `(Q_INIT = FALSE)`
- `SET ↔ RESET` : `CLK`
- `SET / RESET → DeInit` : `INIT & (QI = FALSE)`
- `DeInit → START`: always (condition = 1)

1. **Initializing a Machine with a Defined Start State**

A conveyor belt should always be in the "ready" position (*Q* = TRUE) after being switched on. This is achieved with *Q_INIT* = TRUE and *QI* = TRUE. A clock can then switch the belt between the two states via *CLK*.

1. **Safety-Controlled Toggle**

A safety signal *QI* enables the block. Toggle operations may only be performed when this signal is active. A failure of the enable signal (*QI* = FALSE) leads to de-initialization – the output *Q* remains unchanged and *QO* becomes FALSE.

1. **State Sequence with Initialization Block**

In a sequence control, *E_T_FF_INIT* is used as a flip-flop for a step. Initialization allows the step to be set to either active or inactive immediately after starting, without a separate set or reset pulse.

``## Comparison with Similar Components

| Component | Special Feature |
----------------- | ----------------------------------------------------------------------------- |
| **E_T_FF** | Pure T flip-flop without initialization logic. Always starts in the RESET state. |
| **E_FF** | S-R or D flip-flop – allows setting and resetting via separate events. |
| **E_SR** | Memory component (set-reset) without toggle functionality. |
| **E_T_FF_INIT** | Combines toggle functionality with a freely selectable initial state and enable via *QI*. |

Unlike *E_T_FF*, *E_T_FF_INIT* can set the output to TRUE during initialization and provides explicit enable for toggle operation via *QI*.

The function block **E_T_FF_INIT** is an extended variant of a T-flip-flop, specifically designed for controllers that require a defined initial state after startup. The combination of initialization (via *Q_INIT*), enable (via *QI*), and switching logic (via *CLK*) makes it highly versatile. It is suitable for safety-critical processes where operation is only permitted with active enable, as well as for applications requiring a reproducible startup state. The clearly structured state machine ensures deterministic and predictable behavior.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
