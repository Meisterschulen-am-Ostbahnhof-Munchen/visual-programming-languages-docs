# FB_F_TRIG

<img width="1366" height="219" alt="FB_F_TRIG" src="https://github.com/user-attachments/assets/9ea529ec-c4e2-4e3f-96f0-9a5ddd42ebf5" />

* * * * * * * * * *

## Introduction
The function block `FB_F_TRIG` is used to detect the falling edge of a Boolean signal. It is frequently used in control applications to detect state changes from `TRUE` to `FALSE` and trigger corresponding actions.

![FB_F_TRIG](FB_F_TRIG.svg)

## Interface Structure

### **Event Inputs**

- `REQ` (Normal Execution Request): Starts the execution of the function block. It is linked to the data input `CLK`.


### **Event Outputs**

- `CNF` (Execution Confirmation): Confirms the execution of the function block. Linked to the data output `Q`.

### **Data Inputs**

- `CLK` (BOOL): The signal to be monitored, whose falling edge is to be detected.

### **Data Outputs**

- `Q` (BOOL): Outputs `TRUE` if a falling edge is detected, otherwise `FALSE`.

### **Adapters**

- No adapters available.


### **Adapters**

### ## Functionality

The function block stores the previous state of the `CLK` signal in an internal variable `MEM`. On each call via the `REQ` event, it checks whether the current `CLK` signal is `FALSE` and whether the previous state (`MEM`) was `TRUE`. If so, `Q` is set to `TRUE`; otherwise, it is set to `FALSE`. The current state of `CLK` is then stored in `MEM`.

## Technical Features
- The function block uses an internal memory variable (`MEM`) to store the previous state of the `CLK` signal.

- The logic for detecting the falling edge is implemented in an ST algorithm.

## State Overview

1. **Initialization**: `MEM` is initialized with `TRUE`.

2. **Falling Edge Detection**:

- When `CLK` transitions from `TRUE` to `FALSE`, `Q` is set to `TRUE`.


- In all other cases, `Q` is set to `FALSE`.

3. **Saving the Current State**: The current state of `CLK` is saved to `MEM`.

## Application Scenarios

- Detection of button or switch actuations in control systems.

- Synchronization of processes upon signal changes.

- Triggering of actions on falling edges in time-critical applications.

## ⚖️ Comparison with Similar Function Blocks

- **FB_R_TRIG**: Detection of a rising edge (from `FALSE` to `TRUE`).

- **FB_R_F_TRIG**: Combined detection of rising and falling edges. - **FB_F_TRIG** is specialized for detecting falling edges and is therefore more efficient in this specific application.

## 🛠️ Related Exercises

* [Exercise_178](../../../../Uebungen/test_B/Uebungen_doc/Uebung_178.md)]

* [Exercise_178_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_178_AX.md)]

## Conclusion
The `FB_F_TRIG` function block is a simple and efficient function block for detecting falling edges in Boolean signals. Its clear interface and simple operation make it ideal for control applications where state changes need to be detected.