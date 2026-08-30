# ALI_MUL_2

![ALI_MUL_2](./ALI_MUL_2.svg)

*(No image available)*

* * * * * * * * * *
The function block `ALI_MUL_2` is used to perform an arithmetic multiplication of two values. It is a generic function block designed for a clean and modular architecture in IEC 61499 systems. Instead of classic discrete data and event ports, this block uses unidirectional adapters to transmit control events and data values in a bundled manner.

There are no direct event inputs. Event control is integrated into the input adapters.

There are no direct event outputs. Event control is integrated into the output adapter.

There are no direct data inputs. Data transmission occurs via the adapters.

There are no direct data outputs. Data transmission occurs via the output adapter.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- **Sockets (Input Adapters):**
- `IN1` (Type: `adapter::types::unidirectional::ALI`): First input for multiplication (multiplicand).
- `IN2` (Type: `adapter::types::unidirectional::ALI`): Second input for multiplication (multiplier).
- **Plugs (Output Adapters):**
- `OUT` (Type: `adapter::types::unidirectional::ALI`): Output for the result of the multiplication (product).

## Functionality

The function block `ALI_MUL_2` multiplies the values provided via the adapter sockets `IN1` and `IN2`. As soon as a corresponding trigger event is signaled via the input adapters, the block performs the calculation:

$$\text{OUT} = \text{IN1} \times \text{IN2}$$

The calculated result and the associated output event are then forwarded to subsequent blocks via the output plug `OUT`.

- **Generic Nature:** The function block is declared as `GEN_ALI_MUL` via the attribute `GenericClassName`. This allows for flexible handling of various data types specified by the higher-level system or the adapter type used.
- **Adapter Coupling:** By using the unidirectional adapter type `ALI`, data and trigger events are bundled in a single connection, significantly minimizing wiring effort in the development environment.

Since this is a purely data-flow and adapter-based function block, it does not have a complex internal state machine (Execution Control Chart - ECC). Execution is event-driven and directly coupled to the triggers received via the adapters.

**Adapter Coupling:** ## Application Scenarios

- **Measurement Scaling:** Multiplication of sensor values by calibration or scaling factors.
- **Power Calculation:** Determination of physical quantities such as electrical power ($P = U \times I$) in adapter-based control networks.
- **Compact Computing Networks:** Use in complex mathematical calculations where the visual clarity of the control diagram must be maintained through the use of adapters.

Compared to classic mathematical components of IEC 61131-3 (such as a standard `MUL` component with discrete `REQ` / `CNF` events and separate data lines), the `ALI_MUL_2` eliminates the need for manual linking of event and data paths. This prevents errors in event data mapping and results in a significantly cleaner and more readable application diagram in 4diac-ide.

The `ALI_MUL_2` is a modern and efficient function block for multiplication. Thanks to the consistent use of unidirectional adapters, it is ideally suited for service-oriented and modular control systems where clarity and ease of maintenance are paramount.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Change Detection

The result is only written to the output plug (`OUT`) and its adapter event only sent if the newly computed value differs from the value currently held on `OUT`. If the result is unchanged, no adapter event is sent, avoiding redundant updates on downstream peers.


## Conclusion
