# AS_ADD_4

![AS_ADD_4](./AS_ADD_4.svg)

*(Image of function block not available)*

* * * * * * * * * *
## Introduction

The function block `AS_ADD_4` is a generic function block (FB) designed to perform an arithmetic addition of four input values. The unique feature of this block lies in the use of unidirectional adapters (`AS`) for the inputs and outputs, enabling structured and clean encapsulation of data and associated events in IEC 61499 applications.

## Interface Structure

### **Event Inputs**

*There are no direct event inputs. Event control is implicit via the adapter interfaces.*

### **Event Outputs**

*There are no direct event outputs. Event forwarding is implicit via the output adapter.*

### **Data Inputs**

*There are no direct data inputs. Data is transferred via the input adapters.*

### **Data Outputs**

*There are no direct data outputs. The result is provided via the output adapter.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AS`): First input value (addend 1) for addition.
- **IN2** (Type: `adapter::types::unidirectional::AS`): Second input value (addend 2) for addition.
- **IN3** (Type: `adapter::types::unidirectional::AS`): Third input value (addend 3) for addition.
- **IN4** (Type: `adapter::types::unidirectional::AS`): Fourth input value (addend 4) for the addition.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AS`): Output adapter for displaying the calculated addition result.

---

## Functionality

This function block performs a mathematical addition of the values received via the four input adapters (`IN1` to `IN4`). The mathematical formula is:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3} + \text{IN4}$$

The calculation is typically triggered as soon as a corresponding update event arrives at one or more of the input adapters. After successful calculation, the result, along with a trigger event, is forwarded via the output adapter `OUT`.

---

## Technical Features

- **Generic Nature:** The function block is declared as a generic function block (`GEN_AS_ADD`). This allows for flexible handling of different data types (e.g., `INT`, `REAL`, `DINT`), depending on how the underlying adapter types are defined.
- **Adapter Coupling:** By using unidirectional adapters, the risk of incorrect pin wiring in the 4diac IDE is reduced, as data and events are transmitted together in a single connection.
- ---

## State Overview

Since this is an algorithmic function block for calculations, the FB operates statelessly or event-driven:

1. **Waiting:** The function block waits for an update event at input adapters `IN1` to `IN4`.
2. **Calculation:** Upon arrival of an event, the current values of the inputs are added together.
3. **Output:** The new total value is written to adapter `OUT`, and the corresponding output event is triggered.

--

## Application Scenarios

- **Measurement Value Summation:** Summarizing four analog sensor values (e.g., flow rates or power) into a single total value.
- **Setpoint Generation:** Adding base setpoints with various correction or offset values in a cascade control system.
- **Structured Signal Processing:** Used in complex control architectures where a strict separation of logic and data flow is required through adapter structures.

---

## Comparison with Similar Components

Compared to a classic, standard `ADD` component (according to IEC 61131-3):

- **Advantage:** Reduced wiring effort in the graphical user interface, as separate event and data lines do not need to be drawn.
- **Disadvantage:** Requires the definition and use of the specific adapter type `adapter::types::unidirectional::AS`. Direct connection of standard data types (such as simple `REAL` or `INT` variables) without an adapter is not possible.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AS_ADD_4` is a specialized, highly efficient function block for modern, adapter-based programming in the 4diac IDE. It is ideally suited for applications that require a high degree of modularity and clarity in the signal flow and need to add four summands cleanly and efficiently.
