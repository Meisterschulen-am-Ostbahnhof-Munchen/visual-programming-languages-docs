# AUI_AX_SEL_AUI

![AUI_AX_SEL_AUI](./AUI_AX_SEL_AUI.svg)

*No image available*

* * * * * * * * * *
## Introduction
The function block `AUI_AX_SEL_AUI` is a composite function block for 4diac-ide. It performs binary selection between two analog or numeric input signals provided via adapters. Based on the state of a selection adapter, the block switches one of the two input signals to the output.

## Interface Structure

The function block does not have any traditional, direct event or data channels on its main interface. All communication is handled via adapters.


### **Event Inputs**
*No direct event inputs available.*

### **Event Outputs**
*No direct event outputs available.*

### **Data Inputs**
*No direct data inputs available.*

### **Data Outputs**
*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN0** (Type: `adapter::types::unidirectional::AUI`): Unidirectional adapter for the first selectable input signal. This signal is passed to the output if the selector `G` has the value `FALSE`.

* **IN1** (Type: `adapter::types::unidirectional::AUI`): Unidirectional adapter for the second selectable input signal. This signal is passed to the output when the selector `G` has the value `TRUE`.

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional selector adapter. Determines which of the two input signals is passed through.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AUI`): Unidirectional adapter for the selected output signal.


---

## Functionality

Inside the module is a defined network of standard function blocks that processes the adapter signals:

1. **Buffering & Synchronization:**

Events (`E1`) and data (`D1`) arriving via the adapters `IN0`, `IN1`, and `G` are buffered and synchronized using event-data flip-flops (`E_D_FF` and `E_D_FF_ANY`).

2. **Data Conversion:**

The buffered numeric values of the inputs are forwarded to the actual selection block via internal `F_MOVE` blocks (configured to the data type `UINT`).

3. **Selection:**

The standard selection block `F_SEL` (according to IEC 61131-3) performs the actual selection:

* If the value at selector `G` equals `FALSE`, the signal from `IN0` is selected.

* If the value at selector `G` equals `TRUE`, the signal from `IN1` is selected.

4. **Output:**

The selection result is transferred to the output plug `OUT` via a further buffer containing `F_MOVE` and `E_D_FF_ANY`. Simultaneously, the output event at the plug is triggered to inform subsequent function blocks of the new value.

---

## Technical Features
* **Pure Adapter Interface:** This function block is specifically designed for use in modern, adapter-based architectures. This results in a very clean and clear application diagram, as loose data and event lines are bundled within adapters.


** * **Event-driven:** Any change (sending an event) to the inputs `IN0`, `IN1`, or the selector `G` triggers an immediate recalculation and results in an update of the output `OUT`.

* **Typing:** The internal conversion and forwarding blocks primarily work with the data type `UINT`.

---

## State Overview

Since this is a composite function block, it does not have its own state machine (ECC). Its behavior is purely data- and event-driven:

| State Selector `G` (value of D1) | Output `OUT` (value of D1) | Triggering of `OUT.E1` |

|:---|:---|:---|

| `FALSE` (0) | Corresponds to the value of `IN0` | Yes, on change/event to `IN0` or `G` |

| `TRUE` (1) | Corresponds to the value of `IN1` | Yes, on change/event to `IN1` or `G` |


---

## Application Scenarios

* **Setpoint Switching:** Switching between a manually setpoint (e.g., via an HMI at `IN0`) and an automatic setpoint (e.g., from a calculation logic at `IN1`).

* **Sensor Redundancy:** Switching between two analog sensors (e.g., primary sensor at `IN1` and backup sensor at `IN0`) in case of a fault via a control signal at `G`.

* **Operating Mode Selection:** Selection of different analog control parameters depending on the current machine state.


* ---

## Comparison with Similar Components

The classic standard component `F_SEL` requires direct data lines (e.g., `ANY_ELEMENTARY`) and manual event wiring for calculation triggering (`REQ`/`CNF`).

The component `AUI_AX_SEL_AUI` encapsulates this complete logic, including event synchronization and buffering. It is therefore ideally suited for modularized software architectures where signal groups are already available as adapters by default.

--

## Conclusion
`AUI_AX_SEL_AUI` significantly simplifies signal routing in 4diac applications. It combines the proven selection logic of IEC 61131-3 with the structural advantages of event-driven adapters in IEC 61499.