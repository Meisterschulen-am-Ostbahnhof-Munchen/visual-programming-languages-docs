# FB_SR_T_FF

![FB_SR_T_FF](./FB_SR_T_FF.svg)

* * * * * * * * * *
## Introduction

The function block `FB_SR_T_FF` implements a bistable, set-dominant RS flip-flop with an additional toggle function. The circuit combines the behavior of an SR latch (set-dominant) with an edge-triggered T flip-flop, which toggles its output state on each clock cycle when neither set nor reset is active.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Normal execution command (triggers processing) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Execution Confirmation |

### **Data Inputs**

| Name | Type | Initial Value | Comment |
|------|-----|-------------|-----------|
| S1 | BOOL | - | Set Input (Dominant) |
| R | BOOL | - | Reset Input |
| CLK | BOOL | - | Clock Signal (Rising Edge Triggers Toggle) |

### **Data Outputs**

| Name | Type | Initial Value | Comment |
|------|-----|--------------|-----------|
| Q1 | BOOL | - | Output Signal |

### **Adapter**

No adapters available.

## Functionality

The function block is activated by an event at input `REQ`. On each execution, inputs `S1`, `R`, and `CLK` are sampled, and the internal state (`Q1`) is updated according to the following rules:

1. **Set Dominance:** If `S1 = TRUE` is active, `Q1` is set to `TRUE` (regardless of `R` and `CLK`).
2. **Reset:** If `S1 = FALSE` and `R = TRUE` are already set, `Q1` will be set to `FALSE`.

Reset: If `S1 = FALSE` and `R = TRUE` are already set, then `Q1` will be set to `FALSE`. ... 3. **Toggle on rising edge:** If neither `S1` nor `R` are active (`S1 = FALSE` and `R = FALSE`, respectively), and the current value of `CLK` is `TRUE`, whereas it was `FALSE` in the previous cycle (i.e., rising edge), the output `Q1` is inverted (`Q1 := NOT Q1`). Otherwise, `Q1` remains unchanged.

The internal auxiliary flag `EDGE` stores the last state of `CLK` to enable edge detection. Initially, it is `EDGE = TRUE`, so no rising edge is detected on the first execution unless `CLK` is `FALSE` from the start.

The algorithm is implemented in Structured Text (ST), and the acknowledgment event `CNF` is sent after each execution.

## Technical Features

- **Set-dominant behavior:** As long as `S1 = TRUE` is active, `R` is ignored. This prevents the undefined state of a classic RS flip-flop.

The algorithm is implemented in Structured Text (ST), and the acknowledgment event `CNF` is sent after each execution. - **Edge-Triggered Toggle:** The toggle function is triggered only on a rising edge of `CLK`, not on every clock cycle. This makes the behavior deterministic and allows synchronization with the clock signal.

- **Internal Edge Storage:** The internal marker `EDGE` stores the previous value of `CLK`. Initially set to `TRUE`, it prevents the first cycle from triggering the toggle.
- **Cyclic Processing:** Processing can be called any number of times; the function depends only on the current input values and the stored edge state.

## State Overview

The function block has a functional state machine with one state, `REQ`. This state executes the algorithm and then sends `CNF`. There are no other explicit states in the automaton, as the flip-flop behavior is purely data-driven within the algorithm.

| State | Incoming Events | Action | Outgoing Events |
|---------|-----------------------|--------|------------------------|
| REQ | REQ | Execute the algorithm, update `Q1` and `EDGE` | CNF |

## Application Scenarios

- **Control with Set/Reset Priority:** This function block is suitable for applications where Set takes precedence over Reset (e.g., safety circuits).
- **Toggle Function with Clock:** Combined with a clock, the output can toggle on every clock pulse, as long as no set or reset request is present. This can be used, for example, for modular counters or state machines.
- **Edge-Triggered Circuits:** In automation processes where state changes are only permitted at specific times (e.g., sampling).

## Comparison with Similar Components

Compared to a pure SR flip-flop (e.g., `SR_FF`), this component offers a built-in toggle function that can invert the output on every clock cycle. Compared to a T flip-flop (`T_FF`), this component also has set and reset inputs with dominance. The classic JK flip-flop has two controlling inputs (J, K) without dominance, while this component represents a combination of set-dominant and edge-triggered toggle functionality.

## Conclusion

The `FB_SR_T_FF` is a versatile, compact function block that combines the features of a set-dominant RS flip-flop and an edge-triggered T flip-flop. Thanks to its simple interface (one event input, three Boolean inputs), it can be easily integrated into existing control logic and is suitable for a wide variety of applications requiring a prioritized set/reset operation with an additional toggle function. Its implementation in structured text ensures clear readability and easy customization.
