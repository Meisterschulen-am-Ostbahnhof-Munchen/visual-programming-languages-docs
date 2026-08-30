# FB_CTUD_LINT

<img width="1418" height="340" alt="FB_CTUD_LINT" src="https://github.com/user-attachments/assets/3ef801dc-5210-49fd-b0d4-4c34251fea5f" />
* * * * * * * * * *
## Introduction

The FB_CTUD_LINT is a function block for an incrementing and decrementing counter with 64-bit integer values (LINT). It provides functions for counting up and down, resetting the counter, and loading a predefined value. The counter is particularly suitable for applications requiring large number ranges.
![FB_CTUD_LINT](FB_CTUD_LINT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request. Used to start the counting process. Linked to the data inputs CU, CD, R, LD, and PV.

### **Event Outputs**

- **CNF**: Execution Confirmation. Outputted after completion of the counting operation. Linked to the data outputs QU, QD, and CV.

### **Data Inputs**

- **CU (BOOL)**: Count Up signal.
- **CD (BOOL)**: Count Down signal.
- **R (BOOL)**: Reset counter signal.
- **LD (BOOL)**: Load predefined value signal.
- **PV (LINT)**: Predefined value loaded when LD is active.

### **Data Outputs**

- **QU (BOOL)**: Signal indicating whether the counter value is greater than or equal to the predefined value.
- **QD (BOOL)**: Signal indicating whether the counter value is less than or equal to 0.
- **CV (LINT)**: Current counter value.

### **Adapter**

No adapters available.

## Functionality

The function block performs the following operations when the REQ event occurs:

1. **Reset (R)**: Resets the counter value (CV) to 0.
2. **Load (LD)**: Loads the predefined value (PV) into the counter value (CV).
3. **Count Up (CU)**: Increments the counter value by 1, provided the maximum value (9223372036854775807) is not exceeded.
4. **Count Down (CD)**: Decrements the counter value by 1, provided the minimum value (-9223372036854775808) is not undercut.
5. **Outputs QU and QD**: Updated based on the current counter value.

## Technical Features

- Uses 64-bit integers (LINT) for the counter value and the predefined value.
- Supports both counting up and down with overflow and underflow protection.
- Simultaneous activation of CU and CD is not possible (prevents conflicts).

## State Overview

The function block has no internal state other than the current counter value (CV). The logic is re-executed with each REQ event.

## Application Scenarios

- Industrial controllers with large counting ranges.
- Monitoring of production processes.
- Time measurement or event counting over long periods.

## ⚖️ Comparison with Similar Function Blocks

- Compared to simple counters, FB_CTUD_LINT offers a larger number range (64-bit).
- Similar to FB_CTUD, but with a LINT data type for more advanced applications.

## Conclusion

The FB_CTUD_LINT is a high-performance counter for applications requiring large number ranges. Its flexibility and robustness make it ideal for industrial controls and complex counting tasks.
