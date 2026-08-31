# A2X_SPLIT_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`A2X_SPLIT_2`](A2X_SPLIT_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![A2X_SPLIT_2_UNGATED](./A2X_SPLIT_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `A2X_SPLIT_2_UNGATED` splits an incoming A2X adapter signal into two identical output adapters. It is implemented as a generic function block (`GEN_A2X_SPLIT`) and allows an A2X signal to be forwarded to two independent target function blocks without signal loss or modification.

## Interface Structure

### **Event Inputs**

No event inputs available.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

| Type | Name | Direction | Description |
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::A2X` | `IN` | Socket | Input adapter that receives the A2X signal to be distributed. |
| `adapter::types::unidirectional::A2X` | `OUT1` | Plug | First output adapter that provides an identical copy of the input signal. |
| `adapter::types::unidirectional::A2X` | `OUT2` | Plug | Second output adapter that provides an identical copy of the input signal. |

## Functionality

The function block forwards the A2X adapter signal present at socket `IN` directly to the two plugs `OUT1` and `OUT2` without any transformation or delay. Every event transmitted via the A2X adapter appears simultaneously and unchanged at both outputs. The function block has no internal logic, no state, and no latency.

## Technical Features

- **Generic Function Block**: The function block is declared as the generic type `GEN_A2X_SPLIT` and utilizes the Eclipse 4diac Generic Class concept. This allows for flexible reuse in different projects.
- **Pure Adapter Forwarding**: No event or data inputs/outputs are used; all communication takes place exclusively via the A2X adapter interfaces.
- **Unidirectional**: The A2X adapter is unidirectional, therefore data and events only flow from the socket to the plugs (input → output).

## State Overview

The module has no internal state machine and is completely **stateless**. Every input value is immediately passed to both outputs without storage.

## Application Scenarios

- **Signal Multiplication**: An A2X signal provided by a sensor or controller is to be distributed to two different devices (e.g., actuators, displays, superimposed logic) simultaneously.
- **Redundancy or Monitoring**: A signal is to be routed to a diagnostic or monitoring module in parallel with a primary destination.
- **Testing and Simulation**: An A2X signal is to be connected to both the actual hardware and a simulator during testing.

## Comparison with Similar Modules

- **A2X_SPLIT_3**: Analog module with three outputs instead of two. Both modules function identically, differing only in the number of output plugs.
- **A2X_MERGE**: Combines two A2X signals into one – opposite functionality.
- **Generic Splitters (e.g., for other adapter types)**: Same operating principle, but adapted to the adapter type.

## Conclusion

The `A2X_SPLIT_2_UNGATED` is a simple yet useful module for signal distribution in 4diac applications. Its generic nature allows for flexible use without additional configuration. It is particularly suitable for scenarios where an A2X signal needs to be passed on to multiple receivers without compromising signal integrity.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
