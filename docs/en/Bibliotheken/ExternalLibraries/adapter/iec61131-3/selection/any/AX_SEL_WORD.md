# AX_SEL_WORD

![AX_SEL_WORD](./AX_SEL_WORD.svg)

* * * * * * * * * *
## Introduction
The function block `AX_SEL_WORD` is used for binary selection between two input values of data type `WORD` (`IN0` and `IN1`). The selection is controlled via an adapter of type `AX`. The block is particularly suitable for use in event-driven systems according to IEC 61499, as it combines efficient signal forwarding with integrated event filtering.

## Interface Structure
### **Event Inputs**
* **EI0**: Updates the value of input `IN0`.

* **EI1**: Updates the value of input `IN1`.

### **Event Outputs**

* **CNF**: Acknowledge event. Triggered to indicate that a new selected value is present at output `OUT` (Note: Triggered only when the output value actually changes).

### **Data Inputs**

* **IN0** (`WORD`): First selectable input value (selected when the selection signal is `FALSE`).

* **IN1** (`WORD`): Second selectable input value (selected when the selection signal is `TRUE`).


### **Data Outputs**

* **OUT** (`WORD`): The currently selected output value.

### **Adapter**

* **G** (Type: `adapter::types::unidirectional::AX`, Socket): Adapter interface for controlling the selection. The data signal `D1` of this adapter serves as the selector, while the event `E1` triggers the selection process.


---

## Functionality
Internally, `AX_SEL_WORD` couples the input signals and the adapter status via a network of standard auxiliary modules (such as `F_SEL`, `F_MOVE`, and edge detectors):

1. **Data Acquisition**: When an event arrives at `EI0` or `EI1`, the corresponding data (`IN0` or `IN1`, respectively) is read.

2. **Adapter Evaluation**: An event `E1` at adapter `G` signals a change in the selection signal. The adapter's data value `D1` determines the selection:

* If `G.D1` = `FALSE`, `IN0` is selected.

* If `G.D1` = `TRUE`, `IN1` is selected.

3. **Output Control**: The selected value is provided to `OUT`. The output event `CNF` is handled by an internal change detector (`E_D_FF_ANY`). A `CNF` event is **only** generated if the value of `OUT` has actually changed compared to the previous state.

---

## Technical Features
* **Resource-Saving Event Filtering**: By coupling the output to a value change detector (`E_D_FF_ANY`), redundant events are suppressed. This minimizes the CPU load in subsequent program sections.

* **Adapter-Based Control**: The use of the `AX` adapter allows for clean, modular coupling of the control logic without loose event and data lines.

---

## State Overview

| Selector (`G.D1`) | Input 0 (`IN0`) | Input 1 (`IN1`) | Output (`OUT`) |

| :--- | :--- | :--- | :--- |

**FALSE** | Value_A | Value_B | **Value_A** |

**TRUE** | Value_A | Value_B | **Value_B** |

---

## Application Scenarios

* **Setpoint Switching**: Switching between two different operating parameters (e.g., recipe values or manual/automatic settings) in `WORD` format.

* **Signal Multiplexing**: Forwarding status or control words depending on a higher-level process state.

* **Event-Optimized Data Processing**: Reducing data flow in networks where only value changes should trigger an action.


---

## Comparison with Similar Function Blocks
* **Standard `F_SEL` (IEC 61131-3)**: The standard selector operates purely in a data flow-oriented manner and has no integrated event control or adapter connection. `AX_SEL_WORD` extends this functionality for IEC 61499.
* **`AX_SEL` function blocks for other data types** (e.g., `AX_SEL_INT` or `AX_SEL_REAL`): These have the same internal logic and structure but process the respective other data types at their inputs and outputs.

--

## Conclusion
`AX_SEL_WORD` is a highly optimized function block for the event-driven selection of `WORD` data. Thanks to the intelligent filtering of output events and the modern adapter connection, it is ideally suited for high-performance and clear control architectures.