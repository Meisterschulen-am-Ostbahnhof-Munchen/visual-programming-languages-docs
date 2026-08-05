# FB_CTU_LINT
<img width="1396" height="277" alt="FB_CTU_LINT" src="https://github.com/user-attachments/assets/a956d757-67d1-486f-b882-ab20f78546cf" />
* * * * * * * * * *
## Introduction
The function block `FB_CTU_LINT` is a counter-up function for large integers. It increments with each incoming counting event and can be reset to a predefined value. The block uses the data type `LINT` (64-bit integer) for the counter value and the setpoint.
![FB_CTU_LINT](FB_CTU_LINT.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Normal execution request, triggers the counting operation. It is associated with the data `CU` and `R`.

### **Event Outputs**
- **CNF**: Execution confirmation, output after the counting operation. Linked to the data `Q` and `CV`.

### **Data Inputs**
- **CU** (BOOL): Count Up command. If TRUE, the counter is incremented.
- **R** (BOOL): Reset. If TRUE, the counter is reset to 0.
- **PV** (LINT): Preset Value. The setpoint at which output `Q` is set to TRUE.

### **Data Outputs**
- **Q** (BOOL): Output. Becomes TRUE when the counter value (`CV`) reaches or exceeds the setpoint value (`PV`).
- **CV** (LINT): Current Value. Current counter reading.

### **Adapters**
This function block does not use adapters.

## Functionality
The function block performs the following operations on each `REQ` event:

1. If `R` is TRUE, the counter (`CV`) is reset to 0.

2. If `CU` is TRUE and the counter has not yet reached its maximum value (9223372036854775807), the counter is incremented by 1.

3. The output `Q` is set to TRUE when the counter value (`CV`) reaches or exceeds the setpoint (`PV`).

## Technical Features
- Uses 64-bit integers (`LINT`) for counter value and setpoint
- Maximum counter value: 9223372036854775807 (2^63-1)
- Implemented in Structured Text (ST)

## State Overview
The function block does not have an internal state machine. The logic is re-executed with each `REQ` event.

## Application Scenarios
- Counting events in large number ranges
- Monitoring production quantities
- Controlling processes with high count values

## ⚖️ Comparison with similar blocks
- Compared to `FB_CTU` (standard counter), this block supports larger number ranges (`LINT` instead of `INT`)
- Similar to `FB_CTUD`, but without a down counting function

## Conclusion
The `FB_CTU_LINT` is a powerful up counting block for applications requiring large counting ranges. Its simple interface and robust implementation make it a useful building block for industrial control applications.