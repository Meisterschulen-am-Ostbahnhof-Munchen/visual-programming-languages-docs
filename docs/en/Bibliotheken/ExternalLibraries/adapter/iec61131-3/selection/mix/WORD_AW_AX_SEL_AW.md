# WORD_AW_AX_SEL_AW

![WORD_AW_AX_SEL_AW](./WORD_AW_AX_SEL_AW.svg)

*(No image available)*

* * * * * * * * * *

The function block **WORD_AW_AX_SEL_AW** is an event-driven, binary selector for data of type `WORD`. It implements a selection function (analogous to `SEL` according to IEC 61131-3) using modern, unidirectional adapter interfaces. The block allows for event-based selection between a directly connected `WORD` input and a `WORD` input fed via an adapter, and forwards the result to an output adapter.





| Name | Type | Description |

| :--- | :--- | :--- |

| **EI0** | Event | Updates and adopts the value of the data input `IN0`. |


*This function block does not have direct event outputs at the block level. Event output is coupled via the output adapter `OUT`.*


| Name | Type | Description |

| :--- | :--- | :--- |

| **IN0** | WORD | Direct, selectable input value 0. Selected when selector `G` is in state `FALSE`. |


*This function block does not have direct data outputs at the block level. Data output is coupled via the output adapter `OUT`.*

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

| Name | Direction | Type | Description |

| :--- | :--- | :--- | :--- |

| **OUT** | Plug | `adapter::types::unidirectional::AW` | The selected output value (`WORD`) including the associated update event. |

| **IN1** | Socket | `adapter::types::unidirectional::AW` | Selectable input value 1 (`WORD`) including the associated update event. Selected when selector `G` is in state `TRUE`. |

| **G** | Socket | `adapter::types::unidirectional::AX` | Selector input (Boolean/bit state). Controls which input is connected to the output. |


## Functionality

The module operates internally using a combination of event D flip-flops (`E_D_FF` and `E_D_FF_ANY`) and conversion and selection modules (`F_MOVE`, `F_SEL`).

1. **Data Storage and Synchronization:**

As soon as an event occurs at one of the inputs (`EI0`, `IN1.E1`, or `G.E1`), the corresponding data value (`IN0`, `IN1.D1`, or `G.D1`) is temporarily stored in the respective internal flip-flop. This ensures that the data is consistent.

2. **Selection Logic:**

The internal selection element `F_SEL` evaluates the state of the selector `G.D1`:

* If the state of **`G` = `FALSE`**, the value of **`IN0`** is passed to the output.

* If the state of **`G` = `TRUE`**, the value of **`IN1`** is passed to the output.

3. **Output:**

The selected value is passed to the output adapter `OUT.D1` via the internal function block `F_MOVE_OUT`. Simultaneously, the output event `OUT.E1` is triggered to inform subsequent program components about the data change.


* **Hybrid Interfaces:** This function block bridges the gap between classic IEC 61499 event/data connections (`EI0` / `IN0`) and modern, adapter-based communication structures.


* **Unidirectional Adapters:** Lean, unidirectional adapter types are used (`AW` for *Adapter Word*, `AX` for *Adapter Binary/Boolean*), which simplifies coupling and saves resources.

**Edge and Event-Driven:** Any change to one of the inputs immediately triggers a recalculation and update of the output.


| State Selector `G.D1` | Trigger Event | Selected Output Value `OUT.D1` | Output Event `OUT.E1` |

| :---: | :---: | :---: | :---: |

| `FALSE` | Any (`EI0`, `G.E1`, `IN1.E1`) | **`IN0`** | Enabled |

| `TRUE` | Any (`EI0`, `G.E1`, `IN1.E1`) | **`IN1.D1`** | Enabled |


* **Setpoint Switching:** Switch between a locally defined default setpoint (`IN0`) and a remote setpoint received via a network/adapter (`IN1`).

* **Operating Mode Selection:** Switching of control words (`WORD`) based on the current system state (e.g., automatic operation vs. manual operation via selector `G`).

* **Signal Fallback:** Fast, event-driven switching to a safe backup value in case of a system component failure.


Compared to the standard selection function block `F_SEL` from the IEC 61131-3 library, `WORD_AW_AX_SEL_AW` offers direct integration into the event-driven world of IEC 61499. While the classic `F_SEL` operates purely in a data flow-oriented manner, this function block captures asynchronous events via the adapters, stores the data consistently, and actively signals changes to the subsequent process.


**Signal Fallback:** Fast, event-driven switching to a safe backup value in case of a system component failure. ## Conclusion

The **WORD_AW_AX_SEL_AW** function block is a useful tool for structured signal processing in complex IEC 61499 control applications. By encapsulating the adapter and flip-flop logic, it significantly simplifies the design of switchable signal paths in the application diagram and ensures clean, event-driven data flow.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion