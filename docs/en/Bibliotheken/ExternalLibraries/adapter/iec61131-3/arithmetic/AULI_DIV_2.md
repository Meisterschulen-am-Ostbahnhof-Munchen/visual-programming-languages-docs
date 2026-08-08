# AULI_DIV_2

![AULI_DIV_2](./AULI_DIV_2.svg)

*No image available*

* * * * * * * * * *
## Introduction

The function block `AULI_DIV_2` is a generic function block (Generic FB) designed to perform arithmetic division (DIV). It is based on the IEC 61499 standard and utilizes the concept of adapters to efficiently transfer data and the associated control logic. The block is defined in the namespace `adapter::iec61131::arithmetic` and uses the generic class `GEN_AULI_DIV`.

## Interface Structure

### **Event Inputs**
This function block does not have direct, dedicated event inputs. Signal flow control and event processing are handled entirely via the connected adapters.


### **Event Outputs**
This function block does not have direct, dedicated event outputs. Event forwarding is handled via the output adapter.

### **Data Inputs**
There are no direct data inputs. The values for the calculation are provided via the input adapters.

### **Data Outputs**
There are no direct data outputs. The calculation result is provided via the output adapter.

### **Adapters**
All communication for this function block is implemented via adapters of type `AULI` (unidirectional):

* **IN1 (Socket)**:

* **Type**: `adapter::types::unidirectional::AULI`

* **Description**: First input of the division (dividend/counter).

* **IN2 (Socket)**:

**Type**: `adapter::types::unidirectional::AULI`

**Description**: Second input for division (divisor/denominator).

**OUT (Plug)**:

**Type**: `adapter::types::unidirectional::AULI`

**Description**: Output that provides the result of the division (quotient).

## Functionality

This module performs a mathematical division of the input values provided via the adapters. The formula is:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

Since this is a generic function block (`GEN_AULI_DIV`), it can adapt to various numeric data types at runtime or during instantiation in the 4diac IDE, provided these are supported by type `AULI`. The calculation is typically triggered by an update event on one of the input adapters (`IN1` or `IN2`). The result is then provided at the output adapter `OUT` along with a corresponding output event.


## Technical Features

* **Generic Nature**: The attribute `GenericClassName` with the value `'GEN_AULI_DIV'` makes the function block flexible and not rigidly tied to a single data type (such as only `REAL` or `INT`).

* **Encapsulation via Adapters**: Since no traditional event and data ports are used, the visual design in the function block diagram (FBD) remains very clear. The logical relationship between data and triggers is encapsulated in the `AULI` adapter.

* **Unidirectional Adapters**: The use of `unidirectional::AULI` indicates that the information flow is strictly unidirectional (from the sockets to the function block and from the function block to the plug).


* ## State Overview

Since this function block is a basic arithmetic function block, it typically exhibits simple, stateless behavior (i.e., it behaves like a classic Execution Control Chart (ECC) with a default state that reacts to input events):

1. **Waiting for Event**: The function block waits for an update event at `IN1` or `IN2`.

2. **Calculation**: Upon receiving an event, the division is performed.

3. **Result Transfer**: The calculated value is assigned to `OUT`, and the corresponding output event is triggered at the plug.

4. **Return**: The function block returns to the wait state.

*Note on Division by Zero:* Depending on the implementation of the runtime environment for the generic type `GEN_AULI_DIV`, mechanisms to prevent division by zero (e.g., outputting `NaN`, infinity, or intercepting via the adapter status) should be considered.

## Application Scenarios

* **Sensor Value Scaling**: Division of raw analog values by a scaling factor for conversion to physical units.

* **Ratio Measurement**: Calculation of ratios in process automation (e.g., flow rate ratio of two media).

* **Averaging**: Use in computational networks where total values need to be divided by a number.

* **Structured Architectures**: Use in systems that consistently rely on adapter-based communication to minimize the number of visible connection lines in the system model.


* ## Comparison with Similar Components

* **Standard `DIV` component**: A classic IEC 61131-3 / IEC 61499 `DIV` component uses direct data inputs (`IN1`, `IN2`) and event ports (`REQ`, `CNF`). The `AULI_DIV_2`, on the other hand, bundles these signals in adapters, which significantly simplifies wiring for complex signal structures.

* **Standard `DIV` component**: A classic IEC 61131-3 / IEC 61499 `DIV` component uses direct data inputs (`IN1`, `IN2`) and event ports (`REQ`, `CNF`). The `AULI_DIV_2`, however, bundles these signals in adapters, which significantly simplifies wiring for complex signal structures.

* * **Other AULI Arithmetic Blocks** (e.g., `AULI_ADD`, `AULI_SUB`): These use the same interface philosophy with sockets and plugs, but perform different mathematical operations.

## Conclusion

The `AULI_DIV_2` is a modern, modular function block for arithmetic division in Eclipse 4diac. Through the consistent use of unidirectional adapters, it promotes clean and well-organized software design in distributed control systems according to IEC 61499 by elegantly bundling data and control events.