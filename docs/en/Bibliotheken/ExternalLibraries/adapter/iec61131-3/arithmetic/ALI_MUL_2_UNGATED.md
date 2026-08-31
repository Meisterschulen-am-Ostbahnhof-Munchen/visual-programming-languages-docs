# ALI_MUL_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALI_MUL_2`](ALI_MUL_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALI_MUL_2_UNGATED](./ALI_MUL_2_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ALI_MUL_2_UNGATED` is used to perform an arithmetic multiplication of two values. It is a generic function block designed for a clean and modular architecture in IEC 61499 systems. Instead of classic discrete data and event ports, this block uses unidirectional adapters to transmit control events and data values in a bundled manner.

## Interface Structure

### Event Inputs

There are no direct event inputs. Event control is integrated into the input adapters.

### Event Outputs

There are no direct event outputs. Event control is integrated into the output adapter.

### Data Inputs

There are no direct data inputs. Data transmission occurs via the adapters.

### Data Outputs

There are no direct data outputs. Data transmission occurs via the output adapter.

### **Adapters**

- **Sockets (Input Adapters):**
- `IN1` (Type: `adapter::types::unidirectional::ALI`): First input for multiplication (multiplicand).
- `IN2` (Type: `adapter::types::unidirectional::ALI`): Second input for multiplication (multiplier).
- **Plugs (Output Adapters):**
- `OUT` (Type: `adapter::types::unidirectional::ALI`): Output for the result of the multiplication (product).

## Functionality

The function block `ALI_MUL_2_UNGATED` multiplies the values provided via the adapter sockets `IN1` and `IN2`. As soon as a corresponding trigger event is signaled via the input adapters, the block performs the calculation:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

The calculated result and the associated output event are then forwarded to subsequent blocks via the output plug `OUT`.

- **Generic Nature:** The function block is declared as `GEN_ALI_MUL` via the attribute `GenericClassName`. This allows for flexible handling of various data types specified by the higher-level system or the adapter type used.
- **Adapter Coupling:** By using the unidirectional adapter type `ALI`, data and trigger events are bundled in a single connection, significantly minimizing wiring effort in the development environment.

## Technical Features

Since this is a purely data-flow and adapter-based function block, it does not have a complex internal state machine (Execution Control Chart - ECC). Execution is event-driven and directly coupled to the triggers received via the adapters.

## State Overview

**Adapter Coupling:** ## Application Scenarios

## Application Scenarios

- **Measurement Scaling:** Multiplication of sensor values by calibration or scaling factors.
- **Power Calculation:** Determination of physical quantities such as electrical power ($P = U \times I$) in adapter-based control networks.
- **Compact Computing Networks:** Use in complex mathematical calculations where the visual clarity of the control diagram must be maintained through the use of adapters.

## Comparison with Similar Function Blocks

Compared to classic mathematical components of IEC 61131-3 (such as a standard `MUL` component with discrete `REQ` / `CNF` events and separate data lines), the `ALI_MUL_2_UNGATED` eliminates the need for manual linking of event and data paths. This prevents errors in event data mapping and results in a significantly cleaner and more readable application diagram in 4diac-ide.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALI_MUL_2_UNGATED` is a modern and efficient function block for multiplication. Thanks to the consistent use of unidirectional adapters, it is ideally suited for service-oriented and modular control systems where clarity and ease of maintenance are paramount.
