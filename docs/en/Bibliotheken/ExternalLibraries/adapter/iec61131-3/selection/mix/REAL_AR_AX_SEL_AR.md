# REAL_AR_AX_SEL_AR

![REAL_AR_AX_SEL_AR](./REAL_AR_AX_SEL_AR.svg)

*(No image available)*

* * * * * * * * * *
## Introduction

The function block `REAL_AR_AX_SEL_AR` is used for binary selection between two real-valued input signals (type `REAL`). It combines classic signal-based programming with modern, adapter-based communication according to IEC 61499.

One input is provided as a direct data value, while the second selection input, the control signal (selector), and the output are coupled via standardized, unidirectional adapters. This enables a clean structure and a reduction in connection lines within the 4diac IDE.

## Interface Structure

### **Event Inputs**

* **EI0**: Receives and sets the value present at `IN0`.

### **Event Outputs**

* *(No direct event outputs are available. Event forwarding is encapsulated via the output plug `OUT`)*

### **Data Inputs**

* **IN0** (REAL): The first selectable input value (selected when the selection signal is `FALSE`).

### **Data Outputs**

* (No direct data outputs are available. Data is routed encapsulated via the output plug `OUT`)*

### **Adapters**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AR`): The selected output value.
* **IN1** (Socket, Type: `adapter::types::unidirectional::AR`): The second selectable input value.
* **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector (selection switch). Controls which input is routed to the output.

## Functionality

The internal behavior of the function block is implemented through a network of standard selection blocks (`F_SEL`), signal copiers (`F_MOVE`), and event D flip-flops (`E_D_FF` / `E_D_FF_ANY`):

1. **Value Buffering**: The input values of `IN0` (via `EI0`), `IN1` (via the adapter event `IN1.E1`), and the selection signal `G` (via the adapter event `G.E1`) are buffered internally upon the occurrence of the respective event. Flip-flops are cached.
2. **Selection Logic**: The internal block `F_SEL` evaluates the signal from selector `G.D1`:
* If the signal at the selector adapter is **FALSE**, the value of `IN0` is selected.
* If the signal at the selector adapter is **TRUE**, the value of adapter `IN1` (via `IN1.D1`) is selected.
3. **Output**: The selected value is transferred to the output plug `OUT.D1` via a conversion step (`F_MOVE_OUT`), and the output event `OUT.E1` is triggered simultaneously.

## Technical Features

* **Mixed Operation**: Enables direct bridging between classic data lines (such as `IN0`) and structured adapter interfaces.
* **Safe Event Processing**: The use of event D flip-flops ensures that data values are only transferred upon valid edge events, preventing inconsistent states and signal glitches.
* **Unidirectional Adapters**: The use of the types `AR` (Analog Real) and `AX` (Analog Boolean/Selection) optimizes data flow for pure sender-receiver structures without a return channel.

## State Overview

As a network function block (composite FB), this module does not have its own explicit state machine (ECC). Its behavior is purely data- and event-driven:

| Triggering Event | State Selector `G` | Resulting Action |
| :--- | :--- | :--- |
| `EI0` | `FALSE` | The value of `IN0` is output to `OUT.D1`; `OUT.E1` is triggered. |
| `EI0` | `TRUE` | The value is updated internally but has no effect on the output. |
| `IN1.E1` | `TRUE` | The value of `IN1.D1` is output to `OUT.D1`; `OUT.E1` is triggered. |
| `IN1.E1` | `FALSE` | The value is updated internally but has no effect on the output. |
| `G.E1` | Signal change | The output is immediately re-evaluated and output based on the new state of `G.D1`. |

## Application Scenarios

* **Setpoint Switching**: Switching between a manually set fixed value (via `IN0` on an HMI) and an automatic profile value (via the adapter input `IN1`).
... * **Signal Bypass**: Activation of an emergency or default value in case of sensor malfunctions in the main branch (`IN1`).

* **Modular Plant Design**: Coupling of subsystems where signals need to be transported via adapters in a space-saving manner and switched as required.

## Comparison with Similar Function Blocks

Compared to a standard IEC 61131-3 function block `F_SEL`, `REAL_AR_AX_SEL_AR` offers the advantage that the signal paths do not need to be individually wired as loose data lines. The consolidation of data and events in the adapters `IN1`, `G`, and `OUT` results in a significantly clearer and more maintainable application landscape in the 4diac IDE.

## Conclusion

The `REAL_AR_AX_SEL_AR` is a highly practical utility module for modern and structured programming with 4diac. It is ideally suited for reducing the complexity of signal and event cabling during selection and switching operations of floating-point values.