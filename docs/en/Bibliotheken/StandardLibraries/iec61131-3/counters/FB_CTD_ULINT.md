# FB_CTD_ULINT

<img width="1411" height="282" alt="FB_CTD_ULINT" src="https://github.com/user-attachments/assets/47813539-b542-43ce-82f2-a1f5ec03073f" />
* * * * * * * * * *
## Introduction

The FB_CTD_ULINT is a down counter for the ULINT (Unsigned Long Integer) data type. It is used to count down from a predefined starting value and signals when the counter reaches or falls below 0.
![FB_CTD_ULINT](FB_CTD_ULINT.svg)
## Interface Structure

### **Event Inputs**

- **REQ**: Normal Execution Request. Used to update the counter. Linked to the data inputs CD, PV, and LD.

### **Event Outputs**

- **CNF**: Execution Confirmation. Triggered after the counter has been updated. Linked to the data outputs Q and CV.

### **Data Inputs**

- **CD (BOOL)**: Signals that the counter should be decremented by 1 (Count Down).
- **LD (BOOL)**: Signals that the counter should be loaded with the value of PV (Load).
- **PV (ULINT)**: The preset value with which the counter is loaded when LD is enabled.

### **Data Outputs**

- **Q (BOOL)**: Signals whether the counter reading is less than or equal to 0.
- **CV (ULINT)**: The current counter reading (Count Value).

### **Adapters**

No adapters are defined for this function block.

## Functionality

The function block operates according to the following rules:

1. When LD (Load) is enabled, the counter reading (CV) is set to the preset value (PV).
2. If CD (Count Down) is enabled and the counter value (CV) is greater than 0, the counter value is decremented by 1.
3. Output Q is set to TRUE if the counter value (CV) is less than or equal to 0.

## Technical Features

- The counter uses the ULINT data type, which allows for very large positive numbers (0 to 18,446,744,073,709,551,615).
- The counter is only updated when the REQ event is triggered.

## State Overview

- **Initialization**: The counter value (CV) is undefined until the first REQ event.
- **Loading (LD)**: CV is set to PV.
- **Count (CD)**: CV is decremented by 1 as long as CV > 0.
- **Output Q**: TRUE if CV ≤ 0.

## Application Scenarios

- Controlling production processes with downward counting (e.g., remaining parts in a warehouse).
- Time control with large time intervals.
- Monitoring of events with a limited number of occurrences.

## ⚖️ Comparison with Similar Function Blocks

- Compared to other counters (e.g., FB_CTD_INT), this function block offers a larger number range through ULINT.
- Similar to FB_CTD, but specifically optimized for ULINT values.

## Conclusion

The FB_CTD_ULINT is a powerful downward counter for applications requiring very large counting ranges. Its simple and clear interface makes it easy to integrate into various control systems.