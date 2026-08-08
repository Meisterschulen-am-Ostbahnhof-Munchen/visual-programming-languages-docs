# AX_SEL_REAL

![AX_SEL_REAL](./AX_SEL_REAL.svg)

![AX_SEL_REAL Funktionsblock](https://via.placeholder.com/150?text=AX_SEL_REAL+FB) *Image of the function block could be inserted here*

* * * * * * * * * *
## Introduction
The function block `AX_SEL_REAL` is a binary selector for data of type `REAL`. It is used to select between two analog input values (`IN0` and `IN1`) based on the state of a selection signal passed via an adapter (`G`) and to output the selected value (`OUT`). The block conforms to the standard selection function according to IEC 61131-3.


## Interface Structure

### **Event Inputs**

* **EI0**: Updates the value of input `IN0`.

* **EI1**: Updates the value of input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Triggered to indicate that output `OUT` has been updated.

### **Data Inputs**

* **IN0** (REAL): The first selectable input value (selected if the selector is `FALSE`).

* **IN1** (REAL): The second selectable input value (selected if the selector is `TRUE`).


### **Data Outputs**

* **OUT** (REAL): The currently selected output value.

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. A change to this adapter triggers a recalculation of the selection.

## Functionality
The function block operates internally with standardized IEC 61131 and IEC 61499 elements:

1. When an event arrives at `EI0` or `EI1`, the corresponding data (`IN0` or `IN1`, respectively) are temporarily stored via internal flip-flops (`E_D_FF_ANY`) and passed to the selection kernel.


 2. The state of adapter `G` (event `E1` and data value `D1`) controls another flip-flop (`E_D_FF_G`).

3. The actual selection block (`F_SEL`) evaluates the state:

* If the selection signal at `G` is **FALSE**, the value of `IN0` is passed to output `OUT`.


 * If the selection signal at `G` is **TRUE**, the value of `IN1` is forwarded to output `OUT`.

4. The result is transmitted via `F_MOVE_OUT` to output `OUT`, and a `CNF` event is generated.

## Technical Features
* **Event Generation**: An output event (`CNF`) is primarily generated when the state of selector `G` changes or the selected value changes.


# Technical Features
* **Event Generation**: An output event (`CNF`) is primarily generated when the state of selector `G` changes or the selected value changes.

 * **Adapter Connection**: By using the standardized adapter `AX`, the selection control can be elegantly and clearly encapsulated without having to run separate Boolean control lines across the FB network.

## State Overview

| Selector State (G) | Output (OUT) |

|:---|:---|

| **FALSE** (or 0) | Value of `IN0` |

| **TRUE** (or 1) | Value of `IN1` |


## Application Scenarios

* **Setpoint Switching**: Switching between a manually setpoint (`IN0`) and an automatic setpoint (`IN1`) from a control system (e.g., temperature or pressure in `REAL`).

* **Sensor Redundancy**: Switching to a backup sensor (`IN1`) if the primary sensor (`IN0`) is flagged as faulty.

* **Recipe Control**: Selection of various physical parameters based on the current process step.


* ## Comparison with Similar Function Blocks

Compared to the standard function block `F_SEL` (from the IEC 61131-3 library), `AX_SEL_REAL` offers event-driven processing according to IEC 61499. This function block also uses an adapter for the selection signal, which simplifies coupling to higher-level control logic (e.g., state machines). Other variants of this function block (e.g., `AX_SEL_INT`) operate on the same principle but process different data types.

## Conclusion
The `AX_SEL_REAL` is a robust and flexible function block for the structured selection of analog floating-point values in 4diac applications. By integrating the control signal via an adapter, it significantly reduces the number of connections in the FB network.