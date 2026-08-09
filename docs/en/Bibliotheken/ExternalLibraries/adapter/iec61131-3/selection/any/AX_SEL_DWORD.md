# AX_SEL_DWORD

![AX_SEL_DWORD](./AX_SEL_DWORD.svg)

* * * * * * * * * *
## Introduction

The function block `AX_SEL_DWORD` is a standard selection block (binary selection) for the data type `DWORD` (double word). It is based on the IEC 61131-3 standard and allows, depending on the state of a selection adapter (`G`), a selection between two DWORD input values (`IN0` and `IN1`) and the output of the selected value at `OUT`.

 ## Interface Structure

### **Event Inputs**

* **EI0**: Triggers the update and transfer of data input `IN0`.
* **EI1**: Triggers the update and transfer of data input `IN1`.

### **Event Outputs**

* **CNF**: Confirmation event. Signals to the downstream system that a new selected value is present at `OUT`.

### **Data Inputs**

* **IN0** (`DWORD`): The first selectable input value. Passed through to the output if the selection signal of the adapter `G` is logically `0` (FALSE). * **IN1** (`DWORD`): The second selectable input value. Passed through to the output if the selection signal of adapter `G` is logically `1` (TRUE).

### **Data Outputs**

* **OUT** (`DWORD`): The currently selected DWORD value.

### **Adapters**

* **G** (`adapter::types::unidirectional::AX`): A unidirectional adapter that acts as a selector. This adapter controls which of the two inputs (`IN0` or `IN1`) is routed to the output.

### **Adapters**

* **G** (`adapter::types::unidirectional::AX`): A unidirectional adapter that functions as a selector. This adapter controls which of the two inputs (`IN0` or `IN1`) is routed to the output.

## Functionality

The function block blocks or forwards data based on the state of the adapter `G`:

1. When an event occurs at the adapter `G`, its state is read.
2. The internal standard selection block `F_SEL` decides:
* If the signal from `G` is disabled (FALSE), the value from `IN0` is selected.
* If the signal from `G` is enabled (TRUE), the value from `IN1` is selected.
3. The selected value is passed to the output `OUT`.
4. An output event (`CNF`) is sent to the system.

## Technical Features

* **Event Optimization**: The function block internally uses `E_D_FF_ANY` elements for edge detection. An output event at `CNF` is only generated if the actually selected value at output `OUT` changes. This saves system resources and prevents unnecessary subsequent calculations in the function block network.
* **Adapter-Controlled**: The selection is not performed via a classic Boolean data input, but is encapsulated by a dedicated adapter (`G`). This enables a clean, modular architecture in the control program.
* ## State Overview

The function block does not have its own complex state machine (ECC) because it is a composite function block. Signal and data flow is directly determined by the internal connections of the standardized sub-blocks (`F_SEL`, `F_MOVE`, `E_D_FF_ANY`).

## Application Scenarios

* **Recipe and Parameter Switching**: Dynamic switching of configuration or parameter double words (e.g., limits, bitmasks) at runtime.
* **Redundant Sensors / Signal Sources**: Switching between a primary and secondary data stream in DWORD format in case of failure or maintenance.
* **Mode Selection**: Selection of different status or control words for downstream components.

## Comparison with Similar Function Blocks

Compared to a classic IEC 61131-3 `SEL` function block, `AX_SEL_DWORD` does not require a permanently applied Boolean control input. Instead, the selection is event-driven via the `G` adapter. Furthermore, internal filtering ensures that subsequent program sections are only triggered by a genuine change in the output value.

## Conclusion

`AX_SEL_DWORD` offers an efficient and event-driven way to cleanly manage DWORD data streams within a 4diac application. Thanks to its adapter-based coupling, it is ideally suited for service-oriented and modular software architectures in automation technology.