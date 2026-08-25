# AX_ASR_SWITCH_X

* * * * * * * * * *
## Introduction

The function block **AX_ASR_SWITCH_X** is a composite function block responsible for converting between two different adapter types. It converts signals from an **AX** adapter (Boolean Event) into signals from an **ASR** adapter (Asynchronous Set/Reset).
The special feature of this function block is the **"Crossed Mapping"** indicated by the suffix "X" and the comment. Unlike a standard mapping, this function block inverts the logic: A `TRUE` signal at the input results in a `RESET` event at the output, while a `FALSE` signal triggers a `SET` event.
## Interface Structure

The function block interacts primarily via adapter interfaces.

### **Event Inputs**

*This function block does not have direct event inputs in the interface list, as these are encapsulated within the adapter `G`.*

### **Event Outputs**

*This function block does not have direct event outputs in the interface list, as these are encapsulated within the adapter `Q`.*

### **Data Inputs**

*This function block does not have direct data inputs in the interface list, as these are encapsulated within the adapter `G`.*

### **Data Outputs**

*This function block does not have direct data outputs.*

### **Adapter**

| Name | Type | Component | Comment |
| :--- | :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Socket (Input) | Boolean input adapter (contains event `E1` and data `D1`). |
| **Q** | `adapter::types::unidirectional::ASR` | Plug (Output) | Set/Reset output adapter (contains events `SET` and `RESET`). |

## Functionality

The **AX_ASR_SWITCH_X** internally uses a standard `E_SWITCH` block (`iec61499::events::E_SWITCH`) to execute the logic. The circuit is configured as follows:

1. An event at input adapter **G** (event `E1`) triggers processing.
2. The data value from input adapter **G** (data `D1`) is evaluated.
3. **Logic Inversion (Crossed Mapping):**
* If **G.D1 = TRUE**: The internal switch forwards the event to its output `EO1`. This output is connected to **Q.RESET**.
* If **G.D1 = FALSE**: The internal switch forwards the event to its output `EO0`. This output is connected to **Q.SET**.
* In summary:
* Input `TRUE` $\rightarrow$ Output `RESET`
* Input `FALSE` $\rightarrow$ Output `SET`

## Technical Features

* **Adapter Conversion:** Bridge between the simple Boolean event world (AX) and the set/reset control logic (ASR).
* **Inverted Logic:** This block is specifically designed for applications where an active signal (`TRUE`) should trigger a reset or deactivation (`RESET`), and an inactive signal (`FALSE`) should trigger an activation (`SET`) – or vice versa, depending on the interpretation of the connected systems.

## State Overview

Since this is a Composite Function Block without its own state machine (ECC), its behavior is defined solely by signal passthrough.

| Input G (D1) on Event G (E1) | Triggered Event at Q | Logical Meaning |
| :--- | :--- | :--- |
| **TRUE** | **RESET** | Reset / Stop |
| **FALSE** | **SET** | Set / Start |

## Application Scenarios

* **Fail-Safe Logic:** In systems where an active signal (High/True) represents the "normal state" or "idle state" (Reset), and the absence of the signal (Low/False) should trigger an action (Set) (wire break safety).
* **Logic Inversion:** Adapting sensors that output "Active High" to actuators or control modules that expect "Active Low" (or reset on high).
* **Specific Protocol Adaptation:** When a subsystem communicates via an AX adapter, but the receiving subsystem requires an ASR adapter with inverted polarity.

## ⚖️ Comparison with Similar Modules

* **AX_ASR_SWITCH (hypothetical/standard):** A standard converter would typically map `TRUE` to `SET` and `FALSE` to `RESET`. The `_X` module described here is the exact opposite.
* **AX_ASR_SWITCH (hypothetical/standard):** * **E_SWITCH:** The underlying IEC 61499 standard function block, which handles the actual switching of events based on a Boolean value, but without the encapsulation in an adapter.

## Conclusion

The **AX_ASR_SWITCH_X** is a specialized adapter converter that performs a logical inversion ("crossed mapping") between an AX input and an ASR output. It is essential for system integrations where the signal polarity between source and sink needs to be reversed without placing additional discrete logic devices in the main network.
