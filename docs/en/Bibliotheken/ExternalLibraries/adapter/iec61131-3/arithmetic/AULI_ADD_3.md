# AULI_ADD_3

![AULI_ADD_3](./AULI_ADD_3.svg)

*(Image of the function block temporarily unavailable)*

* * * * * * * * * *

## Introduction

The `AULI_ADD_3` function block is a generic arithmetic function block for IEC 61499 systems, specifically designed for adding three input values. Unlike traditional mathematical function blocks, this block uses `AULI` (unidirectional) adapter connections to transmit data and associated control signals in a bundled manner. This significantly reduces wiring complexity within the development environment (4diac IDE).

## Interface Structure

### **Event Inputs**

*No direct event inputs are defined.* Event-based control is handled implicitly via the connected adapters (`Sockets`).

### **Event Outputs**

*No direct event outputs are defined.* Event forwarding is encapsulated via the output adapter (`Plug`).

### **Data Inputs**

*No direct data inputs are available.* Data transfer occurs via the adapter interfaces.

### **Data Outputs**

*No direct data outputs are available.* The calculation result is provided via the output adapter.

### **Adapters**

#### **Sockets (Input Adapters)**

The sockets serve as receivers for the values to be added.

- **IN1** (Type: `adapter::types::unidirectional::AULI`): First addend of the arithmetic addition.
- **IN2** (Type: `adapter::types::unidirectional::AULI`): Second addend of the arithmetic addition.
- **IN3** (Type: `adapter::types::unidirectional::AULI`): Third addend of the arithmetic addition.

#### **Plugs (Output Adapters)**

The plug serves as a transmitter for the calculated result.

- **OUT** (Type: `adapter::types::unidirectional::AULI`): Output for the result of the addition ($IN1 + IN2 + IN3$).

---

## Functionality

As soon as new data is signaled at the input adapters (`IN1`, `IN2`, `IN3`), the function block performs the mathematical addition.

The underlying formula is:

$$\text{OUT} = \text{IN1} + \text{IN2} + \text{IN3}$$

The calculated result is immediately passed to the output adapter `OUT` and is available to subsequent function blocks. Since these are unidirectional adapters, the data stream flows exclusively from the sockets to the plug.

--

## Technical Features

- **Generic Function Block:** The function block is declared as a generic type in the 4diac IDE (`GenericClassName = 'GEN_AULI_ADD'`). This enables flexible processing of various data types (e.g., INT, REAL, LREAL), supported by the definition of the `AULI` adapter.
- **Adapter Encapsulation:** Using adapters instead of standard data and event channels makes the system design more modular and transparent.
- **Resource Efficiency:** Computations are performed directly based on adapter events, ensuring high-performance execution.

---

## State Overview

The function block operates as a stateless (or purely event-driven) arithmetic block:

1. **Ready (Idle):** The block waits for value changes or trigger signals at the input adapters `IN1`, `IN2`, or `IN3`.

**Resource Efficiency:** Computations are performed directly based on adapter events, ensuring high performance.

---

**The function block operates as a stateless (or purely event-driven) arithmetic block:**

**Ready (Idle):** The block waits for value changes or trigger signals at the input adapters `IN1`, `IN2`, or `IN3`. 2. **Evaluation:** After a signal arrives, the values are read and summed.

1. **Output:** The sum is passed to `OUT`, and the corresponding event in the adapter is triggered. The function block immediately returns to the *Ready* state.

---

## Application Scenarios

- **Measurement Summing:** Summarizing three analog measurements (e.g., three partial currents to determine the total current) in process automation.
- **Setpoint Generation:** Adding base setpoints with two different correction or offset values.
- **Structured Data Processing:** Used in complex IEC 61499 control applications where consistent use of adapters is required to improve clarity.

---

## Comparison with Similar Components

- **Standard Adder (IEC 61131-3):** The classic `ADD` component requires explicit `REQ` and `CNF` event lines, as well as individual data lines. `AULI_ADD_3` replaces these with just four adapter connections, which simplifies the visual programming interface.
- **Cascaded Adders (e.g., 2x `AULI_ADD_2`):** To add three values with classic two-way adders, two components would have to be connected in series. `AULI_ADD_3` eliminates the need for an entire function block and the associated intermediate wiring.

- ---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AULI_ADD_3` is a practical and modern function block for structured programming in 4diac. Thanks to the consistent use of the unidirectional `AULI` adapter, it is ideally suited for clean, clear, and maintainable architectures in distributed control systems according to the IEC 61499 standard.
