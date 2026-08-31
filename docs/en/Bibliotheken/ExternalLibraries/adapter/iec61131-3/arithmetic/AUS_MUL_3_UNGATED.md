# AUS_MUL_3_UNGATED

> ℹ️ **UNGATED variant:** This block is the ungated version of [`AUS_MUL_3`](AUS_MUL_3.md). It suppresses **no** unchanged repeats – every newly computed result is forwarded unconditionally, even without a value change. This matters for consumers that need a periodic cadence regardless of value change (e.g. derivative/frequency calculations that would otherwise fail to decay toward zero). Any change-detection/gating statements further down this page do **not** apply to this block.

![AUS_MUL_3_UNGATED](./AUS_MUL_3_UNGATED.svg)

* * * * * * * * * *

## Introduction

The function block (FB) `AUS_MUL_3_UNGATED` is used for the arithmetic multiplication of three input values. It is a generic function block (`Generic FB`) based on the use of unidirectional adapters of type `AUS`. The block calculates the product of three input values and provides the result at an output adapter.

Since this function block is entirely based on adapters, it has no direct, traditional event or data interfaces at the block level. All communication and synchronization takes place via the declared adapters.

## Interface Structure

### Event Inputs

*No direct event inputs available.* (Event control is handled via the adapter sockets).

### Event Outputs

*No direct event outputs available.* (Event control is handled via the adapter plug).

### Data Inputs

*No direct data inputs available.*

### Data Outputs

*No direct data outputs available.*

### **Adapters**

#### **Sockets (Input Adapters)**

- **IN1** (Type: `adapter::types::unidirectional::AUS`): The first multiplicand for the arithmetic operation.
- **IN2** (Type: `adapter::types::unidirectional::AUS`): The second multiplicand for the arithmetic operation.
- **IN3** (Type: `adapter::types::unidirectional::AUS`): The third multiplicand for the arithmetic operation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AUS`): The calculated result of the multiplication ($OUT = IN1 × IN2 × IN3$).

## Functionality

As soon as new values are present at the input adapters (`IN1`, `IN2`, `IN3`) and a corresponding trigger event is transmitted via the adapters, the function block executes the multiplication.

The mathematical formula is:

$$\text{Result} = \text{Value of IN1} \times \text{Value of IN2} \times \text{Value of IN3}$$

The calculated result, along with a corresponding confirmation event, is passed to subsequent program components via the output plug `OUT`.

## Technical Features

- **Generic Module:** The attribute `GenericClassName` with the value `'GEN_AUS_MUL'` allows for flexible use of the module. Depending on the specific implementation of the adapter type `AUS`, the function block can adapt to various data types (e.g., `INT`, `REAL`, `LREAL`).
- **Encapsulation by Adapter:** The use of unidirectional adapters (`unidirectional::AUS`) drastically reduces the routing of individual event and data lines in the 4diac IDE. This results in a cleaner and more organized application design.

## State Overview

The module behaves in a purely stateless manner (i.e., it reacts to incoming adapter signals in an event-driven manner):

## Application Scenarios

1. **Wait State:** The module waits for an update event at sockets `IN1`, `IN2`, or `IN3`.
2. **Calculation:** Upon receiving an event, the data values of the three input adapters are read and multiplied together.
3. **Output:** The result is written to plug `OUT`, and the corresponding send event of the plug is triggered.

## Comparison with Similar Function Blocks

- **Scaling and Weighting:** Multiplication of a sensor value by two consecutive scaling factors (e.g., physical conversion and calibration factor).
- **Volume Calculation:** Calculating three-dimensional volume or flow rate where three parameters (e.g., length × width × height or three different rates) must be directly multiplied together.
- **Structured Signal Processing:** Used in more complex control loops that require a clean signal architecture using adapters.
- **Standard MUL Component (IEC 61131-3):** The classic `MUL` component uses direct data and event pins. The `AUS_MUL_3_UNGATED`, on the other hand, bundles these signals in adapters, simplifying wiring in large projects.
- **AUS_MUL_2 (Two-Input Variant):** While a hypothetical two-input variant can only multiply two factors, `AUS_MUL_3_UNGATED` eliminates the need for an additional cascading block when multiplying three values.

## Change Detection

This block performs **no** change detection. Every newly computed result is written to the output and its adapter event fired unconditionally, regardless of whether the value differs from the previous run.

## Conclusion

The `AUS_MUL_3_UNGATED` is a highly efficient, generic function block for multiplying three values. Its consistent use of unidirectional adapters makes it ideally suited for modern, adapter-based software architectures in the 4diac environment, as it minimizes the visual complexity of control diagrams.
