# ILOCK_BLOCK_PROTECT

![ILOCK_BLOCK_PROTECT](./ILOCK_BLOCK_PROTECT.svg)

* * * * * * * * * *
## Introduction

The function block `ILOCK_BLOCK_PROTECT` implements an interlock-protected direction control with an adjustable dead time. As soon as an active input (e.g., `EI_UP` with `DI_UP = TRUE`) is detected, it is prioritized, and all conflicting signals are ignored until the active input is reset. After resetting, a configurable protection time (`DT_PROTECT`) elapses before a new direction can be activated. This reliably prevents unwanted direction changes or short circuits.
## Interface Structure

### **Event Inputs**

| Event | with variables | Description |
|----------|---------------|--------------|
| `EI_UP` | `DI_UP`, `DT_PROTECT` | Event to activate forward direction |
| `EI_DOWN`| `DI_DOWN`, `DT_PROTECT` | Event to activate reverse direction |

### **Event Outputs**

| Event | with variables | Description |
|----------|----------------|--------------|
| `EO_UP` | `DO_UP` | Acknowledge active forward direction |
| `EO_DOWN`| `DO_DOWN` | Acknowledge active reverse direction |

### **Data Inputs**

| Variable | Type | Initial Value | Description |
|--------------|---------|-------------|-------------|
| `DI_UP` | BOOL | – | `TRUE` = forward, upward, right, clockwise |
| `DI_DOWN` | BOOL | – | `TRUE` = reverse, downward, left, counterclockwise |
| `DT_PROTECT` | TIME | `T#50ms` | Dead time after resetting a direction |

### **Data Outputs**

| Variable | Type | Description |
|-----------|------|--------------|
| `DO_UP` | BOOL | `TRUE` = Forward direction active |
| `DO_DOWN` | BOOL | `TRUE` = Reverse direction active |

### **Adapters**

| Adapter | Type | Description |
|-----------|--------------------------------|--------------|
| `timeOut` | `iec61499::events::ATimeOut` | Adapter for the time-based control of dead time |

## Functionality

The function block operates according to the **first priority** principle:

1. **Initial state (`STOP`)**

Both outputs are `FALSE`. When an event with a valid condition is received (e.g., `EI_UP` for `DI_UP = TRUE`), the state changes in the corresponding direction (`UP` or `DOWN`).

2. **Directional States (`UP` / `DOWN`)**

The corresponding output (`DO_UP` or `DO_DOWN`) is set to `TRUE`, the other to `FALSE`.

As long as the active input remains active, new events are ignored (especially opposing ones).

A new event with the same input is only processed if the input previously fell to `FALSE` (falling edge) – see `UP_STOP`/`DOWN_STOP`.

... 3. **Reset to Protection Phase (`UP_STOP` / `DOWN_STOP`)**

If the active input is reset (e.g., `DI_UP` from `TRUE` to `FALSE`), the output is immediately set to `FALSE` and the timer `timeOut` is started. The dead time `DT_PROTECT` begins to run.

4. **Evaluation State (`EVAL`)**

After the dead time has elapsed, the function block leaves the protection phase and enters the `EVAL` state. The following decisions are made based on the current inputs:

- `DI_UP = TRUE` and `DI_DOWN = FALSE` → Transition to `UP`
- `DI_DOWN = TRUE` and `DI_UP = FALSE` → Transition to `DOWN`
- Both `FALSE` or both `TRUE` → Return to `STOP`

**Important:** As long as a new event arrives in the state `UP`/`DOWN` while the corresponding input is still `TRUE`, this event is ignored (no State transition). The stop phase is only initiated upon a falling edge.

## Technical Features

- **Internal timer** via adapter `timeOut` (type `ATimeOut`) – the protection time is started by each state transition that deactivates a direction.
- **No simultaneous outputs** – `DO_UP` and `DO_DOWN` are never simultaneously `TRUE`. In the `EVAL` state, both outputs are `FALSE`.
- **Configurable dead time** via input `DT_PROTECT` (factory default 50 ms).
- **Compact implementation** as a Basic Function Block with a finite state machine (6 states).
- The interlock not only prevents conflicting commands but also enforces a minimum pause between two direction changes.

## State Overview

| State | Description |
|--------------|---------------|
| `STOP` | Idle state: both outputs `FALSE`, waiting for the first valid event |
| `UP` | Forward direction active: `DO_UP = TRUE`, `DO_DOWN = FALSE` |
| `DOWN` | Reverse direction active: `DO_DOWN = TRUE`, `DO_UP = FALSE` |
| `UP_STOP` | Protection phase after resetting the forward direction: `DO_UP` to `FALSE`, timer running |
| `DOWN_STOP` | Protection phase after resetting the reverse direction: `DO_DOWN` to `FALSE`, timer running |
| `EVAL` | Evaluation state after timer expiration: Decision on next direction or return to `STOP` |

## Application Scenarios

- **Directional control of motors** (e.g., conveyor belts, hoists, revolving gates) – prevents simultaneous control in both directions and enforces a dead time for the mechanical change of direction.
- **Interlocking of valves or flaps** – e.g., open/close control with protection against rapid switching to prevent mechanical stress.
- **Safety-related controls** – as part of a simple interlock logic when a safety-certified component is not required.
- **Control of feeders** in agricultural technology (see Copyright HR Agrartechnik GmbH) or in conveyor technology.

## Comparison with similar components

| Component | Properties |
|----------|---------------|
| **SR Flip-Flop** | Simple set/reset logic, no dead time, no protection against simultaneous signals |
| **ILOCK_BLOCK_PROTECT** | Prioritizes the first active input, dead time after each direction change, both outputs never active simultaneously `TRUE` |
**Interlock Block without Timer** | Blocking logic only, immediate switching possible, no protection time |
**RS Lock with Time Delay** | Similar, but often less configurable and event-driven |

The `ILOCK_BLOCK_PROTECT`It offers an integrated, configurable dead time and is specifically optimized for event-driven systems according to IEC 61499.

## Conclusion

The `ILOCK_BLOCK_PROTECT` is ideally suited for applications requiring reliable directional interlocking with adjustable protection time. Its clear state machine and use of the standard `ATimeOut` adapter make it easy to integrate into larger control projects. Prioritizing the first active input ensures deterministic behavior, and the enforced dead time protects both the mechanical components and the control logic from unwanted states.
