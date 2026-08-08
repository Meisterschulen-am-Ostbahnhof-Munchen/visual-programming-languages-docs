# OFF_USINT_AX_SEL_OFF

![AUS_USINT_AX_SEL_AUS](./AUS_USINT_AX_SEL_AUS.svg)

*(No image available)*

* * * * * * * * * *

## Introduction
The function block `AUS_USINT_AX_SEL_AUS` is used for binary selection between two input signals of the data type `USINT` (Unsigned Short Integer). The selection is event-driven via a selection signal. The block uses unidirectional adapters to process data and events in a modular and structured manner.

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the acceptance and processing of the directly connected data input `IN1`.


### **Event Outputs**
* *No direct event outputs.* (Event output is coupled via the output adapter `OUT`).

### **Data Inputs**
* **IN1** (USINT): Directly available, selectable input variable.

### **Data Outputs**
* *No direct data outputs.* (Data output is coupled via the output adapter `OUT`).

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::AUS`): The selected output value (`USINT`) and the corresponding confirmation event.

### **Adapters**
* **OUT** (Plug, Type: `adapter::types::unidirectional::AUS`): The selected output value (`USINT`) and the corresponding confirmation event.

### * **IN0** (Socket, Type: `adapter::types::unidirectional::AUS`): The first selectable input value (`USINT`), which is fed in via an adapter.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selection signal (gate) that determines which input is connected to the output.

---

## Functionality
The function block operates internally with a combination of D flip-flops (`E_D_FF_ANY` or `E_D_FF`) and standard selection blocks (`F_SEL`). The internal processing proceeds as follows:

1. **Value Buffering**:

* If an event occurs at adapter `IN0` (`IN0.E1`), the value `IN0.D1` is buffered in flip-flop `E_D_FF_ANY_IN0` and passed to the selector.

* If the event `EI1` occurs, the immediately pending value `IN1` is buffered in flip-flop `E_D_FF_ANY_IN1`.


* * When an event occurs at the selector adapter `G` (`G.E1`), the selection signal `G.D1` is buffered in the flip-flop `E_D_FF`.

2. **Selection Logic (`F_SEL`)**:

* If the selection signal at the adapter `G` is **FALSE** (0), the value of `IN0` is selected.

* If the selection signal at the adapter `G` is **TRUE** (1), the value of `IN1` is selected.


3. **Output**:

* The selected value is passed to the output adapter `OUT`.

* Simultaneously, an output event is generated at the adapter `OUT` (`OUT.E1`) to inform subsequent function blocks about the data change.

---

## Technical Features
* **Mixed Interface Operation**: The function block combines classic IEC 61499 event/data interfaces (`EI1` / `IN1`) with modern, unidirectional adapters (`IN0`, `G`, `OUT`).
...* * **Data Security through Event Coupling**: The use of internal D flip-flops ensures that data values are only transferred and processed when a corresponding event triggers them. This prevents data inconsistencies (race conditions).

---

## State Overview

| Selector State (`G.D1`) | Selected Output (`OUT.D1`) | Triggering Event |

| :--- | :--- | :--- |

| **FALSE** | Value of `IN0.D1` | `IN0.E1` or `G.E1` |

| **TRUE** | Value of `IN1` | `EI1` or `G.E1` |

---

## Application Scenarios

* **Switching between automatic and manual values**: Selection of a setpoint (e.g., a speed or step index as `USINT`) between an automatic process value (`IN0` via adapter) and a manually specified value (`IN1`).

* **Signal multiplexing**: Flexible forwarding of status or control codes in decentralized control systems.


---

## Comparison with Similar Function Blocks

Compared to the standard function block `F_SEL` from the IEC 61131-3 library, this block offers complete encapsulation for IEC 61499. While the standard `F_SEL` operates purely in a data flow-oriented manner, `AUS_USINT_AX_SEL_AUS` integrates event-driven state storage and utilizes adapters, which significantly simplifies and improves the clarity of wiring in the 4diac IDE Application Editor.

--

## Conclusion
The `AUS_USINT_AX_SEL_AUS` is a robust auxiliary function block for structured signal and data flow control. Its use of unidirectional adapters makes it ideally suited for modular and clean software architectures in industrial automation.