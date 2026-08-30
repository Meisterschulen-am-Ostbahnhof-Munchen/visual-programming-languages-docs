# E_RF_TRIG

* * * * * * * * * *

## Introduction

`E_RF_TRIG` (rising/falling trigger) detects both rising and falling edges of a `BOOL` value and reports them via two separate output events. It combines the functionality of `E_R_TRIG` (rising edge) and `E_F_TRIG` (falling edge) in a single block.

![E_RF_TRIG](E_RF_TRIG.svg)

## Interface Structure

### **Event Inputs**

- **EI**: Checks `QI` for a rising or falling edge.
    - **Connected data**: `QI`

### **Event Outputs**

- **ER**: Confirms a detected rising edge (`QI` from `FALSE` to `TRUE`).
- **EF**: Confirms a detected falling edge (`QI` from `TRUE` to `FALSE`).

### **Data Inputs**

- **QI** (BOOL): The value to check for edge transitions.

## Functionality

Internally, an `E_D_FF` stores the last known value of `QI` and, on every `EI` event, delivers the new value via its `EO` to an `E_SWITCH`. Depending on the current `Q` value (`G` input), this forwards the event either to `EO1` (→ `ER`, rising edge) or `EO0` (→ `EF`, falling edge). Since `E_D_FF` only triggers `EO` on an actual change of `Q`, neither `ER` nor `EF` is triggered for an unchanged `QI`.

## Technical Features

- **Composed of two standard blocks**: `E_D_FF` (change detection) + `E_SWITCH` (branch by value), no ECC of its own.
- **Only on actual change**: Repeated `EI` events with unchanged `QI` produce no output event, since `E_D_FF` already filters internally.
- **Basis for [E_TLIM](timers/E_TLIM.md)**: There, `E_RF_TRIG` is used to detect the start (`ER`) and end (`EF`) of a `TRUE` state.

## State Overview

Stateless wiring logic: the only stored state is the last known `QI` value inside the internal `E_D_FF`.

## Application Scenarios

- **Edge detection without two separate blocks**: Wherever both the start and the end of a `TRUE` state need to be detected (e.g. start and end of a signal), `E_RF_TRIG` saves a second block compared to using `E_R_TRIG`/`E_F_TRIG` separately.
- **Duration measurement of states**: Combined with `E_DELAY`/`E_SR` (see [E_TLIM](timers/E_TLIM.md)) to measure how long a `BOOL` signal remains in a state.

## Comparison with similar function blocks

- **`E_R_TRIG`**: detects only rising edges.
- **`E_F_TRIG`**: detects only falling edges.
- **[E_TLIM](timers/E_TLIM.md)**: uses `E_RF_TRIG` internally to time-limit a `TRUE` state.

## Conclusion

`E_RF_TRIG` provides compact, combined edge detection for rising and falling transitions of a `BOOL` signal and is a building block for more complex timing and state logic such as `E_TLIM`.
