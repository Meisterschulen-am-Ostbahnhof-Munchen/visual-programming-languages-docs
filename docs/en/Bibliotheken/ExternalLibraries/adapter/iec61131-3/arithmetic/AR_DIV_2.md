# AR_DIV_2

![AR_DIV_2](./AR_DIV_2.svg)

* * * * * * * * * *

The function block `AR_DIV_2` is a generic arithmetic block designed for performing division operations (`DIV`) in IEC 61499-based systems. Unlike traditional function blocks, this block uses adapters (`unidirectional::AR`) to bundle data and events. This results in clearer and more modular visual programming within the 4diac IDE.

Since it is a purely adapter-based function block, `AR_DIV_2` has no direct, traditional data or event inputs and outputs at the main level. All communication is handled via adapters.

*No direct event inputs available.* (Event control is implicit via the input adapters).

*No direct event outputs available.* (Event control is implicit via the output adapter).

*No direct data inputs available.* (Data is transferred via the input adapters).

*No direct data outputs available.* (Data is transferred via the output adapter).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Type | Name | Adapter Type | Description |
| :--- | :--- | :--- | :--- |
| **Socket** (Input) | `IN1` | `adapter::types::unidirectional::AR` | First input value (dividend) for the division. |
| **Socket** (Input) | `IN2` | `adapter::types::unidirectional::AR` | Second input value (divisor) for the division. |
| **Plug** (Output) | `OUT` | `adapter::types::unidirectional::AR` | The result of the division (quotient). |

## Functionality

This function block performs a mathematical division of the values provided via the adapters. As soon as an update event at the input adapters (`IN1` or `IN2`) signals that new data is available, the calculation is triggered:

$$\text{OUT} = \frac{\text{IN1}}{\text{IN2}}$$

The calculated result is then passed to the output adapter `OUT`, and the corresponding send event of the adapter is triggered to inform subsequent function blocks about the new value.

- **Generic Type (`GEN_AR_DIV`):** The function block is internally declared as a generic type. This allows for flexible adaptation to various data types (e.g., `REAL`, `LREAL`, `INT`), depending on how the underlying `AR` adapter type is defined.
- **Adapter Coupling:** Using unidirectional adapters (`unidirectional::AR`) drastically reduces the number of connection lines in the function block diagram, improving the readability of complex mathematical calculations.
- **Protection Against Division by Zero:** System-integrated protection measures depend on the specific runtime environment. When using the function block, ensure that the divisor (`IN2`) is not zero to avoid calculation errors or runtime crashes.

- ## State Overview

The function block is essentially stateless and reacts in an event-driven manner:

1. **Wait State (Idle):** The function block waits for an update event at the adapters `IN1` or `IN2`.
2. **Calculation:** After an event arrives, the division is performed.
3. **Update:** The result is applied to `OUT`, and the output event is triggered. The function block immediately returns to the wait state.

- **Measurement Scaling:** Division of raw sensor data by a fixed scaling factor for conversion into physical units.
- **Average Calculation:** Division of a sum by the number of measured values in more complex computational networks.
- **Ratio Calculations:** Determining percentages or ratios in process engineering plants.
- **Classic `DIV` Module:** The classic IEC 61131-3 `DIV` module has dedicated pins for `IN1`, `IN2`, and `OUT`, as well as the corresponding `REQ` and `CNF` events. `AR_DIV_2` bundles these signals in adapters, simplifying wiring in large projects.
- **`AR_MUL_2` / `AR_ADD_2`:** These function blocks share the same adapter philosophy but perform multiplications and additions, respectively. They can be seamlessly chained with `AR_DIV_2` to form mathematical calculation trees.

The `AR_DIV_2` is a highly efficient, modular function block for arithmetic division. Through the consistent use of adapters, it is ideally suited for clean, well-organized software architectures in distributed automation according to the IEC 61499 standard.

## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion
