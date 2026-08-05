# AX_T_FF_SR_SYM
![AX_T_FF_SR_SYM](./AX_T_FF_SR_SYM.svg)
* * * * * * * * * *
## Introduction
The AX_T_FF_SR_SYM function block is an event-driven bistable toggle switch with an additional toggle function and symmetrical start behavior. It combines the characteristics of an SR flip-flop (set and reset) with those of a T flip-flop (toggling on every clock signal). The behavior after power-on is symmetrical, meaning the block is initially in a neutral start state and only transitions to a defined state upon an event.
## Interface Structure
### **Event Inputs**
- **S** – Set: Sets output Q to TRUE.
- **R** – Reset: Sets output Q to FALSE.
- **CLK** – Clock: Toggles the output Q (TRUE → FALSE or FALSE → TRUE).

### **Event Outputs**
No direct event outputs. The state is output via adapter Q. The adapter triggers event Q.E1 upon a state change.

### **Data Inputs**
None.

### **Data Outputs**
No direct data outputs. The current value is provided via adapter Q (Q.D1).

### **Adapters**
- **Q**: Adapter of type `adapter::types::unidirectional::AX` (unidirectional). Provides the current state of the flip-flop as a Boolean value (TRUE/FALSE). The adapter triggers event Q.E1 after each state change.

#
## ## Functionality

The function block (FB) has three event inputs and a state machine with three states: `START`, `SET`, and `RESET`.

- **START** is the initial state after power-on. In this state, no algorithm is active, and the output value is undefined.
- Upon receiving `S` or `CLK`, the FB transitions to state `SET`.
- Upon receiving `R`, it transitions to state `RESET`.
- In the **SET** state, the algorithm `SET` is executed: `Q.D1 := TRUE`. Then, the event `Q.E1` is triggered.
- At `R` or `CLK`, the function block transitions to the state `RESET`.
- In the **RESET** state, the algorithm `RESET` is executed: `Q.D1 := FALSE`. Then, `Q.E1` is triggered.

``` - At `S` or `CLK`, the function block (FB) switches back to state `SET`.

The toggle function is implemented by the `CLK` transitions: regardless of the current state, `CLK` leads to the other state.

## Technical Features
- **Symmetrical Start Behavior**: After power-on, the FB is in the neutral `START` state. Only the first event determines the initial state. This allows for a defined system initialization.
- **Adapter-Based Output**: Instead of a direct data output, the state is provided via an adapter (`AX`). This enables flexible coupling with other function blocks and easy event propagation.
- **Combination of SR and T flip-flops**: This component combines set, reset, and toggle functions in a single compact unit.

## State Overview

| State | Description | Output Q.D1 | Event by Algorithm |

|---------|---------------|--------------|----------------------------|

| START | Initial state, no defined value | undefined | - |

| SET | Output is set to TRUE | TRUE | Q.E1 |

| RESET | Output is set to FALSE | FALSE | Q.E1 |

Transitions (Event → Target State):

- START → SET: `S`, `CLK`
- START → RESET: `R`
- SET → RESET: `R`, `CLK`
- RESET → SET: `S`, `CLK`

## Application Scenarios
- **Control of Binary Outputs**: An output can be set, reset, or toggled (e.g., manual operation with Set/Reset and automatic toggling via a clock signal).
- **Toggle Switching**: A process that changes its state with each clock signal but can also be explicitly set or reset.
- **Defined Start Sequences**: The symmetrical start behavior ensures that the component does not output any value after being powered on until a command arrives.

## Comparison with Similar Components
- **E_SR (Pure SR Flip-Flop)**: Has only Set and Reset inputs, no toggle function. After startup, the output is typically FALSE.
- **E_T (Toggle Flip-Flop)**: Only a toggle input, no Set/Reset.
- **AX_T_FF_SR_SYM**: Combines all three functions and additionally offers a neutral start state, allowing for flexible initialization.

## Conclusion
The AX_T_FF_SR_SYM is a versatile function block for binary state logic. The combination of Set, Reset, and Toggle, as well as the symmetrical start behavior, makes it particularly suitable for applications requiring both manual control and automatic switching. The adapter interface facilitates integration into modular systems such as IEC 61499.
