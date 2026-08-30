# AX_FB_R_TRIG

![AX_FB_R_TRIG_ecc](./AX_FB_R_TRIG_ecc.svg)

* * * * * * * * * *
## Introduction

The function block **AX_FB_R_TRIG** (Rising Trigger with AX Adapter) is used to detect the rising edge of a Boolean signal. Unlike the standard `R_TRIG` block according to IEC 61131-3, this block uses **AX adapters** for input and output. It encapsulates the edge detection logic in an adapter-based architecture, which simplifies integration into systems that use `adapter::types::unidirectional::AX`.
The goal is to generate a `TRUE` signal at the output when the input signal transitions from `FALSE` to `TRUE`.

## Interface Structure

### **Event Inputs**

*This block has no direct event inputs. Event control is handled via the adapter `CLK`.*

### **Event Outputs**

*This block has no direct event outputs. Event forwarding is handled via the adapter `Q`.*

### **Data Inputs**

*This block has no direct data inputs. Data is received via the adapter `CLK`.*

### **Data Outputs**

*This block has no direct data outputs. Data is output via the adapter `Q`.*

### **Adapters**

| Name | Type | Comment |
| :--- | :--- | :--- |
| **CLK** | `adapter::types::unidirectional::AX` | **Socket (Input):** The clock input being monitored. Contains the data signal (D1) and the associated event (E1). |
| **Q** | `adapter::types::unidirectional::AX` | **Plug (Output):** The pulse output. Provides `TRUE` only on a rising edge at input `CLK`. |

## Functionality

The component implements the classic logic of a "Rising Edge Detector":

1. The component waits for an event at the adapter input `CLK` (signal `CLK.E1`).
2. As soon as the event occurs, the algorithm `REQ` is executed.
3. The algorithm checks the current value of the data input (`CLK.D1`) and compares it to the stored state from the previous cycle (`MEM`).
- **Logic:** `Q.D1 := CLK.D1 AND NOT MEM`
4. If `CLK.D1` is true (`TRUE`) and the stored value `MEM` was false (`FALSE`), the output `Q.D1` is set to `TRUE`. In all other cases, `Q.D1` is `FALSE`.
5. The internal memory `MEM` is then updated with the current value of `CLK.D1`.
6. Finally, the event is triggered at the output adapter `Q` (`Q.E1`) to inform subsequent function blocks.

## Technical Features

- **Adapter Encapsulation:** The function block is specifically designed for the type `adapter::types::unidirectional::AX`. This adapter type typically bundles an event (`E1`) and a Boolean data point (`D1`). This reduces the visible wiring in the application diagram, as event and data flow are combined in a single connection line.
- **Internal Memory:** The block uses an internal Boolean variable `MEM` to store the state of the input signal between executions.

## State Overview

The block is based on a very simple Execution Control Chart (ECC) with only one state:

- **State `REQ`:** This is the only state.
- **Transition:** The block remains in this state and responds to the input adapter event `CLK.E1`.
- **Action:** On each event, the algorithm `REQ` is executed, and the output adapter event `Q.E1` is sent.

## Application Scenarios

- **Signal Conditioning:** Converting a continuous signal (e.g., switch is ON) into a single pulse to trigger an action exactly once when the device is switched on.
- **Wiring Simplification:** Used in systems that consistently rely on adapter technology to minimize the number of visible connections between functional blocks.
- **Start Trigger:** Detects when a process or machine is started (transition from 0 to 1).

## ⚖️ Comparison with Similar Components

- **`R_TRIG` (Standard):** The functional core is identical. The difference lies in the interface: `R_TRIG` uses separate `CLK` (BOOL) and `REQ` (Event) inputs, as well as `Q` (BOOL) and `CNF` (Event) outputs. `AX_FB_R_TRIG` uses adapters.
- **`AX_FB_F_TRIG`:** The counterpart to this function block, which reacts to falling edges (high-to-low).

## Conclusion

The **AX_FB_R_TRIG** is an essential utility function block for developers working with AX adapters within the 4diac environment. It offers the robust functionality of standard edge detection, packaged in a modern, adapter-based interface, resulting in cleaner and more modular control applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
