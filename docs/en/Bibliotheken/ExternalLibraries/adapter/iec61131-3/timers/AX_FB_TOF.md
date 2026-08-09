# AX_FB_TOF

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />
* * * * * * * * * *
## Introduction

**Important note: This function block only functions correctly if it is called cyclically.**
AX_FB_TOF is a standardized timer function block according to IEC 61131-3 that implements off-delay timing. The block maintains the output signal for a defined duration after the input signal is switched off.

![AX_FB_TOF](AX_FB_TOF.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Event): Normal Execution Request (takes the value from PT); Calls the function block (must be called cyclically)

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **PT** (TIME): Process time - defines the duration of the turn-off delay

### **Data Outputs**

- **ET** (TIME): Elapsed time

### **Adapters**

- **IN** (Socket): Receives input events and data (Type: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sends output events and data (Type: `adapter::types::unidirectional::AX`)

## Functionality

The AX_FB_TOF block functions as a turn-off delay timer:

1. When the input on the IN adapter becomes TRUE, the output on the Q adapter immediately switches to TRUE.
2. When the input at the IN adapter changes from TRUE to FALSE, the internal timer starts.
3. The output at the Q adapter remains TRUE while the timer is running and PT has not yet been reached.
4. After PT has elapsed, the output at the Q adapter changes to FALSE.
5. The data output ET displays the time elapsed since the input signal dropped.
6. If the input at the IN adapter becomes TRUE again while the timer is running, the timer is reset and Q remains TRUE.

## Technical Features

- Implemented based on the IEC 61131-3 TOF standard
- Uses unidirectional adapters for integration into modern control concepts
- Provides an ET output for monitoring the remaining delay time
- Robust implementation for reliable overrun controllers

## State Overview

1. **Inactive**: IN is FALSE, Q is FALSE, ET is 0.
2. **Active**: IN is TRUE, Q is TRUE, ET is 0.
3. **Delay Phase**: IN changes to FALSE, timer is running, Q remains TRUE, ET increases.
4. **Expired**: ET reaches PT, Q changes to FALSE.

## Application Scenarios

- Debouncing controls (e.g., fan control after a device is switched off)
- Debouncing of signals that might drop briefly
- Ensuring minimum runtimes after a stop command

## ⚖️ Comparison with similar function blocks

Compared to event-based timers such as [AX_TOF](../../events/unidirectional/BOOL/timers/AX_TOF.md)], this function block follows classic PLC behavior according to IEC 61131-3 and additionally offers the ET status output.

## 🛠️ Related Exercises

* [Exercise_020e2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e2_AX.md)]

## Conclusion

AX_FB_TOF is the ideal function block for all applications that require a precise switch-off delay with status feedback on the elapsed time.