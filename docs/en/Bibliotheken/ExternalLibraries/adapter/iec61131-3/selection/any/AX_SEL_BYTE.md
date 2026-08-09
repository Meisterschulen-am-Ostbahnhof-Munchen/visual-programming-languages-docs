# AX_SEL_BYTE

![AX_SEL_BYTE](./AX_SEL_BYTE.svg)

* * * * * * * * * *

The function block `AX_SEL_BYTE` is a standardized selection block used for binary selection between two input values of data type `BYTE` (`IN0` and `IN1`). Selection is controlled via a specialized adapter channel (`G`). This block is particularly suitable for event-driven applications where data streams or state bytes need to be switched flexibly depending on an external selection signal.

* **EI0**: Updates and adopts the value at data input `IN0`.
* **EI1**: Updates and adopts the value at data input `IN1`.
* **CNF**: Confirmation event. Signals to the downstream system that a newly selected value is available at output `OUT`.
* **IN0** (`BYTE`): First selectable input value (selected when the selection signal is logically `0` or inactive).
* **IN1** (`BYTE`): Second selectable input value (selected when the selection signal is logically active).
* **OUT** (`BYTE`): The currently selected byte value.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): A unidirectional adapter that functions as a selector. It provides both the event (`E1`) to trigger the selection and the actual Boolean selection data value (`D1`).

## Functionality

The module behaves like an event-driven 2-to-1 multiplexer for byte data:

1. **Input Processing**: As soon as one of the events `EI0` or `EI1` arrives, the corresponding data value (`IN0` or `IN1`) is buffered internally.
2. **Adapter Switching**: If an event `E1` arrives via the adapter `G`, the selection value `D1` is evaluated.
- If the selection value `FALSE` (0), the value of `IN0` is passed to the selector.
- If the selection value `TRUE` (1), the value of `IN1` is passed.
3. **Event Filtering at the Output**: The function block only outputs a confirmation event (`CNF`) if the actually selected value at output `OUT` has changed. This prevents unnecessary subsequent calculations in the system when input data changes without relevance to the output.
* **Event-Based Optimization**: By using internal edge detection (`E_D_FF_ANY`), a `CNF` event is only generated when there is a genuine change in the output value.
* **Adapter Coupling**: Using the `AX` adapter instead of a simple Boolean input allows for clean encapsulation of the control logic and simplifies wiring in complex 4diac networks.
* ## State Overview

Since `AX_SEL_BYTE` is a composite function block (FB), its behavior is defined by the internal interaction of its components:

* **Waiting State**: The block waits for events at `EI0`, `EI1`, or the adapter `G`.
* **Input Update State**: A value at `IN0` or `IN1` changes. The value is stored internally but only results in an output when it is actively selected and the output value changes as a result.
* **Switching State**: The adapter signals a change at `G`. The function block switches the path, updates `OUT`, and triggers `CNF` if the value of `OUT` changes.
* **Operating Mode Switching**: Selection between two different status or command bytes for a machine based on the current automatic/manual operating state.
* **Signal Fallback**: Automatic switching from a primary data byte to a default replacement value if a system error is detected and signaled via the adapter.
* **Parameterization**: Switching between two parameter sets (e.g., predefined byte configurations) during operation.
* **Standard `F_SEL`**: The classic IEC 61131-3 `F_SEL` function block operates purely on a data flow basis and has no event control or adapter interfaces. `AX_SEL_BYTE` extends this basic functionality with event-driven evaluation and event-based output filtering.
* **Other `AX_SEL_x` Function Blocks**: Analogous function blocks exist for other data types (e.g., for `REAL`, `INT`, or `WORD`). They share the exact same functionality but differ in the data type processed for the inputs and outputs.
* ## Conclusion

`AX_SEL_BYTE` is an efficient utility module for structured, event-driven programming in 4diac. It combines the classic selection logic of IEC 61131-3 with the modern, resource-saving paradigms of IEC 61499.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion