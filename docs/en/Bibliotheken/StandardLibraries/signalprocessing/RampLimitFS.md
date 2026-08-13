# RampLimitFS

<img width="842" height="294" alt="RampLimitFS" src="https://github.com/user-attachments/assets/29d36f04-bd95-4ebf-ae98-807414c5e6b9" />

* * * * * * * * * *
## Introduction

The `RampLimitFS` function block incrementally increases or decreases an output value at different speeds (fast/slow), similar to a cruise control function in vehicles. It also allows you to set minimum and maximum values and load a predefined value.

![RampLimitFS](RampLimitFS.svg)

## Interface Structure

### **Event Inputs**

- `INIT`: Initializes all data inputs (`PV`, `VAL_ZERO`, `SLOW`, `FAST`, `VAL_FULL`) together and sets `OUT` to `VAL_ZERO`. **Must be fired once before any other event** — without `INIT`, e.g. `VAL_FULL` stays at its default value of 0 until `FULL` itself has fired once, which breaks the clamp in `UP_SLOW`/`UP_FAST` (see Technical Details).
- `ZERO`: Sets the output `OUT` to the value of `VAL_ZERO`.
- `UP_SLOW`: Increments `OUT` by the value of `SLOW`.
- `UP_FAST`: Increments `OUT` by the value of `FAST`.
- `DOWN_SLOW`: Decrements `OUT` by the value of `SLOW`.
- `DOWN_FAST`: Decrements `OUT` by the value of `FAST`.
- `FULL`: Sets `OUT` to the value of `VAL_FULL`.
- `LOAD`: Loads the value of `PV` into `OUT`.

### **Event Outputs**

- `INITO`: Confirms initialization (response to `INIT`) and outputs the current value of `OUT`.
- `CNF`: Confirms execution and outputs the current value of `OUT`.

### **Data Inputs**

- `PV` (DINT): Preset value, loaded with `LOAD`.
- `VAL_ZERO` (DINT): Minimum value for `OUT`.
- `SLOW` (DINT): Step size for slow changes.
- `FAST` (DINT): Step size for fast changes.
- `VAL_FULL` (DINT): Maximum value for `OUT`.

### **Data Outputs**

- `OUT` (DINT): Current output value.
- `qAtZero` (BOOL): `TRUE` if `OUT` is at or below `VAL_ZERO` (lower limit reached).
- `qAtFull` (BOOL): `TRUE` if `OUT` is at or above `VAL_FULL` (upper limit reached).

### **Adapters**

No adapters available.

## Functionality

This function block allows for incremental adjustment of the output value `OUT` through various events:

- **Incremental Increase/Decrease**:
  - `UP_SLOW`/`DOWN_SLOW`: Changes `OUT` by the `SLOW` value.
  - `UP_FAST`/`DOWN_FAST`: Changes `OUT` by the `FAST` value.
- **Direct Value Assignment**:
  - `ZERO` sets `OUT` to `VAL_ZERO`.
  - `FULL` sets `OUT` to `VAL_FULL`.
  - `LOAD` loads the value of `PV` into `OUT`.

The output value is always clamped to the boundaries `VAL_ZERO` (minimum) and `VAL_FULL` (maximum).

## Technical Details

- **Output Value Limitation**:
  The value of `OUT` is automatically clamped to the defined limits (`VAL_ZERO`, `VAL_FULL`) if the step sizes (`SLOW`, `FAST`) would exceed them.

- **Flexible Step Sizes**:
  Different rates of change via `SLOW` and `FAST`.

- **`INIT` is mandatory before the first event**:
  Each event only reads the data inputs it needs for its own calculation, as declared via its `WITH` list — e.g. `UP_SLOW` reads `SLOW` **and** `VAL_FULL` (for clamping), `DOWN_SLOW` reads `SLOW` **and** `VAL_ZERO`. Without a preceding `INIT` call, these values have never been assigned a valid value and sit at their default of 0 — usually unnoticed for `VAL_ZERO`, but for `VAL_FULL` every `UP_SLOW`/`UP_FAST` step then immediately clamps to 0.

- **Limit detection via `qAtZero`/`qAtFull`**:
  Every event (including `INIT`) recomputes `qAtZero := OUT <= VAL_ZERO` and `qAtFull := OUT >= VAL_FULL` after the actual value change and outputs both alongside `INITO`/`CNF`. A calling block therefore doesn't need to check the limits itself - useful e.g. to hide a control when a limit is reached (see `ScrollFS`/`ScrollFS_PHYS` in `isobus::UT::Q`, which use exactly this for the scroll arrow buttons).

## State Overview

The function block has no internal state. Each event immediately triggers its corresponding calculation and output. The one exception: `INIT` must run once before all other events, so that `VAL_ZERO`/`VAL_FULL`/`SLOW`/`FAST`/`PV` have a defined value in the block at all.

## Application Scenarios

- **Cruise Control**: Stepwise speed adjustment with slow/fast key presses.
- **Process Control**: Limited setpoint specification with manual fine-tuning.
- **Parameter Loading**: Loading predefined values (e.g., from non-volatile memory).

## ⚖️ Comparison with Similar Blocks

- **Comparison with Standard Ramp Functions**:
  `RampLimitFS` additionally offers the option to switch between fast and slow step sizes and assign direct values (min/max).

- **Flexibility**:
  Unlike simple counters, this function block allows for dynamic adjustment of step sizes and limits.

## 🛠️ Related Exercises

* [Exercise_009a](../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)

## Conclusion

The `RampLimitFS` function block is ideal for applications where a value needs to be adjusted stepwise within defined limits. By differentiating between fast and slow changes and offering the ability to load direct values, it provides a high degree of flexibility for various control tasks.
