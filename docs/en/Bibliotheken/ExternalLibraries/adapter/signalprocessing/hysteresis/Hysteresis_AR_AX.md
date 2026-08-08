# Hysteresis_AR_AX

![Hysteresis_AR_AX](./Hysteresis_AR_AX.svg)

* * * * * * * * * *
## Introduction

The function block `Hysteresis_AR_AX` is a basic function block (BFB) for event-driven signal processing according to IEC 61499. It performs analog-to-digital conversion of an analog input signal, taking into account an adjustable hysteresis. This prevents small signal fluctuations or noise around a threshold value from causing rapid, unwanted switching back and forth of the digital output (oscillation).

## Interface Structure

### **Event Inputs**

* **INIT**: Initialization request (`EInit`). Enables or disables the block in conjunction with the input `QI`.


### **Event Outputs**

* **INITO**: Initialization Confirmation (`EInit`). Signals the completion of initialization or deinitialization in conjunction with `QO`.

### **Data Inputs**

* **QI** (BOOL): Input Event Qualifier. Determines whether the function block should be active (`TRUE`) or deinitialized (`FALSE`).

### **Data Outputs**

* **QO** (BOOL): Output Event Qualifier. Displays the current status of the function block activation.

### **Adapters**

The function block uses standardized, unidirectional adapters for clean, modular coupling of data and events.



The function block uses standardized, unidirectional adapters for clean, modular coupling of data and events.

* **Sockets (Input Adapters):**

* **INPUT** (`adapter::types::unidirectional::AR`): The analog input value to be monitored. The value is present at `INPUT.D1`; the evaluation is triggered by the event `INPUT.E1`.

* **THRESHOLD** (`adapter::types::unidirectional::AR`): The midpoint of the hysteresis band (`THRESHOLD.D1`).

* **HYSTERESIS** (`adapter::types::unidirectional::AR`): The total width of the hysteresis band (`HYSTERESIS.D1`).

* **Plugs (Output Adapters):**

* **OUTPUT** (`adapter::types::unidirectional::AX`): The digital output signal. Outputs the switching result at data point `OUTPUT.D1` (BOOL) and triggers the output via the event `OUTPUT.E1`.

## Functionality

The hysteresis is defined symmetrically around the threshold value (`THRESHOLD`). The total width of the hysteresis band is specified by the parameter `HYSTERESIS`.

### Calculation Formulas

To avoid misconfigurations, the absolute value of the hysteresis width (`ABS(HYSTERESIS.D1)`) is always used internally.


# 1. **Switch-on Condition:**

The output switches on (`OUTPUT.D1 := TRUE`) when the input value reaches or exceeds the upper limit of the hysteresis band:

$$\text{INPUT.D1} \ge \text{THRESHOLD.D1} + \frac{|\text{HYSTERESIS.D1}|}{2.0}$$

2. **Switch-off Condition:**

The output switches off (`OUTPUT.D1 := FALSE`) when the input value falls well below the lower limit of the hysteresis band:

$$\text{INPUT.D1} < \text{THRESHOLD.D1} - \frac{|\text{HYSTERESIS.D1}|}{2.0}$$

## Technical Features

* **Oscillation Prevention:** By using a A strict inequality ($<$) when switching off and a soft inequality ($\ge$) when switching on guarantees stable behavior at the exact limits of the hysteresis band.

* **Absolute Hysteresis:** By using the `ABS` function in the Execution Control Chart (ECC), the function block also functions correctly if a negative value is incorrectly passed for the hysteresis width.

* **Adapter-Based Architecture:** The use of unidirectional adapters (`AR` / `AX`) consolidates data and event lines. This significantly improves clarity in the application diagram.

## State Overview

The behavior is controlled via the following states in the Execution Control Chart (ECC):

1. **START**: Idle state before initialization.

2. **Init**: Resets output `OUTPUT.D1` and sets `QO := QI`.

3. **sOFF**: State of the off output. The algorithm `alOff` ensures that `OUTPUT.D1` is set to `FALSE`. A transition to `sON` occurs as soon as the on condition is met.

4. **sON**: State of the on output. The algorithm `alOn` sets `OUTPUT.D1` to `TRUE` (if `QI` is active). A transition back to `sOFF` occurs as soon as the shutdown condition is met.

5. **DeInit**: Deinitialization state. Resets the outputs in a controlled manner.

## Application Scenarios

* **Two-Point Temperature Control:** Controls a heating system. The heating system switches on when the temperature falls below the setpoint minus half the hysteresis and switches off again only when the temperature exceeds the setpoint plus half the hysteresis.

* **Level Control:** Switches pumps in tanks on and off. Prevents the pumps from switching continuously due to turbulent liquid surfaces (wave motion).

* **Limit Monitoring in Process Areas:** Converts noisy analog sensor values (e.g., pressure, flow rate) into stable digital alarm signals.


* ## Comparison with Similar Components

Unlike classic comparator components (such as `GT` or `LT`), which react immediately to even the slightest threshold violation, the `Hysteresis_AR_AX` buffers the signal through the defined band.

Compared to standard hysteresis circuits, which often use separate pins for data and trigger events, this component significantly simplifies signal routing in more complex 4diac applications thanks to its standardized adapter concept (`AR`/`AX`).

## Conclusion

The `Hysteresis_AR_AX` is a highly efficient and robust component for signal preprocessing. Thanks to its integrated absolute hysteresis calculation and asymmetric switching conditions, it offers high reliability in practical operation. The consistent use of adapters allows it to integrate seamlessly into modern, service-oriented control architectures.