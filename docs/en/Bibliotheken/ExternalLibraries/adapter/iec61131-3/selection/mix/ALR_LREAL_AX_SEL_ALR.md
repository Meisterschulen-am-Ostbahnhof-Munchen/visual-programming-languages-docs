# ALR_LREAL_AX_SEL_ALR

![ALR_LREAL_AX_SEL_ALR](./ALR_LREAL_AX_SEL_ALR.svg)

* * * * * * * * * *

The function block `ALR_LREAL_AX_SEL_ALR` is used for binary selection (multiplexing) between two analog input signals of data type `LREAL`. The block combines classic IEC 61499 events and data with modern, adapter-based interfaces.

The control over which of the two inputs is routed to the output is achieved via a binary selection signal (`G`), which is read in via an adapter. The output signal is also output via an adapter.

| Event | Description | Associated Data |
| :--- | :--- | :--- |
**EI1** | Signals the update of the classic data input `IN1`. | `IN1` |

*This function block does not have direct, classic event outputs. Event forwarding is handled via the output adapter `OUT`.*

| Data Point | Data Type | Description |
| :--- | :--- | :--- |
| **IN1** | LREAL | Input value to be selected: 1 (classic variable). |

*This function block does not have direct, classic data outputs. Data output is handled via the output adapter `OUT`.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapter**

| Adapter Name | Type | Direction | Description |
:--- | :--- | :--- | :--- |
**OUT** | `adapter::types::unidirectional::ALR` | Plug | The selected output value (LREAL) including the associated update event. |
**IN0** | `adapter::types::unidirectional::ALR` | Socket | Input value 0 to be selected (LREAL signal via adapter). |
**G** | `adapter::types::unidirectional::AX` | Socket | Selection input (Gate/Selector via adapter). |

**IN0** | `adapter::types::unidirectional::AX` | Socket | Selection input (Gate/Selector via adapter). ## Functionality

The module is internally based on a logic network that buffers events and data and processes them via the standard selection module `F_SEL`:

1. **Input Buffering:**
* The selection signal from the adapter `G` (data point `D1`, event `E1`) is stabilized by a D flip-flop (`E_D_FF`).
* The adapter input `IN0` (data point `D1`, event `E1`) is buffered via a universal D flip-flop (`E_D_FF_ANY_IN0`) and passed to the selector via `F_MOVE_IN0`.
* The classic data input `IN1` (triggered by `EI1`) is processed analogously via `E_D_FF_ANY_IN1` and `F_MOVE_IN1`.
* 2. **Selection Logic (`F_SEL`):**
* If the signal `FALSE` is present at adapter `G`, the value of `IN0` (adapter) is passed through to the output.
* If the signal `TRUE` is present at adapter `G`, the value of `IN1` (classic input) is passed through to the output.
3. **Output Control:**
* Any change to the inputs or the selection signal triggers a recalculation. The selected value is passed from output flip-flop `E_D_FF_ANY_OUT` to output adapter `OUT` (data point `D1`, event `E1`).

          +-----------------------------------------+
|           ALR_LREAL_AX_SEL_ALR          |
|                                         |
(ALR) ---> [IN0]  ======\                          |
|               \                         |
 (AX)  ---> [G]    ========+===> [ F_SEL ] ===> [OUT] ---> (ALR)
|               /                         |
(LREAL)--> [IN1]  ======/                          |
(Event)--> [EI1]  -----/                           |
          +-----------------------------------------+

* **Adapter Coupling:** This function block is ideally suited for bridging adapter-based communication (e.g., structured fieldbus or sensor couplers) and classic function block structures.
* **Event-Driven:** The internal use of event flip-flops (`E_D_FF` / `E_D_FF_ANY`) ensures that the output only fires an event when data or the selector state has actually changed.

The following table shows the behavior of output `OUT` depending on the control signal `G`:

| State of `G` | Selected Output (`OUT.D1`) | Triggering event at output (`OUT.E1`) |
| :--- | :--- | :--- |
| **FALSE** | Value of `IN0.D1` | On change of `IN0.D1`, `IN0.E1`, or state change of `G` |
| **TRUE** | Value of `IN1` | On change of `IN1`, `EI1`, or state change of `G` |

* **Setpoint Switching:** Switching an analog reference value (LREAL) between an automatic sensor value (via adapter `IN0`) and a manually specified parameter (via classic input `IN1`).
* **Manual/Automatic Switching:** Used in process plants where, in case of a fault or for maintenance purposes, a switch to a static substitute value or a manually setpoint value is required via signal `G`.
* **Signal Routing:** Dynamic routing of data streams in complex distributed control systems.
* ## Comparison with Similar Components

Compared to the standard selection block `F_SEL` from the IEC 61131-3 library, which operates purely in a data flow-oriented manner, `ALR_LREAL_AX_SEL_ALR` offers complete integration into the event-driven architecture of IEC 61499. It encapsulates the necessary event and conversion logic, eliminating the need for additional auxiliary blocks for signal buffering in the application network.

The `ALR_LREAL_AX_SEL_ALR` is a specialized and robust multiplexer for `LREAL` signals. Through the clever combination of classic data inputs and modern, unidirectional adapters, it enables clean and clear structuring of control software in 4diac.
## Functionality

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion