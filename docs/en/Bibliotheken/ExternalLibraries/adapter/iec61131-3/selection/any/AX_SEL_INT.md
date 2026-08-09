# AX_SEL_INT

![AX_SEL_INT](./AX_SEL_INT.svg)

*No image file available. The interfaces and internal structure are described in detail below.*

* * * * * * * * * *

The function block `AX_SEL_INT` is a standard selection function block according to IEC 61499. It is used for binary selection between two integer input values (`INT`) via a selector signal provided by a unidirectional adapter. The block is designed to process events with high efficiency and output an optimized event.

| Event | Description | Associated Data |
| :--- | :--- | :--- |
| **EI0** | Signals an update to the input value `IN0`. | `IN0` |
**EI1** | Signals an update to the input value `IN1`. | `IN1` |
| Event | Description | Associated Data |
| :--- | :--- | :--- |
**CNF** | Confirmation event that signals a change or update to the selected output value. | `OUT` |
| Variable | Data Type | Description |
| :--- | :--- | :--- |
**IN0** | INT | First selectable integer input value (selected by default if the selector is `FALSE`). |
| **IN1** | INT | Second selectable integer input value (selected if the selector is `TRUE`). |
| Variable | Data Type | Description |
| :--- | :--- | :--- |
| **OUT** | INT | The currently selected integer output value. |

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

| Adapter Name | Type | Direction | Description |
| :--- | :--- | :--- | :--- |
| **G** | `adapter::types::unidirectional::AX` | Socket | Unidirectional adapter for passing the selector signal (includes the data field `D1` for selection and the event `E1` for triggering).

## Functionality

The function block `AX_SEL_INT` operates as an event-driven multiplexer for two `INT` values.

1. **Value Buffering:** Upon the arrival of the events `EI0` or `EI1`, the data values `IN0` and `IN1`, respectively, are buffered via internal D flip-flops (`E_D_FF_ANY_IN0` / `E_D_FF_ANY_IN1`).
2. **Selection:** The adapter `G` provides the selection signal via its data channel (`G.D1`).

If the signal is `FALSE`, the value of `IN0` is passed through to the output `OUT`.

- If the signal is `TRUE`, the value of `IN1` is passed through to the output `OUT`.
3. **Event Filtering (Important Feature):** An output event (`CNF`) is primarily generated when the selection signal of the adapter `G` changes or when the resulting output value actually changes. This prevents an unnecessary flood of events in the subsequent control network during redundant data updates.
* **Composite Function Block Network:** The function block is internally composed of several standard auxiliary blocks, including `F_SEL` (selection function according to IEC 61131-3), `F_MOVE` (value transmission), and `E_D_FF_ANY` (event-triggered D flip-flops for edge detection and value change verification).
* **Adapter Coupling:** By using the adapter `G` (`AX` type), wiring in the control design is simplified, as control and data signals for the selection are logically bundled and transmitted together.
* **Adapter Coupling:** * **Efficient Event Propagation:** Due to internal filtering, the output event `CNF` is only triggered when a genuine change occurs (especially when the selector `G` is changed).

Since this is a composite function block (FB) without its own state machine (ECC), its behavior is directly determined by the signal flow in the internal network:

* **State "IN0 active":** `G.D1` is `FALSE`. Changes to `IN0` (via `EI0`) result in an update of `OUT` and trigger `CNF`. Changes to `IN1` are ignored.
* **State "IN1 active":** `G.D1` is `TRUE`. Changes to `IN1` (via `EI1`) result in an update of `OUT` and trigger `CNF`. Changes to `IN0` are ignored.
* **Switching process:** As soon as an event `G.E1` arrives, the function block re-evaluates the selection and updates `OUT` according to the newly selected input.
* ## Application Scenarios
* **Setpoint Switching:** Switching between a manually setpoint (`IN0`) and an automatic setpoint (`IN1`) in an industrial plant.
* **Sensor Redundancy:** Switching between two redundant temperature or position sensors (transmitted as integer values) in case of a fault.
* **Recipe Control:** Selection of various predefined parameter IDs based on the state of a higher-level process control system.
* ## Comparison with Similar Function Blocks
* **Standard `F_SEL`:** The classic IEC 61131-3 function block `F_SEL` does not have event-based control and does not react dynamically to signal changes as defined in IEC 61499. `AX_SEL_INT` encapsulates this functionality in an event-driven manner.
* **`AX_SEL_REAL`:** Identical functionality, but specifically designed for the floating-point data type `REAL`, while `AX_SEL_INT` is optimized for integer values `INT`.

The `AX_SEL_INT` is a robust and reusable function block for discrete-event control technology. Through its integrated filtering of redundant events, it makes a significant contribution to performance optimization and stability within 4diac-based runtime environments.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion