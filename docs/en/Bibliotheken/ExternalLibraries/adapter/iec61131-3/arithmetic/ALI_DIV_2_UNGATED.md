# ALI_DIV_2_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`ALI_DIV_2`](ALI_DIV_2.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![ALI_DIV_2_UNGATED](./ALI_DIV_2_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block `ALI_DIV_2_UNGATED` is a generic arithmetic function block for IEC 61499, designed for performing division operations. The unique feature of this block is the use of unidirectional adapters (`ALI`) instead of traditional data and event interfaces. This enables a modular and clear structuring of data flows within the 4diac IDE.

## Interface Structure

### **Event Inputs**

*This function block does not have direct event inputs. Execution is controlled via the connected adapters.*

### **Event Outputs**

*This function block does not have direct event outputs. Events are forwarded via the output adapter.*

### **Data Inputs**

*This function block has no direct data inputs.*

### **Data Outputs**

*This function block has no direct data outputs.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::ALI`): The dividend (numerator) of the division.
- **IN2** (Type: `adapter::types::unidirectional::ALI`): The divisor (denominator) of the division.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::ALI`): The result of the mathematical division ($OUT = IN1 / IN2$).

## Functionality

The function block `ALI_DIV_2_UNGATED` calculates the quotient of the values provided via the input adapters `IN1` and `IN2`. The result is passed to the output adapter `OUT`.

Since it is a generic function block (`GEN_ALI_DIV`), the block can flexibly work with various data types, provided the `ALI` adapters support them (e.g., integers or floating-point numbers). The actual calculation is triggered by the events defined in the adapter. As soon as new data is present at the inputs and a corresponding trigger signal is received via the adapter interface, the division is performed and the result is provided at the output.

Because it is a generic function block (`GEN_ALI_DIV`), the block can flexibly work with different data types, provided the `ALI` adapters support them (e.g., integers or floating-point numbers). The actual calculation is triggered by the events defined in the adapter. As soon as new data is present at the inputs and a corresponding trigger signal is received via the adapter interface, the division is performed and the result is provided at the output.

... ## Technical Features

- **Generic Implementation:** By assigning it to the generic class `GEN_ALI_DIV`, the function block is not limited to a fixed data type (such as `REAL` or `INT`). It dynamically adapts to the type definitions of the connected adapters.
- **Adapter Encapsulation:** The use of unidirectional `ALI` adapters drastically reduces cabling in the 4diac IDE, as data and associated trigger events are bundled and transmitted in a single connection.
- - **Division by Zero:** During implementation and in the runtime environment, care must be taken to handle the value of `0` at input `IN2` to prevent system crashes (e.g., by default returning `NaN`, infinity, or by intercepting the error via adapter error handling).

## State Overview

Since `ALI_DIV_2_UNGATED` is a data- and event-driven block, it does not have a complex internal state machine (no classic ECC). It behaves like a functional block:

1. **Waiting for Trigger:** The block waits for an update event at input adapters `IN1` or `IN2`.

2. **Calculation:** Upon signal reception, the data is read and divided

3. **Output:** The result is assigned to `OUT`, and the corresponding event is signaled via the output adapter.

## Application Scenarios

- **Signal Normalization and Scaling:** Division of sensor values by constant factors for unit conversion within an adapter-based control architecture.
- **Ratio Calculation:** Determination of ratios (e.g., fuel-air mixture, flow ratios) in process engineering plants.
- **Distributed Control Systems:** Use in complex IEC 61499 applications where a clean, modular signal flow is enforced via adapters.

## Comparison with Similar Function Blocks

Compared to a standard `DIV` function block according to IEC 61131-3 or IEC 61499, which uses classic data pins (`IN1`, `IN2`, `OUT`) and separate event pins (`REQ`, `CNF`), the `ALI_DIV_2_UNGATED` offers a significantly cleaner interface in the function block diagram through the use of adapters. It is particularly suitable for advanced software architectures that consistently leverage the advantages of adapters for structuring.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `ALI_DIV_2_UNGATED` is a highly efficient and flexible division block for modern IEC 61499 applications. Through the consistent use of generic types and the `ALI` adapter concept, it significantly contributes to the clarity, reusability, and maintainability of control software in the 4diac IDE.
