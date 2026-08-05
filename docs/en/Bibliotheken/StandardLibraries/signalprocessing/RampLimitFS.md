# RampLimitFS
<img width="842" height="294" alt="RampLimitFS" src="https://github.com/user-attachments/assets/29d36f04-bd95-4ebf-ae98-807414c5e6b9" />
* * * * * * * * * *
## Introduction
The function block `RampLimitFS` is used to incrementally increase or decrease an output value at different speeds (fast/slow), similar to a cruise control function in vehicles. It also allows you to set minimum and maximum values and load a predefined value.
![RampLimitFS](RampLimitFS.svg)
## Interface Structure
### **Event Inputs**
- `ZERO`: Sets the output `OUT` to the value of `VAL_ZERO`.

![RampLimitFS](RampLimitFS.svg)

## Interface Structure
### **Event Inputs**
- `ZERO`: Sets the output `OUT` to the value of `VAL_ZERO`.
- `UP_SLOW`: Increments the value of `OUT` by the value of `SLOW`.
- `UP_FAST`: Increments the value of `OUT` by the value of `FAST`.
- `DOWN_SLOW`: Decrements the value of `OUT` by the value of `SLOW`.
- `DOWN_FAST`: Decrements the value of `OUT` by the value of `FAST`.
- `FULL`: Sets `OUT` to the value of `VAL_FULL`.
- `LOAD`: Loads the value of `PV` into `OUT`.

### **Event Outputs**
- `CNF`: Confirms execution and outputs the current value of `OUT`.

### **Data Inputs**
- `PV` (DINT): Preset value loaded with `LOAD`.

### - `VAL_ZERO` (DINT): Minimum value for `OUT`.
- `SLOW` (DINT): Step size for slow changes.
- `FAST` (DINT): Step size for fast changes.
- `VAL_FULL` (DINT): Maximum value for `OUT`.

### **Data Outputs**
- `OUT` (DINT): Current output value.

### **Adapters**
No adapters available.

## Functionality

This function block allows for incremental adjustment of the output value `OUT` based on various events:

- **Incremental Increase/Decrease**:
- `UP_SLOW`/`DOWN_SLOW`: Changes `OUT` by the value `SLOW`.
- `UP_FAST`/`DOWN_FAST`: Changes `OUT` by the value `FAST`.
- **Direct Value Assignment**:
- `ZERO` sets `OUT` to `VAL_ZERO`.
- `FULL` sets `OUT` to `VAL_FULL`.
- `LOAD` loads the value from `PV` into `OUT`.

The output value is always limited to the boundaries `VAL_ZERO` (minimum) and `VAL_FULL` (maximum).

## Technical Features
- **Output Value Limitation**:

The value of `OUT` is automatically limited to the defined limits (`VAL_ZERO`, `VAL_FULL`) if the step sizes (`SLOW`, `FAST`) would exceed them.

- **Flexible Step Sizes**:

Different value change rates are possible using `SLOW` and `FAST`.

## State Overview

The function block has no internal state. Each event immediately triggers the corresponding calculation and output.

## Application Scenarios
- **Cruise Control**: Stepwise speed adjustment with slow/fast key presses.
- **Process Control**: Limited setpoint specification with manual fine-tuning.
- **Parameter Loading**: Loading predefined values (e.g., from non-volatile memory).

## ⚖️ Comparison with Similar Function Blocks
- **Comparison with Standard Ramp Functions**:

RampLimitFS` additionally offers the option to switch between fast and slow step sizes and assign direct values (min/max).

- **Flexibility**:

Unlike simple counters, this function block allows for dynamic adjustment of step sizes and limits.

## 🛠️ Related Exercises
* [Exercise_009a](../../../Uebungen/test_B/Uebungen_doc/Uebung_009a.md)]

## Conclusion
The `RampLimitFS` function block is ideal for applications where a value needs to be adjusted stepwise within defined limits. By differentiating between fast and slow changes and offering the ability to load direct values, it provides a high degree of flexibility for various control tasks.
