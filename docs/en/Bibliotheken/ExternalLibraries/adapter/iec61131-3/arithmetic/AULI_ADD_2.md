# AULI_ADD_2

       +-------------------------------+
|          AULI_ADD_2           |
|                               |
 IN1 ==| (Socket)               (Plug) |== OUT
|                               |
IN2 ==| (Socket)                      |
       +-------------------------------+

![AULI_ADD_2](./AULI_ADD_2.svg)

* * * * * * * * * *
The function block `AULI_ADD_2` is a generic arithmetic block for the IEC 61499 environment (4diac-ide). It performs the mathematical addition of two input values transmitted via standardized, unidirectional adapters. The calculated result is passed to a corresponding output adapter.

The block does not have any classic, discrete event or data inputs at the top level. All communication and value transmissions are handled via adapters.

*No direct event inputs are available.* (Event control is encapsulated within the adapters).

*No direct event outputs are available.* (Event control is encapsulated within the adapters).

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

- **IN1** (Type: `adapter::types::unidirectional::AULI`):

The first addend for the addition operation.

- **IN2** (Type: `adapter::types::unidirectional::AULI`):

The second addend for the addition operation.

#### **Plugs (Output Adapters)**

- **OUT** (Type: `adapter::types::unidirectional::AULI`):

The result of the addition ($OUT = IN1 + IN2$).

## Functionality

The function block `AULI_ADD_2` performs a classic addition operation. As soon as values change at the input adapters `IN1` or `IN2`, or a corresponding update event is triggered via the adapters, the function block calculates the sum of the transmitted values:

$$ Result = Value(IN1) + Value(IN2)$$

This result, along with the associated update event, is then forwarded to subsequent function blocks via the output plug `OUT`.

- **Generic Nature:** The function block is declared as qzmsdocs0000010qz via the attribute `GenericClassName`. This allows for flexible typing depending on the specific implementation of the `AULI` adapter data used.
- **Adapter Encapsulation:** Using adapters of type `unidirectional::AULI` reduces the complexity of control circuit diagrams because data and associated trigger events are bundled in a single connection.

Since this function block is a purely functional/mathematical coupler, it typically does not have a complex internal state machine (ECC). Its execution is purely data- or event-driven based on the incoming adapter signals:

1. **Idle State:** The function block waits for signal updates at `IN1` or `IN2`.
2. **Evaluate:** When an event is received at one of the sockets, the data values are added.
3. **Output (Propagate):** The added value is output via the plug `OUT`, triggering the corresponding event.
- **Measurement Aggregation:** Addition of two analog process values (e.g., two parallel flow sensors to determine the total flow rate).
- **Setpoint Offset:** Applying a correction value or offset (via `IN2`) to a primary setpoint (via `IN1`).
- **Signal Bundling:** Structured mathematical signal processing in complex plant control systems using standardized adapter interfaces to reduce wiring effort.
- ## Comparison with Similar Components

Compared to a standard add-in component (such as the IEC 61131-3 compliant `ADD` component), which uses discrete pins for `REQ`, `CNF`, `IN1`, `IN2`, and `OUT`, the `AULI_ADD_2` eliminates the need for explicit wiring of control flows (events) and data lines. This significantly improves clarity in the 4diac development environment, as only a single adapter line needs to be drawn per signal source.

The `AULI_ADD_2` is a highly efficient, modular auxiliary component for analog signal processing. Through the consistent use of unidirectional adapters, it facilitates the design of cleanly structured and maintainable control applications according to the IEC 61499 standard.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion
