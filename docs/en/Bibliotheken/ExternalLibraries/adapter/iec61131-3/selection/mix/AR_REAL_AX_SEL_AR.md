# AR_REAL_AX_SEL_AR

![AR_REAL_AX_SEL_AR](./AR_REAL_AX_SEL_AR.svg)

* * * * * * * * * *

## Introduction

The function block `AR_REAL_AX_SEL_AR` is a binary selector (multiplexer) used to select between two analog signal sources (`REAL`). A key feature of this block is its hybrid interface structure: It allows selection between a value read via an adapter and a classic, directly connected IEC 61499 variable. The selection process is also controlled via an adapter-based interface.

## Interface Structure

### **Event Inputs**

* **EI1**: Updates the value of the directly connected data input variable `IN1` and triggers the internal selection process.

### **Event Outputs**

* *(No direct event outputs available. Event forwarding is coupled via the output adapter `OUT`)*.

### **Data Inputs**

* **IN1** (REAL): Selectable input variable (Channel 1). Read in along with the event `EI1`.

### **Data Outputs**

* *(No direct data outputs available. Data is provided coupled via the output adapter `OUT`)*.

### **Adapters**

* **Sockets (Input Adapters):**
* **IN0** (Type: `adapter::types::unidirectional::AR`): Selectable input variable (Channel 0) in the form of a unidirectional adapter for analog values.
* **G** (Type: `adapter::types::unidirectional::AX`): Selection signal (control input) in the form of a unidirectional adapter. Determines which input is connected to the output.
* **Plugs (Output Adapter):**
* **OUT** (Type: `adapter::types::unidirectional::AR`): The selected output value (REAL), provided via a unidirectional adapter.

## Functionality

The function block operates internally as an event-driven network (Composite FB) and uses standardized IEC 61131-3 and IEC 61499 function blocks for data buffering and selection:

1. **Data Buffering (Latching):**
* Events at the inputs (`IN0.E1`, `G.E1`, or `EI1`) each trigger an internal flip-flop (`E_D_FF` or `E_D_FF_ANY`, respectively).
* This ensures that the data values (`IN0.D1`, `G.D1`, and `IN1`) are consistently buffered and synchronously passed to the logic.
* 2. **Value Transfer (Move):**
* The buffered data values of the channels are transferred to the central selector via conversion blocks (`F_MOVE`).
3. **Selection:**
* The core block `F_SEL` (standard selector) evaluates the control signal `G`:
* If the signal at adapter **G** `FALSE` (0), the value from **IN0** (adapter) is passed through to the output.
* If the signal at adapter **G** `TRUE` (1), the value from **IN1** (direct input) is passed through to the output.
* 4. **Output:**
* The selected value is passed to the output plug `OUT` (`OUT.D1`), and simultaneously the output event `OUT.E1` is triggered to inform subsequent modules about the data update.

*```
                  +-------------------------+
|    AR_REAL_AX_SEL_AR    |
[AR] IN0 ------> (0)                     |
|     \                   |
   [AX] G   ------> [Sel]---> [OUT] --------> [AR] OUT
|     /                   |
IN1 ------> (1)                     |
(EI1)    ------>                         |
                  +-------------------------+

## Technical Features

* **Hybrid Interface:** Enables seamless coupling between adapter-based signal processing and classic, event/data-based function blocks.
* **Increased Data Consistency:** The use of internal event D flip-flops (`E_D_FF`) guarantees data and event synchronization. "Slipping through" of incomplete signal states with asynchronous inputs is prevented.
* **Resource Efficiency:** The use of unidirectional adapters (`AR` and `AX`) keeps communication overhead to a minimum.

## State Overview

Since this is a composite function block, its behavior is not controlled by a state machine (ECC) but purely by the internal data and event flow. Every input event leads to an immediate recalculation and update of the output.

| Selection signal (G.D1) | Selected input | Output value (OUT.D1) | Output event |
| :--- | :--- | :--- | :--- |
| `FALSE` | IN0 (Adapter) | Value of `IN0.D1` | `OUT.E1` is triggered |
| `TRUE` | IN1 (Direct input) | Value of `IN1` | `OUT.E1` is triggered |

## Application Scenarios

* **Manual/Automatic Switching:** Integration of an automatic setpoint via a bus system (adapter `IN0`) and a manual setpoint via a local user interface (variable `IN1`).
* **Signal Override / Safety Shutdown:** Temporary activation of a predefined substitute value (`IN1`) upon the occurrence of a specific event (controlled via adapter `G`).
* **Interface Conversion:** Combining various data sources in a modular 4diac application.

## Comparison with Similar Function Blocks

* **Standard `F_SEL`:** This classic selection block processes only standard data types and has no integrated event control or adapter interfaces. `AR_REAL_AX_SEL_AR` encapsulates this functionality and makes it directly network-compatible.
* **Purely adapter-based selectors:** Unlike selectors that rely solely on adapters at their inputs, this block offers flexibility in connecting physical hardware inputs or internal variables thanks to its direct `REAL` input.

## Conclusion

The `AR_REAL_AX_SEL_AR` is a versatile utility block for control projects in the 4diac IDE. It elegantly solves the problem of signal aggregation from different interface types and, through its internal buffering, ensures stable and deterministic behavior in distributed control systems.