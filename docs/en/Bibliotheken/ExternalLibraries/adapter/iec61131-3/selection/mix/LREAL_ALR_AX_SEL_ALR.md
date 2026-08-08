# LREAL_ALR_AX_SEL_ALR

![LREAL_ALR_AX_SEL_ALR](./LREAL_ALR_AX_SEL_ALR.svg)

* * * * * * * * * *
The function block `LREAL_ALR_AX_SEL_ALR` is a binary selection block for the data type `LREAL`. It is used to select one of two high-precision analog input values (`IN0` or `IN1`) based on the state of a selection signal (gate signal `G`) and forward it to the output (`OUT`). By using IEC 61499 adapters, the block enables clean, modular, and event-driven signal processing.




* **EI0**: Triggers the update and transfer of the directly connected data input `IN0`.


* *(No direct event outputs are available on the main interface. Event forwarding is encapsulated via the output adapter `OUT`.)*


* **IN0** (LREAL): The first input value to be selected. This value is passed through to the output when the selection signal `G` is in the state `FALSE`.



* (No direct data outputs are available on the main interface. Data is provided encapsulated via the output adapter `OUT`.)*

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapters**

* **IN1** (Socket, Type: `adapter::types::unidirectional::ALR`): A unidirectional adapter input for the second selectable value.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): A unidirectional adapter input for the selector signal.

* **OUT** (Plug, Type: `adapter::types::unidirectional::ALR`): A unidirectional adapter output that outputs the selected signal and the associated update event.


## Functionality

The module is implemented internally as a network (sub-FB) that ensures reliable, event-driven selection:

1. **Signal Buffering**: The input data from `IN0`, `IN1`, and `G` are buffered via D flip-flops (`E_D_FF` / `E_D_FF_ANY`) when their respective events (`EI0`, `IN1.E1`, `G.E1`) occur.

2. **Value Transfer**: Downstream move blocks (`F_MOVE`) consistently transfer the data to the central selection block (`F_SEL`).

3. **Selection Process**: The block `F_SEL` performs the actual binary selection:

* If the selection signal `G.D1` = `FALSE`, the value of `IN0` is selected.

* If the selection signal `G.D1` = `TRUE`, the value of `IN1.D1` is selected.

4. **Output Update**: The selected value is passed to the output plug `OUT`. Simultaneously, the output event `OUT.E1` is generated to inform subsequent program components about the presence of a new value.

* **Event-driven Data Flow**: Any change to one of the inputs or the selection signal immediately triggers a recalculation and a possible update of the output.

* **Adapter Structure**: The use of unidirectional adapters significantly reduces the complexity of cabling in higher-level systems, as data and events are bundled in a single connection channel.

* **Data Type Precision**: The consistent use of the `LREAL` data type makes this function block suitable for high-precision physical quantities and calculations.


* ## State Overview
Since this is a purely data-flow and event-driven sub-function block, it does not have its own complex state machine (ECC). Its behavior can be described in tabular form as follows:

| State Selector (`G.D1`) | Triggering Event | Output Value (`OUT.D1`) | Description |

| :--- | :--- | :--- | :--- |

| `FALSE` | Any input event | Value of `IN0` | `IN0` is actively enabled. Changes to `IN1` do not affect the output. |

| `TRUE` | Any input event | The value of `IN1.D1` | `IN1` is actively passed through. Changes to `IN0` do not affect the output. |


* **Setpoint Switching**: Switching between a locally defined setpoint (`IN0` via `LREAL`) and an external setpoint provided via a bus system or another software module (`IN1` via adapter).

* **Manual/Automatic Operation**: Switching a manipulated variable between a manually entered value and the calculated value of an automatic controller.

* **Signal Switching for Redundant Sensors**: Selecting a backup sensor in case of failure or for calibration of the primary sensor.


* ## Comparison with Similar Function Blocks
* **Standard Function Block `F_SEL`**: The classic selection function block according to IEC 61131-3 operates purely data-oriented and has no integrated event control or adapter interfaces. `LREAL_ALR_AX_SEL_ALR` extends this basic functionality with the event-based execution of IEC 61499.

* **Type Variants**: Analogous function blocks exist for other data types (e.g., `REAL`, `INT`) that use the same internal logic but are adapted to the respective data types of the adapters.

The function block `LREAL_ALR_AX_SEL_ALR` offers an efficient, reliable, and standardized way to select precise floating-point values in event-driven systems. By encapsulating the D flip-flops for signal stabilization and using modern adapter structures, he makes a significant contribution to the clarity and determinism of control programs.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion