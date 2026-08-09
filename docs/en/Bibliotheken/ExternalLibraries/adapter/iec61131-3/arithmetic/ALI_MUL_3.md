# ALI_MUL_3

![ALI_MUL_3](./ALI_MUL_3.svg)

*No image available. The function block is graphically represented with three input sockets (IN1, IN2, IN3) and one output plug (OUT).*

* * * * * * * * * *

The `ALI_MUL_3` function block is a generic arithmetic block for the 4diac IDE, used for multiplying three input values. It is characterized by the fact that the inputs and outputs are not implemented via classic data and event pins, but entirely via unidirectional adapters of type `ALI`. This enables structured, modular, and clear encapsulation of signal and data flows in IEC 61499 applications.

Since this functional block is entirely based on adapter technology, it has no direct, traditional event or data channels at the main level.

*No direct event inputs are available (signal processing is handled by the adapters).*

*No direct event outputs are available (signal forwarding is handled by the output adapter).*

*No direct data inputs are available.*

*No direct data outputs are available.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

#### **Sockets (Inputs)**

* **IN1** (Type: `adapter::types::unidirectional::ALI`): The first factor (multiplicand 1) for arithmetic multiplication.
* **IN3** (Type: `adapter::types::unidirectional::ALI`): The third factor (multiplicand 3) for arithmetic multiplication.

#### **Plugs (Outputs)**

* **OUT** (Type: `adapter::types::unidirectional::ALI`): The result of the multiplication (product).

---

## Functionality

The primary task of `ALI_MUL_3` is to calculate the product of three values:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3}$$

The calculation timing and the transfer of values are controlled by the `ALI` adapters. As soon as a corresponding trigger event is signaled via the input adapters, the function block reads the values from sockets `IN1`, `IN2`, and `IN3`, calculates the mathematical product, and provides the result at plug `OUT`, whereupon a corresponding output event is initiated.

---

* **Generic Building Block:** The attribute `GenericClassName` with the value `'GEN_ALI_MUL'` makes the function block data-type independent. It can be used for various numeric data types (e.g., `INT`, `REAL`, `LREAL`) depending on the specific `ALI` adapter used.
* **Clean Design:** The use of adapters significantly reduces wiring complexity in the function block diagram (FBD) because control and data flow are combined in a single connection.
* * **Unidirectional Adapters:** Since this is the `adapter::types::unidirectional` package, data and triggers flow directly from the sockets (`IN1`-`IN3`) to the plug (`OUT`).

---

The function block behaves like a classic, stateless mathematical operator (combinatorial behavior):

* **Readiness:** The block waits for incoming update events at the adapters `IN1`, `IN2`, or `IN3`.
* **Calculation:** When triggered, the multiplication is performed.
* * **Output:** The result is directly passed to output `OUT`, triggering the subsequent function block.

---

* **Calculation of Physical Quantities:** Determining volumes (length × width × height) or three-dimensional scales in factory automation.
* **Cascaded Gain Factors:** Multiplication of three different gain factors or correction values in control loops (e.g., sensor value × calibration factor × scaling factor).
* **Signal Processing:** Combining multiple weighting factors in process monitoring.
* ---

Compared to a standard IEC 61131-3 `MUL` component:

* **Classic `MUL` block:** Requires explicit `REQ` and `CNF` events, as well as individual data pins for each operand. This quickly leads to complex schematics with multiple inputs.
* **`ALI_MUL_3`:** Consolidates the interfaces into four clearly arranged adapter connections. Furthermore, it is designed for exactly three inputs, eliminating the need for an intermediate stage (cascading two 2x multipliers).

---

The `ALI_MUL_3` is a modern and highly efficient function block for mathematical operations in the 4diac environment. Through the consistent use of unidirectional adapters, it promotes clean, modularized software design and is ideally suited for complex calculations with three input variables.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion