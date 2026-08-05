# AX_AUI_SEL_AUI
![AX_AUI_SEL_AUI](./AX_AUI_SEL_AUI.svg)

* * * * * * * * * *
## Introduction
The function block **AX_AUI_SEL_AUI** implements binary selection. It selects between two 16-bit input values (**IN0** and **IN1**) and outputs the selected value via a standardized output adapter. The selection is controlled by a Boolean signal provided via an input adapter. The block combines the functionality of the IEC 61131-3 block `F_SEL` with modular adapter interfaces and is particularly suitable for control applications with reusable, encapsulated connections.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment | With Data |
|------|-------|--------------------|----------------|
| EI0 | Event | Set IN0 | IN0 |
| EI1 | Event | Set IN1 | IN1 |

- **EI0**: Sending an event to `EI0` updates the value of **IN0** (the provided data value is adopted).
- **EI1**: Analogous to `EI0` for **IN1**.

**Note:** Events are used to update the input data **before** the actual selection. The selection itself is triggered exclusively by the event of the input adapter **G**.

### **Event Outputs**

No direct event outputs are available. The results are passed on via the output adapter **OUT** (see Adapters).

### **Data Inputs**

| Name | Type | Comment |
|------|------|-----------------------------------|
| IN0 | UINT | First selectable input value |
| IN1 | UINT | Second selectable input value |

Both data values are unsigned 16-bit integers (UINT).

### **Data Outputs**

No direct data outputs. The result is provided via the output adapter **OUT**.

### **Adapter**

| Label | Type | Direction | Comment |
|-------------|----------------------------------|----------|--------------------|
| G | `adapter::types::unidirectional::AX` | Socket | Selector signal |
| OUT | `adapter::types::unidirectional::AUI`| Plug | Selected value |

- **Adapter G (Socket):**

Provides an event **E1** and a date **D1**.

- `G.D1` (BOOL) – Selection signal: `TRUE` selects **IN1**, `FALSE` selects **IN0**.
- `G.E1` (Event) – Triggers the selection operation.
- **Adapter OUT (Plug):**

Returns an event **E1** and a date **D1**.

- `OUT.D1` (UINT) – The selected value (IN0 or IN1).
- `OUT.E1` (Event) – Signals that a new output value is available.

## Functionality

The component functions as an encapsulation of the standard component `F_SEL` from IEC 61131-3. The internal wiring connects:

- `G.E1` → `F_SEL.REQ` (Start of selection)
- `IN0` → `F_SEL.IN0`
- `IN1` → `F_SEL.IN1`
- `G.D1` → `F_SEL.G` (Control input)
- `F_SEL.OUT` → `OUT.D1`
- `F_SEL.CNF` → `OUT.E1`

**Procedure:**

1. The input values **IN0** and **IN1** are either statically defined or updated via the events `EI0` / `EI1`.

2. An event on adapter **G** (signal `G.E1`) starts the selection.

3. The internal `F_SEL` evaluates the Boolean signal `G.D1`:

- If `G.D1 = FALSE` is present: Output = **IN0**
- If `G.D1 = TRUE` is present: Output = **IN1**
4. The result is placed on `OUT.D1`, and simultaneously the event `OUT.E1` is triggered to inform downstream components.
...`` `` ``` `` `` `` The function block thus implements a time-controlled, event-driven assignment: Selection occurs only upon an external event, and the data must already be available.

## Technical Features
- **Composite Function Block:** The function block is built from an existing IEC 61131-3 function block (`F_SEL`) – this simplifies maintenance and certification.
- **Adapter-Based Interfaces:** The use of the adapters `AX` and `AUI` enables loose coupling and facilitates the exchange of submodules.
- **Data Type:** `UINT` (16-bit) – suitable for counters, configuration values, or analog scales.
- **License:** Eclipse Public License 2.0 – allows unrestricted industrial use.
- **No Internal States:** The function block is purely combinatorial with event-driven output; no states are stored.

## State Overview

The function block does not have an explicit state machine. Its functionality is entirely defined by the interaction of events:

1. **Waiting for Trigger Input** – No event is present at `G.E1`.

2. **Selection and Output** – Upon receipt of `G.E1`, the result is determined within a processing step and output via `OUT` (event `OUT.E1`).

An explicit state machine is not required because the internal `F_SEL` has no delays or memory.

## Application Scenarios
- **Switching Between Operating Modes:** A control signal (e.g., via a digital input) selects between two sets of parameters, such as speed limits or configuration values.
- **MUX Function in Data Paths:** In a measurement chain, it is possible to select between two sensor channels without duplicating the entire signal processing.
- **Fail-Safe Switchover:** If the primary value fails, a logical signal can be used to switch to a substitute value.
- **Connection to Adapter Networks:** Thanks to the standardized adapters `AX`/`AUI`, the module can be seamlessly integrated into existing modular control architectures.

## Comparison with Similar Modules

| Module | Description |
|---------------------|-------------------------------------------------------------------------------|
| **`F_SEL`** | Pure IEC 61131-3 function, no adapters – direct data/event connections. |
| **`AX_AUI_SEL_AUI`** | Same selection function, but encapsulated with adapters for modular networking. |
| **`MUX` blocks** | Often more than two inputs (e.g., 4-channel multiplexer) – only binary selection here. |

The AX_AUI_SEL_AUI offers, in comparison to a direct `F_SEL`The advantage of standardized, adapter-based input and output increases reusability and interchangeability in complex systems.

## Conclusion

The **AX_AUI_SEL_AUI** function block provides a robust, IEC 61131-3 compliant solution for the binary selection of 16-bit data. Its adapter-based interface facilitates integration into modular control architectures and makes it particularly suitable for industrial automation solutions where flexibility and standardization are required. The event-driven sequence enables precise timing control of the switching process.
