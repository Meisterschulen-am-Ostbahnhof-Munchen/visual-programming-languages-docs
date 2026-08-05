# E_T_FF_SR_SYM
![E_T_FF_SR_SYM](./E_T_FF_SR_SYM.svg)
* * * * * * * * * *
## Introduction
The function block **E_T_FF_SR_SYM** is an event-driven, bistable toggle switch with an integrated toggle function. It combines the properties of an SR flip-flop (set-reset) and a toggle flip-flop (toggles on clock). Its unique feature is its symmetrical startup behavior: In the initial state, both set and clock events result in the set state, while a reset event directly results in the reset state. This enables defined and predictable behavior immediately after commissioning.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| S | Event | Set output Q (to TRUE) |

R | Event | Reset output Q (to FALSE) |

CLK | Event | Clock to toggle output Q |

### **Event Outputs**

| Name | Type | With Variable | Comment |

|------|-----|--------------|-----------|

EO | Event | Q | Output Q has changed |

### **Data Inputs**

None.

### **Data Outputs**

| Name | Type | Comment |

|------|-----|-----------|

Q | BOOL | Flip-flop value (TRUE = set, FALSE = reset) |

### **Adapters**

None.

## Functionality

The component operates as a finite automaton with three states: **START**, **SET**, and **RESET**.

- In the **START** state (initial state), a **S** event or a **CLK** event causes the component to transition to the **SET** state. A **R** event causes it to transition to the **RESET** state.
- In the **SET** state, an **R** event causes the component to transition to the **RESET** state, as does a **CLK** event. An **S** event would maintain the state (not explicitly modeled, but the output only changes upon transition).
- In the **RESET** state, an **S** event or a **CLK** event causes the component to transition to the **SET** state. An **R** event would maintain the state.

The corresponding algorithm is executed with each state change:

- **SET**: `Q := TRUE;`
- **RESET**: `Q := FALSE;`

The **EO** event is then output, which accompanies the new value of **Q**.

The **toggle** behavior is implemented by ensuring that a CLK event always toggles the current state – regardless of whether SET or RESET is active.

## Technical Features
- No data inputs: Control is achieved exclusively via events. This reduces the number of required connections and simplifies timing analysis.
- Symmetrical start behavior: The initial state START is not equivalent to a defined output value. Instead, a defined subsequent state is immediately assumed with each of the three possible start events (S, R, CLK). This prevents undefined states after the start.
- All algorithms are implemented in ST (Structured Text) and consist of simple assignments.
- Output Q is only updated upon a state change – the EO event indicates precisely this change.

## State Overview

| State | Description |

|---------|--------------|

| START | Initial state after activation of the function block |

| SET | Output Q = TRUE |

| RESET | Output Q = FALSE |

**Transitions** (Event → Target State):

| Initial State | Event | Target State |

|-----------------|----------|-------------|

| START | S | SET |

| START | R | RESET |

| START | CLK | SET |

| SET | R | RESET |

| SET | CLK | RESET |

RESET | S | SET |

| RESET | CLK | SET |

Note: S events remaining in the SET state or R events remaining in the RESET state are not explicitly mapped – the state is retained, and no EO output is generated.

## Application Scenarios
- **Clock Switching Operations**: This function block is suitable for applications where a binary signal needs to be switched by a clock signal, but separate setting or resetting must also be possible (e.g., manual priority control).
- **Symmetrical Start Initialization**: In safety-critical systems, responding equally to S or CLK in the start state prevents the presence of an undefined value.
- **Pulse Width Modulation or Toggle Locking**: As a simple toggle function block with set/reset priority.

## Comparison with Similar Function Blocks

| Function Block | Difference |

|----------|-------------|

| E_FF_SR | Pure SR flip-flop without toggle. No clock function. |

| E_FF_Toggle | Pure toggle flip-flop, no set/reset. |

| E_T_FF_SR | Similar, but without symmetric start behavior. Here, CLK in the START state may lead to undefined behavior. |

| E_T_FF_SR_SYM | Combines SR and toggle with defined start behavior for all input signals. |

## Conclusion

The **E_T_FF_SR_SYM** is a versatile event-driven flip-flop component that combines both set/reset and toggle functions. Its symmetric start behavior makes it particularly suitable for applications where a defined state must be reached immediately after activation – regardless of which event occurs first. Thanks to its purely event-driven control, it can be easily integrated into time-critical control processes.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 The PWM signal & infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)

]