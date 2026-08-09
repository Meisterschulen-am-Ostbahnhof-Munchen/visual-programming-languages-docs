# ADI_SUB_2

       +------------------------------------+
|             ADI_SUB_2              |
|                                    |
 IN1 ==# [ADI]                        [ADI] #== OUT
IN2 ==# [ADI]                              |
       +------------------------------------+

![ADI_SUB_2](./ADI_SUB_2.svg)

* * * * * * * * * *
The function block `ADI_SUB_2` is a generic function block (Generic FB) for performing arithmetic subtractions in IEC 61499 applications. The block uses unidirectional adapters of type `ADI` to receive input data and output the calculated result. Using adapters simplifies the wiring within the 4diac IDE and increases modularity.

The function block does not have direct event inputs. Event control is handled entirely via the connected adapters.

The function block does not have direct event outputs. Event forwarding is handled via the output adapter.

No direct data inputs are defined. Data is passed via the input adapters.

No direct data outputs are defined. The result is provided via the output adapter.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

| Type | Name | Adapter Type | Description |
| :--- | :--- | :--- | :--- |
| **Socket (Input)** | `IN1` | `adapter::types::unidirectional::ADI` | First input value (minuend) for subtraction. |
| **Socket (Input)** | `IN2` | `adapter::types::unidirectional::ADI` | Second input value (subtrahend) for subtraction. |
| **Plug (Output)** | `OUT` | `adapter::types::unidirectional::ADI` | Result (difference) of the subtraction ($OUT = IN1 - IN2$). |

## Functionality

As soon as a corresponding calculation event is signaled at the input adapters `IN1` or `IN2`, the function block performs the subtraction:

$$OUT = IN1 - IN2$

The result is passed to the output adapter `OUT`, and the corresponding output event of the adapter is triggered to inform subsequent function blocks of the new value.

* **Generic Type:** The function block is defined as a generic type (`eclipse4diac::core::GenericClassName` with the value `'GEN_ADI_SUB'`). This allows for flexible adaptation to different data types within the `ADI` adapter.
* **Unidirectional Adapters:** By using the unidirectional adapter structure (`adapter::types::unidirectional::ADI`), the data flow remains directed and cyclic dependencies are avoided.

Since this is a mathematical calculation function block, its behavior is essentially stateless and event-driven:

1. **Waiting:** The function block waits for a trigger event at one of the input adapters (`IN1` or `IN2`).
2. **Calculation:** Upon event input, the data values are read and subtracted.
3. **Output:** The calculated value is written to the adapter `OUT`, triggering the corresponding send event.
* **Control Engineering:** Calculation of a control deviation ($e = w - x$), where the setpoint ($w$) and actual value ($x$) are transmitted via standardized ADI interfaces.
* **Measurement Processing:** Differential pressure measurement or offset correction of sensor values integrated into the application via adapters.
* **Signal Preprocessing:** Reduction of signal values by fixed or variable limits before forwarding them to actuators.
* ## Comparison with Similar Blocks

Compared to a standard subtraction block (such as the classic `SUB` block according to IEC 61131-3), which uses direct data and event pins, `ADI_SUB_2` offers the following advantages:
* **Fewer connection lines:** Data and events are bundled in the `ADI` adapter, making the application diagram in 4diac clearer.
* **Standardized interfaces:** Facilitates the exchange of calculation and processing blocks, as only the adapters need to be connected.

The `ADI_SUB_2` is an efficient auxiliary block for structured IEC 61499 control applications. It is ideally suited for demanding architectures where clarity and standardized adapter interfaces are paramount.
## Technical Features

## State Overview

## Application Scenarios

## Comparison with Similar Function Blocks

## Conclusion