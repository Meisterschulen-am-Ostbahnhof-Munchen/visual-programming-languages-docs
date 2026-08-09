# AX_SEL_BOOL

![AX_SEL_BOOL](./AX_SEL_BOOL.svg)

*(No image available)*

* * * * * * * * * *
The function block `AX_SEL_BOOL` is used for the binary selection of Boolean signals. It is based on the standardized selection function according to IEC 61131-3 and allows event-driven selection between two Boolean input values (`IN0` and `IN1`). Selection is elegantly controlled via an adapter input.

* **EI0**: Triggers the update and transfer of the data input `IN0`.
* **EI1**: Triggers the update and transfer of the data input `IN1`.
* **CNF**: Confirmation event. Signals that the selected output value `OUT` has been updated.
* **IN0** (BOOL): First selectable input value. This value is passed through to the output when the selector is in the state `FALSE`.
* **IN1** (BOOL): Second selectable input value. This value is passed through to the output when the selector is in the state `TRUE`.
* **OUT** (BOOL): The currently selected output value (corresponds to either `IN0` or `IN1`, depending on the selector's state).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): A unidirectional adapter socket that functions as a selector. The switching signal is received via this adapter. An event at this adapter triggers the recalculation of the selection.

## Functionality

Internally, `AX_SEL_BOOL` is implemented as a composite function block (FB). The essential steps of the signal processing are:

1. If an event occurs at `EI0` or `EI1`, the respective data value (`IN0` or `IN1`, respectively) is temporarily stored via internal event D flip-flops (`E_D_FF_ANY`) and passed on to the central selection block `F_SEL`.
2. The selector adapter `G` provides the control signal. When an event occurs at the adapter (`G.E1`), the selection signal (`G.D1`) is acquired.
2. The selector adapter `G` provides the control signal. 3. The function block `F_SEL` (IEC 61131-3 standard selector) evaluates the selector's state:
* If the selection signal is `FALSE`, the value of `IN0` is passed to the output.
* If the selection signal is `TRUE`, the value of `IN1` is passed to the output.
4. The result is passed to the output flip-flop. The acknowledgment event `CNF` is output event-driven.
* **Event-driven control on selector change**: An output event (`CNF`) is primarily generated when a relevant change or update is initiated via the selector adapter `G`.
* **Resource efficiency**: By using edge-triggered and event-triggered D flip-flops (`E_D_FF` and `E_D_FF_ANY`) in the internal network, the CPU load is minimized, as calculations and signal forwarding only occur when actual signal changes occur.
* **Adapter coupling**: The use of the unidirectional adapter `AX` ensures clean encapsulation of the control logic and reduces the number of individual connections required in the higher-level system.
* ## State Overview
As a composite function block, `AX_SEL_BOOL` does not have a classic state machine (ECC). Instead, its behavior is determined purely by the signal and event flow of the internal network:

| Input Event | State Selector (G) | Internal Flow | Output Event | Output (OUT) |
| :--- | :--- | :--- | :--- | :--- |
| `EI0` / `EI1` | *No Change* | Values at `IN0`/`IN1` are updated. | - | No direct change to the output without selector triggering. |
| Adapter Event (`G.E1`) | `FALSE` | Selector switches to `IN0`. | `CNF` | Value of `IN0` |
| Adapter event (`G.E1`) | `TRUE` | Selector switches to `IN1`. | `CNF` | Value of `IN1` |
`` | `` | `` | ``CNF` | Value of `IN0` |
`| `IN0` | | `G.E1` | | `TRUE` | | `TRUE` | | `CNF` | `IN0` |

`IN0` | | ... ## Application Scenarios

* **Operating Mode Switching**: Ideally suited for switching control signals between automatic operation (`IN0`) and manual operation (`IN1`), where the adapter `G` is directly coupled to the operating mode selector switch.
* **Redundant Signal Paths**: Selection between a primary and a secondary (backup) sensor signal in case of a fault.
* **Event-Based Signal Routing**: Dynamic path selection in distributed control systems where the selection logic is provided by another control module via an adapter.
* ## Comparison with Similar Components
* **Standard Selector (`F_SEL` according to IEC 61131-3)**: Unlike the pure `F_SEL`, the `AX_SEL_BOOL` integrates event-driven memory logic and uses an adapter interface instead of loose Boolean inputs for selection. This significantly simplifies structured wiring in IEC 61499 applications.
* **Multiplexer (MUX)**: While a multiplexer allows selection from a multitude of channels via an integer index, the `AX_SEL_BOOL` is specifically optimized for fast, binary switching between exactly two Boolean signals.
* ## Conclusion

The `AX_SEL_BOOL` is a practical building block for modern industrial automation according to IEC 61499. By combining proven IEC 61131-3 selection logic with modern, adapter-based event control, it represents a clean and reusable solution for binary signal switching.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion