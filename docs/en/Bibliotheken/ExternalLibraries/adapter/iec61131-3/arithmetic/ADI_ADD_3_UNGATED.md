# ADI_ADD_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ADI_ADD_3`](ADI_ADD_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ADI_ADD_3_UNGATED](./ADI_ADD_3_UNGATED.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `ADI_ADD_3_UNGATED` is a generic arithmetic block used to add three input values. It is based on the IEC 61499-2 standard and uses an adapter-based communication model. By using unidirectional adapters of type `ADI` (adapters for data integration/interaction), the block enables structured and clean signal and data routing within 4diac-ide.

## Interface Structure

### **Event Inputs**

*There are no direct, standalone event inputs. Event control is implemented via the assigned adapter inputs (sockets).*

### **Event Outputs**

*There are no direct, standalone event outputs. Event forwarding is implemented via the adapter output (plug).*

### **Data Inputs**

*There are no direct data inputs. Data transmission occurs via the adapters.*

### **Data Outputs**

*There are no direct data outputs. Data transmission occurs via the output adapter.*

### **Adapters**

#### **Sockets (Input Interfaces)**

- **IN1** (Type: `adapter::types::unidirectional::ADI`): First input summation for addition.
- **IN2** (Type: `adapter::types::unidirectional::ADI`): Second input summation.
- **IN3** (Type: `adapter::types::unidirectional::ADI`): Third input summand for addition.

#### **Plugs (Output Interfaces)**

- **OUT** (Type: `adapter::types::unidirectional::ADI`): Output for the calculated addition result ($OUT = IN1 + IN2 + IN3$).

---

## Functionality

As soon as a new event or new data arrives at one of the input sockets (`IN1`, `IN2`, or `IN3`), the function block reads the values from the three adapters. It performs an arithmetic addition of the three values:

$$\text{Result} = \text{IN1} + \text{IN2} + \text{IN3}$$

The calculated result and the associated update event are then transmitted to the subsequent function blocks in the system via the output plug `OUT`.

---

## Technical Features

- **Generic Function Block (FB):** Due to the attribute `eclipse4diac::core::GenericClassName` with the value `GEN_ADI_ADD`, this function block behaves polymorphically. It is not fixed to a specific data type (such as `INT` or `REAL`), but adapts flexibly to the data type defined in the adapter.
- **Adapter-Based Architecture:** Encapsulating data and events in the `ADI` adapters significantly reduces cable clutter in the 4diac IDE, as separate event and data lines are not required for each summand.

---

## State Overview

The function block operates in a purely stateless (reactive) state:

1. **Idle State:** The block waits for trigger signals from the input sockets.
2. **Calculation & Forwarding:** Upon triggering at `IN1`, `IN2`, or `IN3`, the sum is calculated instantly and output via the `OUT` plug.

---

## Application Scenarios

- **Sensor Consolidation:** Summing of three different physical quantities (e.g., three partial flows in a system to determine the total flow).
- **Setpoint Offset Calculation:** Combination of a main setpoint, a correction value, and an additional tolerance or offset value.
- **Process Value Calculation:** Balancing of inflows at three different measuring points in process engineering.

- ---

## Comparison with Similar Components

- **Standard `ADD` (IEC 61131-3):** The classic ADD component uses direct pins for data and events. `ADI_ADD_3_UNGATED`, due to its use of unidirectional adapters, is better suited for modular and hierarchical architectures in IEC 61499.
- **Two-way adder (e.g., `ADI_ADD_2`):** While adding three values with standard function blocks would require cascading two blocks, `ADI_ADD_3_UNGATED` performs this task in a single step, saving resources and improving clarity.

---

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ADI_ADD_3_UNGATED` is a practical, generic auxiliary function block for arithmetic operations in modern IEC 61499 control applications. Its consistent use of adapters allows it to integrate seamlessly into clean software architectures and minimizes wiring effort in the development environment.
