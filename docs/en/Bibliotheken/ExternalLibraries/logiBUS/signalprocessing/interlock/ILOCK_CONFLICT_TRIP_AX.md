# ILOCK_CONFLICT_TRIP_AX

![ILOCK_CONFLICT_TRIP_AX](./ILOCK_CONFLICT_TRIP_AX.svg)

* * * * * * * * * *
## Introduction
The function block `ILOCK_CONFLICT_TRIP_AX` implements interlock logic for two opposing directions (UP and DOWN). It prioritizes the first active input signal and immediately switches to a trip state when both inputs are activated simultaneously. Resetting from the trip state is only possible via the event `EI_RESET` when both inputs are inactive. All communication takes place via adapters of type `unidirectional::AX`, enabling flexible and modular integration.

## Interface Structure
### **Event Inputs**

- **EI_RESET** – Event to reset the trip state (only effective if both data inputs of the adapters are FALSE).


### **Event Outputs**
The FB has no direct event outputs. State changes are signaled via the event outputs of the output adapters (plugs):

- **UP_OUT.E1**
- **DOWN_OUT.E1**
- **TRIP_OUT.E1**

### **Data Inputs**
The FB has no direct data inputs. The input data is provided via the adapter sockets:

- **UP_IN.D1** (BOOL) – Enables the up direction.

- **DOWN_IN.D1** (BOOL) – Enables the down direction.

### **Data Outputs**
The FB has no direct data outputs. The output data is provided via the adapter plugs:

- **UP_OUT.D1** (BOOL) – Signal for the up direction.

- **DOWN_OUT.D1** (BOOL) – Signal for the down direction. - **TRIP_OUT.D1** (BOOL) – Signal for trip state.

### **Adapters**
**Sockets (Inputs)**

| Adapter | Type | Description |

|---|---|---|

| `UP_IN` | `adapter::types::unidirectional::AX` | Input for up-direction (event + data) |

| `DOWN_IN` | `adapter::types::unidirectional::AX` | Input for down-direction (event + data) |

**Plugs (Outputs)**

| Adapter | Type | Description |

|---|---|---|

| `UP_OUT` | `adapter::types::unidirectional::AX` | Output for Upward Direction |

| `DOWN_OUT` | `adapter::types::unidirectional::AX` | Output for Downward Direction |

| `TRIP_OUT` | `adapter::types::unidirectional::AX` | Trip State Output |

*Note:* The interface `unidirectional::AX` is interpreted here as an adapter with one event (E1) and one BOOL data element (D1), which carries the activation state.

## Functionality
The function block operates as a finite state machine with four states:

1. **STOP** – Idle state. All outputs are FALSE.

- On event `UP_IN.E1` with the condition `UP_IN.D1 AND NOT DOWN_IN.D1` → transition to **UP**.

- On event `DOWN_IN.E1` with condition `DOWN_IN.D1 AND NOT UP_IN.D1` → transition to **DOWN**.

- On event at either input with condition `UP_IN.D1 AND DOWN_IN.D1` → transition to **TRIP**.

2. **UP** – Upward direction active. `UP_OUT.D1 = TRUE`, all others FALSE.

- On event `UP_IN.E1` with `NOT UP_IN.D1` → return to **STOP**.

- On event `DOWN_IN.E1` with `DOWN_IN.D1` → **TRIP** (conflict).

3. **DOWN** – Downward direction active. `DOWN_OUT.D1 = TRUE`, all others FALSE.

- On event `DOWN_IN.E1` with `NOT DOWN_IN.D1` → return to **STOP**.

- On event `UP_IN.E1` with `UP_IN.D1` → **TRIP** (conflict).

4. **TRIP** – Error/conflict state. `TRIP_OUT.D1 = TRUE`, all others FALSE.

- Only output: Event `EI_RESET`, if `NOT UP_IN.D1 AND NOT DOWN_IN.D1` → return to **STOP**.

Prioritization is implicit: As long as there is no conflict, the first detected and valid request is executed. A change from UP to DOWN (or vice versa) without an intermediate stop is only possible via STOP, unless a conflict occurs that immediately triggers a trip.

## Technical Features
- **Adapter-based communication:** All inputs and outputs are implemented as adapters, enabling loose coupling and easy reuse in complex systems.

- **Trip on conflict:** Simultaneous activation of both directions immediately triggers a separate trip state, which can only be exited by an explicit reset.

- **Reset condition:** The reset (`EI_RESET`) is only effective if both input data are FALSE – this prevents accidental release while a conflict persists.

- **No direct events/data:** The function block has no traditional event or data inputs/outputs, but uses only the adapter interfaces.

## State overview

| State | UP_OUT.D1 | DOWN_OUT.D1 | TRIP_OUT.D1 | Description |

|---|---|---|---|---|

| `STOP` | FALSE | FALSE | FALSE | Resting position, no direction active |

| `UP` | TRUE | FALSE | FALSE | Upward direction active |

| `DOWN` | FALSE | TRUE | FALSE | Downward direction active |

| `TRIP` | FALSE | FALSE | TRUE | Conflict / Trip, requires reset |

**Important Transitions:**

- STOP → UP: when UP_IN is active and DOWN_IN is inactive.

- STOP → DOWN: when DOWN_IN is active and UP_IN is inactive.

- STOP → TRIP: when both inputs are active simultaneously (conflict).

- UP → STOP: when UP_IN is deactivated.

- UP → TRIP: when DOWN_IN is active.

- DOWN → STOP: when DOWN_IN is deactivated.

- DOWN → TRIP: when UP_IN is active.

- TRIP → STOP: only via EI_RESET when both inputs are inactive.

## Application Scenarios

- **Interlock Control on Machines:** Prevents simultaneous movement in two opposite directions (e.g., raising/lowering, forward/backward).

- **Safety-Related Applications:** Detects critical conflict situations and enforces a defined error state that must be acknowledged.

- **Adapter-Based Systems:** Integration into modular automation solutions where components communicate via standardized adapters.


## Comparison with Similar Function Blocks

- Simple interlock function blocks (e.g., `ILOCK`) often switch directly between directions without implementing a trip state.

- Function blocks with priority logic favor one direction, while this function block prioritizes the first arriving request and reports an error in case of a conflict.

- `ILOCK_CONFLICT_TRIP_AX` is distinguished by its explicit trip state and adapter interface – this enables a clean separation of control and diagnostic functions.

## Conclusion
The `ILOCK_CONFLICT_TRIP_AX` is a robust interlock function block specifically designed for conflict situations. The trip state with external reset ensures safe handling of parallel requests. The adapter-based structure facilitates integration into larger automation projects and promotes reusability. This function block represents a reliable and flexible solution for safety-critical or fault-tolerant systems.