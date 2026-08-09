# DWORD_AD_AX_SEL_AD

![DWORD_AD_AX_SEL_AD](./DWORD_AD_AX_SEL_AD.svg)

*No image available*

* * * * * * * * * *
The function block `DWORD_AD_AX_SEL_AD` is a composite function block for the event-driven binary selection of two signal sources of data type `DWORD`. It acts as a multiplexer, which, based on the state of a selection signal `G` (provided via an adapter of type `AX`), switches either the direct data input `IN0` or the input `IN1` (provided via an adapter `AD`) to the output adapter `OUT`.

* **EI0**: Triggers the acquisition and storage of the directly applied data value `IN0`.
* *No direct event outputs.* (Event forwarding is handled via the output adapter `OUT`).
* **IN0** (DWORD): Directly available, selectable input variable.
* *No direct data outputs.* (Data forwarding is handled via the output adapter `OUT`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AD`): The output adapter that outputs the selected `DWORD` value (`D1`) along with the associated update event (`E1`).
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector adapter. The binary signal (`D1`) controls the selection, and the event (`E1`) triggers the update of the selection state.

---

## Functionality

Inside the function block, several standardized sub-blocks work together to process and forward data in an event-driven manner:

1. **Data Storage (Latch Mechanism):**
* Each time an event is registered at one of the inputs (`EI0`, `G.E1`, `IN1.E1`), an internal flip-flop block (`E_D_FF` or `E_D_FF_ANY`) temporarily stores the current value of the corresponding data point.
* The value of `IN0` is stored in block `E_D_FF_ANY_IN0` when `EI0` occurs.
* * The value of `IN1.D1` is stored in block `E_D_FF_ANY_IN1` at `IN1.E1`.
* The selection signal `G.D1` is stored in block `E_D_FF_G` at `G.E1`.
2. **Value Transfer (Move):**
* The temporarily stored input values are forwarded to the central selection block via `F_MOVE_IN0` and `F_MOVE_IN1`.
3. **Selection:**
* The function block `F_SEL` (IEC 61131-3 Standard Selection) determines the output based on the state of `G`:
* If **`G` = FALSE**, the value of **`IN0`** is passed to the output.
* If **`G` = TRUE**, the value of **`IN1`** is passed to the output.
4. **Output Synchronization:**
* After a selection is made, the value is passed via `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`.
* * This outputs the selected value to `OUT.D1` and triggers the event `OUT.E1`.

---

* **Complete Event Decoupling:** By using event flip-flops (`E_D_FF`) at all inputs, it is ensured that data is only processed on an explicit event edge. This prevents inconsistent states or unnecessary calculation cycles for purely static signal changes.
* **Adapter-Based Architecture:** The use of standardized unidirectional adapters (`AD` and `AX`) minimizes wiring effort in the higher-level system and increases modularity in the 4diac network.

---

| State Selector (`G`) | Triggering Event | Active Input | Output Value (`OUT.D1`) | Output Event (`OUT.E1`) |
| :--- | :--- | :--- | :--- | :--- |
**FALSE** | `EI0` or `G.E1` | `IN0` (Direct) | Value of `IN0` | Triggered |
**TRUE** | `IN1.E1` or `G.E1` | `IN1` (Adapter) | Value of `IN1` | Triggered |

---

* **Switching between manual and automatic values:** Direct parameter input via an HMI (`IN0` via `EI0`) or use of an automatically calculated value from another program component (`IN1` via adapter).
* **Sensor redundancy/fallback systems:** Switching between a primary sensor value and a default/substitute value in case of signal loss or error conditions.
* **Dynamic parameter control:** Flexible assignment of configuration or threshold values in complex control networks.
* ---

Compared to the standard IEC 61131-3 `F_SEL` function block, `DWORD_AD_AX_SEL_AD` offers the following advantages:
* **Event Control:** The standard `F_SEL` operates purely on a data flow basis. This function block integrates the event-based implementation of IEC 61499.
* **Interface Encapsulation:** It combines data and event lines in adapters, allowing for cleaner modeling of signal bus structures instead of having to create numerous individual event and data connections.

--

The `DWORD_AD_AX_SEL_AD` is a robust, reusable selection function block for distributed control systems. It is ideally suited for applications where `DWORD` data streams need to be switched in an event-driven and modular manner.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion