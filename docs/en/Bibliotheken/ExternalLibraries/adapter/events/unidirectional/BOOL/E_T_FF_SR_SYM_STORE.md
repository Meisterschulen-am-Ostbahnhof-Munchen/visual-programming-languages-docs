# E_T_FF_SR_SYM_STORE

![E_T_FF_SR_SYM_STORE](./E_T_FF_SR_SYM_STORE.svg)

* * * * * * * * * *

## Introduction

The function block `E_T_FF_SR_SYM_STORE` implements an event-driven bistable flip-flop with the functions **Set** (S), **Reset** (R), and **Toggle** (CLK). Its special feature is the **symmetrical start-up behavior**: The initial state of the output Q is set via an adapter (`Q_INIT`) during startup or after a `INIT` event. This ensures that the function block behaves deterministically and repeatably at every start time – an important property for safety-critical or predictable automation systems.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `S` | Event | Set output Q to TRUE |

| `R` | Event | Reset output Q to FALSE |

| `CLK` | Event | Toggle – switches Q (TRUE → FALSE or FALSE → TRUE) |

### **Event Outputs**

| Name | Type | With Data | Comment |

|------|-----|------------|-----------|

| `EO` | Event | Q | Indicates that the value of Q has changed |

### **Data Inputs**

None (all inputs are via events).

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `Q` | BOOL | Current value of the flip-flop (TRUE or FALSE) |

### **Adapter**

| Name | Type | Comment |

|------|-----|-----------|

| `Q_INIT` | `adapter::types::bidirectional::AX2` | Sets the initial value of Q on the INIT event. The adapter provides an event-driven, bidirectional channel: Q_INIT.EI1 triggers the initialization, and Q_INIT.DI1 returns the desired initial value (TRUE or FALSE). Additionally, the function block returns the set value via Q_INIT.DO1.

## Functionality

The internal process is controlled by the finite state machine (ECC):

1. **START State:** After power is supplied or a system reset is performed, the function block is in state `START`.

2. **Initialization (State `Init`):** As soon as the event `Q_INIT.EI1` occurs, state `Init` is reached. The following is then determined based on the Boolean value of `Q_INIT.DI1`:

- `TRUE` → Transition to state `SET`

- `FALSE` → Transition to state `RESET`
3. **Operating states `SET` and `RESET`:**

- **SET:** Sets `Q := TRUE` and `Q_INIT.DO1 := TRUE`. Sends output event `EO` and adapter output event `Q_INIT.EO1`.


- **RESET:** Sets `Q := FALSE` and `Q_INIT.DO1 := FALSE`. Also sends `EO` and `Q_INIT.EO1`.

4. **Toggling between SET and RESET:**

- Event `S` (when in RESET state) → toggles to SET.

- Event `R` (when in SET state) → toggles to RESET.

- Event `CLK` (always) → toggles between the two states.

The output `EO` is activated with every state change of Q.


## Technical Features

- **Symmetrical Start-Up:** Unlike simple SR flip-flops with a fixed start value (e.g., FALSE), the start value can be configured via the adapter. This increases flexibility and reproducibility.

- **Toggle Function:** The `CLK` input allows changing the state without knowing the current value – useful for counters, flashers, or state machines.

- **Bidirectional Adapter Interface:** The device reports its set value back to the adapter (`Q_INIT.DO1`), so the initializer can confirm the final state.

- **Prioritization:** If `S`, `R`, or `CLK` arrive simultaneously, only the first processed event is considered (based on the event order in the 4diac IDE). In this specific design, `CLK` is applied as a toggle to the current state, while `S` and `R` set the state independently of the toggle. The state transitions show that `CLK` transitions from each state to the other.

## State Overview

The state machine (ECC) comprises four states:

| State | Description | Outgoing Transitions |

|---------|--------------|--------------------------|

| `START` | Initial sleep state after power-on | → `Init` at `Q_INIT.EI1` |

| `Init` | Initialization state – determines the start value | → `SET` at `TRUE = Q_INIT.DI1` <br> → `RESET` at `FALSE = Q_INIT.DI1` |

| `SET` | Q = TRUE | → `RESET` at `R` or `CLK` |

| `RESET` | Q = FALSE | → `SET` at `S` or `CLK` |

After exiting `Init`, the state `SET` or `RESET` is reached; the states `START` and `Init` are not traversed during normal operation.


## Application Scenarios

- **Machine Control with Defined Start State:** A system should always start in a specific operating mode after a reset. Using `Q_INIT`, for example, a PLC configuration can be used to specify whether a valve position is open or closed at startup.

- **Toggling as a Flashing Function:** The `CLK` input can be triggered periodically (e.g., by a timer block) to implement a flashing signal.

- **Redundant Feedback:** The adapter output `Q_INIT.DO1` returns the set value – ideal for safety functions that require feedback on the switching state.

## Comparison with Similar Blocks

| Block | Properties | Difference to `E_T_FF_SR_SYM_STORE` |

|----------|--------------|---------------------------------------|

| `E_SR_FF` (Standard SR Flip-Flop) | Set, reset; usually no toggle, no configurable start value | Missing toggle function; start value often fixed at FALSE |

| `E_RS_FF` | Set prioritized | Different prioritization; no toggle |

| `E_D_FF` (D Flip-Flop) | Receives a data input with clock | No set/reset without data; no symmetric start |

| `E_CTU` (Counter) | Counts events | No bistable behavior, but counter value |

The `E_T_FF_SR_SYM_STORE`Combines SR functionality, toggle switching, and an initialized start value in a single component – a rare combination in the IEC 61499 world.

## Conclusion

The **E_T_FF_SR_SYM_STORE** is a powerful event-driven flip-flop component for the 4diac IDE. It offers full SR functionality, a toggle option, and symmetrical start-up behavior configurable via an adapter. This makes it particularly suitable for applications requiring deterministic initialization and flexible switching mechanisms. The bidirectional adapter interface increases the integration depth in complex control architectures.


---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 E_CTU Event Counter module on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/event-function-blocks/e_ctu/)

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]