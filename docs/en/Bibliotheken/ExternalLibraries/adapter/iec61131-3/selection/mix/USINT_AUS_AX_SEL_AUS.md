# USINT_AUS_AX_SEL_AUS

![USINT_AUS_AX_SEL_AUS](./USINT_AUS_AX_SEL_AUS.svg)

* * * * * * * * * *

## Introduction

The function block `USINT_AUS_AX_SEL_AUS` is used for binary selection between two input signals of the data type `USINT` (Unsigned Short Integer). Which of the two values is passed to the output is controlled by a selection signal from an adapter. The block uses internal event-driven mechanisms to conserve resources and process data only when changes occur. The use of adapters significantly simplifies the wiring within the 4diac IDE.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **EI0** | Event | Updated the value at the local data input `IN0`. |

### **Event Outputs**

*This function block does not have direct standard event outputs. Event forwarding is handled entirely via the output adapter `OUT`.*

### **Data Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **IN0** | USINT | First selectable data channel (local input). |

### **Data Outputs**

*This function block does not have direct standard data outputs. Data forwarding is handled entirely via the output adapter `OUT`.*

### **Adapter**

| Name | Direction | Type | Description |
| :--- | :--- | :--- | :--- |
| **OUT** | Plug | `adapter::types::unidirectional::AUS` | The selected output channel (contains the event `E1` and the data `D1`). |
| **IN1** | Socket | `adapter::types::unidirectional::AUS` | Second selectable data channel via adapter (contains the event `E1` and the data `D1`). |
| **G** | Socket | `adapter::types::unidirectional::AX` | Selector input (control signal for selecting between `IN0` and `IN1`). |

---

## Functionality

The module is internally based on a network of standard function blocks that implement event-driven selection:

1. **Data Storage and Synchronization**:
* As soon as a signal arrives at the event input `EI0`, the value of `IN0` is temporarily stored via an event-driven D flip-flop (`E_D_FF_ANY_IN0`) and a copy block (`F_MOVE_IN0`).
* Analogous processes occur for the adapter input `IN1` (via `E_D_FF_ANY_IN1` / `F_MOVE_IN1` upon arrival of `IN1.E1`) and the selector `G` (via `E_D_FF_G` upon arrival of `G.E1`).
2. **Selection Logic**:
* The actual selection process is performed by the standard selection block `F_SEL`.
* If the state `FALSE` (0) is present at selector input `G`, the value of `IN0` is selected.
* If the state `TRUE` (1) is present at selector input `G`, the value of `IN1` is selected.
3. **Output**:
* The result of the selection is passed to the output adapter `OUT`.
* Any change to the selected value triggers the output event `OUT.E1` and makes the new value `USINT` available at `OUT.D1`.

---

## Technical Features

* **Mixed Operation**: The function block allows for clean coupling between a classic data input (`IN0`) and an adapter-based input (`IN1`).
* **Event-Driven Design**: No continuous cyclic calculation is performed. Processing occurs only when input data changes or a selection event occurs.
* **Compact Architecture**: By encapsulating the D flip-flops and the logic within the FB network, the complexity is hidden from the user.
* ---

## State Overview

| State Selector (`G`) | Triggering Event | Active Channel | Output (`OUT.D1`) | Output Event (`OUT.E1`) |
| :---: | :---: | :---: | :---: | :---: |
| `FALSE` | `EI0` or `G.E1` | `IN0` | Value of `IN0` | Yes |
| `TRUE` | `IN1.E1` or `G.E1` | `IN1` | Value of `IN1.D1` | Yes |

---

## Application Scenarios

* **Operating Mode Switching**: Switching a parameter (e.g., an ID or a mode value in the range 0–255) between a fixed default value (`IN0`) and a value dynamically received via a bus adapter (`IN1`).
* **Manual/Automatic Switching**: Setting target values for actuators where, in manual mode, a local value (`IN0`) is activated, and in automatic mode, a higher-level adapter value (`IN1`) is activated.

---

## Comparison with Similar Building Blocks

Compared to a standard IEC 61131-3 `F_SEL` building block, this block offers direct integration of IEC 61499 adapters. While event handling and adapter conversion would have to be manually configured externally with a standard `F_SEL`, `USINT_AUS_AX_SEL_AUS` handles these tasks directly internally. This saves space in the application diagram and minimizes errors in event chaining.

---

## Conclusion

The `USINT_AUS_AX_SEL_AUS` building block is an efficient, robust, and ready-to-install solution for signal switching in the `USINT` range. Its consistent use of adapters makes it ideally suited for modern, service-oriented, and modular architectures within the 4diac environment.