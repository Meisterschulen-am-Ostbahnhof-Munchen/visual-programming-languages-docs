# AS_ADD_3

![AS_ADD_3](./AS_ADD_3.svg)

**********

## Introduction

The function block `AS_ADD_3` is a generic function block (FB) for IEC 61499, designed to perform arithmetic addition of three input values. A key feature of this block is that it has no direct data or event inputs/outputs, but relies entirely on the use of unidirectional adapters. This significantly simplifies modeling and wiring in more complex systems.

## Interface Structure

### **Event Inputs**

This function block has no direct event inputs. Event control is handled via the connected adapters.

### **Event Outputs**

This function block has no direct event outputs. Events are forwarded via the output adapter.

### **Data Inputs**

There are no direct data inputs.

### **Data Outputs**

There are no direct data outputs.

### **Adapters**

The module communicates exclusively via adapter interfaces.

#### **Sockets (Inputs):**

- **IN1** (Type: `adapter::types::unidirectional::AS`): First input for addition.
- **IN2** (Type: `adapter::types::unidirectional::AS`): Second input for addition.
- **IN3** (Type: `adapter::types::unidirectional::AS`): Third input for addition.

#### **Plugs (Outputs):**

- **OUT** (Type: `adapter::types::unidirectional::AS`): Output providing the result of the addition (`IN1 + IN2 + IN3`).

---

## Functionality

The function block `AS_ADD_3` performs a classic addition:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

Since the block is defined as a generic function block (`GEN_AS_ADD`), it can process various numeric data types (e.g., `INT`, `REAL`, `DINT`) depending on the specific instantiation and the data type used in the adapter.

As soon as new values and their corresponding events are signaled at the input adapters (`IN1`, `IN2`, `IN3`), the function block calculates the sum and triggers the corresponding output event at the `OUT` adapter to pass the new value on to subsequent function blocks.

---

## Technical Features

- **Generic Type (Generic FB):** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AS_ADD'`. This allows for flexible adaptation to different data types without having to create a separate function block for each type.
- **Encapsulation via Adapters:** By using unidirectional adapters (`AS`), data and the associated trigger events are encapsulated in a single connection. This ensures a clean and uncluttered user interface design in the 4diac IDE.

---

## State Overview

The function block operates in an event-driven manner and does not have a complex internal state diagram (ECC). Its execution is triggered by the adapter events received at the sockets:

1. **Waiting:** The function block waits for an update event at the adapters `IN1`, `IN2`, or `IN3`.
2. **Calculation:** Upon receiving an event, the current values of the three inputs are added together.
3. **Output:** The result is created in the plug `OUT`, and an update event is sent via the adapter.

---

## Application Scenarios

- **Measurement Summing:** Addition of three analog sensor values (e.g., three flow meters to calculate a total flow rate).
- **Setpoint Offset Calculation:** Calculation of an overall setpoint based on a base setpoint, a user offset, and a correction value from a higher-level controller.
- **Signal Source Combination:** Combining three partial signals in process automation using standardized adapter structures.
- ---

## Comparison with Similar Components

- **Standard ADD Components (IEC 61131-3):** Classic ADD components use dedicated data pins (e.g., `IN1`, `IN2`) and separate event pins (`REQ`, `CNF`). `AS_ADD_3` minimizes the wiring effort in the FBD (Function Block Diagram) by using adapters.
- **AS_ADD_2 (Two-Way Adder):** Compared to a variant with only two inputs, the `AS_ADD_3` saves an entire component and the associated intermediate wiring when adding three values.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AS_ADD_3` is a highly efficient, modular component for adding three values. Thanks to the consistent use of unidirectional adapters, it integrates perfectly into modern, service-oriented, and well-structured IEC 61499 control applications.
