# AI_INT_AX_SEL_AI

![AI_INT_AX_SEL_AI](./AI_INT_AX_SEL_AI.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AI_INT_AX_SEL_AI` is used for binary selection between two analog integer input values (type `INT`). The block combines classic control interfaces (direct event and data inputs) with modern, adapter-based connection concepts. The selection of which of the two values is passed to the output is made via a binary selection signal at a dedicated adapter interface.

## Interface Structure

### **Event Inputs**

* **EI1**: Triggers the update and transfer of the directly applied data input value `IN1`.

### **Event Outputs**

* (No direct event outputs declared; event forwarding is encapsulated via the adapter output `OUT`)*

### **Data Inputs**

* **IN1** (`INT`): Directly applied, selectable integer input value (passed through to the output when the selection signal `G`/`TRUE` is active).

### **Data Outputs**

* (No direct data outputs declared; data output is encapsulated via the adapter output `OUT`)*

### **Adapters**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AI`): The selected output port (Analog Output). The selected data value and the corresponding update event are output via this adapter.
* **IN0** (Socket, Type: `adapter::types::unidirectional::AI`): The first selectable input channel (passed through to the output when the selection signal `G` is inactive/`FALSE`).
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector input (Analog Selector). Controls which of the two inputs (`IN0` or `IN1`) is connected to the output `OUT`.

---

## Functionality

The function block is implemented internally as a composite function block (FB network). The core logic is based on the standard selection element `F_SEL` according to IEC 61131-3.

1. **Data Acquisition and Synchronization**:

As soon as a new event arrives at one of the interfaces (`IN0`, `IN1` via `EI1`, or at the selector `G`), the corresponding data value is temporarily stored via edge-triggered memory elements (`E_D_FF` or `E_D_FF_ANY`) and transferred to the central selection block `F_SEL` using a data converter (`F_MOVE`).

2. **Selection Logic**:

The state of selector `G` controls the following:

* If the signal at adapter `G` equals `FALSE` (0), the value of `IN0` is passed to output `OUT`.
* If the signal at adapter `G` equals `TRUE` (1), the value of the direct input `IN1` is passed to output `OUT`.
3. **Output**:

The selected value is passed to the output plug `OUT`, followed by a synchronous output event (`OUT.E1`) to inform subsequent program components about the data update.

---

## Technical Features

* **Hybrid Design**: The component provides an elegant bridge between classic IEC 61499 connectors (`IN1`/`EI1`) and structured adapters (`IN0`, `G`, `OUT`). This facilitates integration into existing applications that use different signaling standards.
* **Event-driven Processing**: No cyclic processing takes place. The function block reacts exclusively to changes in values or events at its inputs, which conserves system resources and ensures deterministic response times.

---

## State Overview

Since this is a pure data flow and selection network (composite function block), the function block does not have its own Execution Control Chart (ECC). The function block's state is purely combinatorial and is directly determined by the state of its inputs and internal memory elements (flip-flops).

---

## Application Scenarios

* **Manual/Automatic Switching**: Acceptance of a sensor signal during normal operation (`IN0` via adapter) or switching a manually specified fixed value (`IN1`) via a control command to adapter `G`.
* **Sensor Redundancy / Signal Fallback**: Switching to a backup value (`IN1`) if the main sensor (`IN0`) reports an error (the error condition is evaluated externally and triggers `G`).

---

## Comparison with Similar Function Blocks

* **Standard `F_SEL`**: The standard selection block operates purely on a data basis without adapter support and without event-driven storage. `AI_INT_AX_SEL_AI` extends this functionality with direct integration into adapter-based communication structures and ensures the necessary event synchronization in IEC 61499 systems.

---

## Conclusion

The `AI_INT_AX_SEL_AI` is a robust and flexible auxiliary function block for signal preprocessing. It is ideally suited for modular control architectures where analog integer values need to be switched dynamically and event-driven based on logical conditions.