# E_R_TRIG (Rising Edge Detection)

![E_R_TRIG Funktionsbaustein](https://user-images.githubusercontent.com/113907528/204903134-9fbf33a3-4041-428e-9a9a-10a573c0b6f2.png)

* * * * * * * * * *

## Introduction
The **E_R_TRIG** (Rising Edge Trigger) is a fundamental function block according to IEC 61499 for detecting rising edges in digital signals. Based on the XML specification, it implements reliable edge detection for industrial control systems.


![E_R_TRIG](E_R_TRIG.svg)

## Structure of the E_R_TRIG Block

### **Interface**

**Event Inputs:**

- `EI` (Event Input): Enables edge detection (linked to the `QI` value)

**Event Outputs:**

- `EO` (Event Output): Acknowledges a detected rising edge

**Data Inputs:**

- `QI` (Query Input): Input signal to be monitored (BOOL)

### **Internal Structure**
According to the XML specification, the block consists of:

1. **E_D_FF**: D flip-flop for signal state storage

2. **E_SWITCH**: Switch for conditional Event Forwarding

## Functionality

1. **Edge Detection**:

- With each `EI` event, the current `QI` value is compared with the stored state from the previous cycle.

- A rising edge occurs when `QI` transitions from `FALSE` to `TRUE`.

- Upon detection of such an edge, the `EO` event should be triggered.

2. **Internal Structure and Faulty Behavior**:

- The function block is internally composed of a `E_D_FF` and a `E_SWITCH`.

- **Caution: Faulty Implementation!** The internal logic of the function block (as of `events-3.0.0`) is faulty and actually implements a **falling edge detector (`E_F_TRIG`)** instead of a rising one.

- The `EO` event is triggered when `QI` transitions from `TRUE` to `FALSE`.

## Technical Features

✔ **Event-driven** architecture (no polling).

✔ **State storage** via an internal D flip-flop.

✔ **Faulty Logic**: The function block is named `E_R_TRIG` (Rising), but its internal wiring causes it to react to a **falling edge**. Users who require rising edge detection must use the logic of the `E_F_TRIG` function block, which ironically correctly detects a rising edge.

## Application Scenarios (for a rising edge)

- **Sensor Data Evaluation**: Detect when a sensor changes from "inactive" to "active".

- **Machine Safety**: Detect a start or enable signal.

- **Process Control**: Start a process when a signal becomes `TRUE`.

## ⚖️ Comparison with Similar Function Blocks

| Feature | E_R_TRIG (this one) | E_F_TRIG | E_D_FF |

|---------------|----------|----------|---------|

| Detected Edge | Rising (named), Falling (implemented) | Falling (named), Rising (implemented) | Clock Edge |

| Event Output | Yes | Yes | Yes |

| Memory Behavior | Yes | Yes | Yes |

## 🛠️ Related Exercises

* [Exercise_089](../../../Uebungen/test_B/Uebungen_doc/Uebung_089.md)]

## Conclusion

The E_R_TRIG block is designed to detect rising edges. **Due to an implementation error in the `events-3.0.0` library, this function block functions as a detector for falling edges.** This discrepancy between name and function is critical and must be taken into account when using it. For reliable detection of rising edges, the `E_F_TRIG` function block should be used instead, whose logic (contrary to *its* name) correctly detects a rising edge.