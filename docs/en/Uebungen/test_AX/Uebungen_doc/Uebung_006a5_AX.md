# Exercise_006a5_AX: SR and T Flip-Flop as a Latching/Momentary Implementation

![Uebung_006a5_AX_network](./Uebung_006a5_AX_network.svg)

* * * * * * * * * *

## Introduction

The exercise `Uebung_006a5_AX` shows how a **single physical pushbutton** (`Input_I1`) can be used to realize both **latching** (switch-like) and **momentary** (toggle-like) operating behavior. Unlike `Uebung_006a_AX`, which needs three separate pushbuttons (`I1`, `I2`, `I3`) for Set, Reset, and Toggle, this exercise evaluates different button gestures on a single input — long press, release after long press, and short click — and feeds them into the `AX_T_FF_SR` block.

This allows a single pushbutton to:

- **switch on firmly** (hold/long press → *latching*, like a switch),
- **switch off firmly** (release after a long press),
- **toggle** (short click → *momentary*, like a classic pushbutton).

## Function Blocks (FBs) Used

| FB Name | Type | Parameters |
| --------- | ----- | ----------- |
| `BUTTON_LONG_PRESS_START` | `logiBUS::io::DI::logiBUS_IE` | Input = `Input_I1`, InputEvent = `BUTTON_LONG_PRESS_START` |
| `BUTTON_LONG_PRESS_UP` | `logiBUS::io::DI::logiBUS_IE` | Input = `Input_I1`, InputEvent = `BUTTON_LONG_PRESS_UP` |
| `BUTTON_SINGLE_CLICK` | `logiBUS::io::DI::logiBUS_IE` | Input = `Input_I1`, InputEvent = `BUTTON_SINGLE_CLICK` |
| `AX_T_FF_SR` | `adapter::events::unidirectional::AX_T_FF_SR` | (no parameters) |
| `DigitalOutput_Q1` | `logiBUS::io::DQ::logiBUS_QXA` | Output = `Output_Q1` |

- **`logiBUS_IE`**: Event input block that turns the raw button signal from `Input_I1` into recognized button gestures (e.g. click, double click, long press) as events. The `InputEvent` parameter determines which specific gesture each block reacts to; its `IND` output fires once the configured gesture is detected. All three `logiBUS_IE` blocks in this exercise listen to the **same** physical input `Input_I1`, but each filters out a different gesture.
- **`AX_T_FF_SR`**: Combines Set (`S`), Reset (`R`), and Toggle (`CLK`) in a single block with adapter output `Q`. `S` forces the output to `TRUE`, `R` forces it to `FALSE`, `CLK` toggles the current state.
- **`logiBUS_QXA`**: Digital output that forwards the adapter signal `Q` to the physical output `Output_Q1`.

The network also contains a plain comment block ("Universal input: this way we can work with a pushbutton OR a switch.") noting that the same wiring works whether the physical input is a momentary pushbutton or a latching switch.

## Program Flow and Connections

1. **Gesture detection**: All three `logiBUS_IE` blocks read the same input `Input_I1`, but each recognizes its own gesture:
   - `BUTTON_LONG_PRESS_START` → fires once the button has been held long enough (start of the long press).
   - `BUTTON_LONG_PRESS_UP` → fires when the button is released after a long press.
   - `BUTTON_SINGLE_CLICK` → fires on a short, single click.
2. **Wiring to the flip-flop** (`EventConnections`):
   - `BUTTON_LONG_PRESS_START.IND` → `AX_T_FF_SR.S` (long press **starts** → output is set)
   - `BUTTON_LONG_PRESS_UP.IND` → `AX_T_FF_SR.R` (release after long press → output is reset)
   - `BUTTON_SINGLE_CLICK.IND` → `AX_T_FF_SR.CLK` (short click → output is toggled)
3. **Output** (`AdapterConnections`): `AX_T_FF_SR.Q` → `DigitalOutput_Q1.OUT` → physical output `Output_Q1`.

## How the AX_T_FF_SR Works

The `AX_T_FF_SR` block has three internal states: `START`, `SET`, and `RESET`:

- In state `SET`, `Q = TRUE`; in state `RESET`, `Q = FALSE`.
- An `S` event always switches to state `SET` (`Q := TRUE`).
- An `R` event always switches to state `RESET` (`Q := FALSE`).
- A `CLK` event **toggles** between `SET` and `RESET` (from `SET` it goes to `RESET` and vice versa).

Translated to operating a single pushbutton, this gives:

- **Hold (long press)** → `S` → the output goes reliably to `TRUE` (behaves like a *latching* switch that "clicks in" to on).
- **Release after a long press** → `R` → the output goes reliably to `FALSE`.
- **Short click** → `CLK` → the output toggles its state (behaves like a classic *momentary* pushbutton).

This lets a single pushbutton provide both a deterministic "on"/"off" (via a long press) and a convenient toggle (via a short click), without needing multiple buttons.

## Application Example

**Smart home lighting control with a single pushbutton:**

- Short click on the wall switch: toggle the light on/off (`CLK`).
- Hold the button down: force the light on regardless of its previous state (`S`) — e.g. for guests who don't know the current state.
- Release after holding: force the light off (`R`) — e.g. when leaving the room.

## Learning Objectives

- Understanding how different button gestures (`BUTTON_LONG_PRESS_START`, `BUTTON_LONG_PRESS_UP`, `BUTTON_SINGLE_CLICK`) turn **one** physical input into several logical events.
- Understanding the combined Set/Reset/Toggle behavior of `AX_T_FF_SR`.
- Recognizing the advantage over `Uebung_006a_AX`: identical Set/Reset/Toggle behavior, but with a single pushbutton instead of three.
- Distinguishing between *latching* (held) and *momentary* (pulsed) operation on one and the same button.

**Difficulty Level**: Medium

**Prerequisites**: `Uebung_006a_AX` (SR/T flip-flop with three pushbuttons), basics of logiBUS button events (`logiBUS_IE`).

## Summary

The exercise `Uebung_006a5_AX` shows how the all-in-one block `AX_T_FF_SR` can be operated with a single pushbutton by having three `logiBUS_IE` blocks evaluate the same physical input source `Input_I1` for different gestures. A long press sets and releasing it resets, while a short click toggles — combining latching and momentary behavior in a single button.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
