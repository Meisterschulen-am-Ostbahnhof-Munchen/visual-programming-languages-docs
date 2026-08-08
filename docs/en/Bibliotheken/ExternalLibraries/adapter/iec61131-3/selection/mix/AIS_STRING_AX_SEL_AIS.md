# AIS_STRING_AX_SEL_AIS

![AIS_STRING_AX_SEL_AIS](./AIS_STRING_AX_SEL_AIS.svg)

*(No image available)*

* * * * * * * * * *

The function block `AIS_STRING_AX_SEL_AIS` is used for binary selection between two signal sources of different structures: an adapter input of type `AIS` and a classic string input (`IN1`). The control over which signal is passed to the output adapter is handled by a selector adapter of type `AX`. Internally, the block uses the standardized selection logic according to IEC 61131-3, encapsulated in a fully event-driven IEC 61499 network structure.




* **EI1**: Triggers the acquisition of the data input `IN1` (associated data variable: `IN1`).


* *No direct event outputs available.* (Event control is implicit via the output adapter `OUT`).


* **IN1** (STRING): Selectable input variable (string).


* *No direct data outputs available.* (Data is passed via the output adapter `OUT`).


### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AIS`): The selected and updated output. Sends the selected signal to the subsequent logic.

* **IN0** (Socket, Type: `adapter::types::unidirectional::AIS`): First selectable input via adapter connection.

* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector adapter. Determines, via its data signal, which input is enabled.


* **OUT** (Plug, Type: `adapter::types::unidirectional::AX`): The selector adapter. Determines, via its data signal, which input is enabled.

* ## Functionality

The module operates as an event-driven multiplexer for string and adapter signals:

1. **Selection Logic:**

* If the selection signal at adapter `G` (data field `D1`) is **FALSE**, the value from input `IN0` (data field `D1`) is passed to output `OUT` (data field `D1`).

* If the selection signal is **TRUE**, the string value from input `IN1` is passed to output `OUT`.

* If the selection signal is **TRUE**, the string value from input `IN1` is passed to output `OUT`. 2. **Event Processing:**

* Any change to the inputs (`IN0`, `IN1` via `EI1`) or the selector `G` triggers a recalculation via internal Event D flip-flops (`E_D_FF` and `E_D_FF_ANY`, respectively) and assignment blocks (`F_MOVE`).

* After successful selection, the output event `OUT.E1` is generated to inform subsequent blocks about the availability of new data.


* ## Technical Features

* **Hybrid Interface:** Enables seamless coupling of structured adapter interfaces (`AIS`, `AX`) with simple IEC 61131 data types (`STRING`).

* **Data Type Security:** The internal use of data type-independent event flip-flops and dedicated `F_MOVE` copiers (configured to the `STRING` data type) ensures consistent data consistency with every switching operation.

* **Unidirectional Adapters:** The use of unidirectional adapter types ensures a clear, feedback-free signal flow.


* **Unidirectional Adapters:** ## State Overview

Since this is a composite function block (FB), its behavior is controlled by the internal interaction of its components. The logical state table is as follows:

| Selector (`G.D1`) | State / Change at Inputs | Output (`OUT.D1`) | Event at Output (`OUT.E1`) |

| :--- | :--- | :--- | :--- |

| **FALSE** | `IN0.D1` changes / Event `IN0.E1` | Value of `IN0.D1` | Triggered |

| **TRUE** | `IN1` changes / Event `EI1` | Value of `IN1` | Triggered |

| **Change (arbitrary)** | Event at `G.E1` | Current value according to selector | Triggered |


* **Status and Text Displays:** Switching a visualization display between a standard system status (provided via the `IN0` adapter) and a dynamic user message (passed as a string to `IN1`).

* **Error Routing:** Conditionally routing predefined error messages to a central diagnostic bus.

* **Recipe Management:** Selection between a standard process parameter string and a manually entered correction value in automated production plants.



Compared to the standard selection block `F_SEL`, this block offers direct integration of IEC 61499 adapters. Developers no longer need to painstakingly decompose the adapter signals into individual data points for selection. All event synchronization is handled out-of-the-box within the block.


`AIS_STRING_AX_SEL_AIS` provides a convenient and robust solution for bridging the gap between structured adapters and simple string variables in event-driven systems. It significantly minimizes the wiring effort in the higher-level function block diagram and guarantees deterministic behavior during signal changes.
## Functionality
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion