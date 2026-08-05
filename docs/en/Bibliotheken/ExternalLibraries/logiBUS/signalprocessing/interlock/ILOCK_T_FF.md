# ILOCK_T_FF
![ILOCK_T_FF](./ILOCK_T_FF.svg)
* * * * * * * * * *
## Introduction
The **ILOCK_T_FF** is a composite function block (FB) that implements a lockable toggle flip-flop (T flip-flop). It extends a simple T flip-flop with a bidirectional interlock interface, allowing multiple blocks to be chained together in an interlock chain. This block is particularly suitable for safety-related control systems where states that have been switched must be blocked and passed on to subsequent elements.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-----|--------------|

| CLK | Event | Trigger signal to toggle the output. |

### **Event Outputs**

| Name | Type | Description |

|------|-----|-------------|

| EO | Event | Triggered as soon as the internal set/reset latch changes its state. |

### **Data Inputs**
No data inputs (control is achieved solely through events and the adapters).

### **Data Outputs**

| Name | Type | Description |

|------|-----|-------------|

| Q | BOOL | Current state of the flip-flop (0 or 1). |

### **Adapter**

| Name | Type | Direction | Description |

|------|-----|----------|-------------|

| ILOCK_IN | `adapter::types::bidirectional::AE2` | Socket | Receives and sends lock signals to and from upstream components in the chain. |

ILOCK_OUT | `adapter::types::bidirectional::AE2` | Plug | Sends and receives lock signals to and from downstream components. |

## Functionality
Internally, the component consists of an **E_SWITCH** (event branch) and an **E_SR** (set-reset latch):

1. **Normal Operation (No Lock)**

- An event at the **CLK** is forwarded to the **E_SWITCH**.
- The output **Q** of the internal latch serves as the control signal **G** for the **E_SWITCH**:
- If **Q = FALSE**, the **E_SWITCH** switches the event to **E_SR.S** (Set) – **Q** becomes **TRUE**.
- If **Q = TRUE**, the **E_SWITCH** switches the event to **E_SR.R** (Reset) – **Q** becomes **FALSE**.
- This ensures a clean toggle (edge transition) with every **CLK**.

2. **Lock Mechanism (Interlock)**

- Lock events can be fed into the chain via the adapters **ILOCK_IN** and **ILOCK_OUT**.
- A lock event (e.g., from an upstream component via **ILOCK_IN.EO1** or from a downstream component via **ILOCK_OUT.EI1**) is applied to the **Reset** (**R**) of the latch.
- This immediately resets **Q** to **FALSE**. The toggle operation is interrupted because the **E_SWITCH** now remains in the **Q = FALSE** state and would attempt to set it on the next **CLK** event – however, the lock signal can take effect again.

``` - **Lock Propagation**: Each incoming lock event is simultaneously propagated to the other adapter output:

- **ILOCK_IN.EO1** → **ILOCK_OUT.EO1** (to subsequent devices)
- **ILOCK_OUT.EI1** → **ILOCK_IN.EI1** (to previous devices)
- This allows a lock to propagate in both directions (**Multi-Hop Chain Propagation**).

3. **Result**

- As long as no lock is active, the device operates like a normal T flip-flop.
- As soon as a lock becomes active, it forces **Q = FALSE** and blocks further toggle attempts until the lock is released.

## Technical Features
- **Bidirectional Lock Propagation**: The device can both receive and propagate lock signals, enabling a daisy chain of multiple ILOCK_T_FF devices.
- **Feedback of its own state**: The output signal **Q** is used internally as a control signal for the **E_SWITCH** and determines the toggle direction.
- **No dedicated ECC**: All logic is implemented using the two included basic modules (E_SR, E_SWITCH).

## State Overview
Since the module does not have its own state diagram, the states are derived from the internal **E_SR**:

| State **Q** | Meaning in normal operation | Meaning when Lock is active |

|---------------|----------------------------|-----------------------------|

| 0 | On the next CLK, it toggles to 1. | Lock has set Q to 0 and holds it there. |

| 1 | On the next CLK, it toggles to 0. | Lock immediately resets Q to 0. |

An active lock is present as soon as one of the adapter events (ILOCK_IN.EO1 or ILOCK_OUT.EI1) is received. The lock is maintained until no further lock events are present (the exact resolution depends on the external signal control).

## Application Scenarios
- **Safety interlocks in agricultural technology** (e.g., control of implements): Once activated, a lock state blocks all subsequent switching operations and is propagated to all other components in the chain.
- **Chained emergency stop systems**: Allows the propagation of a stop signal along multiple stations, while each station manages its own state.
- **Protocol adaptation for interlock signals**: The function block can be used as a universal link in an interlock chain where the output Q represents a switching operation.

## Comparison with similar function blocks

| Function block | Properties | Difference from ILOCK_T_FF |

|----------|---------------|----------------------------|

| **T Flip-Flop (e.g., `E_TOGGLE`)** | Pure toggle function without locking logic. | Lacks lock/interlock capability, no adapter interface. |

| **RS Flip-Flop (e.g., `E_SR`)** | Set/reset with two inputs, no toggle. | Can be extended with external logic to enable toggle functionality, but without integrated lock propagation. |

| **Simple Interlock Block** | Only lock propagation, no toggle. | The ILOCK_T_FF combines toggle and lock propagation in a single block. |

## Conclusion

The **ILOCK_T_FF** combines the functionality of a clocked T-flip-flop with efficient, bidirectional interlock propagation. Thanks to its integrated multi-hop propagation, it is ideally suited for networked safety circuits where a switching state must be blocked and simultaneously propagated to the entire circuit. Its compact design as a composite function block makes it easy to understand and reusable.