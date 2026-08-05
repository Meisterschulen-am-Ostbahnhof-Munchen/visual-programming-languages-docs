# ILOCK_SWITCH
![ILOCK_SWITCH](./ILOCK_SWITCH.svg)
* * * * * * * * * *
## Introduction
The function block **ILOCK_SWITCH** serves as a priority-controlled switch with an interlock function. It evaluates two event signals (**EI_UP** and **EI_DOWN**) in combination with associated Boolean data values and sets the outputs **DO_UP** and **DO_DOWN** accordingly. The last active input is always prioritized – simultaneous activation of both outputs is impossible. The logic prevents oscillations and ensures a defined state even with invalid or conflicting input assignments.
## Interface Structure

### **Event Inputs**

| Event | with Data | Description |

|----------|------------|--------------|

| **EI_UP** | DI_UP | Event for requesting the up/forward direction. |

**EI_DOWN** | DI_DOWN | Event for requesting the down/backward direction. |

### **Event Outputs**

| Event | with data | Description |

|----------|-----------|--------------|

**EO_UP** | DO_UP | Triggered when the up direction is activated or when exiting the UP state. |

**EO_DOWN** | DO_DOWN | Triggered when the down direction is activated or when exiting the DOWN state. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| **DI_UP** | BOOL | TRUE = forward, up, right, clockwise |

| **DI_DOWN** | BOOL | TRUE = backward, down, left, counterclockwise |

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| **DO_UP** | BOOL | TRUE = forward, up, right, clockwise |

| **DO_DOWN** | BOOL | TRUE = backward, down, left, counterclockwise |

### **Adapter**
None.

## Functionality

This component implements a finite automaton with six states. The basic idea: **The last valid instruction received sets the output state.** A command is only considered valid if the corresponding Boolean data value is **TRUE**.

- **STOP** (Idle State): Both outputs are **FALSE**.
- **UP**: DO_UP = TRUE, DO_DOWN = FALSE.

This is reached when **EI_UP** occurs with **DI_UP = TRUE** while the STOP state is in the STOP state.

- **DOWN**: DO_UP = FALSE, DO_DOWN = TRUE.

This is reached when **EI_DOWN** occurs with **DI_DOWN = TRUE** while the STOP state is in the STOP state.

- **UP_STOP**: An intermediate state that occurs when **EI_UP** occurs during the UP state, but **DI_UP = FALSE** (and also **DI_DOWN = FALSE**).

In UP_STOP, both outputs are set to FALSE, and the system immediately returns to STOP.

- **DOWN_STOP**: Analogous to UP_STOP for the DOWN state when **EI_DOWN** is **DI_DOWN = FALSE**.
- Direct switching is possible:

From **UP** → **DOWN** when **EI_DOWN** is **DI_DOWN = TRUE** or **EI_UP** is **DI_UP = FALSE** and **DI_DOWN = TRUE** (implicit request for the opposite direction).

From **DOWN** → **UP** analogously.

This logic ensures that only one direction is active at any given time and that the module cleanly returns to its idle state when invalid signals (FALSE values) are received.

## Technical Features
- **Interlocking via state machines**: It is not possible to set both outputs to TRUE simultaneously – even with simultaneous events, switching occurs sequentially.
- **Intermediate States (UP_STOP, DOWN_STOP)**: These prevent unwanted flickering of the outputs by immediately resetting them and transitioning to STOP upon receiving invalid signals.
- **Implicit Switching**: An event whose data value requests the opposite direction (e.g., EI_UP with DI_UP=FALSE and DI_DOWN=TRUE) directly causes the direction change without requiring a separate EI_DOWN event.

## State Overview

| State | DO_UP | DO_DOWN | Achieved by |

|---------|-------|---------|----------------|

| STOP | FALSE | FALSE | Start / after UP_STOP and DOWN_STOP |

| UP | TRUE | FALSE | EI_UP with DI_UP=TRUE from STOP or DOWN |

| DOWN | FALSE | TRUE | EI_DOWN with DI_DOWN=TRUE from STOP or UP |

| UP_STOP | FALSE | FALSE | EI_UP with DI_UP=FALSE and DI_DOWN=FALSE in the UP state |

| DOWN_STOP | FALSE | FALSE | EI_DOWN with DI_DOWN=FALSE and DI_UP=FALSE in the DOWN state |

The transitions between states always occur via an incoming event and the evaluation of the current data values.

## Application Scenarios
- **Motor control for linear actuators, swivel arms, or lifting devices**, where simultaneous movement in both directions must be prevented mechanically or for safety reasons.
- **Interlocking of valve actuators** (open/close) with feedback via limit switches.
- **Operator interfaces with pushbuttons for "Up" and "Down"**, where the last button press takes precedence and permanent blockage is avoided.

## Comparison with Similar Function Blocks
- A simple **AND/OR gate** cannot implement interlocking and would activate both outputs with simultaneous TRUE signals.
- An **RS flip-flop** stores one state, but may allow both set/reset inputs to be activated simultaneously (metastable). ILOCK_SWITCH avoids this through its rigid transition logic.
- A **mux** would only pass through one data value, but cannot implement event-driven prioritization with intermediate states. ILOCK_SWITCH offers a solution specifically optimized for drive interlocks.

## Conclusion

The **ILOCK_SWITCH** is a robust, event-driven function block for interlocked direction control. The combination of a state machine, data dependency, and explicit intermediate states reliably prevents typical problems such as simultaneous activation of both outputs or oscillations. It is particularly suitable for safety-critical controls in automation technology, where a clear and resettable priority logic is required.