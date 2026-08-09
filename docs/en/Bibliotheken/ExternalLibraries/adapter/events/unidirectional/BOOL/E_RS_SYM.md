# E_RS_SYM

![E_RS_SYM](./E_RS_SYM.svg)

* * * * * * * * * *
## Introduction

The function block **E_RS_SYM** is an event-driven, bistable flip-flop with symmetrical start behavior. It implements set-reset functionality, where the output Q is defined by both a set and a reset event. Unlike a classic RS flip-flop, this component has an explicit start state that reacts to both events equally.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|--------|-------------------------|
| `R` | Event | Reset of output Q |
| `S` | Event | Set of output Q |

### **Event Outputs**

| Name | Type | Description | With Data |
|------|--------|-------------------------------------|-----------|
| `EO` | Event | Output Q has changed | Yes (with Q)|

### **Data Inputs**

No data inputs available.

### **Data Outputs**

| Name | Type | Description |
|------|--------|---------------------------|
| `Q` | BOOL | Flip-flop value (TRUE/FALSE) |

### **Adapters**

No adapters available.

## Functionality

After being switched on, the module is in the **START** state. From this state, an event at `S` triggers the **SET** state, and an event at `R` triggers the **RESET** state. In each case, the output `Q` is set to `TRUE` (SET) or `FALSE` (RESET), and the event `EO` is output.

- In the **SET** state, an event at `R` returns the module to the **RESET** state.
- In the **RESET** state, an event at `S` returns the module to the **SET** state.
- The output `Q` is only updated upon a state change (i.e., transition to SET or RESET).

The symmetrical start behavior means that both a Set and a Reset event are accepted immediately after initialization – there is no default setting for `Q`.

## Technical Features

- **Symmetrical Start Behavior:** No output value is set in the START state. The device responds equally to the first arriving event (S or R). This distinguishes it from typical RS flip-flops, which usually deliver a defined (often FALSE) initial value after startup.
- **Event-Driven Output:** The event `EO` is triggered precisely when the value of `Q` changes. Thus, a signal change is explicitly transmitted.
- **No Data Inputs:** This function block operates purely event-driven without additional data parameters.

## State Overview

The function block has three states:

| State | Description |
|---------|--------------|
| START | Initial state after power-on; waits for the first S or R event. |
| SET | Q = TRUE; can be switched to the RESET state by R. |
| RESET | Q = FALSE; can be switched to the SET state by S. |

**Transitions:**

- START → SET on event `S`
- START → RESET on event `R`
- SET → RESET on event `R`
- RESET → SET on event `S`

## Application Scenarios

- **Initialization of memory bits** in controllers where the initial value should not be predefined.
- **Symmetrical switching logic** that allows both setting and resetting a marker at the beginning.
- **Alternative to classic RS holders** when a defined startup behavior must be avoided (e.g., in safety-critical applications where an undefined initial state is tolerated).

## Comparison with Similar Function Blocks

| Function Block | Property |
|----------|-------------|
| **E_RS** | Classic RS flip-flop with typically asymmetric start behavior (Q initial FALSE). |
| **E_RS_SYM** | Like E_RS, but with symmetric start behavior – no preset value, start state accepts both events equally. |
| **SR flip-flop** | Similar function, but often with priority for Set or Reset; E_RS_SYM is priority-neutral. |

## Conclusion

The **E_RS_SYM** is suitable for all applications that require simple, yet start-symmetric memory behavior. Due to the clean separation of event change (EO) and data output (Q), it can be easily integrated into event-driven control architectures according to IEC 61499. Its clear state machine makes it reliable and easy to understand.
