# AX_RangeBasedPulse
![AX_RangeBasedPulse](./AX_RangeBasedPulse.svg)
* * * * * * * * * *
## Introduction
This function block generates a pulse on an AX adapter based on a distance traveled (adapter version). It is licensed under the Eclipse Public License 2.0 and designed for use in signal processing of distance data.
## Interface Structure

### **Event Inputs**
- `DIST_IN.E1`: Event from the distance adapter that signals an update of the distance value.

### **Event Outputs**
- `OUT.E1`: Event on the output adapter that is sent when the pulse output changes state.

### **Data Inputs**
- `DIST_HIGH` (UDINT): Distance in mm that must be traveled to generate the HIGH pulse (initial value: 5000).
- `DIST_LOW` (UDINT): Distance in mm that must be traveled to generate the LOW pulse (initial value: 5000).
- `DIST_IN.D1` (UDINT): Current distance from the input adapter (updated via the event).

### **Data Outputs**
- `OUT.D1` (BOOL): Pulse output – toggles between TRUE (HIGH) and FALSE (LOW) depending on the accumulated distance.

### **Adapters**
- **DIST_IN (Socket):** Adapter of type `adapter::types::unidirectional::AUDI`. Provides a unidirectional distance value (`D1`) and a corresponding event (`E1`).
- **OUT (Plug):** Adapter of type `adapter::types::unidirectional::AX`. Provides a unidirectional Boolean value (`D1`) and an event (`E1`).

## Functionality

The function block operates according to a hysteresis principle with two threshold values:

1. **Initialization:** During the first iteration (`FirstRun = TRUE`), the current distance is stored as the start value `LastDist`, the output `OUT.D1` is set to FALSE, and `FirstRun` is reset.

`` 2. **State Check:** On each incoming event via `DIST_IN.E1`, the block executes the `CHECK` algorithm:

- If the current output is LOW (FALSE) and the new distance `DIST_IN.D1` reaches or exceeds the value `LastDist + DIST_LOW`, `OUT.D1` is set to TRUE and `LastDist` is updated to the current distance value.
- If the output is HIGH (TRUE) and the new distance reaches or exceeds the value `LastDist + DIST_HIGH`, `OUT.D1` is set to FALSE and `LastDist` is updated.

3. **Output:** When the state of `OUT.D1` changes, the event `OUT.E1` is sent, and the new state is stored in `LastState` for the next check.

## Technical Features
- **Adapter-based Communication:** The use of plugs and sockets (`AX`, `AUDI`) enables modular and flexible interconnection in the 4diac IDE.
- **Asymmetric Pulse Widths:** The separate parameters `DIST_HIGH` and `DIST_LOW` allow for different distances for HIGH and LOW phases.
- **Asymmetric Pulse Widths:** - **Initialization Logic:** An internal `FirstRun` flag ensures that the first measurement is correctly set as the starting point.
- **Package Context:** The function block (FB) is intended for the `logiBUS::signalprocessing::distance` package.

## State Overview

The Execution Control Chart (ECC) consists of four states:

- **START:** Waiting state after initialization or processing.
- **INIT:** Executes the `INIT` algorithm (setting the initial values). This state is only entered on the first iteration (`FirstRun = TRUE`).
- **CHECK:** Executes the `CHECK` algorithm for distance checking and modifies the output if necessary.
- **EMIT:** Executes the `SAVE` algorithm (stores the current output state) and sends the event `OUT.E1`.

**Transitions:**

- `START → INIT`: When `DIST_IN.E1` and `FirstRun = TRUE` arrive.
- `START → CHECK`: When `DIST_IN.E1` and `FirstRun = FALSE` arrive.
- `INIT → CHECK`: Immediately after `INIT` (condition 1).
- `CHECK → EMIT`: If `OUT.D1` has changed compared to `LastState`.
- `CHECK → START`: If no change occurs (`OUT.D1 = LastState`).
- `EMIT → START`: Immediately after `EMIT` (condition 1).

## Application Scenarios
- **Distance Pulse Generators in Agricultural Technology:** Generating pulses after each defined distance traveled (e.g., a HIGH pulse every 5m, then a LOW pulse after another 5m) for control or counting tasks.
- **Distance-Based Switching Functions:** Triggering actions in conveyor systems, automated guided vehicles (AGVs), or automated machinery after specific distances have been traveled.
- **Pulse Width Modulation over Distance:** Variable pulse widths can be achieved by setting different values for `DIST_HIGH` and `DIST_LOW`, e.g., 10m HIGH and 2m LOW.

## Comparison with Similar Function Blocks
- **Tone-Based Pulse Generators (e.g., `E_CYCLE`):** Generate pulses based on time, while `AX_RangeBasedPulse` operates based on distance – for applications without a fixed time base.
- **Simple Edge Detectors:** Detect signal changes, but without hysteresis and without accumulating distance.
- **Other Distance Adapter Function Blocks:** Function blocks exist that aggregate distance values, but this function block combines event processing with threshold logic and asymmetric configuration.

**
## Conclusion

The `AX_RangeBasedPulse` function block offers a robust and flexible solution for distance-based pulse generation. Thanks to its adapter interface, separately configurable distance thresholds, and hysteresis logic, it is ideally suited for modular use in industrial control systems, particularly in agricultural technology and automation. Its implementation as a BasicFB ensures deterministic and predictable behavior.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
* [🌐 The PWM Signal & Infographic on ms-muc-docs.de](https://www.ms-muc-docs.de/automatisierung/das-pwm-signal-die-kunst-spannung-zu-zerhacken/das-pwm-signal-die-kunst-spannung-zu-zerhacken-website/)

]
