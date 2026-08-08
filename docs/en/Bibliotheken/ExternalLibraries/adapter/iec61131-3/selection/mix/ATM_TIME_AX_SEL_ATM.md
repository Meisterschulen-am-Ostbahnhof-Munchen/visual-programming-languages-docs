# ATM_TIME_AX_SEL_ATM

![ATM_TIME_AX_SEL_ATM](./ATM_TIME_AX_SEL_ATM.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `ATM_TIME_AX_SEL_ATM` is used for binary selection between two time values (type `TIME`). It acts as a link between different interface concepts of IEC 61499 by utilizing both classic event/data inputs and adapter-based connections. Based on a control signal from a selector adapter (`G`), the block selects one of the two inputs (`IN0` or `IN1`) and outputs it at the adapter output (`OUT`).



 ## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |

| :--- | :--- | :--- |

| **EI1** | Signals that a new value is present at data input `IN1` and should be updated. | `IN1` |

### **Event Outputs**

*The function block does not have direct event outputs at the main level. Event output is coupled via the output adapter `OUT`.*

### **Data Inputs**

| Data Point | Type | Description |

| :--- | :--- | :--- |

| **IN1** | TIME | Directly selectable input variable (time value). |


### **Data Outputs**

*This function block does not have direct data outputs at the main level. Data output is coupled via the output adapter `OUT`.*

### **Adapters**

| Adapter Name | Type | Direction | Description |

| :--- | :--- | :--- | :--- |

| **OUT** | `adapter::types::unidirectional::ATM` | Plug | The selected output time value (contains data `D1` and event `E1`). |

| **IN0** | `adapter::types::unidirectional::ATM` | Socket | Selectable adapter input for a time value (contains data `D1` and event `E1`). |

| **G** | `adapter::types::unidirectional::AX` | Socket | Selector adapter to control which input is selected (contains data `D1` as a Boolean and event `E1`). |


---

## Functionality

The function block's internal network implements event-driven selection logic:

1. **Data Storage and Synchronization:**

* When an event is received at the selector adapter `G.E1`, the selection state (Boolean from `G.D1`) is temporarily stored using a D flip-flop (`E_D_FF_G`).

* When an event is received at the adapter input `IN0.E1`, the time value from `IN0.D1` is transferred via a universal D flip-flop (`E_D_FF_ANY_IN0`) and a copy block (`F_MOVE_IN0`).

* An event at the classic input `EI1` inherits the value of `IN1` analogously via `E_D_FF_ANY_IN1` and `F_MOVE_IN1`.

2. **Selection Logic:**

* The standard selection block `F_SEL` evaluates the control signal:

* If the latched signal of `G` is **FALSE**, the value of `IN0` is passed through.

* If the latched signal of `G` is **TRUE**, the value of `IN1` is passed through.


* If the latched signal of `G` is **TRUE**, the value of `IN1` is passed through.

* * Any change to the inputs or the selector triggers the recalculation of the function block `F_SEL`.

3. **Output:**

* The selected value is passed via `F_MOVE_OUT` to an output flip-flop (`E_D_FF_ANY_OUT`).

* This flip-flop passes the selected time value to the data element `OUT.D1` of the output adapter and simultaneously triggers the adapter event `OUT.E1`.


---

## Technical Features

* **Hybrid Architecture:** This module combines classic IEC 61499 data/event interfaces (for `IN1` / `EI1`) with modern, unidirectional adapters (`IN0`, `G`, `OUT`). This makes it extremely flexible for use in heterogeneous control applications.

* **Event Decoupling:** The use of internal D flip-flops (`E_D_FF_ANY` and `E_D_FF`) ensures that data is only acquired and processed when the corresponding events occur.


* ---

## State Overview

Since this is a composite function block (FB), its behavior is determined by the internal data and event flow:

| Selector state (`G.D1`) | Trigger event | Output behavior (`OUT`) |

| :--- | :--- | :--- |

| **FALSE** | Any input event | The value of `IN0.D1` is output to `OUT.D1`; `OUT.E1` is triggered. |

| **TRUE** | Any input event | The value of `IN1` is output to `OUT.D1`; `OUT.E1` is triggered. |

---

## Application Scenarios

* **Setpoint Switching:** Dynamic switching of process times (e.g., purge times, aeration durations, or delay times) between an automatic default value (via adapter `IN0`) and a manually specified parameter (via data input `IN1`).

* **Interface Adaptation:** Use as a bridge block in systems where older program components (operating with standard data ports) need to interact with new, adapter-based software components.

---

## Comparison with Similar Blocks

Compared to a standard selector block (such as `F_SEL` from the IEC 61131-3 library), `ATM_TIME_AX_SEL_ATM` offers complete encapsulation of event processing. While the simple `F_SEL` requires manual event wiring, this module handles event latching and signal routing via adapters completely automatically.

---

## Conclusion

The `ATM_TIME_AX_SEL_ATM` is a specialized, robust selection module for time values. Through the intelligent combination of classic inputs and modern adapters, it significantly simplifies signal routing in complex, event-driven control applications and reduces manual wiring effort in the 4diac application editor.