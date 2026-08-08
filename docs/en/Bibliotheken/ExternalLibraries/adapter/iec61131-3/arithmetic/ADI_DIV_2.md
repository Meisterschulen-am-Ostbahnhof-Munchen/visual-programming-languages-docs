# ADI_DIV_2

![ADI_DIV_2](./ADI_DIV_2.svg)

* * * * * * * * * *
The function block `ADI_DIV_2` performs an arithmetic division (DIV) of two input values via adapter connections. It is a generic function block (Generic FB) based on type `GEN_ADI_DIV`. The consistent use of unidirectional adapters of type `ADI` ensures clean encapsulation of data and events. This simplifies application design in the 4diac IDE, as the number of visible connection lines is significantly reduced.

Since this function block operates entirely on an adapter basis, it does not have traditional, discrete event or data connections at the top level. All interaction takes place via the adapter interfaces.


*No direct event inputs are available. Event control is handled via the input adapters (`IN1`, `IN2`).*

*No direct event outputs are available. Event output is handled via the output adapter (`OUT`).*

*No direct data inputs are available.*

*No direct data outputs are available.*

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**
* **Sockets (Input Adapters):**

* **`IN1`** (Type: `adapter::types::unidirectional::ADI`): First input value (dividend/counter) for division.

* **`IN2`** (Type: `adapter::types::unidirectional::ADI`): Second input value (divisor/denominator) for the division.

* **Plugs (Output Adapters):**

* **`OUT`** (Type: `adapter::types::unidirectional::ADI`): The calculated result (quotient) of the division.

## Functionality
The function block divides the value received via adapter `IN1` by the value received via adapter `IN2`:

$$\text{Result (OUT)} = \frac{\text{Value of IN1}}{\text{Value of IN2}}$$

The calculation is triggered as soon as corresponding update events are received at the input adapters. After successful calculation, the new quotient, along with an output event, is passed via the adapter `OUT`. Due to the generic nature of the function block (`GEN_ADI_DIV`), its behavior adapts to the underlying data types of the `ADI` adapters used.

* **Generic Instantiation:** The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_ADI_DIV'`. This allows for flexible typing at runtime, depending on the adapter subtype used.

* **Adapter Encapsulation:** Data and the associated trigger events are bundled in the adapter type `ADI`, which facilitates loose coupling of the software components.

* **Division by Zero:** During implementation and use, it is essential to ensure that the value at adapter `IN2` (divisor) is not zero. Division by zero must be handled in an application-oriented manner before the function block to prevent runtime errors.

The function block behaves in a stateless (i.e., purely reactive) manner:

1. **Wait State:** The function block waits for events at sockets `IN1` or `IN2`.

2. **Calculation:** After receiving valid data/events at the inputs, the division is performed.

3. **Update:** The result is passed to output plug `OUT`, and the corresponding send event is triggered.



* **Measurement Scaling:** Normalization of analog sensor values (e.g., dividing a raw value by a scaling factor).

* **Calculation of Ratios:** Determination of mixing ratios or percentages in process engineering plants.

* **Average Calculations:** Division of a sum by the number of recorded values in simple mathematical computational networks.


* ## Comparison with Similar Function Blocks

Compared to a classic, standard `DIV` function block (according to IEC 61131-3), which uses discrete data pins (`IN1`, `IN2`, `OUT`) and explicit event pins (`REQ`, `CNF`):

* **Advantages of `ADI_DIV_2`:** Significantly cleaner appearance in the 4diac function block diagram (FBD). Data consistency is directly enforced through the coupling in the adapter.

* **Disadvantages:** Direct use with standard data streams without adapter encapsulation is not possible. Dedicated converter modules must be used if the signal source does not support adapters.

`ADI_DIV_2` is a specialized and efficient module for modern IEC 61499 architectures within 4diac. It is ideally suited for developers who rely on a clean, adapter-based, and modular software architecture and want to implement mathematical division in a clear and concise manner.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion