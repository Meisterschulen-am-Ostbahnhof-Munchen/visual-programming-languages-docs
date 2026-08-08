# AUI_UINT_AX_SEL_AUI

![AUI_UINT_AX_SEL_AUI](AUI_UINT_AX_SEL_AUI.png)

![AUI_UINT_AX_SEL_AUI](./AUI_UINT_AX_SEL_AUI.svg)

* * * * * * * * * *
## Introduction
The function block `AUI_UINT_AX_SEL_AUI` is used for binary selection (multiplexing) between two input sources and forwards the selected signal to an output. The special feature of this block is the combination of classic IEC 61499 interfaces (discrete data inputs and events) and modern, adapter-based connection interfaces.

The block allows for flexible switching between an adapter-based signal (`IN0`) and a value directly applied to the block (`UINT`) (`IN1`). Selection is controlled via a separate adapter input (`G`).

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acquisition and processing of the discrete data input `IN1`.

### **Event Outputs**
*(No direct event outputs are available at the component level. Event output is implemented via the output adapter `OUT`.)*

### **Data Inputs**

* **IN1** (UINT): Selectable, discrete input variable (data type `UINT`).


### ### **Data Outputs**

*(No direct data outputs are available at the component level. Data output is implemented via the output adapter `OUT`.)*

### **Adapters**

* **IN0** (Socket, Type: `adapter::types::unidirectional::AUI`): Selectable adapter input (Channel 0). Expects a unidirectional `AUI` adapter signal.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): Selector input. The received signal (Boolean on `G.D1` with event `G.E1`) determines which input is routed to the output.

* **OUT** (Plug / Connector, Type: `adapter::types::unidirectional::AUI`): The selected output as a unidirectional `AUI` adapter signal.

---

## Functionality
The component operates internally with a combination of flip-flops for state storage (`E_D_FF` and `E_D_FF_ANY`), data copiers (`F_MOVE`), and the standard selection component `F_SEL` according to IEC 61131-3.


1. **Signal Buffering**:

* The input data from the adapter `IN0` (`IN0.D1`) and the discrete input `IN1`, as well as the selector signal `G.D1`, are buffered in internal registers when their respective events (`IN0.E1`, `EI1`, `G.E1`) occur.

2. **Selection Logic (`F_SEL`)**:

* When the selector signal `G` is in the state `FALSE` (0), the value of `IN0` is selected.

* If the selector signal `G` has the state `TRUE` (1), the value of `IN1` is selected.

3. **Output**:

* After selection, the corresponding value is passed to the output plug `OUT`. Simultaneously, the output event `OUT.E1` is triggered to inform subsequent program sections about the data update.

---

## Technical Features
* **Hybrid Interface**: This module bridges the gap between classic wiring (discrete `UINT` input) and modern adapter wiring.

* **Event-driven caching**: The internal `E_D_FF` blocks ensure that even asynchronously arriving data and events are reliably synchronized and processed without errors.

* **Unidirectional adapters**: The use of the `AUI` and `AX` types ensures resource-efficient, unidirectional data flow (transmit only).

---

## State overview

| Selector value (`G.D1`) | Active channel | Output value (`OUT.D1`) | Output event trigger (`OUT.E1`) |

| :--- | :--- | :--- | :--- |

**FALSE** | Channel 0 (`IN0`) | Value of `IN0.D1` | On change of `IN0.D1`, `IN0.E1`, or on edge transition at `G` |

| **TRUE** | Channel 1 (`IN1`) | Value of `IN1` | On change of `IN1`, `EI1`, or on edge transition at `G` |


---

## Application Scenarios
* **Setpoint Switching (Auto/Manual)**:

An automatic setpoint is continuously read via a bus system and provided via the adapter `IN0`. A manual emergency or fixed value can be specified directly on the function block via `IN1`. A key switch or software flag on the selector `G` switches between the two values based on an event.

* **Modular Machine Architectures**:

Reduced wiring effort in complex 4diac applications by encapsulating signal groups in adapters, while simultaneously allowing for flexible adjustment of local parameters.

--

## Comparison with Similar Function Blocks
* **Standard `F_SEL` (IEC 61131-3)**: The standard selector operates purely data-oriented and does not support adapters or event synchronization. `AUI_UINT_AX_SEL_AUI` extends this functionality with the event-based execution system of IEC 61499.

* **Standard Copy Blocks**: Unlike simple routers or demultiplexers, this block combines different interface types (adapters and discrete variables) into a single logical component.

---

## Conclusion
The `AUI_UINT_AX_SEL_AUI` block is a powerful and flexible solution for switching and selection logic in event-driven systems. Through the seamless integration of adapters and discrete data lines, it significantly contributes to the clarity and modularity of 4diac application networks.