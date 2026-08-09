# AI_DIV_2

![AI_DIV_2](./AI_DIV_2.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AI_DIV_2` is a generic arithmetic block for the 4diac platform. It is used to perform mathematical division (DIV) of two analog values. Unlike classic arithmetic blocks, this block uses standardized, unidirectional adapters of type `AI` (Analog Input) for its inputs and outputs. This enables structured, modular, and clear signal wiring within IEC 61499 applications.

## Interface Structure

### **Event Inputs**

The block does not have direct event inputs. Synchronization and event control are handled implicitly via the connected adapters.

### **Event Outputs**

This function block has no direct event outputs.

### **Data Inputs**

There are no direct data inputs. Data transmission is handled entirely via the adapter interfaces.

### **Data Outputs**

There are no direct data outputs.

### **Adapter**

| Name | Type | Interface Type | Description |
| :--- | :--- | :--- | :--- |
| **IN1** | `adapter::types::unidirectional::AI` | Socket | First Input Value (Dividend) |
| **IN2** | `adapter::types::unidirectional::AI` | Socket | Second Input Value (Divisor) |
| **OUT** | `adapter::types::unidirectional::AI` | Plug | Result of Division (Quotient) |

---

## Functionality

The function block calculates the quotient of the values of the two input adapters:

$$OUT = \frac{IN1}{IN2}$$

As soon as the values at sockets `IN1` or `IN2` change and a corresponding update event is received via the adapter, the division is performed. The result and the associated update event are immediately forwarded to the output adapter `OUT` (plug).

Due to its generic type (`GEN_AI_DIV`), the function block is not limited to a specific data type (such as `REAL` or `INT`). The specific data type is determined flexibly during instantiation in the 4diac IDE.

---

## Technical Features

- **Generic Typing:** The function block can be used polymorphically via the attribute `GenericClassName` with the value `GEN_AI_DIV` and can work with various compatible analog data types.
- **Adapter Encapsulation:** By using unidirectional adapters (`unidirectional::AI`), data and event lines are bundled into a single connection. This reduces the risk of wiring errors and improves clarity in the function block diagram (FBD).
- **Division by Zero:** Since this is a mathematical division, the system or upstream logic must ensure that the value at `IN2` is not zero to avoid calculation errors or division-by-zero exceptions at runtime.

---

## State Overview

The function block `AI_DIV_2` is a stateless combination block. It does not have an internal Execution Control Chart (ECC). Every event at the input adapters directly triggers the calculation and update of the output adapter.

---

## Application Scenarios

- **Ratio Calculations:** Determining ratios in process engineering plants (e.g., air-fuel ratio or mixing ratios of liquids).
- **Scaling and Normalization:** Dividing an analog raw value (e.g., sensor reading) by a scaling factor to convert it into physical units.
- **Measurement Averaging:** Used in computing networks where sum values need to be divided by a fixed or variable number.

---

## Comparison with Similar Components

- **Standard Arithmetic Component (DIV):** A classic `DIV` component of IEC 61131-3 / IEC 61499 operates with direct PIN inputs (e.g., `IN1`, `IN2` as `REAL`) and separate event pins (`REQ`, `CNF`). `AI_DIV_2`, on the other hand, bundles these signals into adapters, enabling cleaner interface separation in complex signal paths.
- **AI_SUB_2 / AI_ADD_2:** These modules share the same adapter philosophy but perform subtractions and additions, respectively, instead of division.

---

## Conclusion

The `AI_DIV_2` is a highly efficient and modern auxiliary module for analog signal processing in 4diac. Through the consistent use of adapters, it integrates seamlessly into service-oriented control architectures and minimizes the implementation and testing effort for basic mathematical operations.