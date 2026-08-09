# ILOCK_2_E

![ILOCK_2_E](./ILOCK_2_E.svg)

* * * * * * * * * *
## Introduction

The function block **ILOCK_2_E** is an event-driven bistable toggle block with dual interlock. It is used to control two mutually exclusive outputs (OUT1, OUT2). In addition to explicit set and reset functions, the block offers an edge-triggered toggle function that allows a single toggle per activation. The block is particularly suitable for control logics where both outputs must never be TRUE simultaneously and a repeated toggle command only takes effect after being released again (e.g., by setting the other channel or resetting).
## Interface Structure

### **Event Inputs**

| Event | Comment |
|----------|-----------|
| `SET1` | Sets OUT1 to TRUE and OUT2 to FALSE. |
CLK1` | Toggles OUT1 (upon initial activation after a set/reset) and sets OUT2 to FALSE. |
SET2` | Sets OUT2 to TRUE and OUT1 to FALSE. |
CLK2` | Toggles OUT2 and sets OUT1 to FALSE. |
R` | Resets both outputs to FALSE. |

### **Event Outputs**

| Event | Comment |
----------|-----------|
EO` | Triggered after every output change (SET, TOGGLE, or RESET). Stores the current values of OUT1 and OUT2. |

### **Data Inputs**

None (the function block is purely event-driven).

### **Data Outputs**

| Output | Type | Comment |
|---------|-------|-----------|
| `OUT1` | BOOL | First output (bistable value). |
| `OUT2` | BOOL | Second output (bistable value). |

### **Adapters**

None.

## Functionality

The function block has six states: the initial idle state **STOP** and five action states (**SET1**, **SET2**, **TOGGLE1**, **TOGGLE2**, **RESET**). Upon the occurrence of an event, the block immediately switches to the corresponding state, executes the associated algorithm, and then outputs the event `EO`. Afterward, the block immediately returns to the **STOP** state (condition `1` on all transitions).

The internal logic provides **dual interlocking**: When one output is set, the other is forcibly set to FALSE. Similarly, when one output is toggled, the other output is reset.

The **toggle function** is edge-triggered: The internal variables `EDGE1` and `EDGE2` store whether a toggle has already been executed on the corresponding channel. Only after a reset or a set of the other channel (`EDGE = FALSE`) is the toggle actually executed and the flag set to TRUE. Repeated CLK events without an intermediate set/reset of the same or the other channel are ignored.

## Technical Features

- **Edge Detection for Toggle** – The internal flags `EDGE1`/`EDGE2` prevent multiple toggling events with the same enable signal.
- **Always Exclusive Outputs** – Each algorithm ensures that both outputs are never TRUE simultaneously.
- **No Data Inputs** – All control is exclusively event-based, enabling easy integration into event-driven automation systems.
- **Robust Reset Behavior** – A reset clears both the outputs and the internal edge flags, making the toggle function available again.

## Status Overview

| Status | Description | Trigger | Algorithm Effect (Simplified) | Output |
|-------------|-----------------------------|----------|---------------------------------------------------------|---------|
| `STOP` | Initial, waits for event | - | – | – |
| `SET1` | Set Output 1 | `SET1` | OUT1=TRUE, OUT2=FALSE, EDGE1=FALSE, EDGE2=FALSE | `EO` |
| `SET2` | Set Output 2 | `SET2` | OUT1=FALSE, OUT2=TRUE, EDGE1=FALSE, EDGE2=FALSE | `EO` |
| `TOGGLE1` | Toggle Output 1 | `CLK1` | If EDGE1=FALSE: OUT1 = NOT OUT1; OUT2=FALSE; EDGE1=TRUE; EDGE2=FALSE | `EO` |
| `TOGGLE2` | Toggle Output 2 | `CLK2` | OUT1=FALSE; if EDGE2=FALSE: OUT2 = NOT OUT2; EDGE1=FALSE; EDGE2=TRUE | `EO` |
| `RESET` | Reset all outputs | `R` | OUT1=FALSE, OUT2=FALSE, EDGE1=FALSE, EDGE2=FALSE | `EO` |

All action states immediately revert to `STOP` after the algorithm is executed.

## Application Scenarios

- **Direction Control** (e.g., motor left/right) – both directions are never active simultaneously.
- **Pump Control with Priority** – two pumps, but only one may run at a time.
- **Mode Switching with Single Toggle** – e.g., "Start/Stop" behavior, where a repeated toggle command only takes effect after a reset or other action.
- **Interlocked Switching States in Safety Controllers** – guaranteed exclusivity of the outputs.

## Comparison with Similar Function Blocks

| Function Block | Properties |
|---------------|-------------------------------------------------------------------------------|
| `E_SR` | Simple set/reset flip-flop, no toggle, no dual locking. |
| `SR-Flipflop` (two outputs) | Often only combinatorial or without edge detection. |
| `ILOCK_2_E` | Offers both: **Set** (exclusive) and **edge-triggered toggle** with automatic locking. Ideal for advanced requirements. |

## Conclusion

The `ILOCK_2_E` function block is a powerful function block for applications with two mutually exclusive states. The combination of explicit setting, edge-triggered toggle, and robust reset behavior makes it particularly suitable for control logics that require a clear separation of outputs and a defined response to repeated commands. Integration into event-based automation systems (e.g., IEC 61499) is achieved through the purely event-driven interface and the unified output `EO`.
