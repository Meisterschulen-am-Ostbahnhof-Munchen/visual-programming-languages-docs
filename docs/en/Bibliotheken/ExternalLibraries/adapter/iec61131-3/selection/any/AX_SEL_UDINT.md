# AX_SEL_UDINT

![AX_SEL_UDINT](./AX_SEL_UDINT.svg)

* * * * * * * * * *

## Introduction

The function block `AX_SEL_UDINT` is used for binary selection between two input signals of the data type `UDINT` (Unsigned Double Integer). The control over which of the two inputs is passed to the output is handled via a dedicated adapter input. This function block is based on the IEC 61131-3 standard for selection functions and is specifically designed for use in IEC 61499 environments (such as 4diac IDE).

## Interface Structure

### **Event Inputs**

* **EI0**: Updates and adopts the value of data input `IN0`.
* **EI1**: Updates and adopts the value of data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. It is output as soon as the selected value at output `OUT` has been successfully updated. *(Note: An output event is primarily generated when the state of selector G changes).*

### **Data Inputs**

* **IN0** (UDINT): First selectable data channel.
* **IN1** (UDINT): Second selectable data channel.

### **Data Outputs**

* **OUT** (UDINT): The currently selected data value.

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): Receiver adapter (socket) that provides the selection signal. The data and events it contains control the switching between `IN0` and `IN1`.

---

## Functionality

The `AX_SEL_UDINT` function block operates internally as a network of several elementary function blocks. The selection control process works as follows:

1. **Value Acquisition**: The inputs `IN0` and `IN1` are temporarily stored via Event D flip-flops (`E_D_FF_ANY`) upon the arrival of their respective events (`EI0` and `EI1`, respectively) and forwarded to the internal assignment blocks (`F_MOVE`).
2. **Selection**: The adapter `G` provides the control signal. The event `G.E1` triggers the acquisition of the selection signal `G.D1` via a flip-flop (`E_D_FF_G`).
* If the selection signal at the adapter is **FALSE** (0), the value of `IN0` is switched to `OUT`.
* If the selection signal at the adapter is **TRUE** (1), the value of `IN1` is switched to `OUT`.
3. **Output**: The result is passed to the output `OUT` via the internal selector `F_SEL`, followed by the triggering of the `CNF` event.

---

## Technical Features

* **Composite FB Network**: The function block is implemented internally as a network and uses standard IEC 61131 functions such as `F_SEL` and `F_MOVE`.
* **Adapter Coupling**: Switching is not performed via a classic Boolean data field, but elegantly and modularly via an adapter interface (`AX`). This simplifies wiring in complex applications.
* **Event-Driven Behavior**: An output event (`CNF`) is reliably triggered when the selection state (`G`) changes, in order to inform subsequent program parts about the switch.

--

## State Overview

The selection behaves according to the following truth table:

| Adapter status `G` (data `D1`) | Active input | Value at `OUT` |
:--- | :--- | :--- |
**FALSE** | `IN0` | Value from `IN0` |
**TRUE** | `IN1` | Value from `IN1` |

---

## Application Scenarios

* **Setpoint Switching**: Switching between an automatic setpoint (e.g., from a profile generator) and a manual setpoint (e.g., from an HMI), both of which are stored as `UDINT`. * **Recipe Control**: Selection between different parameter sets or limit values based on machine states signaled via the adapter `G`.
* **Fail-Safe Default Value**: Switches to a safe default value (`IN0`) if a sensor value (`IN1`) becomes invalid.

---

## Comparison with Similar Function Blocks

* **F_SEL (Standard)**: The classic `F_SEL` function block directly has a Boolean input `G` for selection. `AX_SEL_UDINT` encapsulates this logic and instead uses a standardized adapter interface, which increases reusability and clarity in system design.
* **F_SEL (Standard)**: The classic `F_SEL` function block has a Boolean input `G` for selection. `AX_SEL_UDINT` encapsulates this logic and uses a standardized adapter interface instead, which increases reusability and clarity in system design.
* * **AX_SEL (other data types)**: Analogous function blocks exist for other data types (e.g., `AX_SEL_REAL`, `AX_SEL_INT`). `AX_SEL_UDINT` is strictly typed to the data type `UDINT` to ensure type safety in IEC 61499.

---

## Conclusion

The `AX_SEL_UDINT` function block offers a clean, adapter-based solution for binary signal selection for `UDINT` data streams. Thanks to the integrated adapter, it is ideally suited for modular control architectures where selection signals need to be bundled and event-driven.