# AX_FB_TP

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />
* * * * * * * * * *
## Introduction

**Important note: This function block only functions correctly if it is called cyclically.**
AX_FB_TP is a standardized timer function block according to IEC 61131-3 that generates a pulse of defined length. A rising edge at the input generates an output pulse for the specified duration.

![AX_FB_TP](AX_FB_TP.svg)

## Interface Structure

### **Event Inputs**

- **REQ** (Event): Normal Execution Request (takes the value from PT); Calls the function block (must be called cyclically)

### **Event Outputs**

- No direct event outputs available

### **Data Inputs**

- **PT** (TIME): Pulse time - defines the duration of the output pulse

### **Data Outputs**

- **ET** (TIME): Elapsed Time

### **Adapters**

- **IN** (Socket): Receives input events and data (Type: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sends output events and data (Type: `adapter::types::unidirectional::AX`)

## Functionality

The AX_FB_TP block functions as a pulse generator:

1. On a rising edge (change from FALSE to TRUE) at the IN adapter, the output at the Q adapter immediately changes to TRUE.
2. The internal timer starts and runs for the duration PT.
3. The output on the Q-adapter remains TRUE for the entire duration PT, regardless of whether the input signal on the IN-adapter changes back to FALSE in the meantime.
4. While the pulse is running (as long as ET < PT), further edges at the input have no effect on the running timer (not retriggerable).
5. After the duration PT has elapsed, the output on the Q-adapter returns to FALSE.
6. The data output ET displays the time that has elapsed since the pulse started.

## Technical Features

- Implemented based on the IEC 61131-3 TP standard
- Uses unidirectional adapters for clean encapsulation in adapter-based architectures
- Not retriggerable during the active pulse phase
- Precise timing control through the use of the TIME data type

## State Overview

1. **Idle State**: IN is FALSE, Q is FALSE, ET is 0.
2. **Pulse Phase**: Rising edge detected at IN, Q is TRUE, ET rises to PT.
3. **End Phase**: ET has reached PT, Q changes to FALSE.
4. **Waiting for Reset**: If IN is still TRUE, Q remains FALSE and ET remains at PT until IN becomes FALSE again.

## Application Scenarios

- Generation of time-limited control signals (e.g., start pulse for a motor)
- Time-limiting of operating processes
- Generation of defined signal pulses in process automation

## ⚖️ Comparison with similar function blocks

Compared to [AX_PULSE](../../events/unidirectional/BOOL/timers/AX_PULSE.md), AX_FB_TP offers the classic IEC 61131-3 TP characteristic, including the ET status output.

## 🛠️ Related Exercises

- [Exercise_020f2_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f2_AX.md)

## Conclusion

AX_FB_TP is the standard function block for generating stable, precisely time-defined pulses in an adapter-based environment.
