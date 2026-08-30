# FB_F_TRIG

<img width="1366" height="219" alt="FB_F_TRIG" src="https://github.com/user-attachments/assets/9ea529ec-c4e2-4e3f-96f0-9a5ddd42ebf5" />
* * * * * * * * * *
The function block `FB_F_TRIG` is used to detect the falling edge of a Boolean signal. It is frequently used in control applications to detect state changes from `TRUE` to `FALSE` and trigger corresponding actions.
![FB_F_TRIG](FB_F_TRIG.svg)

- `REQ` (Normal Execution Request): Starts the execution of the function block. It is linked to the data input `CLK`.
- `CNF` (Execution Confirmation): Confirms the execution of the function block. Linked to the data output `Q`.
- `CLK` (BOOL): The signal to be monitored, whose falling edge is to be detected.
- `Q` (BOOL): Outputs `TRUE` if a falling edge is detected, otherwise `FALSE`.

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

- No adapters available.


The function block stores the previous state of the `CLK` signal in an internal variable `MEM`. On each call via the `REQ` event, it checks whether the current `CLK` signal is `FALSE` and whether the previous state (`MEM`) was `TRUE`. If so, `Q` is set to `TRUE`; otherwise, it is set to `FALSE`. The current state of `CLK` is then stored in `MEM`.

- The function block uses an internal memory variable (`MEM`) to store the previous state of the `CLK` signal.
- The logic for detecting the falling edge is implemented in an ST algorithm.

1. **Initialization**: `MEM` is initialized with `TRUE`.
2. **Falling Edge Detection**:

- When `CLK` transitions from `TRUE` to `FALSE`, `Q` is set to `TRUE`.
- In all other cases, `Q` is set to `FALSE`.
1. **Saving the Current State**: The current state of `CLK` is saved to `MEM`.

- Detection of button or switch actuations in control systems.
- Synchronization of processes upon signal changes.
- Triggering of actions on falling edges in time-critical applications.
- **FB_R_TRIG**: Detection of a rising edge (from `FALSE` to `TRUE`).
- **FB_R_F_TRIG**: Combined detection of rising and falling edges. - **FB_F_TRIG** is specialized for detecting falling edges and is therefore more efficient in this specific application.
- [Exercise_178](../../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)
- [Exercise_178_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_178_AX.md)

The `FB_F_TRIG` function block is a simple and efficient function block for detecting falling edges in Boolean signals. Its clear interface and simple operation make it ideal for control applications where state changes need to be detected.

## Functionality

## Technical Features

## State Overview

## Application Scenarios

## ⚖️ Vergleich mit ähnlichen Bausteinen

## 🛠️ Zugehörige Übungen

## Conclusion
