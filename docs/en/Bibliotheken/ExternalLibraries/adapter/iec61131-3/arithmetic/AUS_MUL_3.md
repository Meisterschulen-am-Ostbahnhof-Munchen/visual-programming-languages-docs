# AUS_MUL_3

![AUS_MUL_3](./AUS_MUL_3.svg)

* * * * * * * * * *

The function block (FB) `AUS_MUL_3` is used for the arithmetic multiplication of three input values. It is a generic function block (`Generic FB`) based on the use of unidirectional adapters of type `AUS`. The block calculates the product of three input values and provides the result at an output adapter.

Since this function block is entirely based on adapters, it has no direct, traditional event or data interfaces at the block level. All communication and synchronization takes place via the declared adapters.

*No direct event inputs available.* (Event control is handled via the adapter sockets).

*No direct event outputs available.* (Event control is handled via the adapter plug).

*No direct data inputs available.*

*No direct data outputs available.*

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::AUS`): The first multiplicand for the arithmetic operation.
* **IN2** (Type: `adapter::types::unidirectional::AUS`): The second multiplicand for the arithmetic operation.
* **IN3** (Type: `adapter::types::unidirectional::AUS`): The third multiplicand for the arithmetic operation.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AUS`): The calculated result of the multiplication ($OUT = IN1 × IN2 × IN3$).

## Functionality

As soon as new values are present at the input adapters (`IN1`, `IN2`, `IN3`) and a corresponding trigger event is transmitted via the adapters, the function block executes the multiplication.

The mathematical formula is:

$$\text{Result} = \text{Value of IN1} \times \text{Value of IN2} \times \text{Value of IN3}$$

The calculated result, along with a corresponding confirmation event, is passed to subsequent program components via the output plug `OUT`.

* **Generic Module:** The attribute `GenericClassName` with the value `'GEN_AUS_MUL'` allows for flexible use of the module. Depending on the specific implementation of the adapter type `AUS`, the function block can adapt to various data types (e.g., `INT`, `REAL`, `LREAL`).
* **Encapsulation by Adapter:** The use of unidirectional adapters (`unidirectional::AUS`) drastically reduces the routing of individual event and data lines in the 4diac IDE. This results in a cleaner and more organized application design.
* ## State Overview

The module behaves in a purely stateless manner (i.e., it reacts to incoming adapter signals in an event-driven manner):

1. **Wait State:** The module waits for an update event at sockets `IN1`, `IN2`, or `IN3`.
2. **Calculation:** Upon receiving an event, the data values of the three input adapters are read and multiplied together.
3. **Output:** The result is written to plug `OUT`, and the corresponding send event of the plug is triggered.
* **Scaling and Weighting:** Multiplication of a sensor value by two consecutive scaling factors (e.g., physical conversion and calibration factor).
* **Volume Calculation:** Calculating three-dimensional volume or flow rate where three parameters (e.g., length × width × height or three different rates) must be directly multiplied together.
* **Structured Signal Processing:** Used in more complex control loops that require a clean signal architecture using adapters.
* **Standard MUL Component (IEC 61131-3):** The classic `MUL` component uses direct data and event pins. The `AUS_MUL_3`, on the other hand, bundles these signals in adapters, simplifying wiring in large projects.
* **AUS_MUL_2 (Two-Input Variant):** While a hypothetical two-input variant can only multiply two factors, `AUS_MUL_3` eliminates the need for an additional cascading block when multiplying three values.

The `AUS_MUL_3` is a highly efficient, generic function block for multiplying three values. Its consistent use of unidirectional adapters makes it ideally suited for modern, adapter-based software architectures in the 4diac environment, as it minimizes the visual complexity of control diagrams.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion