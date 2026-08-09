# AX_SEL_DINT

![AX_SEL_DINT](./AX_SEL_DINT.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AX_SEL_DINT` is used for binary selection between two input values of type `DINT` (Double Integer). Which of the two inputs is passed to the output is controlled by a connected selector adapter (`G`). The block is optimized for use in event-driven systems according to the IEC 61499 standard.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the reading and processing of the data input `IN0`.
* **EI1**: Triggers the reading and processing of data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. It is output to signal that the selected output value `OUT` has been updated.

### **Data Inputs**

* **IN0** (DINT): First selectable data input value. Passed to the output when the adapter's selection signal `G` specifies the state for the first input.
* **IN1** (DINT): Second selectable data input value. Passed to the output when the adapter's selection signal `G` specifies the state for the second input.

### **Data Outputs**

* **OUT** (DINT): The currently selected output value (corresponds to either `IN0` or `IN1`).

### **Adapters**

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that acts as a selector. This adapter receives the control signal that determines which input is activated.

---

## Functionality

The function block `AX_SEL_DINT` encapsulates an internal network of auxiliary function blocks to implement clean event-driven selection:

1. **Data Storage and Forwarding**:
* When an event arrives at `EI0` or `EI1`, the corresponding data (`IN0` or `IN1`, respectively) is temporarily stored via internal D flip-flops (`E_D_FF_ANY_IN0` / `E_D_FF_ANY_IN1`) and forwarded to the internal selection unit (`F_SEL`).
* When an event arrives at `EI0` or `IN1`, the corresponding data (`E_D_FF_ANY_IN0` / `E_D_FF_ANY_IN1`) is temporarily stored and forwarded to the internal selection unit (`F_SEL`). 2. **Selection Logic via Adapter**:
* The adapter input `G` receives both the selection data signal and the corresponding trigger event.
* The adapter's event (`G.E1`) triggers the acceptance of the selection signal (`G.D1`) in the internal flip-flop `E_D_FF_G`.
* The actual selection process is performed by the standard function block `F_SEL`. If the selection signal `False` (0), `IN0` is selected. If it is `True` (1), `IN1` is selected.
* 3. **Event Generation at the Output**:
* The selected value is passed to the output flip-flop `E_D_FF_ANY_OUT`.
* An output event at `CNF` is only generated if the selected value at output `OUT` actually changes. This prevents unnecessary subsequent events in the system when values are updated without relevance.

---

## Technical Features

* **Event Filtering**: By using `E_D_FF_ANY_OUT` at the output, it is ensured that subsequent program parts are only triggered by a genuine change in the output value.
* **Adapter Connection**: The use of the standardized, unidirectional adapter `AX` simplifies wiring in complex systems, as control lines and associated events are bundled in a single connection.

---

## State Overview

| Selector State (G.D1) | Active Event | Output Value (OUT) |
| :--- | :--- | :--- |
| `0` (or False) | `G.E1` / `EI0` / `EI1` | `IN0` |
| `1` (or True) | `G.E1` / `EI0` / `EI1` | `IN1` |

*Note: An output event (`CNF`) is generated when the output value `OUT` changes.*

---

## Application Scenarios

* **Setpoint Switching**: Switching between an automatic setpoint (e.g., from a higher-level controller) and a manual setpoint (e.g., from an HMI) in industrial plants or agricultural machinery.
* **Sensor Redundancy**: Switching between a primary and a backup sensor in case of failure or for calibration.
* **Recipe Control**: Dynamic selection of different configuration parameters during operation.

---

## Comparison with Similar Function Blocks

* **Classic `SEL` (IEC 61131-3)**: The standard selection block operates purely data-flow oriented and does not have event control. It also requires a direct `BOOL` signal for selection.
* **`AX_SEL_DINT`**: Provides a fully-fledged event-driven implementation for IEC 61499. The `G` adapter interface neatly encapsulates control and data signals, and the block's internal logic minimizes the event load on the control network.

---

## Conclusion

The `AX_SEL_DINT` function block is a robust and efficient block for event-driven signal switching. Thanks to the encapsulation of the selection and memory logic, as well as the use of adapters, it is ideally suited for modular and well-organized system architectures in modern control environments.