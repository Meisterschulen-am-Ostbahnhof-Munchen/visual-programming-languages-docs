# AUI_UDINT_AX_SEL_AUI

![AUI_UDINT_AX_SEL_AUI](./AUI_UDINT_AX_SEL_AUI.svg)

* * * * * * * * * *

## Introduction

The function block `AUI_UDINT_AX_SEL_AUI` implements a binary selection between two input values, controlled by an adapter of type *AX*. The selected value is output via an *AUI* adapter. The block is classified as a standard selection function according to IEC 61131-3 and is suitable for use in automation applications requiring flexible, event-driven signal switching.

## Interface Structure

### **Event Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `EI0` | Event | Sets/receives the value of `IN0` (linked to `IN0`) |

| `EI1` | Event | Sets/receives the value of `IN1` (linked to `IN1`) |

### **Event Outputs**

The FB does not have a standalone event output. The output event is provided via the *AUI* adapter `OUT` (see Adapter).

### **Data Inputs**

| Name | Type | Description |

|------|-----|---------------|

| `IN0` | UINT | First selectable input value |

| `IN1` | ANY_ELEMENTARY | Second selectable input value (polymorphic, any elementary data type) |

### **Data Outputs**

No direct data outputs. The selected value is output via the *AUI* adapter `OUT`.

### **Adapters**

| Name | Type | Description |

|------|-----|---------------|

| `G` (Socket) | AX | Control adapter (selector); provides the selection signal `D1` and the trigger event `E1` |

| `OUT` (Plug) | AUI | Result Adapter; outputs the selected value via `D1` and a completion event via `E1` |

## Functionality

This function block encapsulates an IEC 61131-3 standard function block `F_SEL` (binary selection). Selection is event-driven:

1. The event inputs `EI0` and `EI1` are used to update and update the two input values, respectively. They are linked to the data `IN0` and `IN1`.

2. The control adapter `G` receives an external event (`G.E1`) and a Boolean/digital value (`G.D1`). This event triggers the internal `F_SEL` (via its `REQ` input).


The control adapter `G` receives an external event (`G.E1`) and a Boolean/digital value (`G.D1`). The event triggers the internal `F_SEL` (via its `REQ` input).


``` 3. The internal function block `F_SEL` selects the value of `IN0` (if `G = FALSE`) or `IN1` (if `G = TRUE`) based on the control signal (`F_SEL.G`) and places it at output `F_SEL.OUT`.

4. The confirmation event `F_SEL.CNF` is forwarded to output adapter `OUT.E1`, and the selected value is output via `OUT.D1`.

Thus, the function block functions as a unified, adapter-based interface for binary selection operations.


4. ## Technical Features

- **Adapters instead of individual signals:** Instead of individual event and data outputs, the FB uses adapters (`AUI` and `AX`). This enables modular encapsulation and simplifies integration into adapter-based architectures.

- **Polymorphism:** The second input (`IN1`) is declared as `ANY_ELEMENTARY`, so it accepts values of various elementary data types (e.g., INT, BOOL, REAL). The output adopts this type, provided it is compatible with the first input.

- **Event-driven processing:** Selection is only executed when an event arrives at `G.E1`, which supports concurrency and controlled data flow.

**Copyright Notice:** This function block is licensed under the Eclipse Public License 2.0 (EPL-2.0). Developed by TU Wien ACIN and HR Agrartechnik GmbH.

## State Overview

This function block does not have its own state machine, but delegates the selection to the internal `F_SEL` function block. Its behavior is purely event-driven:

- A selection is triggered on a rising edge of `G.E1`.

- The events `EI0` and `EI1` have no direct effect on the selection; they merely serve to transfer the input values (e.g., from an asynchronous process).



``` A detailed description of the internal `F_SEL` can be found in the IEC 61131-3 specification or the documentation of the standard function block.

## Application Scenarios

- **Signal Switching:** Selection between two measured values or control signals in an automation system, controlled by an enable or mode signal (e.g., manual/automatic).

- **Adapter-Based Architectures:** Use in systems based on the adapter pattern of the 4diac IDE (e.g., for connecting components with standardized interfaces).

- **Polymorphic Data Paths:** Processing different data types (e.g., optionally UINT or BOOL) within the same function block without requiring separate conversion.


## Comparison with Similar Function Blocks

Compared to the simple IEC 61131-3 function block `SEL` (which operates with a binary input and two data values), `AUI_UDINT_AX_SEL_AUI` extends the functionality with adapter interfaces and event-driven control. Standard SEL function blocks usually operate without explicit events and output the result immediately. This function block offers a tighter coupling between data and event flow, which is advantageous in event-oriented systems (e.g., distributed automation systems).

## Conclusion

The function block `AUI_UDINT_AX_SEL_AUI` provides flexible, adapter-based binary selection. It combines proven IEC 61131-3 logic with modern interface concepts (adapters, ANY_ELEMENTARY). Due to the clear separation of event and data paths, it is particularly well-suited for modular, event-driven automation solutions implemented on the 4diac IDE platform.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]