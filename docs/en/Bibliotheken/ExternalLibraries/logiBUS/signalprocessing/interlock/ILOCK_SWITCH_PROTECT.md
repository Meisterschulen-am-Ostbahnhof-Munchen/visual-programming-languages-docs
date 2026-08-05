# ILOCK_SWITCH_PROTECT
![ILOCK_SWITCH_PROTECT](./ILOCK_SWITCH_PROTECT.svg)

* * * * * * * * * *
## Introduction
The **ILOCK_SWITCH_PROTECT** function block implements a prioritized interlock between two switching directions – e.g., up/down, forward/backward, or right/left. It features a configurable dead-time delay that prevents immediate re-switching after a change of direction. The block evaluates the two binary inputs and outputs a switching signal only if the last active input is still active after the dead-time has expired. This prevents momentary oscillations and protects connected actuators.
## Interface Structure

### **Event Inputs**

| Name | With Parameters | Description |
|---------|--------------------------------|------------------------------------------------------|
| EI_UP | `DI_UP`, `DT_PROTECT` | Event requesting the "Up" direction |
| EI_DOWN | `DI_DOWN`, `DT_PROTECT` | Event requesting the "Down" direction |

### **Event Outputs**

| Name | With Parameters | Description |
|---------|----------------|------------------------------------------------------|
| EO_UP | `DO_UP` | Confirmation that the "Up" direction has been activated |
| EO_DOWN | `DO_DOWN` | Confirmation that the "Down" direction has been activated |

### **Data Inputs**

| Name | Data Type | Initial Value | Description |
|------------|----------|-------------|-------------------------------------------------------|
| DI_UP | BOOL | – | TRUE = forward, up, right, clockwise |
| DI_DOWN | BOOL | – | TRUE = backward, down, left, counterclockwise |
| DT_PROTECT | TIME | T#50ms | Protection delay (dead time) before a change of direction|

### **Data Outputs**

| Name | Data Type | Description |
|---------|----------|-------------------------------------------------------|
| DO_UP | BOOL | TRUE = Output active for direction "Up" |
| DO_DOWN | BOOL | TRUE = Output active for direction "Down" |

### **Adapter**

| Name | Type | Description |
|---------|--------------------------------|-----------------------------------------------|
| timeOut | `iec61499::events::ATimeOut` | Adapter for implementing the protection delay |

## Functionality

The module operates as a finite state machine with five states:

1. **STOP** – Idle state. Both outputs are FALSE.

- Upon an event with a valid input (`EI_UP[DI_UP]` or `EI_DOWN[DI_DOWN]`), the module switches directly to the corresponding state.

2. **UP** – The "Up" direction is active. `DO_UP = TRUE`, `DO_DOWN = FALSE`.

- A repeat `EI_UP` with an inactive request (`NOT DI_UP`) or a `EI_DOWN` with an active request (`DI_DOWN`) triggers the protection state.

3. **DOWN** – The "Down" direction is active. `DO_UP = FALSE`, `DO_DOWN = TRUE`.

Similarly: `EI_DOWN[NOT DI_DOWN]` or `EI_UP[DI_UP]` initiates the protection state.

4. **PROTECT** – Protection state. Both outputs are immediately reset (FALSE) and the timer of the adapter `timeOut` is started.

- Only after the configured time (`DT_PROTECT`) has elapsed does the evaluation state begin.

5. **EVAL** – Evaluation after the protection time.

- Based on the current inputs, the following is determined:
- `DI_UP AND NOT DI_DOWN` → **UP**
- `DI_DOWN AND NOT DI_UP` → **DOWN**
- `NOT DI_UP AND NOT DI_DOWN` → **STOP**
- `DI_UP AND DI_DOWN` (both active simultaneously) → **PROTECT** again (invalidation case)

The event outputs are triggered along with the respective executed algorithm. In the UP, DOWN, and PROTECT states, **both** event outputs (EO_UP and EO_DOWN) are sent sequentially – this is a specific behavior of this function block.

## Technical Features
- **Adapter-Based Timer Implementation**: The protection delay is implemented using the standardized IEC61499 adapter `ATimeOut`. This makes the time control platform-independent and allows it to be used in various runtime environments.
- **Dead Time Preset**: The time `DT_PROTECT` is set in the algorithms for the UP, DOWN, and STOP states before the timer is started, if applicable. This ensures that the current time configuration always applies, even if the protection state is repeatedly entered.
- **Lockout for Simultaneous Requests**: If both inputs (`DI_UP` and `DI_DOWN`) are simultaneously requested, the timer is locked.If both conditions are TRUE, the function block remains in the protection state until the request is resolved.

## State Overview

| State | Description | DO_UP | DO_DOWN | Triggered Event Outputs |
|----------|------------------------------------------------------------------|-------|---------|-----------------------------|
| **STOP** | Waiting for a valid request; outputs inactive | FALSE | FALSE | – |
| **UP** | Up direction active; switching blocked without intermediate step | TRUE | FALSE | EO_UP, EO_DOWN |
| **DOWN** | Down direction active; switching blocked without intermediate step | FALSE | TRUE | EO_DOWN, EO_UP |
| **PROTECT** | Protection delay in progress; all outputs disabled | FALSE | FALSE | EO_UP, EO_DOWN, timeOut.START|
| **EVAL** | After the protection time has elapsed, the inputs are evaluated | – | – | – (state change) |

## Application Scenarios
- **Drive Control**: Prevents rapid changes of direction in motors that require a mechanical or electrical dead time (e.g., fans, conveyor belts, sliding gates).
- **Valve or Damper Control**: Ensures that a defined pause is observed before a change of direction (opening/closing) to prevent pressure surges or cavitation.
- **Safety-Oriented Interlock**: The function block can be used to debounce competing control signals and only accept the last pending command after a defined hold time.

## Comparison with Similar Function Blocks

| Function Block | Special Feature |
|------------------------------|--------------------------------------------------------|
| **SR Latch** | Simple set-reset flip-flop with no delay |
| **Interlock (simple)** | Switches instantly, no dead time |
| **ILOCK_SWITCH_PROTECT** | Configurable protection delay, evaluation after the delay, handling of simultaneous requests |

Compared to simple latches, **ILOCK_SWITCH_PROTECT** offers controlled switching, which is particularly advantageous with inductive loads or mechanically slow systems.

## Conclusion

The **ILOCK_SWITCH_PROTECT** function block is a robust IEC 61499 component for applications requiring time-delayed, prioritized switching between two states. Its adjustable dead time, adapter-based timer implementation, and clear state logic make it particularly suitable for industrial control systems where reliability and protection mechanisms are paramount. The simultaneous activation of both event outputs in the action states should be considered during integration.
