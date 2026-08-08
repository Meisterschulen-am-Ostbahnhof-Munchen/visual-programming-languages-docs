# AX_SEL_ULINT

![AX_SEL_ULINT](./AX_SEL_ULINT.svg)

* * * * * * * * * *


The function block `AX_SEL_ULINT` is a binary selection block (multiplexer) for the data type `ULINT` (Unsigned Long Integer / 64-bit integer) according to the IEC 61131-3 standard. It enables switching between two input values (`IN0` and `IN1`) based on the state of a selector connected via an adapter (`G`).





* **EI0**: Trigger event for accepting and updating the input value `IN0`.

* **EI1**: Trigger event for accepting and updating the input value `IN1`.


* **CNF**: Confirmation event. Signals the update of the selected output value `OUT`.


* **IN0** (ULINT): First selectable input value. The output is routed when the selector signal at adapter `G` specifies the state for `IN0` (logically `0` or `FALSE`).

* **IN1** (ULINT): Second selectable input value. The output is routed when the selector signal at adapter `G` specifies the state for `IN1` (logically `1` or `TRUE`).


* **OUT** (ULINT): The currently selected output value.


### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`): A socket adapter of type `AX`. It serves as a selector for switching between the two inputs `IN0` and `IN1`.

## Functionality

The module operates internally with a standard selector (`F_SEL`). Data transfer is event-driven:

1. As soon as an event arrives at `EI0` or `EI1`, the corresponding data values (`IN0` or `IN1`) are updated in the module.

2. The selector state is read via the adapter `G` (event `E1` and data value `D1`).

3. Based on the selector state, either `IN0` or `IN1` is forwarded to the output `OUT`.

4. An output event is sent to `CNF` to inform subsequent function blocks of the new value.
...4. ## Technical Features

* **Event Filtering on Value Change:** The module uses an internal edge detector (`E_D_FF_ANY`) to ensure that the confirmation event `CNF` is only triggered when the selected output value `OUT` actually changes.

* **Special Selector Logic:** According to the specification details, the behavior is optimized so that output is primarily generated when the selection signal `G` changes.

* **Efficiency:** By using adapters, the wiring complexity in the 4diac network is significantly reduced, as control events and selection data are transmitted together.


| Adapter State `G` (Value) | Selected Input | Output (`OUT`) |

| :--- | :--- | :--- |

| `0` (FALSE) | `IN0` | Value of `IN0` |

| `1` (TRUE) | `IN1` | Value of `IN1` |


* **Mode-Dependent Counter Value Selection:** Switching between two large counter readings (e.g., total quantity vs. batch quantity based on `ULINT`) depending on a system status provided via an adapter.


* **Signal Routing:** Dynamic routing of 64-bit integer data in modular automation architectures.

* **Redundant Sensors:** Selection between a primary and a secondary sensor (e.g., high-precision timestamps or pulse counters).


Unlike a classic `SEL` component according to IEC 61131-3, which requires discrete control lines for data and events, `AX_SEL_ULINT` utilizes an integrated adapter concept (`G`). This makes it particularly suitable for modern, service-oriented IEC 61499 architectures where coupling signals need to be transmitted in a structured manner. Furthermore, it is specifically designed for the resource-efficient, high-precision data type `ULINT`.



`AX_SEL_ULINT` is a specialized and robust function block for data- and event-driven signal switching in the 64-bit range. Thanks to integrated change detection and the use of adapters, it operates with high event efficiency and contributes to clear control diagrams.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion