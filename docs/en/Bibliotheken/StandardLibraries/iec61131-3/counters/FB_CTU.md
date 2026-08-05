# FB_CTU
<img width="1331" height="282" alt="FB_CTU" src="https://github.com/user-attachments/assets/98a598a6-b535-4237-abf5-a9546457fb05" />
* * * * * * * * * *
## Introduction
The FB_CTU (Up Counter) is a function block that acts as an up counter. It increments the number of events and can be reset. The counter value is compared to a predefined value (PV), and an output signal (Q) is triggered as soon as the counter value reaches or exceeds the predefined value.
![FB_CTU](FB_CTU.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal Execution Request. Used to trigger the counting process. Linked to the data inputs `CU` and `R`.

### **Event Outputs**
- **CNF**: Execution Acknowledgement. Triggered after the counting process is complete. Linked to the data outputs `Q` and `CV`.

### **Data Inputs**
- **CU** (BOOL): Increments when `TRUE` is reached. Only evaluated when `R` is reached or `FALSE` is reached.
- **R** (BOOL): Resets the counter value (`CV`) to 0 when `TRUE` is reached.
- **PV** (INT): Predefined value against which the counter value (`CV`) is compared.

### **Data Outputs**
- **Q** (BOOL): Outputs `TRUE` when the counter value (`CV`) reaches or exceeds the predefined value (`PV`).
- **CV** (INT): Current counter value.

### **Adapters**
No adapters available.

## Functionality
The FB_CTU performs the following steps when the event `REQ` occurs:

1. If `R` is `TRUE`, the counter value (`CV`) is reset to 0.
...
### **Functionality**

### **Functionality**

### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality**
### **Functionality** 2. If `CU` is `TRUE` and the counter value (`CV`) is less than 32767, `CV` is incremented by 1.

3. The output `Q` is set to `TRUE` if `CV` is greater than or equal to `PV`.

## Technical Features
- The counter value (`CV`) is limited to a maximum value of 32767.
- The FB_CTU is a simple function block without internal state management between calls.

## State Overview
The FB_CTU has no internal states. The logic is re-executed with each `REQ` event.

## Application Scenarios
- Counting events, e.g., production steps in a manufacturing line.
- Monitoring processes where a specific number of steps must be completed.
- Controlling sequences that should trigger an action after a certain number of repetitions.

## ⚖️ Comparison with Similar Function Blocks
- **FB_CTD**: A down counter that, unlike FB_CTU, counts down.
- **FB_CTUD**: A combined up and down counter that can count both up and down.

## Conclusion
The FB_CTU is a simple and effective function block for up counting operations. It is particularly suitable for applications where events need to be counted and an action triggered when a specific value is reached. Its clear interface structure and simple functionality make it a useful component in control engineering.