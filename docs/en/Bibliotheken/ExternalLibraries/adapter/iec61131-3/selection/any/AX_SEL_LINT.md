# AX_SEL_LINT

![AX_SEL_LINT](./AX_SEL_LINT.svg)

* * * * * * * * * *
## Introduction

The function block `AX_SEL_LINT` is a standard selection function block according to IEC 61131-3 for binary selection between two input values of the data type `LINT` (Long Integer). Control and selection of the active channel are performed via a standardized adapter interface. The block is event-driven and optimized for use in IEC 61499 applications within the 4diac IDE.

## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the transfer of the data value from `IN0`.
* **EI1**: Triggers the transfer of the data value from `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Signals that the selected output value (`OUT`) has changed.

### **Data Inputs**

* **IN0** (LINT): First selectable data input value.
* **IN1** (LINT): Second selectable data input value.

### **Data Outputs**

* **OUT** (LINT): The currently selected output value.

### **Adapters**

* **G** (Type: `adapter::types::unidirectional::AX`): Unidirectional adapter that functions as a selector. It provides the switching event (`E1`) and the selection data signal (`D1`), which determines which of the inputs is enabled.

 ---

## Functionality

The `AX_SEL_LINT` module combines internal storage and selection functions to switch one of the two inputs (`IN0` or `IN1`) to the output `OUT`:

1. **Data Acquisition:** Upon the occurrence of the events `EI0` or `EI1`, the values at the inputs `IN0` and `IN1` are buffered via internal event D flip-flops (`E_D_FF_ANY`).
2. **Selection:** The `G` adapter acts as a control channel. When an event occurs at `G.E1`, the Boolean state of `G.D1` is evaluated:
* If the state of `FALSE` is 0, the value of `IN0` is selected.
* If the state of `TRUE` is 1, the value of `IN1` is selected.
3. **Output Filtering:** The selected value is passed to output `OUT`. An output event (`CNF`) is triggered by a downstream flip-flop (`E_D_FF_ANY_OUT`) **only** if the value at output `OUT` has actually changed. This avoids redundant event cascades in the network.

---

## Technical Features

* **Event Reduction:** An output event (`CNF`) is not generated with every input event, but only when the selected output value actually changes.
* **Adapter Connection:** By encapsulating the selection logic in a `AX` adapter, the signal wiring in the application diagram is significantly simplified and made clearer.
* * **Data Type Specific:** This function block processes dedicated 64-bit integers (`LINT`).

---

## State Overview

| Selector State (`G.D1`) | Last Active Event | Output Value (`OUT`) | Behavior of `CNF` |
| :--- | :--- | :--- | :--- |
| `FALSE` | Any | Equivalent to `IN0` | Triggered when `IN0` changes |
| `TRUE` | Any | Corresponds to `IN1` | Triggered when `IN1` changes |
| Change from `FALSE` to `TRUE` | `G.E1` | Change from `IN0` to `IN1` | Triggered if `IN0 != IN1` |
| Change from `TRUE` to `FALSE` | `G.E1` | Change from `IN1` to `IN0` | Triggered if `IN0 != IN1` |

---

## Application Scenarios

* **Setpoint Switching:** Switching between two different identification numbers, counter readings, or large timestamps (declared as `LINT`) in an automated system.
* **Recipe Change:** Selection between predefined configuration parameters during operation via an HMI (using the selector adapter).
* **Signal Routing:** Dynamic routing of data streams in event-driven systems.

---

## Comparison with Similar Function Blocks

* **`F_SEL` (Standard Selection Function Block):** The classic `F_SEL` has no integrated event inputs for value storage and no adapter connection. It reacts purely in terms of data flow.
* * **`AX_SEL_INT` / `AX_SEL_REAL`:** Identical functionality and structure, but designed for the respective data types `INT` (16-bit) and `REAL` (floating-point number).

---

## Conclusion

The `AX_SEL_LINT` is a powerful utility block for structured programming in 4diac. Through the combination of event-based filtering and the clear adapter interface, it significantly contributes to the creation of clean, high-performance, and maintainable IEC 61499 control applications.