# AX_SEL_STRING

![AX_SEL_STRING](./AX_SEL_STRING.svg)

*(No image available)*

* * * * * * * * * *
## Introduction
The function block `AX_SEL_STRING` is used for binary selection between two strings (`STRING`). It is based on the IEC 61131-3 standard for selection functions and is adapted for event-driven execution in 4diac (IEC 61499). The selection of which of the two inputs is passed to the output is made via a unidirectional adapter.

## Interface Structure
### **Event Inputs**
* **EI0**: Triggers the reading and processing of the data input `IN0`.

* **EI1**: Triggers the reading and processing of data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Sent when a new selected value is provided at output `OUT`.

### **Data Inputs**

* **IN0** (STRING): The first selectable input value. This is passed to the output when the selection signal is in the state `FALSE`.

* **IN1** (STRING): The second selectable input value. This is passed to the output when the selection signal is in the state `TRUE`.


### **Data Outputs**

* **OUT** (STRING): The currently selected output value (`IN0` or `IN1`).

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): A unidirectional adapter that provides the selection signal. This adapter controls which of the two data inputs is activated.

## Functionality
In the internal network of `AX_SEL_STRING`, the input data is buffered via memory elements (`E_D_FF_ANY`).


1. **Input Events**: As soon as an event arrives at `EI0` or `EI1`, the respective string (`IN0` or `IN1`, respectively) is updated internally.

2. **Adapter Control**: The adapter `G` provides the control signal. When the adapter state changes (event `E1` at the adapter `G`), the selection value is updated.


2. **Adapter Control**: The adapter `G` provides the control signal. 3. **Selection**: The internal standard function block `F_SEL` determines, based on the state of `G.D1` (data line of the adapter), which value is passed to the output:

- If the state of selector `G` or `FALSE`, the value of `IN0` is passed through.

- If the state of selector `G` or `TRUE`, the value of `IN1` is passed through.

4. **Event Filtering**: At the output of the function block, a `E_D_FF_ANY` element monitors whether the value at `OUT` has actually changed. A `CNF` output event is only triggered if the output value changes.

## Technical Features
* **Event Optimization**: An output event (`CNF`) is only generated if the selected state at the output actually changes (e.g., by switching the selector `G` or by changing the active input value). Static updates without a value change do not trigger an unnecessary output event.

* **Adapter Coupling**: Using the `AX` adapter enables elegant, loose coupling of the selection logic within the overall system, without having to run direct Boolean data lines across the application diagram.

## State Overview
The following table shows the logical mapping of the output depending on the adapter state:

| Selector State (G.D1) | Output Value (OUT) |

| :--- | :--- |

| `FALSE` / `0` | Corresponds to the value of `IN0` |

| `TRUE` / `1` | Corresponds to the value of `IN1` |


## Application Scenarios

* **HMI Text Switching**: Dynamic selection between two status messages or display texts based on a system state (e.g., "OPERATION" vs. "FAILURE").

* **Recipe Management**: Switching recipe or product names in string format when changing operating modes.

* **Multilingualism**: Easy switching of interface texts between two languages via a central control signal.

## Comparison with Similar Function Blocks

* **F_SEL (IEC 61131-3)**: The standard selection function block requires a direct `BOOL` signal for selection and does not have inherent event control. `AX_SEL_STRING` encapsulates this functionality in an event-based manner and uses an adapter for control.

* **AX_SEL_INT / AX_SEL_REAL**: These function blocks operate on the same principle but are designed for numeric data types, while `AX_SEL_STRING` is specifically optimized for processing character strings (`STRING`).

## Conclusion

`AX_SEL_STRING` is a specialized and efficient auxiliary function block for IEC 61499 applications that enables a clean separation of control logic and data flow when working with character strings. Its integrated event filtering conserves system resources by minimizing redundant subsequent calculations in the control network.