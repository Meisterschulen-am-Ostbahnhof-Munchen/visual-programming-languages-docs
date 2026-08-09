# E_SR_SYM

![E_SR_SYM](./E_SR_SYM.svg)

* * * * * * * * * *
## Introduction

The E_SR_SYM function block is an event-driven bistable element with symmetric start behavior. It implements a flip-flop that responds to set and reset events and whose initial state is not predetermined but is determined by the first arriving event.
## Interface Structure

### **Event Inputs**

- **S** (Event): Sets the output \( Q \) to `TRUE`.
- **R** (Event): Sets the output \( Q \) to `FALSE`.

### **Event Outputs**

- **EO** (Event): Triggered when the value of \( Q \) changes (after an S or R event). The output data memory \( Q \) is assigned to this event (`With Var="Q"`).

### **Data Inputs**

None.

### **Data Outputs**

- **Q** (BOOL): Current logical state of the flip-flop (`TRUE` or `FALSE`).

### **Adapters**

None.

## Functionality

The function block operates in a state-based manner and has three states:

- **START** – Initial state after powering on or resetting the controller.
- **SET** – State after a Set event.
- **RESET** – State after a reset event.

If an event arrives at **S** while the device is in the START state, it switches to the SET state, sets \( Q := \text{TRUE} \), and sends the **EO** event. If, instead, an event arrives at **R**, it switches to RESET, sets \( Q := \text{FALSE} \), and also sends **EO**.

If the device is already in one of the active states (SET or RESET), it can be switched by the other event. This results in symmetrical behavior: Neither S nor R has a priority – the last received pulse determines the output.

If the device is already in one of the active states (SET or RESET), it can be switched by the other event.
## Technical Features

- **Symmetrical Start Behavior:** Unlike classic SR flip-flops, which deliver a fixed initial value (usually `FALSE`) after startup, E_SR_SYM waits in the START state for the first event. Until then, the output \( Q \) remains in an undefined or unset state. This allows for flexible initialization by the environment.
- **Three-State Machine:** The ECC uses the states START, SET, and RESET, as well as two algorithms (SET, RESET) in structured text.
- **Compact Interface:** Only two event inputs, one event output, and one data output – making it easy to integrate into larger control systems.

## State Overview

| State | Meaning | Action on Entry | Trigger for Transitions |
| |---------|-----------|----------------------|---------------------------|
| **START** | Initial state | None (Waiting for first event) | S → SET, R → RESET |
| **SET** | Output \( Q \) is `TRUE` | Execute algorithm SET (\( Q := \text{TRUE} \)), send EO | R → RESET |
| **RESET** | Output \( Q \) is `FALSE` | Execute algorithm RESET (\( Q := \text{FALSE} \)), send EO | S → SET |

Transitions:

- START → SET at **S**
- START → RESET at **R**
- SET → RESET at **R**
- RESET → SET at **S**

## Application Scenarios

- **Event-driven enable signals:** A binary enable signal is set by a set pulse and reset by a reset pulse.
- **Initially indeterminate systems:** Startup behavior where the first valid command (set or reset) determines the subsequent sequence.
- **Simple two-point control:** Switching actuators (e.g., valve open/close) using external command transmitters.
- **Toggle replacement:** Combination with downstream logic blocks also enables toggle functions.

## Comparison with Similar Function Blocks

The standard function block **E_SR** (or E_RS) typically has a predefined initial state (usually `FALSE`) and immediately resets to the RESET state after startup. In contrast, the initial state of E_SR_SYM is neutral (START), allowing for symmetrical handling of both events. Unlike dominant variants (E_SR with set dominance or E_RS with reset dominance), there is no priority here – the last event to arrive determines the output.

## Conclusion

The function block **E_SR_SYM** offers a flexible, event-driven bistable memory cell with symmetrical startup behavior. Its simple state machine and clear interface make it particularly suitable for control tasks where the initial state is not predefined but rather determined by the first impulse from the environment. This distinguishes it from classic SR modules and expands the toolbox for event-based automation solutions.
