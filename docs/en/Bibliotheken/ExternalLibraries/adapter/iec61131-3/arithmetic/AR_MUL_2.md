# AR_MUL_2

![AR_MUL_2](./AR_MUL_2.svg)

*(No image available)*

* * * * * * * * * *

## Introduction

The function block (FB) **AR_MUL_2** is a generic arithmetic block for the 4diac IDE. It is used to multiply two values that are transmitted via unidirectional adapters. By encapsulating the mathematical operation in an adapter interface, this block enables clean, modular, and clear modeling of calculations within IEC 61499 applications.

## Interface Structure

The block does not have any classic event- or data-based inputs and outputs. All communication is handled via adapters.

### **Event Inputs**

*No direct event inputs available.* (Event control is implemented via the adapters.)

### **Event Outputs**

*No direct event outputs available.*

### **Data Inputs**

*No direct data inputs available.*

### **Data Outputs**

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AR`): First input value (multiplicand 1) for multiplication.
- **IN2** (Type: `adapter::types::unidirectional::AR`): Second input value (multiplicand 2) for multiplication.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AR`): Output for the calculated product of the multiplication ($OUT = IN1 \times IN2$).

---

## Functionality

As soon as new values or corresponding trigger events arrive via the input adapters `IN1` and `IN2`, the function block multiplies the values of the two inputs. The result of the mathematical operation ($IN1 \cdot IN2$) is immediately passed to the output adapter `OUT` and made available for subsequent function blocks.

Since this is a generic function block (`GEN_AR_MUL`), its implementation is flexible with respect to the specific data types used within the `AR` adapter structure.

---

## Technical Features

- **Generic Function Block:** The attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AR_MUL'` allows the function block to be used for various numeric data types, provided the adapters support them.
- **Unidirectional Adapters:** Using the type `unidirectional::AR` ensures a clean data flow without feedback loops, which increases application stability and minimizes latency.
- **Compiler Affiliation:** The function block is assigned to the package `adapter::iec61131::arithmetic` and conforms to the IEC 61499-2 standard.

- ---

## State Overview

Since this function block primarily operates via adapters using data flow control, it does not have a complex internal state diagram (ECC). It acts as a stateless transfer element:

1. **Waiting:** The block waits for data updates at the adapters `IN1` and/or `IN2`.
2. **Calculation:** When a value changes, the product is calculated.
3. **Output:** The result is directly forwarded to the output `OUT`.

--

## Application Scenarios

- **Measurement Scaling:** Multiplication of an analog sensor value (e.g., a voltage) by a scaling factor to convert it into a physical unit.
- **Signal Amplification:** Proportional amplification of control signals in process automation.
- **Mathematical Calculations:** Use as a modular component in more complex computational networks within 4diac applications.

---

## Comparison with Similar Components

Compared to standard multiplication components (such as the classic `MUL` component according to IEC 61131-3), which work with elementary data types (e.g., `INT`, `REAL`), `AR_MUL_2` uses structured **adapters**. This offers the following advantages:

- **Reduced Wiring Effort:** Signals and associated control events are bundled in a single adapter connection.
- **Improved Readability:** Complex control diagrams remain clear because fewer individual connections need to be drawn on the workspace.

---

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion

The `AR_MUL_2` function block is an efficient tool for arithmetic operations in modern, adapter-based control programs. Its encapsulation in unidirectional interfaces offers a high degree of reusability and ensures a clean and structured design within the 4diac environment.
