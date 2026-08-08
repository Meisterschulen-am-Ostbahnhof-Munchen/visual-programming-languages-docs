# AX_SEL_LREAL

![AX_SEL_LREAL](./AX_SEL_LREAL.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `AX_SEL_LREAL` is used for binary selection between two analog input values of the data type `LREAL` (Double Precision Floating Point). Which of the two inputs is passed through to the output is controlled by a connected adapter of type `AX`. The block is designed for use in event-driven systems according to the IEC 61499 standard and optimizes network load by efficiently filtering events.

## Interface Structure
### **Event Inputs**
* **EI0**: Updates the value of the first data input (`IN0`). * **EI1**: Updates the value of the second data input (`IN1`).

### **Event Outputs**

* **CNF**: Confirmation event. Triggered when the selected output value has changed.

### **Data Inputs**

* **IN0** (LREAL): First selectable input value. Passed to the output if the selection (`G`) specifies the value `FALSE` (or 0).

* **IN1** (LREAL): Second selectable input value. Passed to the output if the selection (`G`) specifies the value `TRUE` (or 1).


### **Data Outputs**

* **OUT** (LREAL): The currently selected input value.

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. The control signal for selecting the active input is read via this adapter.



* **OUT** (LREAL): The currently selected input value.


* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. This adapter reads the control signal for selecting the active input.


* **OUT** (LREAL): The currently selected input value.


* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. ---

## Functionality
Inside the composite function block `AX_SEL_LREAL`, a network of standard selection and filter blocks operates:

1. **Value Storage**: The input data at `IN0` and `IN1` are buffered via edge detection and storage blocks (`E_D_FF_ANY`) when the corresponding events (`EI0`, `EI1`) occur.

2. **Selection**: The adapter `G` provides the selection signal. Upon an event at the adapter (`G.E1`), the state of `G.D1` is transferred to an internal flip-flop. 3. **Pass-Through**: The standard selection block `F_SEL` passes through either `IN0` or `IN1` based on the selector's state.

4. **Event Filtering**: The output `OUT` is monitored by a `E_D_FF_ANY` block. A `CNF` output event is only generated if the actual value at the output `OUT` changes. This prevents unnecessary subsequent calculations in the system during redundant signal updates.


---

## Technical Features
* **Event Reduction**: The integrated value change detector at the output ensures that subsequent program sections are only triggered by a genuine value change (and not by any arbitrary input event).

* **Asynchronous Operation**: The inputs and the selector can be updated completely independently and at different times.

--

## State Overview
Since this is a composite function block (FB network), its behavior is determined by the states of the internal blocks:

* **Waiting State (Idle)**: The block waits for an event at `EI0`, `EI1`, or the adapter `G`.


* **Waiting State**: The block waits for an event at `EI0`, `EI1`, or the adapter `G`. * **Input Update State**: A value at `IN0` or `IN1` changes. The value is updated internally. However, it is only passed to the output if the affected channel is currently active and the output value changes as a result.

* **Switching State**: The signal at adapter `G` changes. The function block immediately switches to the other channel and outputs the `CNF` event if the value changes.

---

## Application Scenarios

* **Setpoint Switching**: Switching between an automatic setpoint (e.g., from a recipe controller) and a manual setpoint (e.g., from a visualization/HMI).

* **Setpoint Switching** * **Sensor Redundancy**: Switching between a primary and a secondary sensor (LREAL precision) in case of a sensor failure.

* **Operating Mode Selection**: Routing of different physical measured variables depending on the active process step.

---

## Comparison with Similar Function Blocks

* **Standard `F_SEL` (IEC 61131-3)**: The standard selector has no event control and no integrated adapter connections. `AX_SEL_LREAL` extends this basic functionality with full IEC 61499 compliance, including event-based optimization and standardized adapter coupling.

* **`AX_SEL_REAL`**: Works analogously to this function block, but is limited to the data type `REAL` (single precision). `AX_SEL_LREAL` offers the 64-bit floating-point representation necessary for high-precision calculations.

---

## Conclusion

`AX_SEL_LREAL` is a robust and efficient component for event-driven signal switching. Thanks to the encapsulated adapter interface and the intelligent suppression of redundant output events, it is ideally suited for high-performance and clean control architectures in industrial automation.