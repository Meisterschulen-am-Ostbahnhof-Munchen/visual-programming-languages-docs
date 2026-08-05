# AX_SR_SYM
![AX_SR_SYM](./AX_SR_SYM.svg)

* * * * * * * * * *
## Introduction
The function block **AX_SR_SYM** is an event-driven, bistable flip-flop with symmetrical turn-on behavior. It implements a set/reset memory, which is accessed via the events `S` (Set) and `R` (Reset). Unlike similar function blocks, the start state is not predefined; the block reacts to the first arriving event – regardless of whether it is `S` or `R`.
## Interface Structure
### **Event Inputs**

| Name | Type | Description |

|------|-------|----------------------------|

| S | Event | Sets output Q to TRUE. |

| R | Event | Sets output Q to FALSE. |

### **Event Outputs**
None (the output value is provided via an adapter).

### **Data Inputs**
None.

### **Data Outputs**
None (the output value is provided via an adapter).

### **Adapter**

| Name | Type | Description |

|------|----------------------------------------------|---------------------------------------|

| Q | `adapter::types::unidirectional::AX` | Provides the current binary state. The adapter provides an event (`E1`) and a data value (`D1`). After each state change, `Q.E1` is triggered, and the new value is output to `Q.D1`.

## Functionality
The function block is based on a simple state machine with three states:

- **START**: Initial state after startup. No output value is output.
- **SET**: The output is set to TRUE. Upon entering this state, `Q.E1` is triggered, and `Q.D1` is set to `TRUE`.
- **RESET**: The output is set to FALSE. Upon entering this state, `Q.E1` is triggered, and `Q.D1` is set to `FALSE`.

Transitions occur exclusively through the events `S` and `R`. From the START state, both `S` and `R` lead to SET (symmetrical behavior). From SET, only `R` leads to RESET, and from RESET, only `S` leads back to SET.

## Technical Features
- **Symmetrical Start-up Behavior**: The function block starts in the START state without a defined output value. Only the first arriving event (S or R) determines the initial state. This differs from function blocks that initialize to FALSE or TRUE by default.
- **Adapter Interface**: The state is not directly transmitted as a data output, but via a unidirectional adapter (`AX`). Changes are signaled by an event (`Q.E1`), allowing the receiving function block to react asynchronously.

## State Overview

| State | Description |

|---------|------------------------------------------------------|

| START | Waiting for first event; no output value defined. |

| SET | Output value TRUE; set by event `S`. |

| RESET | Output value FALSE; reset by event `R`. |

**Transitions:**

- START → SET on event `S`
- START → RESET on event `R`
- SET → RESET on event `R`
- RESET → SET on event `S`

## Application Scenarios
- **Storing a binary state** in control logic where the initial value is defined by an event.
- **Event-driven switches** in conjunction with adapter-based communication patterns.
- **Replacing an SR flip-flop** when symmetrical turn-on behavior is required.

## Comparison with Similar Function Blocks
- **SR Flip-Flop** (e.g., `AX_SR`): Often has a defined initial value (e.g., FALSE) and behaves asymmetrically when both inputs are active simultaneously. In contrast, the `AX_SR_SYM` only sets its initial value upon the first event.
- **RS Flip-Flop**: Fundamentally similar logic, but with reversed priority (reset dominates). The `AX_SR_SYM` has no priority – the last received input determines the state.
- **Adapter-Based Function Blocks**: Advantage of event-driven state transfer via adapters; many standard function blocks use direct data outputs instead.

## Conclusion
The `AX_SR_SYM` is ideally suited for applications requiring bistable memory behavior with an undefined initial value. The symmetrical response to `S` and `R` in the startup state, as well as the output via an adapter, makes it a flexible component in event-driven automation systems.
