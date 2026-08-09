# AS_SINT_AX_SEL_AS

![AS_SINT_AX_SEL_AS](./AS_SINT_AX_SEL_AS.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AS_SINT_AX_SEL_AS` serves as a binary selector (selection switch) for signals of data type `SINT` (Short Integer) using standardized adapters. It allows dynamic switching between an input value (`IN0`) supplied via an adapter and a data value (`IN1`) directly at the function block, based on the state of a selection signal (`G`). The selected value is then passed to an output adapter (`OUT`).

 ## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acquisition and processing of the locally available data input `IN1`.

### **Event Outputs**

* *No direct event outputs are available at the block level. Event output is handled via the output adapter `OUT`.*

### **Data Inputs**

* **IN1** (SINT): The selectable input value directly available at the block.

### **Data Outputs**

* *No direct data outputs are available at the block level. Data output is provided via the output adapter `OUT`.*

### **Adapters**

* **Sockets (Input Interfaces):**
* **IN0** (Type: `adapter::types::unidirectional::AS`): Selectable input adapter carrying a `SINT` value.
* **G** (Type: `adapter::types::unidirectional::AX`): Selector adapter (control signal for selection).
* **Plugs (Output Interfaces):**
* **OUT** (Type: `adapter::types::unidirectional::AS`): Adapter for outputting the selected `SINT` value.

## Functionality

Inside the function block, a network of IEC 61131 and IEC 61499 standard function blocks is used to implement edge-triggered selection:

1. **Event and Data Buffering:**

Both the signals from the input adapters (`IN0`, `G`) and the local input (`IN1` coupled to `EI1`) are buffered via D flip-flops (`E_D_FF_ANY` and `E_D_FF`, respectively). This ensures that data values are captured synchronously with their respective events.

The signals from both the input adapters (`IN0`, `G`) and the local input (`IN1` coupled to `EI1`) are buffered using D flip-flops (`E_D_FF_ANY` and `E_D_FF`, respectively). This ensures that data values are captured synchronously with their respective events. 2. **Data Conversion/Forwarding:**

The buffered values for `IN0` and `IN1` are passed to the central selection block `F_SEL` via `F_MOVE` function blocks.

3. **Selection Logic (F_SEL):**
* If the selection signal received via the adapter `G` is **FALSE** (0), the value of `IN0` is passed to the output.
* If the selection signal is **TRUE** (1), the value of `IN1` is passed to the output.
* If the selection signal is **TRUE** (1), the value of `IN1` is passed to the output. 4. **Output:**

The selected value is passed to the flip-flop `E_D_FF_ANY_OUT`, which then outputs the event `E1` and the new data value `D1` to the output adapter `OUT`.

## Technical Features

* **Adapter-Based Architecture:** The use of unidirectional adapters (`AS` and `AX`) greatly simplifies the wiring in the higher-level system.
* **Event-Driven:** The function block reacts immediately to changes in the value of any of the inputs (`IN0`, `IN1`, or `G`) and recalculates the output value.
...* * **Secure State Storage:** The internal flip-flops ensure that even with asynchronously arriving events, the most up-to-date data is always processed consistently.

## State Overview

The selection behaves as follows:

| State Selector `G` | Selected Input | Signal at Output `OUT` |
|:---:|:---:|:---:|
| **FALSE** | `IN0` (via adapter) | Value of `IN0` |
| **TRUE** | `IN1` (local input) | Value of `IN1` |

## Application Scenarios

* **Switching between automatic and manual operation:** Reading a setpoint via a bus system (`IN0`) in automatic mode or via a local HMI (`IN1`) in manual mode, controlled by the signal `G`.
* **Signal bypass/fallback level:** Temporarily switching a fixed value or safe substitute value (`IN1`) onto a signal path if the primary sensor (`IN0`) reports a fault.

## Comparison with similar function blocks

Compared to the standard IEC 61131 function block `SEL`, this function block does not operate on pure data levels, but is fully integrated into the event-driven architecture of IEC 61499. It encapsulates the necessary event-to-data conversions and, unlike the simpler `SEL`, is directly suitable for coupling with adapter connections.

## Conclusion

`AS_SINT_AX_SEL_AS` is a robust and reusable signal switch for event-driven control applications. It combines the flexibility of local variables with the structural elegance of adapter interfaces.