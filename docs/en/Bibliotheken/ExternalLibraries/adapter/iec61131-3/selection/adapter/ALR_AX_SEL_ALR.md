# ALR_AX_SEL_ALR

![ALR_AX_SEL_ALR](./ALR_AX_SEL_ALR.svg)

* * * * * * * * * *
The function block `ALR_AX_SEL_ALR` is used for binary selection between two analog input signals provided by adapters of type `ALR`. This selection is controlled by a selector adapter of type `AX`. The selected signal is passed on to an output adapter of type `ALR`.

The function block is internally based on the IEC 61131-3 selection function `F_SEL` and is optimized for event-driven IEC 61499 architectures.

Since this component is designed as an adapter coupler, it does not have any classic, direct event or data interfaces at the top level. All communication is handled via sockets (input adapters) and plugs (output adapters).

*No direct event inputs available.*

*No direct event outputs available.*

*No direct data inputs available.*

*No direct data outputs available.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **Sockets (Input Interfaces):**
- `IN0` (Type: `adapter::types::unidirectional::ALR`): First selectable input channel (switched to output when selector `G` has the value `FALSE`).
- `IN1` (Type: `adapter::types::unidirectional::ALR`): Second selectable input channel (switched to output when selector `G` has the value `TRUE`).
- `G` (Type: `adapter::types::unidirectional::AX`): Selector input for controlling channel selection.
- **Plugs (Output Interfaces):**
- `OUT` (Type: `adapter::types::unidirectional::ALR`): Output carrying the selected signal.
- ## Functionality

This module implements a software-controlled 1-out-of-2 selection based on adapters:

1. **Event Buffering:** Incoming events and data at sockets `IN0`, `IN1`, and `G` are buffered via internal event D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) to ensure consistent data transfer.
2. **Value Transfer:** Data values are prepared for the data type `LREAL` via internal assignment elements (`F_MOVE`).
3. **Selection Logic (`F_SEL`):** Selection is performed using the standard selection block:
- If the signal at `G.D1` equals `FALSE`, the value of `IN0.D1` is passed to the output.
- If the signal at `G.D1` equals `TRUE`, the value of `IN1.D1` is passed to the output.
4. **Output Triggering:** Any change to one of the inputs or the selector triggers an update of the output adapter `OUT`, signaled by the event `OUT.E1` and the new data value `OUT.D1`.
- **Precise Data Processing (LREAL):** The internal data paths are designed for the data type `LREAL`, enabling lossless transmission of highly accurate analog measurements.
- **Adapter Encapsulation:** The use of standardized adapters (`ALR`, `AX`) eliminates the need for complex individual wiring of data and event pins in the application editor.
- **Event-driven:** The output reacts dynamically and without delay to value changes and triggers at the inputs.

The behavior of the function block is determined by the data and event flow in the internal network:

| State Selector `G.D1` | Channel Passed | Output Value `OUT.D1` | Output Event `OUT.E1` |
| :--- | :--- | :--- | :--- |
| `FALSE` | Channel 0 (`IN0`) | Value of `IN0.D1` | Triggers on events on `IN0.E1` or changes to `G` |
| `TRUE` | Channel 1 (`IN1`) | Value of `IN1.D1` | Triggered by events on `IN1.E1` or a change in `G` |

- **Sensor Redundancy / Failover:** Switching between a primary sensor (`IN0`) and a backup sensor (`IN1`) in case of failure or signal interference, controlled by a diagnostic signal at `G`.
- **Setpoint Switching:** Switching between an automatic setpoint and a manual target value in process control loops.
- **Recipe and Parameter Set Selection:** Dynamic assignment of different analog process parameters based on the current plant state.

Compared to a classic IEC 61131-3 `SEL` function block, `ALR_AX_SEL_ALR` completely encapsulates the signal paths in adapter structures. This significantly reduces the visual complexity in 4diac application diagrams, as only structured adapter lines need to be drawn instead of multiple individual connections.

The `ALR_AX_SEL_ALR` is a robust and reusable function block for structured signal switching in IEC 61499. Through the consistent use of adapters and the support of high-resolution `LREAL` data, it is ideally suited for modern control concepts in industrial automation.
## Functionality

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion
