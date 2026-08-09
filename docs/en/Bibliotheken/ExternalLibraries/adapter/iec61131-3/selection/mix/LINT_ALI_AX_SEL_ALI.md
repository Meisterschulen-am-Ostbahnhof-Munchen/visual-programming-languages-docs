# LINT_ALI_AX_SEL_ALI

![LINT_ALI_AX_SEL_ALI](./LINT_ALI_AX_SEL_ALI.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `LINT_ALI_AX_SEL_ALI` performs binary selection between two input values of data type `LINT` (64-bit integer) and outputs the result to an adapter.

The unique feature of this block is its hybrid interface: It allows selection between a directly input data value (`IN0`) and a data value fed in via an adapter (`IN1`). The selection process is also controlled via an adapter (`G`).

## Interface Structure

### **Event Inputs**

| Event | Description | Associated Data |
| :--- | :--- | :--- |
| **EI0** | Sets the value of `IN0` and triggers the internal calculation. | `IN0` |

### **Event Outputs**

*No direct event outputs on the main interface. Event forwarding is done via the adapters (see section Adapters).*

### **Data Inputs**

| Variable | Data Type | Description |
| :--- | :--- | :--- |
| **IN0** | LINT | First selectable input value (selected when the selector `G` is in the state `FALSE`). |

### **Data Outputs**

*No direct data outputs on the main interface. Data output is via the adapter plug `OUT`.*

### **Adapters**

| Adapter Name | Type | Direction (Plug/Socket) | Description |
| :--- | :--- | :--- | :--- |
| **OUT** | `adapter::types::unidirectional::ALI` | Plug | The selected output value (type `LINT`), packaged in a unidirectional adapter interface. |
| **IN1** | `adapter::types::unidirectional::ALI` | Socket | Second selectable input value (type `LINT`), which is fed in via an adapter (selected when `G` is in the state `TRUE`). |
| **G** | `adapter::types::unidirectional::AX` | Socket | Selector input (Boolean) received via an adapter. |

---

## Functionality

The function block is internally based on the IEC 61131-3 standard selection algorithm (`F_SEL`). Control is edge- or event-triggered via D flip-flops (`E_D_FF` and `E_D_FF_ANY`) to guarantee consistent data transfer upon the occurrence of events.

1. **Event Processing**:
* An event at `EI0` updates the internal value for `IN0`.
* An event at adapter `IN1` (`IN1.E1`) updates the internal value for `IN1`.
* An event at selector adapter `G` (`G.E1`) updates the selection signal.
* 2. **Selection Logic**:
* If the value `FALSE` is present at selector adapter `G.D1`, the value of `IN0` is passed to output `OUT.D1`.
* If the value `TRUE` is present at selector adapter `IN1.D1`, the value of `OUT.D1` is passed to output `OUT.D1`.
3. **Output**:
* After each internal value change or selection update, the output event `OUT.E1` of the output adapter is triggered to inform subsequent program components about the data change.
* ---

## Technical Features

* **Data Security through Event Coupling**: By using `E_D_FF` (D flip-flop) function blocks, it is ensured that data values are only transferred when the corresponding event occurs. This prevents glitches or the processing of incomplete data packets.
* **Reduced Wiring Effort**: The use of adapters (`ALI` and `AX`) combines data and events into logical channels. This results in a clearer structure in the 4diac application network.

--

## State Overview

Since this is a composite/network function block (FB), there is no classic state machine (Execution Control Chart - ECC). However, the behavior can be described using the following function table:

| State Selector (`G.D1`) | Input `IN0` | Input `IN1.D1` | Output (`OUT.D1`) | Triggered Event |
| :---: | :---: | :---: | :---: |
**FALSE** | `Wert A` | `Wert B` | **Value A** | `OUT.E1` |
**TRUE** | `Wert A` | `Wert B` | **Value B** | `OUT.E1` |

---

## Application Scenarios

* **Setpoint Switching**: Switching between a locally stored default value (`IN0` as a static parameter in the function block) and an alternative value dynamically received via the network or an HMI (`IN1` via adapter).
* **Operating Mode Selection**: Selection of different time or counting parameters (represented as a 64-bit integer `LINT`) depending on the state of a higher-level controller (e.g., automatic vs. manual operation).

--

## Comparison with Similar Function Blocks

* **Classic `F_SEL`**: The standard selection function block does not support adapters and requires direct wiring of all data and event lines. `LINT_ALI_AX_SEL_ALI` encapsulates this logic and is specifically optimized for the data type `LINT`.
* **Other Type Selectors**: Analogous selectors exist for other data types (e.g., for `REAL` or `INT`). This block is designed exclusively for 64-bit integers (`LINT`).

---

## Conclusion

The `LINT_ALI_AX_SEL_ALI` is a specialized auxiliary block that simplifies the selection of 64-bit integer values in modern, adapter-based 4diac applications. Through the clean separation and encapsulation of signal paths, it significantly contributes to the clarity and maintainability of control software.