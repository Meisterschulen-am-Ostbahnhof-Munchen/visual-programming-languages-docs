# ULINT_AULI_AX_SEL_AULI

![ULINT_AULI_AX_SEL_AULI](./ULINT_AULI_AX_SEL_AULI.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ULINT_AULI_AX_SEL_AULI` is a binary selection block (selector switch) for unsigned 64-bit integers (`ULINT`). It allows switching between two input values based on the state of a selection adapter (`G`). The result is provided via an output adapter (`OUT`). The block combines classic IEC 61131-3 selection logic with the event-driven architecture of IEC 61499, using adapters to reduce wiring complexity.

## Interface Structure

### **Event Inputs**

| Name | Type | Description | Associated Data |
| :--- | :--- | :--- | :--- |
| **EI0** | Event | Signals that a new value is available for the static data input `IN0`. | `IN0` |

### **Event Outputs**

*This function block does not have direct, independent event outputs at the main level. Event forwarding is handled encapsulated via the adapters.*

### **Data Inputs**

| Name | Type | Description |
| :--- | :--- | :--- |
| **IN0** | ULINT | Directly connectable, selectable input variable (static). |

### **Data Outputs**

*This function block does not have direct, independent data outputs at the main level. The selected value is output via the adapter `OUT`.*

### **Adapters**

| Name | Type | Direction | Description |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::AULI` | Plug | The selected output value (Type: `ULINT` including event control).
| **IN1** | `adapter::types::unidirectional::AULI` | Socket | The selectable input value via an adapter interface.
| **G** | `adapter::types::unidirectional::AX` | Socket | The selector (control signal for selecting between `IN0` and `IN1`). |

---

## Functionality

The module internally implements a multiplexer function (corresponding to the standard function `SEL`).

1. **Event and Data Processing:**
* As soon as an event arrives at one of the inputs (`EI0`, `IN1.E1`, or `G.E1`), the corresponding data values are temporarily stored and synchronized via internal D flip-flops (`E_D_FF` or `E_D_FF_ANY`).
* The internal selection block `F_SEL` evaluates the state of selector `G`.
2. **Selection Logic:**
* If selector `G.D1` is **FALSE (0)**, the value of **`IN0`** is passed to the output.
* If selector `G.D1` is **TRUE (1)**, the value of **`IN1`** (supplied via the adapter) is passed to the output.
3. **Output:**
* After selection, the value is transferred to the output register via a `F_MOVE` block.
* * A trigger event is sent via the output adapter `OUT.E1` to inform subsequent program components about the data change.

---

## Technical Features

* **Hybrid Interface:** The module combines classic hardware pins (`IN0`, `EI0`) with modern, event-driven communication adapters (`IN1`, `G`, `OUT`). This facilitates structured, modular programming.
* **Edge-Triggered Update:** Any change to the inputs or the selector immediately triggers a recalculation and update of the output via the internal event circuitry.
* **Edge-Triggered Update:** * **Data Type Specific:** The function block is specifically designed for the data type `ULINT` (64-bit unsigned), guaranteeing high precision and a wide range of values.

---

## State Overview

| State Selector (`G.D1`) | Enabled Event | Resulting Value at `OUT.D1` | Generated Output Event |
| :--- | :--- | :--- | :--- |
**FALSE** | Any (`EI0` / `G.E1` / `IN1.E1`) | **`IN0`** | `OUT.E1` |
**TRUE** | Any (`EI0` / `G.E1` / `IN1.E1`) | **`IN1.D1`** | `OUT.E1` |

---

## Application Scenarios

* **Setpoint Switching:** Switching between a manually entered default value (`IN0`) and an automatically calculated value supplied via a bus system or another module (`IN1`).
* **Redundant Sensors:** Switching between two sensor channels in case of failure or for calibration.
* * **Operating Mode Selection:** Selection of different configuration parameters (encoded as `ULINT`) based on the current system state (automatic/manual operation).

---

## Comparison with Similar Function Blocks

Compared to the standard selection block `SEL` from IEC 61131-3, this block requires significantly fewer manual connections in the 4diac function block diagram thanks to its integrated adapter structures. While a classic `SEL` requires all event lines separately, `ULINT_AULI_AX_SEL_AULI` encapsulates the events for the inputs and output directly in the adapters `IN1`, `G`, and `OUT`.

---

## Conclusion

The `ULINT_AULI_AX_SEL_AULI` is a specialized and highly efficient component for signal and data flow control in complex IEC 61499 applications. Through the consistent use of unidirectional adapters, it ensures clean, well-organized, and easy-to-maintain application networks in the 4diac IDE.