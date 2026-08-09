# UINT_AUI_AX_SEL_AUI

![UINT_AUI_AX_SEL_AUI](./UINT_AUI_AX_SEL_AUI.svg)

* * * * * * * * * *

## Introduction

The function block `UINT_AUI_AX_SEL_AUI` is a binary selector that uses an event-driven selection between two input signals and forwards the result to an output. The unique feature of this block is the combination of classic IEC 61499 interfaces (standard data and events) and adapter-based connections. This enables seamless integration and clean structuring of signal flows in complex control applications.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the acquisition and updating of the directly connected data input `IN0`. (Linked to `IN0`).

### **Event Outputs**

* *No direct event outputs available.* (Event forwarding is handled via the output adapter `OUT`).

### **Data Inputs**

* **IN0** (UINT): Selectable input channel 0 (default data variable).

### **Data Outputs**

* *No direct data outputs available.* (Data is forwarded via the output adapter `OUT`).

### **Adapters**

* **IN1** (Socket, type `adapter::types::unidirectional::AUI`): Selectable input channel 1 via adapter connection.
* **G** (Socket, type `adapter::types::unidirectional::AX`): Selector input via adapter. Determines which of the two channels is routed to the output.
* **OUT** (Plug, type `adapter::types::unidirectional::AUI`): The selected output adapter that forwards the selected signal and its associated event.

---

## Functionality

The component is internally based on a network of standard selection and memory components:

1. **Latching (Signal Storage):**

The input signals (`IN0`, `IN1`, and the selector `G`) are temporarily stored via internal D flip-flops (`E_D_FF` / `E_D_FF_ANY`) when their respective events (`EI0`, `IN1.E1`, or `G.E1`) occur. This ensures that the values remain stable until the next explicit update.

The input signals (`EI0`, `IN1.E1`, or `G.E1`) are temporarily stored. 2. **Value Transfer:**

The buffered values are transferred to the central selection block `F_SEL` via internal `F_MOVE` blocks.

3. **Selection Logic:**

The block `F_SEL` switches the signal based on the state of selector `G`:

* If `G` is **FALSE** (0), the value from channel `IN0` is selected.
* If `G` is **TRUE** (1), the value from channel `IN1` is selected.
4. **Output:**

The selected value is passed to the output D flip-flop `E_D_FF_ANY_OUT`, which then triggers the adapter plug `OUT` (data value `D1` and event `E1`).

       +--------------------------------------------+
|             UINT_AUI_AX_SEL_AUI            |
|                                            |
EI0 ---> [E_D_FF]                                   |
IN0 ---> [ IN0  ] -------\                          |
+---> [ F_SEL ] ---> OUT   |
IN1 ---> [  IN1 ] -------/       ^                  |
(AUI)  |                         |                  |
|                         |                  |
G ---> [   G  ] ---------------/                  |
(AX)  |                                            |
       +--------------------------------------------+

---

## Technical Features

* **Mixed Interface Operation:** This module acts as a bridge between the classic IEC 61499 event/data environment (`IN0`/`EI0`) and modern, adapter-based connection concepts.
* **Event Decoupling:** Thanks to internal buffering, not every minimal fluctuation at the inputs leads to uncontrolled state changes. Only the corresponding event validates the new value.
* **Consistency:** Since all paths are synchronized via D flip-flops, it is ensured that data and events at output `OUT` are always consistent.

---

## State Overview

| Selector State (`G`) | Selected Input | Signal at Output `OUT` | Triggering of `OUT.E1` on... |
| :--- | :--- | :--- | :--- |
| **FALSE** (0) | `IN0` (Standard Input) | Value of `IN0` | Event on `EI0` or change of `G` |
| **TRUE** (1) | `IN1` (Adapter Input) | Value of `IN1` | Event on `IN1.E1` or change of `G` |

---

## Application Scenarios

* **Manual/Automatic Switching:** A process value can be set either manually via a local HMI (specified at `IN0`) or automatically via a bus system/higher-level controller (provided via the adapter `IN1`). The selector `G` switches between the modes.
* **Configurable Default Values:** A default value can be set directly at `IN0` for initialization or error situations, while dynamic data is supplied via the adapter `IN1` during normal operation.
* **Redundant Signal Paths:** Switching to a backup channel in case of a primary sensor failure.
* ---

## Comparison with Similar Components

* **`F_SEL` (Standard Selector):** Operates purely value-based and has no integrated event control or adapter support.
* **Standard Multiplexer (`MUX`):** Usually allows switching many channels, but does not offer native integration of unidirectional adapters like `AUI` and `AX`.

--

## Conclusion

The `UINT_AUI_AX_SEL_AUI` is an extremely useful auxiliary component for modular 4diac architectures. It simplifies signal routing when using adapters and, thanks to its internal event-driven memory architecture, guarantees robust and deterministic signal processing.