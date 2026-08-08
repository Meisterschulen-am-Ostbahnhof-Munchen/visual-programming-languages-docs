# AX_SEL_TIME

![AX_SEL_TIME](./AX_SEL_TIME.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `AX_SEL_TIME` is a composite function block for IEC 61499-based systems. It serves as a binary selector for data of type `TIME`. Using a unidirectional adapter (`G`), it allows dynamic selection between two different time input values (`IN0` and `IN1`) to pass the selected value to the output (`OUT`).



 ## Interface Structure

### **Event Inputs**

* **EI0**: Sets the time value at input `IN0` (associated with data variable `IN0`).

* **EI1**: Sets the time value at input `IN1` (associated with data variable `IN1`).

### **Event Outputs**

* **CNF**: Confirmation event that signals that the selected output value has been updated (associated with data variable `OUT`).

### **Data Inputs**

* **IN0** (`TIME`): First selectable time value.

* **IN1** (`TIME`): Second selectable time value.

### **Data Outputs**

* **OUT** (`TIME`): The currently selected time value.

### **Adapter**

* **G** (`adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. It provides both the switching event and the selection value (state).

## Functionality

This function block encapsulates an internal network for event-driven selection of time values. The selection is controlled via the adapter `G`:

* If the adapter `G` provides the selection signal for the first path (logically equivalent to `FALSE` / `0`), the value of `IN0` is switched to the output `OUT`.

* If the adapter `G` provides the selection signal for the second path (logically equivalent to `TRUE` / `1`), the value of `IN1` is switched to the output `OUT`.



* Internally, the inputs are buffered via D flip-flops and processed using the standard selection block `F_SEL`. A downstream `E_D_FF_ANY` ensures event-based forwarding when values change.

## Technical Features

* **Event Filtering at the Output:** An output event (`CNF`) is primarily controlled by the internal `E_D_FF_ANY_OUT`. This means that an output event is typically only generated if the state of the selector `G` or the value of the currently selected input actually changes, resulting in a change to the output value `OUT`.


* **Adapter Coupling:** Using the `AX` adapter modularizes the selector's control logic and significantly simplifies wiring in the higher-level system network.

## State Overview

Since this is a composite function block, it does not have its own ECC (Execution Control Chart). Its behavior is entirely determined by the internal network:

1. **Change of `IN0` / `IN1`**: An event on `EI0` or `EI1` updates the respective internal memory. If the changed input is currently selected, the new value is applied to `OUT` and triggers a `CNF` event. 2. **Switching via `G`**: An event via the adapter `G` triggers the recalculation of the selection. If this changes the value at output `OUT`, event `CNF` is output.

## Application Scenarios

* **Recipe and Process Control:** Switching between different process or delay times (e.g., different rinsing or heating times) based on operating modes.

* **Day/Night Switching:** Selection between two predefined time intervals for control tasks in building automation or agricultural technology.

* **Maintenance and Diagnostic Modes:** Temporary reduction of monitoring times (setpoint interfaces) during service operation.


## Comparison with Similar Function Blocks

* **Comparison with `F_SEL` (IEC 61131-3):** The classic `F_SEL` function block operates purely in a data flow-oriented manner. `AX_SEL_TIME` extends this functionality with full event control (IEC 61499) and integrates an adapter port for a cleaner software architecture.

* **Comparison with Generic Selectors:** Unlike generic selection blocks, `AX_SEL_TIME` offers increased type safety at development time due to its fixed typing on the data type `TIME`.

## Conclusion

`AX_SEL_TIME` is a robust and reusable function block for event-driven selection of time values. The combination of simple binary selection and modern adapter connectivity makes it an ideal component for flexible control applications in distributed systems.