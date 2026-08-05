# AX_FB_F_TRIG
![AX_FB_F_TRIG_ecc](./AX_FB_F_TRIG_ecc.svg)
*Insert placeholder for the function block image here, if available*

* * * * * * * * * *
## Introduction
The **AX_FB_F_TRIG** function block (Falling Edge Trigger with AX Adapter) is used to detect a falling edge (signal change from TRUE to FALSE) within an adapter-based architecture. It implements the logic of a standard IEC 61131-3 function block (`F_TRIG`), but uses **AX Adapters** to encapsulate data and event signals, thus reducing wiring complexity in IEC 61499 applications.

## Interface Structure

The function block does not use traditional separate event and data pins, but instead utilizes adapter interfaces.

### **Event Inputs**
* *No direct event inputs (encapsulated in adapter `CLK`).*

### **Event Outputs**
* *No direct event outputs (encapsulated in adapter `Q`).*

### **Data Inputs**
* *No direct data inputs (encapsulated in adapter `CLK`).*

### **Data Outputs**
* *No direct data outputs (encapsulated in adapter `Q`).*

### **Adapter**

| Name | Type | Comment | Description |
| :--- | :--- | :--- | :--- |
| **CLK** | `adapter::types::unidirectional::AX` | Clock | **Socket (Input):** The input adapter that provides the signal to be monitored. Typically contains an event (`E1`) and a Boolean data value (`D1`). |
| **Q** | `adapter::types::unidirectional::AX` | Output | **Plug (Output):** The output adapter that sends the result of the edge detection. |

## Functionality

The function block monitors the logical state of the data input in adapter `CLK` (field `D1`). For each event at input `CLK` (`E1`), the following algorithm is executed:

1. The function block checks whether a transition from **TRUE** (High) to **FALSE** (Low) has occurred. 2. An internal memory (`MEM`) is used to store the inverted state of the last cycle.

3. The logic is: `Q.D1 := NOT CLK.D1 AND NOT MEM`.

4. The memory is updated: `MEM := NOT CLK.D1`.

**Behavior:**

* When the input signal changes from 1 to 0, the output `Q.D1` is set to TRUE for exactly one cycle.
* In all other cases (0->0, 0->1, 1->1), the output remains FALSE.
* The result is signaled via the event `Q.E1`.

## Technical Features
* **Adapter Technology:** By using the `AX` adapter (generic data type, interpreted here as Boolean), event flow and data flow are bundled. This results in clearer function block diagrams.
* **Internal Storage:** The function block has an internal variable `MEM` (initial value TRUE) to reference the previous state of the input signal.
* **Minimalist ECC:** The state machine (ECC) consists of only a single state, which ensures very fast and direct algorithm execution.

## State Overview

The function block's Execution Control Chart (ECC) is very simple:

* **REQ (State):** This is the only state.
* **Transition:** It is triggered by the event `CLK.E1` (from the input adapter).
* **Action:** Executes the algorithm `REQ` and then triggers the output event `Q.E1`.

## Application Scenarios

The **AX_FB_F_TRIG** is suitable for various control tasks where "switching off" or "releasing" needs to be detected:

* **Button Evaluation:** Detects when a button is released (falling edge).
* **Sensors:** Triggers an action when a workpiece leaves a sensor area (light barrier becomes clear).
* **Alarm Reset:** Detects when an error signal is no longer present.
* **Structured Programming:** Used in complex applications that rely heavily on adapters to avoid "spaghetti code" (many individual connection lines).

## ⚖️ Comparison with similar function blocks

| Function Block | Difference |
| :--- | :--- |
| **F_TRIG** (Standard) | Uses separate `CLK` (BOOL) and `Q` (BOOL) pins, as well as separate `REQ`/`CNF` events. Functionally identical, but with a different interface. |
| **AX_FB_R_TRIG** | The counterpart to this function block. It detects the **rising edge (0 to 1). |
| **E_F_TRIG** | Event-based trigger in IEC 61499, often operates purely at the event level without encapsulated data adapters. |

## Conclusion

The **AX_FB_F_TRIG** is an essential component for developers who rely on adapter-based designs within the 4diac IDE and IEC 61499. It offers the reliable functionality of classic edge detection, packaged in a modern, bandwidth-efficient interface.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
