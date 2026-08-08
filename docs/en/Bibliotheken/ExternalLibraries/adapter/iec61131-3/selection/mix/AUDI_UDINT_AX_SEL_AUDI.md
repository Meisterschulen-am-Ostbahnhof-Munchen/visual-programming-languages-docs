# AUDI_UDINT_AX_SEL_AUDI

![AUDI_UDINT_AX_SEL_AUDI](./AUDI_UDINT_AX_SEL_AUDI.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AUDI_UDINT_AX_SEL_AUDI` is used for binary selection (multiplexing) between two input signals of the data type `UDINT` (Unsigned Double Integer). A selector signal controls which of the two inputs is passed through to the output. The block uses an event-driven network of IEC 61499 standard components and employs adapters for structured signal transmission.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |

| :--- | :--- | :--- |

| **EI1** | Event | Updated and adopts the value of the data input `IN1`. |

### **Event Outputs**

No event outputs are defined at the direct block level. Event output is coupled via the output adapter `OUT`.

### **Data Inputs**

| Name | Type | Description |

| :--- | :--- | :--- |

| **IN1** | UDINT | Selectable input variable (value 1). Read via the event `EI1`. |

### **Data Outputs**

No data outputs are defined at the direct block level. Data transmission is coupled via the output adapter `OUT`.

### **Adapters**

| Name | Direction | Type | Description |

| :--- | :--- | :--- | :--- |

| **OUT** | Plug | `adapter::types::unidirectional::AUDI` | The selected and passed-through output value. |

| **IN0** | Socket | `adapter::types::unidirectional::AUDI` | Selectable data input (value 0), provided via an adapter. |

| **G** | Socket | `adapter::types::unidirectional::AX` | Selector signal for controlling the selection. |

* * * * * * * * * *

## Functionality

The function block is internally based on a logic network (`FBNetwork`) that synchronizes the input values, makes the selection, and provides the result at the output.


### Signal Flow and Logic:

1. **Input Synchronization (`IN0` and `IN1`):**

* An event at the adapter input `IN0.E1` reads the data value `IN0.D1` via a D flip-flop (`E_D_FF_ANY_IN0`). This value is then passed to the selector block via `F_MOVE_IN0`.

* An event at the physical input `EI1` reads the data value `IN1` via the D flip-flop (`E_D_FF_ANY_IN1`). This value is then passed to the selector block via `F_MOVE_IN1`.

2. **Selection Control (`G`):**

* An event at the selector adapter `G.E1` reads the state `G.D1`. The D flip-flop `E_D_FF_G` stores this state and controls the selection input `G` of the internal selection block `F_SEL`.


3. **Selection and Output (`F_SEL`):**

* The function block `F_SEL` (standard IEC 61131-3 selection function) evaluates the selection signal `G`:

* If `G` is **FALSE** (0), the value of `IN0` is passed to the output.

* If `G` is **TRUE** (1), the value of `IN1` is passed to the output.

* The result is passed to the output D flip-flop (`E_D_FF_ANY_OUT`) via `F_MOVE_OUT`.


* If `G` is **TRUE** (1), the value of `IN1` is passed to the output. * After a successful update, the event `OUT.E1` is triggered, and the updated value is available at `OUT.D1`.

* * * * * * * * * *

## Technical Features

* **Adapter Coupling:** By using `AUDI` and `AX` adapters, the number of external wires is minimized, and a standardized interface for unidirectional signal paths is provided.

* **Event-Data Decoupling:** The internal D flip-flops (`E_D_FF_ANY`) ensure that data values are only received and consistently forwarded upon the corresponding trigger events (preventing race conditions).


* **Adapter Coupling:** * **Data Type Stability:** The internal data paths and `F_MOVE` functions are explicitly parameterized for the type `UDINT`.

* * * * * * * * * *

## State Overview

Since this is a composite function block (`Composite FB`), its behavior is determined by the internal event-driven data flow:

| Triggering Event | State Selector `G` | State Data Inputs | Resulting Output Behavior |

| :--- | :--- | :--- | :--- |

| `G.E1` (Change) | **FALSE** | Any | `OUT.D1` inherits the current value from `IN0.D1`; trigger on `OUT.E1` |

| `G.E1` (change) | **TRUE** | Any | `OUT.D1` inherits the current value from `IN1`; trigger on `OUT.E1` |

| `IN0.E1` (value change) | **FALSE** | `IN0.D1` has a new value | `OUT.D1` is updated with the new value from `IN0.D1`; trigger on `OUT.E1` |

`IN0.E1` (Value Change) | **TRUE** | `IN0.D1` has a new value | No change to output `OUT`. |

| `EI1` (Value Change) | **FALSE** | `IN1` has a new value | No change to output `OUT`. |

| `EI1` (Value Change) | **TRUE** | `IN1` has a new value | `OUT.D1` is updated with the new value of `IN1`; trigger on `OUT.E1` |


* * * * * * * * * *

## Application Scenarios

* **Recipe or Parameter Switching:** Dynamic switching between two configuration IDs or limit values in `UDINT` format during operation.

* **Sensor Redundancy:** Switching between a primary measured value (`IN0` via adapter) and a backup or calibration value (`IN1` via direct input) based on fault diagnosis (controlled via `G`).

* **Operating Mode Selection:** Routing of different counter readings or timers depending on the active operating mode of the system.


* **Sensor Redundancy:** * * * * * * * * * *

## Comparison with Similar Function Blocks

* **Standard `F_SEL`:** The pure IEC 61131-3 function `F_SEL` has no integrated event control and no adapter support. `AUDI_UDINT_AX_SEL_AUDI` encapsulates this function and makes it directly usable for event-driven IEC 61499 architectures.

* **Generic Selector Blocks:** Compared to purely data-based selectors, this block enforces strict synchronization between data and events through its internal D flip-flops, which increases deterministic execution in the control system.

* * * * * * * * * *

## Conclusion

The `AUDI_UDINT_AX_SEL_AUDI` is a specialized and robust multiplexer for `UDINT` data streams. Through the clever combination of standardized IEC 61131 logic and event-based IEC 61499 adapter technology, it is ideally suited for modular and clearly structured control applications where values need to be switched safely and consistently.