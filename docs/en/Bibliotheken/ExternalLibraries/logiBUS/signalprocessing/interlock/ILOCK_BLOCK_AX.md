# ILOCK_BLOCK_AX

![ILOCK_BLOCK_AX](./ILOCK_BLOCK_AX.svg)

* * * * * * * * * *
## Introduction
The function block **ILOCK_BLOCK_AX** implements an interlock for two opposing directions (up/down or forward/backward). It prioritizes the first active input and ensures that only one direction can be active at a time. The block is implemented as a basic function block (FB) according to IEC 61499-2.

## Interface Structure
The function block uses adapter interfaces of type `adapter::types::unidirectional::AX`. Each adapter consists of an event input `E1` and a data input `D1` (BOOL).

### **Event Inputs**
No discrete event inputs. Events are received via the adapter interfaces:

- `UP_IN.E1` – Upward/forward direction event
- `DOWN_IN.E1` – Downward/backward direction event

### **Event Outputs**
No discrete event outputs. Outputs are provided via the adapter plugs:

- `UP_OUT.E1` – Event when the up direction is enabled/disabled

- `DOWN_OUT.E1` – Event when the down direction is enabled/disabled

### **Data Inputs**

- `UP_IN.D1` (BOOL) – Validation signal for the up direction
- `DOWN_IN.D1` (BOOL) – Validation signal for the down direction

### **Data Outputs**

- `UP_OUT.D1` (BOOL) – Validation signal for the up direction at the output

- `DOWN_OUT.D1` (BOOL) – Validation signal for the down direction at the output

### **Adapters**

- **Sockets (Inputs):**

- `UP_IN` – Adapter for upward control

- `DOWN_IN` – Adapter for downward control

- **Plugs (Outputs):**

- `UP_OUT` – Adapter for upward output

- `DOWN_OUT` – Adapter for downward output

## Functionality
The module operates using a finite state logic controller (ECC). It starts in the **STOP** state. As soon as one of the two events occurs and the corresponding `D1` signal is `TRUE`, it switches to the corresponding directional state. The state is maintained as long as `D1` of the active input remains `TRUE`. If the `D1` signal of the active input is set to `FALSE` (upon a subsequent event), the machine first switches to a **stop intermediate state** (UP_STOP or DOWN_STOP) and then automatically returns to **STOP**. The other input is ignored as long as one direction is active – the function block prioritizes the input that was active first.

The algorithms set the output signals:

- **UP**: `UP_OUT.D1 := TRUE`, `DOWN_OUT.D1 := FALSE`
- **DOWN**: `UP_OUT.D1 := FALSE`, `DOWN_OUT.D1 := TRUE`
- **STOP**: Both outputs set to `FALSE`

## Technical Features

- **Prioritizing the first active input:** Only the first valid command received is executed; The other is blocked until the active one is deactivated.

- **Adapter-based interface:** The use of adapters of type `unidirectional::AX` allows flexible coupling with other components without direct event/data separation.

- **Interlocking at the automaton level:** The state transitions simulate hardware-level safety – `UP_OUT.D1` and `DOWN_OUT.D1 = TRUE` can never occur simultaneously.

- **Intermediate states:** The states `UP_STOP` and `DOWN_STOP` ensure that deactivation is properly acknowledged with an event on the corresponding output adapter.

## State overview

| State | Description | Output signals |

|---------|--------------|-----------------|

| **STOP** | Idle state, no direction active | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |

**UP** | Up direction active | `UP_OUT.D1 = TRUE`, `DOWN_OUT.D1 = FALSE` |

**DOWN** | Down direction active | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = TRUE` |

**UP_STOP** | Disable UP (exit immediately) | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |

**DOWN_STOP** | Disable DOWN (exit immediately) | `UP_OUT.D1 = FALSE`, `DOWN_OUT.D1 = FALSE` |

**Transitions:**

- `STOP → UP` on event from `UP_IN` to `UP_IN.D1 = TRUE`

- `STOP → DOWN` on event from `DOWN_IN` to `DOWN_IN.D1 = TRUE`

- `UP → UP_STOP` on event from `UP_IN` to `UP_IN.D1 = FALSE`

- `DOWN → DOWN_STOP` on event from `DOWN_IN` to `DOWN_IN.D1 = FALSE`

- `UP_STOP → STOP` automatically (Transition 1)

- `DOWN_STOP → STOP` automatic (Transition 1)

## Application Scenarios

- **Traction control (e.g., lifting tables, conveyor belts):** Prevents simultaneous up/down movement.

- **Valve control:** Opening/closing a slide valve with mutual interlocking.

- **Safety-related logic:** Ensures that both drive directions are never activated simultaneously.

- **Control of switches or flaps:** Only one position may be active.

## Comparison with similar function blocks
Compared to a simple RS flip-flop, `ILOCK_BLOCK_AX` offers explicit interlocking and the consideration of validation signals (`D1`). A conventional SR function block would allow simultaneous activation of both outputs without external logic. This function block guarantees mutual exclusivity at the state level.


## Conclusion

`ILOCK_BLOCK_AX` is a compact, safety-oriented functional block for interlocking two opposing directions. Its adapter-based interface and clearly defined mechanism make it easy to integrate and reliable in applications requiring exclusive directional control.