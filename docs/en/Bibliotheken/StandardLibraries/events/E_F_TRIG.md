# E_F_TRIG
![E_F_TRIG Diagram](https://user-images.githubusercontent.com/113907528/204898671-3eb058ff-7481-4fc8-a2d4-8cf50f349cee.png)

* * * * * * * * * *
## Introduction
The **E_F_TRIG** (Falling Edge Trigger) is a fundamental function block of the IEC 61499 standard for detecting falling signal edges. This block plays an important role in event detection and signal processing in industrial control systems.
![E_F_TRIG](E_F_TRIG.svg)

## Structure of the E_F_TRIG Block

### Interface

**Event Inputs:**

- **EI (Event Input)**: Triggers the edge detection.
- **Associated Data**: `QI`

**Event Outputs:**

- **EO (Event Output)**: Triggered when an edge is detected.

**Data Inputs:**

- **QI (Qualifier Input)**: The Boolean signal to be monitored (data type: `BOOL`).

## Functionality
The `E_F_TRIG` input is designed to detect a falling edge at the `QI` input. A falling edge occurs when `QI` was `TRUE` at the last `EI` event and is `FALSE` at the current `EI` event.

Each `EI` event compares the current state of `QI` with the state from the previous cycle. If a falling edge is detected, the `EO` event should be triggered.

**Caution: Incorrect Implementation**
The internal logic of the function block (as of `events-3.0.0`) is incorrect and actually implements a **rising edge detector (`E_R_TRIG`)** instead of a falling one. The `EO` event is triggered when `QI` transitions from `FALSE` to `TRUE`.

**Caution: Incorrect Implementation**
**The internal logic of the function block (as of `events-3.0.0`)** is incorrect and actually implements a **rising edge detector (`E_R_TRIG`)** instead of a falling one.** The `EO` event is triggered when `QI` transitions from `FALSE` to `TRUE`.**

**
## Technical Features

✔ **Event-driven**: The check only occurs when a `EI` event occurs.

✔ **Faulty logic**: The function block is named `E_F_TRIG`, but its internal wiring of `E_D_FF` and `E_SWITCH` causes it to react to a **rising edge**. Users who require falling edge detection must instead use the `E_R_TRIG` function block and invert its input or wait for a correction of the function block.

## Application Scenarios (for a falling edge)
- **Sensor data evaluation**: Detect when a sensor changes from "active" to "inactive".
- **Machine Safety**: Detection when a protective contact changes from "closed" (TRUE) to "open" (FALSE).
- **Process Monitoring**: Detection of the end of a signal or process.

## ⚖️ Comparison with similar function blocks

| Feature | E_F_TRIG (this) | E_R_TRIG | E_SWITCH |
|---------------|------------------|----------|----------|
| Detected Edge | Falling (named), Rising (implemented) | Rising | - |
| Event Control | Yes | Yes | Yes |
| Principle | Edge Detector | Edge Detector | Event Switch |

## 🛠️ Related Exercises
* [Exercise_088](../../../Uebungen/test_B/Uebungen_doc/Uebung_088.md)

## Conclusion

The E_F_TRIG function block is designed to detect falling edges, a common use case in control engineering. **However, due to an implementation error in the `events-3.0.0` library, this function block also functions as a detector for rising edges.** This discrepancy between name and function is critical and must be carefully considered during use. For reliable detection of falling edges, alternative logic should be used.
