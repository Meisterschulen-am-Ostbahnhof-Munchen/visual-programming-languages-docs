# SINT_AS_AX_SEL_AS

![SINT_AS_AX_SEL_AS](./SINT_AS_AX_SEL_AS.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `SINT_AS_AX_SEL_AS` is a binary selector (multiplexer) for signed 8-bit integers (`SINT`). It is used to select between two input values (`IN0` and `IN1`) based on a selection signal (`G`) and to output the selected value (`OUT`). The block uses a combination of classic interfaces and modern adapter interfaces to enable modular and clear wiring within 4diac applications.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the acquisition and processing of the data input `IN0`.

### **Event Outputs**

* *No direct event outputs at the block level.* The event output is encapsulated via the output adapter `OUT`.

### **Data Inputs**

* **IN0** (`SINT`): The first selectable input value (standard SINT variable).

### **Data Outputs**

* *No direct data outputs at the block level.* The data output is encapsulated via the output adapter `OUT`.

### **Adapter**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AS`): The selected output channel through which the selected `SINT` value and its associated event are output.
* **IN1** (Socket, Type: `adapter::types::unidirectional::AS`): The second selectable input channel, implemented as an adapter.
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector input for choosing the active channel (adapter for the selection signal).

---

## Functionality

The module operates internally as an event-driven network that buffers input values and routes them through a standard selection gate:

1. **Input Buffering**:
* An event at `EI0` stores the value of `IN0` in an internal flip-flop (`E_D_FF_ANY_IN0`).
* An event at the adapter input `IN1` (`IN1.E1`) stores the value `IN1.D1` in the flip-flop `E_D_FF_ANY_IN1`.
* A change to the selector adapter `G` (`G.E1`) saves the state `G.D1` in the flip-flop `E_D_FF_G`.
2. **Selection Logic (`F_SEL`)**:

As soon as one of the inputs or the selection signal changes, the selection in the internal block `F_SEL` is triggered:

* If the selection signal (`G`) is **FALSE** (0), the value of **IN0** is passed through to the output.
* If the selection signal (`G`) is **TRUE** (1), the value of **IN1** is passed through to the output.
3. **Output**:

The selected value is transferred to the output adapter `OUT` via an internal `F_MOVE` element. Simultaneously, the output event `OUT.E1` is generated to inform subsequent function blocks about the value change.

---

## Technical Features

* **Hybrid Interfaces**: The function block combines classic IEC 61499 variables (`IN0`, `EI0`) with adapter interfaces (`IN1`, `G`, `OUT`). This enables flexible integration into existing systems.

--- * **Asynchronous Event Processing**: Any change to one of the inputs (be it `IN0`, `IN1`, or the selector `G`) immediately triggers a re-evaluation and, if necessary, an update of the output.

* **Data Type Specific**: Optimized for the data type `SINT` (Short Integer, 8-bit), ensuring efficient memory usage for smaller number ranges.

---

## State Overview

Since this is a composite function block (FB), its behavior is determined by the internal signal flow:

| Trigger Event | State Selector `G` | Selected Output (`OUT.D1`) | Generated Event |
| :--- | :--- | :--- | :--- |
| `EI0` | `FALSE` | Value of `IN0` | `OUT.E1` |
| `EI0` | `TRUE` | Value of `IN1.D1` (unchanged) | `OUT.E1` |
| `IN1.E1` | `FALSE` | Value of `IN0` (unchanged) | `OUT.E1` |
| `IN1.E1` | `TRUE` | Value of `IN1.D1` | `OUT.E1` |
| `G.E1` (change to `FALSE`) | `FALSE` | Value of `IN0` | `OUT.E1` |
| `G.E1` (change to `TRUE`) | `TRUE` | Value of `IN1.D1` | `OUT.E1` |

---

## Application Scenarios

* **Switching Between Operating Modes**: Optionally specify a manually set value (`IN0`) or an automatic value dynamically received via an adapter (`IN1`).
* **Signal Routing**: Dynamic forwarding of sensor or control data in modular plant structures.
* **Compact Programming**: Reduction of line crossings in the FB network through the use of adapters for signals and values.

---

## Comparison with Similar Function Blocks

Compared to the standard selection function block `F_SEL` from the IEC 61131-3 library, `SINT_AS_AX_SEL_AS` offers integrated event control. While a standard `F_SEL` operates purely in a data-flow-oriented manner and requires external triggers, this component independently manages event generation and value storage (latching) via internal D flip-flops. Furthermore, the use of adapters significantly reduces wiring effort in the graphical editor compared to traditional multiplexers.

---

## Conclusion

The `SINT_AS_AX_SEL_AS` is a specialized yet highly efficient component for signal control in the 8-bit range. By encapsulating the event logic and utilizing adapters, it significantly contributes to the clarity and maintainability of complex IEC 61499 control applications.