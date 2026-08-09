# BOOL_AX_AX_SEL_AX

![BOOL_AX_AX_SEL_AX](./BOOL_AX_AX_SEL_AX.svg)

* * * * * * * * * *

The function block `BOOL_AX_AX_SEL_AX` is a composite function block for IEC 61499. It performs binary selection between two Boolean signal sources and forwards the selected signal to an output.

The unique feature of this block is the combination of classic event-based data channels and modern, adapter-based interfaces. It is ideally suited for dynamically filtering and forwarding a simple Boolean signal and an adapter-based signal using a selector.

* **EI0**: Sets the value of the direct data input `IN0` and triggers its processing in the internal network.
* *No direct event outputs are available. Events are output via the output adapter `OUT`.*
* **IN0** (BOOL): Directly available Boolean input variable, which can be selected.
* *No direct data outputs are available. Data transmission occurs via the output adapter `OUT`.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

* **IN1** (Socket, Type: `adapter::types::unidirectional::AX`): Adapter-based, selectable data channel.
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector channel. The signal applied here determines which input is enabled.
* **OUT** (Plug, Type: `adapter::types::unidirectional::AX`): The selected output channel that carries the signal from the selected input.

## Functionality

The component is internally based on the standard selection logic of IEC 61131-3 (`F_SEL`). It switches the signals as follows:

1. **Selection (`G` = FALSE):** If the selector adapter `G` delivers the logical state `FALSE`, the directly connected data input `IN0` is switched to the output adapter `OUT`.
2. **Selection (`G` = TRUE):** If the selector adapter `G` delivers the logical state `TRUE`, the adapter-based input `IN1` is switched to the output adapter `OUT`.

The internal memory and conversion elements (`E_D_FF`, `E_D_FF_ANY`, and `F_MOVE`) ensure that the data values are buffered at each relevant event (`EI0`, `G.E1`, or `IN1.E1`) and consistently transmitted to the output. Each change triggers an update of the output adapter `OUT`, including the corresponding event.

* **Hybrid Interface:** This component acts as a bridge between classic IEC 61499 event control (for `IN0`) and adapter-based signal transmission (for `IN1`, `G`, `OUT`).
* **Event Consistency:** The use of D flip-flops (`E_D_FF` / `E_D_FF_ANY`) in the internal network ensures that data is only transmitted when a valid trigger event signals the data's validity.
* **Event Consistency:** ## State Overview

The output signal selection follows this logic:

| State Selector (G.D1) | Active Input | Output Value (OUT.D1) | Triggering Event for Output (OUT.E1) |
| :--- | :--- | :--- | :--- |
| **FALSE** | `IN0` | Value of `IN0` | `EI0` (if selected) or edge on `G.E1` |
| **TRUE** | `IN1.D1` | Value of `IN1.D1` | `IN1.E1` (if selected) or edge on `G.E1` |

* **Manual/Automatic Switching:** In automatic mode, a control signal is to be obtained from a complex software subsystem via an adapter (`IN1`). In manual mode or during maintenance, a physical, directly wired push button (`IN0`) should take over control. The switchover is performed via the selector `G`.
* **Signal Override / Bypass Control:** Temporarily connecting an emergency or test signal to a standardized adapter line.
* **Standard `F_SEL`:** The classic IEC 61131-3 selection block processes only elementary data types and has no event control or adapter compatibility. `BOOL_AX_AX_SEL_AX` extends this functionality for distributed, event-driven systems.
* **Purely Adapter-Based Selectors:** Unlike pure adapter couplers, this block allows the direct input of a standard Boolean data point (`IN0`) without requiring a separate adapter constructor.

The `BOOL_AX_AX_SEL_AX` is a useful auxiliary function block for modular control concepts in 4diac. It simplifies signal routing in mixed system architectures where both classic I/O signals and structured adapter connections coexist.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion