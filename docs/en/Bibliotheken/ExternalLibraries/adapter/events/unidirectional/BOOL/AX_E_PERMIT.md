# AX_E_PERMIT

![AX_E_PERMIT](./AX_E_PERMIT.svg)

* * * * * * * * * *
## Introduction

The **AX_E_PERMIT** function block implements conditional event propagation (permissive propagation). An incoming event is only forwarded to the output if a permit signal provided via an adapter has the value `TRUE`. The function block acts as a gate that can interrupt or enable the processing chain depending on external conditions.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-------|----------------|
| EI | Event | Event Input |

### **Event Outputs**

| Name | Type | Comment |
|------|-------|-----------------|
| EO | Event | Event Output |

### **Data Inputs**

This function block has no data inputs of its own. The enable signal is provided via an adapter.

### **Data Outputs**

This function block has no data outputs.

### **Adapter**

| Role | Name | Type | Comment |
|---------|--------|----------------------------------------|-------------------------------|
| Socket | PERMIT | `adapter::types::unidirectional::AX` | Provides the enable signal (D1) |

The adapter is unidirectional and provides a Boolean value (`D1`) that controls the behavior of the event gate.

## Functionality

The function block internally contains a standard function block `E_PERMIT` from the IEC 61499 library. The incoming event `EI` is directly forwarded to the internal input `E_PERMIT`. Its output `EO` is only active if the corresponding enable input (`PERMIT` of the internal block) assumes the value `TRUE`. This enable signal is fed from the adapter `PERMIT` via the connection `PERMIT.D1`.

Therefore:

- **Permit = TRUE:** The event `EI` is passed on to `EO` without delay.
- **Permit = FALSE:** The event is suppressed; `EO` remains inactive.

## Technical Features

- **Adapter-Based Interface:** The enable signal is not provided as a classic data input, but via an adapter (`AX`, unidirectional). This enables modular coupling and reuse of the enable logic.
- **No Data Forwarding:** The function block itself does not output any data. It serves solely to control the event flow.
- **Unidirectional Adapter:** The adapter provides only one data value (D1) to the function block; feedback is not provided.
- **Use of a Standard Block:** Internally, the proven `E_PERMIT` block is used, which implements the actual enable logic.

## State Overview

The block itself has no visible states. Its internal behavior is determined by the `E_PERMIT` block, which essentially represents a passive wait loop:

- **Waiting for Event:** The block waits for an event at input `EI`.
- **Permit Check:** Upon arrival of an event, the state of the enable signal is evaluated.
- **Forwarding:** The event is only output to `EO` if `PERMIT = TRUE` is present.

There is no explicit state machine; the block operates purely combinatorially at the event level.

## Application Scenarios

- **Safety Interlock:** An event (e.g., machine start) is only forwarded if an external safety circuit provides a release signal.
- **Conditional Processing:** In a production control system, data from sensors can only be sent to the higher-level controller when the operating mode is activated.
- **Test and Simulation Environments:** An event can be selectively enabled or disabled via a manual release signal to test specific scenarios.
- **Resource Conservation:** In a complex automation system, unnecessary events can be suppressed by disabling the permit to reduce bus load.

## Comparison with Similar Blocks

| Block | Special Feature |
|-------------------|-----------------------------------------------------------------------------|
| **E_PERMIT** | Standard block with direct Boolean input. No adapter required. |
| **AX_E_PERMIT** | Same logic, but the enable signal is provided via a unidirectional adapter, which facilitates coupling across subsystems. |
| **E_SR** (Set-Reset) | Event-based state storage; not directly suitable as a gate. |
| **E_MUX** | Event switch that toggles between two outputs depending on a data input – not a pure blocking function. |

The advantage of `AX_E_PERMIT` lies in the clean separation of the enable logic by an adapter, which promotes the reuse of control modules.

## Conclusion

The `AX_E_PERMIT` function block represents a flexible and modular solution for conditional event forwarding. By using an adapter for the enable signal, the interface is clearly defined and can be used across hierarchical boundaries. The block is particularly suitable for safety-critical or configurable control applications where event processing depends on external conditions.
