# BYTE_AB_AX_SEL_AB

![BYTE_AB_AX_SEL_AB](./BYTE_AB_AX_SEL_AB.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `BYTE_AB_AX_SEL_AB` is a composite function block for IEC 61499 systems. It is used for binary selection (multiplexing) of data of type `BYTE`. The block allows selection between a local input value and an input value supplied via an adapter. The selection is controlled via a separate adapter input (selector). The result is also output via an adapter.

The use of adapters significantly simplifies the wiring within the 4diac IDE and improves the encapsulation of signal and event flows.

---

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |
| :--- | :--- | :--- |
| `EI0` | Sets/updates the local input value `IN0`. | `IN0` |

### **Event Outputs**

*No direct event outputs are available. Event output is exclusively encapsulated via the output adapter `OUT`.*

### **Data Inputs**

| Variable | Data Type | Description |
| :--- | :--- | :--- |
| `IN0` | `BYTE` | Selectable local input value (Input 0). |

### **Data Outputs**

*No direct data outputs are available. Data output is exclusively encapsulated via the output adapter `OUT`.*

### **Adapters**

| Adapter Name | Type | Direction | Description |
| :--- | :--- | :--- | :--- |
| `OUT` | `adapter::types::unidirectional::AB` | Plug | The selected output value (contains event `E1` and data `D1` of type `BYTE`). |
| `IN1` | `adapter::types::unidirectional::AB` | Socket | Selectable input value 1 (contains event `E1` and data `D1` of type `BYTE`). |
| `G` | `adapter::types::unidirectional::AX` | Socket | Selector input (contains selection signal `D1` and trigger event `E1`). |

---

## Functionality

The function block is internally based on a network of standard function blocks that ensure event and data synchronization:

1. **Storage & Triggering:**
* An event at `EI0` stores the value `IN0` in the D flip-flop `E_D_FF_ANY_IN0` and triggers the internal transfer (`F_MOVE_IN0`).
* An event at the adapter `IN1` (`IN1.E1`) stores the value `IN1.D1` in the D flip-flop `E_D_FF_ANY_IN1` and triggers the transfer (`F_MOVE_IN1`).
* An event on the adapter `G` (`G.E1`) stores the selector state `G.D1` in the flip-flop `E_D_FF_G` and triggers the evaluation.
2. **Selection Logic:**
* The function block `F_SEL` (IEC 61131-3 Selection) performs the actual selection.
* If the state of `G` (via `E_D_FF_G.Q`) is **FALSE**, the value of `IN0` is passed to the output.
2. **Selection Logic:**
* The function block `F_SEL` (IEC 61131-3 Selection) performs the actual selection. * If the state of `G` is **TRUE**, the value of `IN1` is passed to the output.
3. **Output:**
* After selection, the value is passed via the conversion block `F_MOVE_OUT` to the output flip-flop `E_D_FF_ANY_OUT`.
* This generates the output event `OUT.E1` and places the selected byte on the data channel `OUT.D1` of the output adapter.

---

## Technical Features

* **Adapter Coupling:** By using unidirectional adapters (`AB` and `AX`), this module is ideally suited for modularized software architectures, as data and events are bundled in structured channels.
* **Edge and Event Triggering:** Any change at one of the inputs (`IN0`, `IN1`, or `G`) immediately triggers a recalculation, ensuring that the output `OUT` always delivers consistent and up-to-date data.
* **Edge and Event Triggering:** Any change at one of the inputs (`IN0`, `IN1`, or `G`) immediately triggers a recalculation, ensuring that the output `OUT` always provides consistent and current data.
* * **Security through Data Flip-Flops:** The use of `E_D_FF` blocks in the internal network prevents data race conditions by buffering data values synchronously with their associated events.

---

## State Overview

| State Selector (`G.D1`) | Updated Input | Output Behavior (`OUT`) |
| :---: | :---: | :--- |
| `FALSE` | `IN0` / `EI0` | `OUT.D1` inherits the value of `IN0`. Event `OUT.E1` is triggered. |
| `FALSE` | `IN1` / `IN1.E1` | No direct change to the output (value `IN1` is inactive). |
| `TRUE` | `IN1` / `IN1.E1` | `OUT.D1` inherits the value of `IN1.D1`. Event `OUT.E1` is triggered. |
| `TRUE` | `IN0` / `EI0` | No direct change to the output (value `IN0` is inactive). |
| Any | Switching from `G.D1` | The output immediately switches to the now active input and triggers `OUT.E1`. |

---

## Application Scenarios

* **Switching Operating Modes:** Dynamic switching between a locally defined standard operating mode (via `IN0` as a byte constant) and a remotely received operating mode (via adapter `IN1`).

**Dual switching between a locally defined standard operating mode (via `IN0` as a byte constant) and a remotely received operating mode (via adapter `IN1`). * **Signal Routing in Fieldbus Systems:** Routing of status or diagnostic bytes in distributed control systems depending on system states (controlled via `G`).

* **Redundant Sensors:** Selection between two redundant byte-coded sensor values based on a higher-level fault detection flag.

---

## Comparison with Similar Function Blocks

Compared to the standard selection function block `F_SEL` from the IEC 61131-3 library, `BYTE_AB_AX_SEL_AB` offers the following advantages:

* No manual wiring of event and data lines is required for the selector and the second input, as these run via standardized adapter interfaces.
* Integrated buffering of data streams, which increases robustness in distributed IEC 61499 applications.

---

## Conclusion

The `BYTE_AB_AX_SEL_AB` is a specialized and highly encapsulated module for byte-based signal switching. Through the consistent use of adapters, it integrates seamlessly into modern, event-driven control architectures and minimizes the implementation and testing effort for complex routing tasks in the 4diac IDE.