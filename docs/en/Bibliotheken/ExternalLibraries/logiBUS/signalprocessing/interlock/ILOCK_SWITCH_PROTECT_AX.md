# ILOCK_SWITCH_PROTECT_AX

![ILOCK_SWITCH_PROTECT_AX](./ILOCK_SWITCH_PROTECT_AX.svg)

* * * * * * * * * *

## Introduction

The function block `ILOCK_SWITCH_PROTECT_AX` is used for interlocked switching between two input channels (UP/DOWN) with an adjustable protection dead time. It prioritizes the last active input and, through the dead time, prevents uncontrolled switching back and forth (bouncing) in the case of simultaneous or rapidly changing demands. The interface is provided via standardized unidirectional adapters (type `AX`) and a timer adapter.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| `UPDATE` | Parameterization event; The current value of `DT_PROTECT` is assigned to the timer. |

### **Event Outputs**

No direct event outputs. Output is implicit via the adapters:

- `UP_OUT.E1` – Event output of the Up adapter
- `DOWN_OUT.E1` – Event output of the Down adapter
- `timeOut.TimeOut` – Event of the Timer adapter (internal use)

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|--------------|

| `DT_PROTECT` | `TIME` | `T#50ms` | Protection dead time that is activated after a state change. |

### **Data Outputs**

No direct data outputs. State output is provided via the adapters:

- `UP_OUT.D1` – Boolean value for the up output (`TRUE` when active)
- `DOWN_OUT.D1` – Boolean value for the down output (`TRUE` when active)

### **Adapters**

| Direction | Name | Type | Description |

|----------|------|-----|--------------|

| Socket | `UP_IN` | `adapter::types::unidirectional::AX` | Input for the "Up/Forward" request. Contains event `E1` and Boolean data `D1`. |

Socket | `DOWN_IN` | `adapter::types::unidirectional::AX` | Input for the "Down/Backward" request. |

Plug | `UP_OUT` | `adapter::types::unidirectional::AX` | Output for the Up direction. |

Plug | `DOWN_OUT` | `adapter::types::unidirectional::AX` | Output for the Down direction. |

Plug | `timeOut` | `iec61499::events::ATimeOut` | Timer adapter for implementing dead time. Controls the event `TimeOut` after `DT_PROTECT` has elapsed. |

## Functionality

This module implements a **latched two-channel circuit with dead time**:

- The two inputs `UP_IN` and `DOWN_IN` can never be active simultaneously.

- As soon as an input becomes active (i.e., its event `E1` occurs and the corresponding data `D1` is `TRUE`), the module switches to the corresponding state (`UP` or `DOWN`) after a short dead time.


``` - If a direction change occurs, the **protection state `PROTECT`** is first entered, in which all outputs are set to `FALSE` and the timer is started with `DT_PROTECT`. After the dead time has elapsed, the system switches to state `EVAL`, which determines the final state based on the current input signals.

- The dead time prevents crosstalk or signal bounce, e.g., with mechanical switches or overlapping requirements.

## Technical Features

- **Adapter-based interface**: The function block communicates exclusively via standardized adapters (`AX` for Boolean control, `ATimeOut` for timers). This allows for easy reuse in various container blocks.

- **Integrated Protection Logic**: In state `PROTECT`, all outputs are deactivated before a new direction is activated – this protects connected hardware (e.g., motors, valves) from short circuits or mutual blocking.

- **Parameter Update**: The event `UPDATE` allows dynamic adjustment of the dead time at runtime without having to reset the function block.

- **Dead Time on Every State Change**: Every transition (Stop→Up, Down→Up, etc.) always goes through the protection phase, regardless of the previous direction.

## State Overview

| State | Description |

|---------|--------------|

| `STOP` | Idle state. No output active. Waiting for an input to be activated. |

| `UP` | Output `UP_OUT.D1 = TRUE`, `DOWN_OUT.D1 = FALSE`. Activates when `UP_IN.D1` is present and `DOWN_IN.D1` is inactive. |

| `DOWN` | Output `DOWN_OUT.D1 = TRUE`, `UP_OUT.D1 = FALSE`. Activates when `DOWN_IN.D1` is present and `UP_IN.D1` is inactive. |

| `PROTECT` | Protection phase. Both outputs are immediately set to `FALSE`, and the timer is started. After `DT_PROTECT` expires, the process switches to `EVAL`. |

| `EVAL` | Evaluation status. Based on the current input data, a decision is made as to which final state (STOP, UP, DOWN) or PROTECT (in case of simultaneous requests) will be applied. |














































































The transitions defined in the ECC are:

- STOP → UP (at UP_IN.E1 and UP_IN.D1)
- STOP → DOWN (at DOWN_IN.E1 and DOWN_IN.D1)
- UP → PROTECT (at UP_IN.E1 and NOT UP_IN.D1 OR DOWN_IN.E1 and DOWN_IN.D1)
- DOWN → PROTECT (analogous)
- PROTECT → EVAL (after timeOut.TimeOut)
- EVAL → UP (at UP_IN.D1 AND NOT DOWN_IN.D1)
- EVAL → DOWN (at DOWN_IN.D1 AND NOT UP_IN.D1)
- EVAL → STOP (at NOT UP_IN.D1 AND NOT DOWN_IN.D1)

- EVAL → PROTECT (at UP_IN.D1 AND DOWN_IN.D1)

- In each state, an UPDATE event can re-evaluate the state and Update the dead time.

## Application Scenarios

- **Interlocking of drives**: For example, in a lifting table or conveyor belt that may only be active in one direction at a time.

- **Short-circuit protection** in H-bridge circuits: Before the polarity of a motor is switched, both outputs are briefly deactivated.

- **Switching safety logic** in agricultural technology or automation, where mechanical limit switches or proximity sensors require time-based debouncing.

- **Interface between two control systems**: If both systems control a common axis, the function block prevents collisions by prioritizing the last active input.

## Comparison with similar function blocks

- **Simple RS flip-flop**: Offers no dead time and switches instantly – can oscillate with overlapping signals.

- **SWITCH (without protection)**: Standard toggle switch also switches without delay and without debouncing.

- **SR Latch with Timer**: Similar function, but usually implemented as a composite function block. `ILOCK_SWITCH_PROTECT_AX` encapsulates all the logic, including the timer and evaluation, in a single Basic Function Block.

- **Interlock Function Blocks in IEC 61499**: Many libraries offer interlock function blocks, but often without an adapter interface or with fixed delays. This block is specifically designed for use with unidirectional `AX` adapters.

## Conclusion

`ILOCK_SWITCH_PROTECT_AX`This robust and flexible component for interlocked switching with adjustable protection dead time. The adapter-based interface enables seamless integration into modular 4diac architectures. The clear state machine ensures deterministic behavior and provides protection against faulty switching in time-critical applications. Ideal for applications in agricultural technology, automation, and drive technology where reliable direction changes are required.


```

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]