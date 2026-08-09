# ATM_AX_SEL_ATM

![ATM_AX_SEL_ATM](./ATM_AX_SEL_ATM.svg)

* * * * * * * * * *

## Introduction

The function block `ATM_AX_SEL_ATM` serves as a binary selector (multiplexer) for adapter interfaces according to the IEC 61499 standard. Based on the state of a selection adapter (`G` of type `AX`), it allows dynamic selection between two input adapters (`IN0` and `IN1` of type `ATM`) and forwards the selected signal to the output adapter (`OUT` of type `ATM`). The function block operates purely event-driven and is internally designed for processing time-based signals (`TIME`).

## Interface Structure

The function block does not have any directly accessible standard event or data pins. All communication is elegantly encapsulated via sockets (input adapters) and plugs (output adapters).

### **Event Inputs**

*No direct event inputs are available on the function block body. Event control is implicit via the adapter sockets.*

### **Event Outputs**

*No direct event outputs are available on the function block body. Event signaling is implicit via the adapter plug.*

### **Data Inputs**

*No direct data inputs are available on the FB body.*

### **Data Outputs**

*No direct data outputs are available on the FB body.*

### **Adapters**

#### **Sockets (Input Interfaces)**

* **IN0** (Type: `adapter::types::unidirectional::ATM`):

The first selectable input adapter (corresponds to the selection in logical `FALSE`).

* **IN1** (Type: `adapter::types::unidirectional::ATM`):

The second selectable input adapter (corresponds to the selection in logical `TRUE`).

* **G** (Type: `adapter::types::unidirectional::AX`):

The selector adapter. The signal applied here determines which of the two inputs is routed to the output.

#### **Plugs (Output Interfaces)**

* **OUT** (Type: `adapter::types::unidirectional::ATM`):

The output adapter that carries the data and events of the currently selected input (`IN0` or `IN1`).

---

## Functionality

The internal structure of the `ATM_AX_SEL_ATM` consists of a network of standardized auxiliary components that ensure reliable and consistent signal transmission:

1. **Event Acquisition and Buffering**:

As soon as an event (`E1`) arrives at one of the sockets (`IN0`, `IN1`, or `G`), it is captured via edge-triggered flip-flops (`E_D_FF_ANY` or `E_D_FF`). The data values (`D1`) are stabilized and passed to internal buffers.

As soon as an event (`E1`) arrives at one of the sockets (`E_D_FF_ANY` or `E_D_FF`), it is captured via edge-triggered flip-flops. 2. **Data Conversion**:

The data from inputs `IN0` and `IN1` are buffered via two `F_MOVE` function blocks (configured to the data type `TIME`) and made available for the selection logic.

3. **Selection**:

The function block `F_SEL` (a standard selection block according to IEC 61131-3) evaluates the state of selector `G`:

* If the signal from `G` is equal to `FALSE`, the value from `IN0` is selected.
* If the signal from `G` is equal to `TRUE`, the value from `IN1` is selected.
4. **Output**:

The selected value is passed via another `F_MOVE` module to the output adapter `OUT`, whereupon the output event (`OUT.E1`) is triggered simultaneously.

---

## Technical Features

* **Adapter Encapsulation**: By using adapters instead of individual pins, the number of connection lines in the overall control diagram is drastically reduced, which improves the readability of the entire system.
* **Data Type Focus**: The function block is internally optimized for the data type `F_MOVE` (time values) through the parameterization of the `F_MOVE` function blocks.
* **Event Integrity**: The use of event flip-flops ensures that no signal changes are lost and the output is only updated when relevant input data or the selector actually changes.

---

## State Overview

Since this is a composite function block network (FB), the function block does not have its own classic ECC (Event Execution Control) state machine. Its behavior is purely data flow and event-driven:

| State Selector `G.D1` | Triggering Event | State Output `OUT.D1` | Output Event |
| :--- | :--- | :--- | :--- |
| `FALSE` | Change to `IN0.E1` or `G.E1` | Value of `IN0.D1` | `OUT.E1` |
| `TRUE` | Change to `IN1.E1` or `G.E1` | Value of `IN1.D1` | `OUT.E1` |

---

## Application Scenarios

* **Process Time Switching**: In industrial or agricultural processes where switching between two different cycle, rinsing, or delay times (e.g., summer/winter operation or recipe A/recipe B) is required.
* **Setpoint Switching**: Dynamic selection of a time-based setpoint from two different sources based on a higher-level operating mode.

--

## Comparison with Similar Function Blocks

* **Standard `F_SEL`**: The classic `F_SEL` function block operates directly on elementary data types and does not have integrated event control for adapters. `ATM_AX_SEL_ATM` moves this logic to the structured adapter level.
* * **Standard Multiplexer**: Unlike general-purpose multiplexers, which often feature complex bus structures, this component is highly specialized, extremely lightweight, and perfectly matched to the combination of `ATM` and `AX` adapters.

---

## Conclusion

The `ATM_AX_SEL_ATM` is a robust and reusable auxiliary component for modern control architectures according to IEC 61499. It elegantly solves the task of binary signal switching for time-based data streams, leveraging the advantages of adapter technology.