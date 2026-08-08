# AX_SEL_LWORD

![AX_SEL_LWORD](./AX_SEL_LWORD.svg)

*(No image available)*

* * * * * * * * * *

The function block `AX_SEL_LWORD` is used for binary selection between two `LWORD` input values (`IN0` and `IN1`). The control over which of the two inputs is passed to the output is handled by an adapter input `G` of type `AX`. This block is based on the classic selection function of the IEC 61131-3 standard and prepares it for event-driven execution in IEC 61499 environments such as 4diac-ide.



* **`EI0`**: Signals that the input value `IN0` has been updated or set.

* **`EI1`**: Signals that the input value `IN1` has been updated or set.


* **`CNF`**: Confirmation event. Signals to the subsequent network that a newly selected value is present at the data output `OUT`.



* **`IN0` (`LWORD`)**: First selectable data input value (active when the selection signal `G` is logically `FALSE`).

* **`IN1` (`LWORD`)**: Second selectable data input value (active when the selection signal `G` is logically `TRUE`).


* **`OUT` (`LWORD`)**: The currently selected data output value.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
### **Adapter**

* **`G` (Type: `adapter::types::unidirectional::AX`)**: Unidirectional adapter socket that acts as a selector. The switching signal is received via this adapter.


## Functionality

The internal network of `AX_SEL_LWORD` processes events and data using edge and value-triggered processing:

1. **Event Processing**: When an event arrives at `EI0` or `EI1`, the corresponding data value (`IN0` or `IN1`) is buffered via internal flip-flops (`E_D_FF_ANY`) and passed to the core selection block (`F_SEL`).


2. **Adapter Selection**: Events at adapter `G` (event `E1`) trigger the internal flip-flop `E_D_FF_G` with the data value `D1`. This controls the selection input of the internal selector.

3. **Output and Filtering**: The selected value is applied to output `OUT`. An output event at `CNF` is generated via a downstream `E_D_FF_ANY` only if the state of selector `G` changes or if an actual value change occurs at the output.


3. **Output and Filtering**: The selected value is applied to output `OUT`. ## Technical Features

* **Data Type**: The function block is specifically designed for the 64-bit data type `LWORD`.

* **Event Optimization**: An output event (`CNF`) is primarily generated when the selection adapter `G` changes or when the output value actually changes, in order to minimize unnecessary event cascades in the system.

* **Simple Wiring**: By using the standardized `AX` adapter, the number of explicit connection lines in the application editor is reduced.


| Selector State `G` | Relevant Event Input | Output Value `OUT` | Event output `CNF` |

:---|:---|:---|:---|

| `FALSE` (0) | `EI0` | `IN0` | Triggered on value change |

| `TRUE` (1) | `EI1` | `IN1` | Triggered on value change |

| Signal changes to `G` | `G.E1` | Switches to the newly selected input | Triggered |



* **Signal Switching**: Selection between two redundant signal sources (e.g., primary and secondary data bus) based on a global system status.

* **Mode Switching**: Loading different 64-bit configuration registers or bitmasks depending on the operating mode (e.g., automatic vs. manual operation).

* **Data Routing**: Dynamic routing of data streams in distributed control systems.


* **`F_SEL` (IEC 61131-3)**: The standard selection block `F_SEL` operates purely in a data flow-oriented manner. `AX_SEL_LWORD` extends this functionality to include the event-based execution model of IEC 61499 and connects to the controller via a convenient adapter.

* **`AX_SEL` for other data types** (e.g., `AX_SEL_DWORD`): These have the same functional structure but are designed for smaller bit widths (e.g., 32-bit).


`AX_SEL_LWORD` is a specialized and optimized function block for the safe, event-driven selection of 64-bit data values. Thanks to its adapter interface, it integrates seamlessly and clearly into complex 4diac applications.
## Technical Features
## State Overview
## Application Scenarios
## Comparison with Similar Function Blocks
## Conclusion