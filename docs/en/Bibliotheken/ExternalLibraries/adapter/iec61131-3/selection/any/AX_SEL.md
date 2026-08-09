# AX_SEL

![AX_SEL](./AX_SEL.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AX_SEL` is used for binary selection between two input signals via an adapter selector. The special feature of this block is that an output event is only generated when the state of the selection input (via the adapter `G`) changes. Value changes at the data inputs alone do not trigger data transmission at the output.

## Interface Structure

### **Event Inputs**

* **EI0**: Updates the value of the data input `IN0`.
* **EI1**: Updates the value of the data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Signals that a newly selected value is present at output `OUT`. This event is only triggered when the selector `G` changes.

### **Data Inputs**

* **IN0** (`ANY`): First selectable data input.
* **IN1** (`ANY`): Second selectable data input.

### **Data Outputs**

* **OUT** (`ANY`): The currently selected output value (corresponds to either `IN0` or `IN1`).

### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. It contains:
* an event `E1` (which serves as the clock signal for the selection)
* a data element `D1` (the actual selection signal)

---

## Functionality

Internally, the composite function block `AX_SEL` is composed of two subordinate blocks:

1. **`E_D_FF`** (Event D Flip-Flop): This block stores the state of the selection signal `G.D1` as soon as the event `G.E1` arrives.
2. **`F_SEL`** (Standard selection function according to IEC 61131-3): Performs the actual selection.

If an event arrives via the adapter `G` (`G.E1`), the value of `G.D1` is transferred to the flip-flop. The flip-flop then outputs an event `EO`, which triggers the calculation in the selection block `F_SEL`.

* If the state of the selector `FALSE`, `IN0` is passed through to the output `OUT`.
* If the selector is in the state `TRUE`, `IN1` is passed through to the output `OUT`.

Since the event inputs `EI0` and `EI1` are not connected to the internal trigger network, a simple change in the value of the inputs `IN0` or `IN1` does not result in an immediate update of the output event `CNF`.

` ... `

``

 ---

## Technical Features

* **Data Type Flexibility**: By using the generic data type `ANY` for `IN0`, `IN1`, and `OUT`, the function block can be used for a wide variety of data types (e.g., `INT`, `REAL`, `BOOL`, etc.).
* **Event Filtering**: Prevents "event spamming." The output `CNF` is triggered extremely efficiently, only when an actual switching operation takes place via the adapter `G`.

**Event Filtering**: Prevents "event spamming." ---

## State Overview

This function block does not have a complex internal state machine (ECC) because it is implemented as a composite function block (network). Its behavior is determined by the combination of the event-driven D flip-flop (`E_D_FF`) and the standard selector (`F_SEL`):

| State Selector (`G.D1`) | Trigger Event | Output Value (`OUT`) | Output Event (`CNF`) |
|:---|:---|:---|:---|
| Any | `EI0` or `EI1` | No change to the output | No event |
| `FALSE` | `G.E1` | Value of `IN0` | `CNF` is triggered |
| `TRUE` | `G.E1` | Value of `IN1` | `CNF` is triggered |

---

## Application Scenarios

* **Switching between operating modes**: Selection between a manual setpoint (`IN0`) and an automatic setpoint (`IN1`), with the switching coordinated via a central control signal (adapter `G`).
* * **Redundant Sensors**: Switching between a primary sensor and a backup sensor upon signal change.
* **Resource-Efficient Data Transmission**: Scenarios in which subsequent program components should only become active upon an explicit change in the signal source.

---

## Comparison with Similar Function Blocks

* **Standard `F_SEL`**: The standard selection block reacts directly to each calculation event (`REQ`) and requires separate control lines. `AX_SEL`, on the other hand, encapsulates the control via a standardized adapter interface (`AX`) and ensures internally that events are only forwarded upon a selector change.
* **Simple Multiplexers**: Standard multiplexers often continuously pass data through. `AX_SEL` operates purely on an event-driven basis, thus minimizing CPU load in distributed IEC 61499 systems.

---

## Conclusion

`AX_SEL` is a specialized and highly efficient component for signal selection in distributed automation. By linking the evaluation to the adapter event, an unwanted flood of output events is prevented, which optimizes performance and clarity within the 4diac control application.