# AX_SEL_SINT

![AX_SEL_SINT](./AX_SEL_SINT.svg)

* * * * * * * * * *

The function block `AX_SEL_SINT` is a standardized selection function for the data type `SINT` (short integer). It enables binary selection between two input values based on the state of a selection signal, which is read via an adapter. The block is designed for use in event-driven systems and combines classic IEC 61131-3 selection logic with event-based execution according to IEC 61499.

* **EI0**: Updates the value of the data input `IN0`.
* **EI1**: Updates the value of data input `IN1`.
* **CNF**: Confirmation event. Signals that an evaluation has taken place and an updated value is available at `OUT`.
* **IN0** (SINT): First selectable input value. This value is passed to the output when the adapter's selection signal is `FALSE`.
* **IN1** (SINT): Second selectable input value. This value is passed to the output when the adapter's selection signal is `TRUE`.
* **OUT** (SINT): The currently selected output value.

**IN0** (SINT): ### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional receiver adapter that serves as a selector. This adapter receives the control signal for the selection (data value `D1`, clocked by the event `E1`).

---

### **Adapter**

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

## Functionality

The function block `AX_SEL_SINT` operates internally as a composite function block (FB). It coordinates the data flow between the inputs and the output via memory elements (D flip-flops):

1. **Input Update**: As soon as an event arrives at `EI0` or `EI1`, the corresponding data value (`IN0` or `IN1`, respectively) is transferred via an internal flip-flop (`E_D_FF_ANY`) and forwarded to the internal selection kernel.
2. **Selector Input**: An event at the adapter input `G.E1` triggers the transfer of the selection signal `G.D1` via `E_D_FF_G`.
3. **Selection Logic (F_SEL)**:
* If the selection signal is `FALSE`, `IN0` is switched to output `OUT`.
* If the selection signal is `TRUE`, `IN1` is switched to output `OUT`.
4. **Event Generation**: Any change or update to the inputs or the selector triggers a recalculation via the internal circuitry. After successful selection, the output event `CNF` is triggered to inform subsequent function blocks of the new value at `OUT`.

---

* **Adapter Coupling**: The use of a unidirectional adapter for the selection signal allows for clean encapsulation and reduces wiring complexity in the FB network.
* **Event-Driven Memory**: By using `E_D_FF` and `E_D_FF_ANY`, input values are stably buffered, ensuring that even asynchronous signal changes are processed without errors.
* **Signal Change**: An output event is reliably generated when one of the input components (`IN0`, `IN1`) or the selector signal is updated.

--

Since `AX_SEL_SINT` is a composite function block, it does not have its own internal state machine (ECC). The behavior is entirely determined by the interaction of the internal components and their data/event flows:

| Triggering Event | State Selector (`G.D1`) | Effect at Output | Output Event |
| :--- | :--- | :--- | :--- |
| `EI0` / `EI1` / `G.E1` | `FALSE` | `OUT` assumes the value of `IN0` | `CNF` |
`EI0` / `EI1` / `G.E1` | `TRUE` | `OUT` assumes the value of `IN1` | `CNF` |

---

* **Setpoint Switching**: Switching between two predefined states or limit values (e.g., recipe values, standard vs. maintenance speeds) that are defined as `SINT` (range -128 to 127).
* * **Manual/Automatic Switching**: Selection of a setpoint either from an automatic control (`IN1`) or a manual setting (`IN0`) via a logical control signal at the adapter `G`.

---

* **F_SEL (IEC 61131-3)**: The standard selection function block `F_SEL` operates purely in a data flow-oriented manner. `AX_SEL_SINT` extends this functionality to include the event-driven execution of IEC 61499 and elegantly integrates the selection signal via an adapter interface.
* **F_SEL (IEC 61131-3)**: The standard selection function block `F_SEL` operates purely in a data flow-oriented manner. `AX_SEL_SINT` extends this functionality to include the event-driven execution of IEC 61499 and elegantly connects the selection signal via an adapter interface.
* * **Other AX_SEL Blocks**: Blocks like `AX_SEL_INT` or `AX_SEL_REAL` offer the same functionality but are designed for larger integer or floating-point data types. `AX_SEL_SINT` is optimized for resource-efficient 8-bit integers.

---

`AX_SEL_SINT` offers a high-performance and clean way to implement binary selections on `SINT` data in IEC 61499 applications. The combination of adapter connectivity and event-driven triggering makes it a flexible block for modular control architectures.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion