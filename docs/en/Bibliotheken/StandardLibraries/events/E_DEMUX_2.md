# E_DEMUX_2
<!-- Hier wäre Platz für ein Bild des Funktionsblocks, falls vorhanden. -->
* * * * * * * * * *
## Introduction
The `E_DEMUX_2` (Event Demultiplexer) is a function block according to IEC 61499 that forwards a single input event (`EI`) to one of two outputs. The output selection is determined by the value of the input variable `K`.
![E_DEMUX_2](E_DEMUX_2.svg)

## Interface Structure

### **Event Inputs**
- **EI (Event Input)**: The input event to be distributed.
- **Associated Data**: `K`

### **Event Outputs**
- **EO1**: Triggered when `EI` arrives and the selection index is `K = 0`.
- **EO2**: Triggered when `EI` arrives and the selection index is `K = 1`.

### **Data Inputs**
- **K**: The zero-based selection index that determines which output is triggered (data type: `UINT`).

## Functionality

1. **Event Reception**: The function block waits for an event at input `EI`.

# 2. **Selection**: When the `EI` event occurs, the value of the data variable `K` is evaluated.

3. **Forwarding**:

If `K` = 0, the event is forwarded to `EO1`.

If `K` = 1, the event is forwarded to `EO2`.

4. **Invalid Index**: If the value of `K` is outside the valid range [0, 1], no output event is triggered.

The input event is therefore always forwarded exclusively to exactly one output, provided the index `K` is valid.

## Technical Features
- **1-to-2 Distribution**: This function block distributes an event to two possible outputs.
- **Index-Driven**: The logic is based on a numeric index (`K`).
- **Confusing Naming Convention**: Note that the outputs are named 1-based (`EO1`, `EO2`), but the selection index `K` is 0-based (`K=0` for `EO1`, `K=1` for `EO2`).
- **Generic Building Block**: The functionality is provided by the generic class `GEN_E_DEMUX`.

## Application Scenarios
- **Conditional Branching**: Splitting an event flow based on a simple condition that results in either 0 or 1.
- **State Machines**: Selection between two possible next states.
- **Activation/Deactivation**: Forwarding an event to an "on" or "off" path.

## Conclusion
The `E_DEMUX_2` is a specialized version of the demultiplexer for cases where an event needs to be split into exactly two paths. It is useful for simple binary decisions in the event flow. The inconsistent naming of the outputs relative to the index value requires special attention during implementation.