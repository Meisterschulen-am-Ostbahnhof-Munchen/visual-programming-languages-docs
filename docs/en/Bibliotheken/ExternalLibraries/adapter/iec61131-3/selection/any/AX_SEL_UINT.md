# AX_SEL_UINT

![AX_SEL_UINT](./AX_SEL_UINT.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AX_SEL_UINT` is a standard binary selection block for unsigned 16-bit integers (`UINT`). It allows selection between two data inputs (`IN0` and `IN1`) and outputs the selected value to `OUT`. Which input is activated is controlled by a specialized, unidirectional adapter (`G`).

 ## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the acquisition and processing of data input `IN0`.
* **EI1**: Triggers the acquisition and processing of data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Signals to the system that a new value is available at output `OUT`.

### **Data Inputs**

* **IN0** (UINT): First selectable input value.
* **IN1** (UINT): Second selectable input value.

### **Data Outputs**

* **OUT** (UINT): The currently selected and forwarded data value.

### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`): Socket adapter that functions as a selector. The selection signal (event and data value) is fed in via this adapter.
* * * * * * * * * *

## Functionality

The function block `AX_SEL_UINT` is internally based on a function block network that synchronizes and filters the incoming signals:

1. **Data Acquisition**: When an event occurs at `EI0` or `EI1`, the respective value (`IN0` or `IN1`, respectively) is buffered via an event-driven flip-flop (`E_D_FF_ANY`) and passed to the actual selection function block (`F_SEL`).
2. **Selection Logic (Selector)**: The adapter `G` provides the control signal. A change to this adapter triggers the internal flip-flop `E_D_FF_G`. The state of this signal determines the active path in the standardized selection block `F_SEL` (IEC 61131-3 `SEL`):
* If the selector state is **0 (FALSE)**, the value of `IN0` is passed through.
* If the selector state is **1 (TRUE)**, the value of `IN1` is passed through.
3. **Output Filtering**: The selected value is passed to the output flip-flop `E_D_FF_ANY_OUT`. An output event at `CNF` is only generated if the output value actually changes or if a corresponding trigger event occurs due to the switching of the selector `G`.
* * * * * * * * * *

## Technical Features

* **Event Filtering on Value Change**: By connecting to `E_D_FF_ANY` at the output, it is ensured that subsequent program parts are not unnecessarily triggered with identical values. A `CNF` event is primarily generated when the selected output value actually changes.
* * **Adapter Connection**: Moving the selector to a separate adapter `G` (type `AX`) allows for clean, modularized coupling in the 4diac network and reduces wiring effort at the higher application level.
* * * * * * * * * *

## State Overview

Since this is a composite function block, its behavior is directly determined by the internal data and event flow network:

| Selector State (Adapter G) | Triggering Input Event | Active Data Path | Output (OUT) | Output Event (CNF) |
| :--- | :--- | :--- | :--- | :--- |
**FALSE (0)** | `EI0` or change to `G` | `IN0` is passed through | Value of `IN0` | Activated on value change |
| **TRUE (1)** | `EI1` or change to `G` | `IN1` is passed through | Value of `IN1` | Activated on value change |

* * * * * * * * * *

## Application Scenarios

* **Setpoint Switching**: Switching a system between a manually set safety setpoint (`IN0`) and an automatically calculated process setpoint (`IN1`) via a central control signal at the adapter `G`.
* * **Sensor Redundancy**: Dynamic switching between two redundant `UINT` measured values based on a higher-level diagnostic status transmitted via the adapter.
* **Recipe Control**: Selection of different configuration or operating parameters during operation.
* * * * * * * * * *

## Comparison with Similar Function Blocks

* **Standard `F_SEL`**: The basic IEC 61131-3 `F_SEL` function block does not have an adapter connection and does not offer integrated event and value filtering. `AX_SEL_UINT` extends this functionality with edge-triggered event flip-flops for resource-efficient operation.
* **`MUX` (Multiplexer)**: A classic multiplexer allows selection from more than two channels, but requires an integer as a selector and is generally not as optimized for discrete-event control networks as this selective component.
* * * * * * * * * *

## Conclusion

The `AX_SEL_UINT` is a highly optimized auxiliary component for 4diac applications that combines the classic binary selection function with modern, event-driven principles. Using the `AX` adapter significantly improves the clarity of the application diagram, while the internal filter structure ensures stable and deterministic behavior.