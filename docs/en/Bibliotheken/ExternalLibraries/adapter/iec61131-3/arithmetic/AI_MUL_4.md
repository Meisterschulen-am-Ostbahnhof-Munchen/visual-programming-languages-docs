# AI_MUL_4

![AI_MUL_4](./AI_MUL_4.svg)

* * * * * * * * * *

The function block `AI_MUL_4` is a generic arithmetic function block for 4diac-IDE, compliant with the IEC 61131-3 standard. Its primary function is to calculate the mathematical product of four analog input values. The block utilizes unidirectional adapters of type `AI` (Analog Input) to transmit both data and the associated events in encapsulated form. This significantly reduces the wiring effort in the function block diagram and ensures a cleaner structure for the control logic.


The function block does not have direct, independent event inputs. Event control is handled entirely via the connected adapters.


This function block does not have direct, independent event outputs. Subsequent blocks are triggered via the output adapter.

There are no direct data inputs. Values are provided via the adapter inputs.

There are no direct data outputs. The calculated value is output via the adapter output.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**

#### **Sockets (Input Adapters)**

* **IN1** (Type: `adapter::types::unidirectional::AI`): First multiplicand.

* **IN2** (Type: `adapter::types::unidirectional::AI`): Second multiplicand.

* **IN3** (Type: `adapter::types::unidirectional::AI`): Third multiplicand.

* **IN4** (Type: `adapter::types::unidirectional::AI`): Fourth multiplicand.

#### **Plugs (Output Adapters)**

* **OUT** (Type: `adapter::types::unidirectional::AI`): Product of the multiplication of all four inputs ($OUT = IN1 \cdot IN2 \cdot IN3 \cdot IN4$).

## Functionality

As soon as a new event is signaled at one of the input adapters (`IN1` to `IN4`) indicating that the data has been updated, the function block reads the analog values of the four adapters.


The calculation is performed according to the formula:

$$\text{Result} = \text{Value}(IN1) \cdot \text{Value}(IN2) \cdot \text{Value}(IN3) \cdot \text{Value}(IN4)$$

The result of this calculation is passed to the output adapter `OUT`, and the corresponding update event of the adapter is triggered to inform subsequent blocks in the control flow about the new value.


* **Generic Class:** The block is internally based on the generic class `GEN_AI_MUL`. This enables flexible processing of data streams independent of specific hardware implementations.

* **Unidirectional Adapters:** By using the type `adapter::types::unidirectional::AI`, data and trigger signals flow in only one direction (from sender to receiver). This simplifies signal design and avoids feedback loops.

* **Compact Structure:** Processing four inputs in a single function block eliminates the need to cascade multiple multiplication blocks.


Since `AI_MUL_4` is a purely mathematical, data- and event-driven function block, it does not have an internal state machine (ECC). Its execution is purely stateless:

1. **Wait:** The function block waits for an update event at one of the sockets (`IN1` to `IN4`).

2. **Calculate:** Upon triggering, the current values of all four inputs are multiplied.

3. **Output:** The result is applied to the plug `OUT`, and the output event is triggered. The module immediately returns to standby mode.


* **Scaling and Calibration:** Calculation of compound correction factors for analog sensor values (e.g., sensor value \cdot $ calibration factor \cdot $ temperature compensation \cdot $ unit conversion).

* **Physical Calculations:** Calculation of values that depend on multiple analog factors, such as volumetric flow rates or electrical power, taking into account different efficiencies.

* **Cascaded Gains:** Use in control loops where multiple gains must be applied sequentially to an analog signal.


* ## Comparison with Similar Function Blocks

* **Standard MUL (IEC 61131-3):** Classic multiplication function blocks typically only work with elementary data types (e.g., `REAL`, `INT`) and require separate event lines (`REQ` / `CNF`). Furthermore, they often only support two inputs by default. `AI_MUL_4`, on the other hand, directly processes four inputs and uses adapters for encapsulation, resulting in a clearer network layout.

* **AI_MUL_2:** A similar adapter-based function block, but only for two inputs. `AI_MUL_4` saves additional wiring effort and function block instances for more complex calculations with up to four factors.



The `AI_MUL_4` function block offers an efficient and clean way to implement complex multiplication tasks with up to four analog signals in 4diac-IDE. The consistent use of unidirectional adapters minimizes cabling effort and significantly improves the readability of the application design.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion