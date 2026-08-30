# AULI_MUL_3

![AULI_MUL_3](./AULI_MUL_3.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block `AULI_MUL_3` is a generic function block (FB) designed for the arithmetic multiplication of three input values via unidirectional adapters. It is defined in the package `adapter::iec61131::arithmetic` and enables clean, adapter-based data processing within the 4diac environment.

## Interface Structure

### **Event Inputs**

*This function block has no direct event inputs. Control and event processing are handled via the connected adapters.*

### **Event Outputs**

*This function block has no direct event outputs. Events are forwarded via the output adapter.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AULI`): First input value (multiplicand 1) for multiplication.
- **IN2** (Type: `adapter::types::unidirectional::AULI`): Second input value (multiplicand 2) for multiplication.
- **IN3** (Type: `adapter::types::unidirectional::AULI`): Third input value (multiplicand 3) for multiplication.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AULI`): Output for the calculated product of the three input values.

---

## Functionality

The `AULI_MUL_3` function block performs a classic multiplication of the values provided by the three input adapters (`IN1`, `IN2`, and `IN3`). The calculation follows the mathematical formula:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

Since this is a generic function block (`GEN_AULI_MUL`) based on unidirectional adapters (`AULI`), the values and their corresponding update events are transmitted within the adapter connections. As soon as new data is received and signaled at the inputs, the calculation is performed, and the result is output via the output adapter `OUT`.

---

## Technical Features

- **Generic Type:** The function block is declared as a generic type (`GenericClassName` = `"GEN_AULI_MUL"`). This allows for flexible handling depending on the underlying data type of the adapters used.
- **Adapter Encapsulation:** By using adapters of type `AULI`, data and associated control flows (events) are bundled into a single connection, significantly reducing wiring complexity in the function block diagram.

**Unidirectionality:** The interfaces utilize a unidirectional profile, ensuring a clear flow of information from the inputs to the output.

---

## State Overview

The function block operates in an event-driven manner and has no internal, persistent state (stateless/combinatorial).

1. **Waiting for Update:** The function block waits for an update event at the input sockets (`IN1`, `IN2`, or `IN3`).
2. **Calculation:** Upon receiving an event, the current values are read and multiplied.

- ... 3. **Output:** The result is passed to the `OUT` plug and the corresponding output event is triggered.

---

## Application Scenarios

- **Volume Calculation:** Calculation of three-dimensional quantities (e.g., length × width × height) in process automation.
- **Scaling and Weighting:** Application of two consecutive scaling factors to a measured value (e.g., sensor value × calibration factor × unit conversion).
- **Power Calculation:** Three-phase or multi-stage calculations where three physical quantities must be combined multiplicatively.

---

## Comparison with Similar Blocks

- **Standard MUL (IEC 61131-3):** The classic `MUL` block uses direct data and event pins. `AULI_MUL_3` differs in that it has exactly three inputs, which are completely encapsulated by adapters (`AULI`), resulting in a more streamlined architecture.
- **AULI_MUL_2 (if present):** A hypothetical component with only two inputs. `AULI_MUL_3` eliminates the need for an entire cascading component when multiplying three values.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

`AULI_MUL_3` is an efficient auxiliary component for applications requiring a high degree of modularity. Through the consistent use of unidirectional adapters, it helps reduce "signal spaghetti" in complex 4diac applications and simplifies the multiplication of three variables.
