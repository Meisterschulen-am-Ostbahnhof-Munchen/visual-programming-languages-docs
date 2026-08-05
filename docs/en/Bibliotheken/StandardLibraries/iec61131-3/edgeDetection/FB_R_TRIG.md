# FB_R_TRIG
<img width="1366" height="212" alt="FB_R_TRIG" src="https://github.com/user-attachments/assets/b8af3b36-dc40-44c3-8692-198ed7f809a8" />
* * * * * * * * * *
## Introduction
The function block `FB_R_TRIG` is used to detect the rising edge of a Boolean signal. It is typically used to detect and react to state changes from `FALSE` to `TRUE`.
![FB_R_TRIG](FB_R_TRIG.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal Execution Request. Used to trigger edge detection. Linked to the data input `CLK`.

### **Event Outputs**
- **CNF**: Execution Acknowledgement. Triggered after edge detection is complete. Linked to the data output `Q`.

### **Data Inputs**
- **CLK** (BOOL): The input signal whose rising edge is to be detected.

### **Data Outputs**
- **Q** (BOOL): The output signal `TRUE` is generated when a rising edge is detected at the input `CLK`.

### **Adapters**
This function block does not use any adapters.

## Functionality
FB_R_TRIG` stores the previous state of the input signal `CLK` in an internal variable `MEM`. Each time the algorithm is called via the event `REQ`, it checks whether the current state was `CLK` or `TRUE` and the previous state was `FALSE`. If so, the output `Q` is set to `TRUE`; otherwise, it is set to `FALSE`. The current state of `CLK` is then stored in `MEM` for the next iteration.

## Technical Features
- The function block is implemented according to the IEC 61499-1 standard.
- It uses a simple edge detection algorithm that can be executed efficiently and quickly.

## State Overview

This function block does not have a complex state machine. The state is represented solely by the value of the internal variable `MEM`, which stores the previous state of `CLK`.

## Application Scenarios
- Detection of key presses or switch activations.
- Synchronization of processes to rising edges of control signals.
- Triggering of actions upon specific events.

## ⚖️ Comparison with Similar Function Blocks
- **FB_F_TRIG**: Detection of a falling edge (from `TRUE` to `FALSE`).
- **FB_R_TRIG** is specific for rising edges and therefore complementary to `FB_F_TRIG`.

## 🛠️ Related Exercises
* [Exercise_177](../../../../Uebungen/test_B/Uebungen_doc/Uebung_177.md)]
* [Exercise_177_AX](../../../../Uebungen/test_AX/Uebungen_doc/Uebung_177_AX.md)]

## Conclusion
The `FB_R_TRIG` function block is a simple and effective function block for detecting rising edges. Its clear interface structure and simple functionality make it a useful component in many control applications.
