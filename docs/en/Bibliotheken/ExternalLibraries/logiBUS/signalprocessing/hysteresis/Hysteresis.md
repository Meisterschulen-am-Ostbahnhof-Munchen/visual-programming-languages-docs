# Hysteresis
![Hysteresis](./Hysteresis.svg)

* * * * * * * * * *
## Introduction
The **Hysteresis** function block converts an analog input signal (REAL) into a digital output signal (BOOL). It operates with an adjustable hysteresis threshold to ensure stable switching behavior and prevent oscillations at the threshold. The switching points are arranged symmetrically around a mean value (THRESHOLD).
## Interface Structure

### **Event Inputs**

| Event | Type | Description | With Data |

|----------|-------|--------------------------------------------------------|---------------------------|

| INIT | EInit | Initialization request; activates or deactivates the function block. | QI |

| REQ | Event | Normal processing request; Performs the hysteresis calculation. | QI, INPUT, THRESHOLD, HYSTERESIS |

### **Event Outputs**

| Event | Type | Description | With Data |

|----------|-------|------------------------------------------------------------|----------------------------|

| INITO | EInit | Acknowledges the initialization/deinitialization request. | QO |

| CNF | Event | Acknowledges normal processing; outputs the hysteresis result. | OUTPUT |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------------|-------|-------------|---------------------------------------------------------------------------------------------------|

| QI | BOOL | – | Input qualifier; switches the module on (TRUE) or off (FALSE). |

| INPUT | REAL | – | Analog input value being monitored. |

| THRESHOLD | REAL | 0.0 | Midpoint of the hysteresis band. The switch-on threshold is THRESHOLD + (HYSTERESIS / 2). |

| HYSTERESIS | REAL | 0.1 | Width of the hysteresis band. Using ABS(HYSTERESIS) always guarantees a positive margin. |

### **Data Outputs**

| Name | Type | Description |

|--------|-------|------------------------------------------------------------------|

| QO | BOOL | Output qualifier; takes the value of QI when processing is active. |

| OUTPUT | BOOL | Hysteresis output; TRUE when the input exceeds the turn-on point, FALSE until it falls below the turn-off point. |

### **Adapters**

No adapters available.

## Functionality

This module performs **analog-to-digital conversion with hysteresis**. The switching points are calculated as follows:

- **Turn-on point**: `THRESHOLD + ABS(HYSTERESIS) / 2.0`

(Inclusive comparison: `INPUT >= ...`)

- **Turn-off point**: `THRESHOLD - ABS(HYSTERESIS) / 2.0`

(Strict comparison: `INPUT < ...`)

By using `ABS(HYSTERESIS)`, the hysteresis remains symmetrical even if a negative value is passed. The strict turn-off comparison (strict inequality) prevents oscillations at the switching point.

Initialization (`INIT`) and normal operation (`REQ`) are controlled by the qualifier `QI`. The function block operates as long as `QI = TRUE` is present; it deinitializes (outputs go to FALSE) when `QI = FALSE` is present.

## Technical Features
- **Symmetrical Hysteresis**: `ABS(HYSTERESIS)` ensures the hysteresis width is always positive.
- **Strict Turn-Off Condition**: The condition `INPUT < THRESHOLD - (ABS(HYSTERESIS) / 2.0)` prevents erratic behavior when values are exactly the same.
- **State Control via QI**: A `INIT` event with `QI = FALSE` deactivates the function block and resets all outputs.
- **Fault Tolerance**: If the function block is deactivated (`QI = FALSE`), the output `OUTPUT` is set to FALSE.

## State Overview

The function block goes through the following states:

| State | Description |

|---------|-------------------------------------------------------------------------------------------------|

| START | Initial sleep state after power-on. Waits for an INIT event with QI=TRUE. |

| Init | Initialization: Sets `QO = QI` and `OUTPUT = FALSE`. Sends INITO. |

| sOFF | Normal state with output off (OUTPUT=FALSE). Waits for REQ or INIT with QI=FALSE. |

| sON | State with output on (OUTPUT=TRUE). Waits for REQ to check the off point. |

| DeInit | Deinitialization: Sets `QO = FALSE` and `OUTPUT = FALSE`. Sends INITO and returns to START. |

**Transitions:**

- `START → Init` at `INIT[QI = TRUE]`
- `Init → sOFF` at `REQ`
- `sOFF → sON` at `REQ[INPUT >= THRESHOLD + ABS(HYSTERESIS)/2.0]` (Turn on)
- `sON → sOFF` at `REQ[INPUT < THRESHOLD - ABS(HYSTERESIS)/2.0]` (Turn off)
- `sOFF → DeInit` at `INIT[QI = FALSE]`
- `DeInit → START` immediately after deinitialization

## Application Scenarios
- **Temperature Control**: A heating system switches on when an upper threshold is reached and off when a lower threshold is reached, to prevent frequent To avoid switching on and off.
- **Level Monitoring**: Signals "full" or "empty" with hysteresis to protect pumps from continuous cycling.
- **Pressure Switch**: Triggers alarms or valves when pressure is exceeded, with a defined reset point.
- **Light Sensor**: Hysteresis prevents flickering in ambient light near the switching threshold.

## Comparison with Similar Function Blocks

| Function Block | Property |

|--------------------------------|-------------------------------------------------------------------------------------------------|

| **Hysteresis** (of this FB) | Provides symmetrical hysteresis around a mean value, flexible adjustment of width and switching point, strict switch-off condition. |

| **Simple Threshold Switch** | No hysteresis; switches at the exact threshold, which can lead to oscillation. |

| **Schmitt Trigger** | Has two fixed thresholds (upper and lower); Similar to hysteresis, but often without adjustable width. |

**Comparator with Flip-Flop** | Combines a comparator with a flip-flop; also implements hysteresis, but requires more logic. |

## Conclusion

The **Hysteresis** function block offers robust, adjustable analog-to-digital conversion with hysteresis. The use of `ABS(HYSTERESIS)` and the strict off-condition ensures stable and predictable switching behavior. Control viaThe `QI` state machine is suitable for both initialization phases and continuous operation. It is ideal for all applications requiring a digital output with defined switching thresholds.
