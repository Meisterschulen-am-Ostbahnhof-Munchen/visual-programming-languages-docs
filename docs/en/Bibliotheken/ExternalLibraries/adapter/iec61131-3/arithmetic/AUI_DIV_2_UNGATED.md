# AUI_DIV_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUI_DIV_2`](AUI_DIV_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

      +-----------------------------------+
|             AUI_DIV_2_UNGATED             |
      +-----------------------------------+
=====>| [AUI] IN1                 OUT [AUI]|=====>
=====>| [AUI] IN2                         |
      +-----------------------------------+

![AUI_DIV_2_UNGATED](./AUI_DIV_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `AUI_DIV_2_UNGATED` is a generic function block for performing an arithmetic division of two input values. The block uses an adapter-based concept, where data and event streams are bundled in unidirectional adapters. This enables clean, modularized, and clear modeling within IEC 61499 applications in 4diac.

## Interface Structure

### Event Inputs

*No direct event inputs are defined. Event control is implicit via the adapter interfaces.*

### Event Outputs

*No direct event outputs are defined. Event control is implicit via the adapter interfaces.*

### Data Inputs

*No direct data inputs are defined. Data is transferred via the input adapters.*

### Data Outputs

*No direct data outputs are defined. Data is transferred via the output adapter.*

### **Adapters**

- **IN1** (Type: `adapter::types::unidirectional::AUI`):

The first input adapter. It provides the dividend (numerator) for the division operation and the associated trigger events.

- **IN2** (Type: `adapter::types::unidirectional::AUI`):

The second input adapter. It provides the divisor (denominator) for the division operation and the associated trigger events.

- **OUT** (Type: `adapter::types::unidirectional::AUI`):

The output adapter. It outputs the result of the division (quotient) and the corresponding calculation event.

#### **Plugs (Ausgangs-Schnittstellen)**

#### **Sockets (Eingangs-Schnittstellen)**

## Functionality

The function block performs the mathematical operation `OUT = IN1 / IN2`.

As soon as a corresponding trigger event is registered at the input adapters (`IN1` or `IN2`), the function block reads the current values from the adapters, calculates the quotient, and outputs it along with an output event via the adapter `OUT`.

Since it is a generic function block (`GEN_AUI_DIV`), the function block can adapt to different numeric data types (e.g., INT, REAL, LREAL) depending on the implementation and system configuration, provided the underlying adapters support the same data type.

- **Generic Type:** The attribute `GenericClassName` with the value `'GEN_AUI_DIV'` allows the function block to be used flexibly and is not restricted to a specific data type.
- **Interface Encapsulation:** The use of unidirectional adapters (`AUI`) significantly reduces wiring effort in the 4diac IDE, as event and data lines are bundled into a single connection.
- **Division by Zero:** When using this function block, it must be ensured that the value of `IN2` is not zero to avoid runtime errors or infinite values (NaN/Inf) in the control system.

- ## Status Overview

1. **Waiting State (IDLE):** The function block waits for incoming events via the adapters `IN1` or `IN2`.
2. **Calculation (EVALUATE):** After receiving an event, the data from the adapters is read and the division is performed.
3. **Output (DISPATCH):** The result and the associated event are provided via the adapter `OUT`.

- **Scaling of Sensor Values:** Division of raw values by scaling factors in modular control architectures.
- **Calculation of Averages:** Use in mathematical computing networks where data streams are transmitted in a structured manner via adapters.
- **Signal Processing:** Reduction of signal strength or frequency divisions in distributed systems.

Compared to a classic standard DIV function block (e.g., from the IEC 61131-3 standard library), which uses individual pins for `REQ`, `CNF`, `IN1`, `IN2`, and `OUT`, the `AUI_DIV_2_UNGATED` offers a significantly cleaner visual representation in the function block diagram. Encapsulation in adapters minimizes the potential for errors when manually wiring event-to-data mappings.

The `AUI_DIV_2_UNGATED` is a modern, modular, and reusable function block for division. Through the consistent use of unidirectional adapters, it is ideally suited for complex, distributed control applications in 4diac where clarity and easy maintainability of the code are paramount.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion
