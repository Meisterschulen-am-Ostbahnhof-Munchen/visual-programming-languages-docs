# AX_FB_TON
<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />
* * * * * * * * * *
## Introduction
**Important note: This function block only functions correctly if it is called cyclically.**
AX_FB_TON is a standardized timer function block according to IEC 61131-3 that implements on-delay timing and has adapter interfaces. After activation, the block waits a defined time before setting the output signal and provides the elapsed time.

![AX_FB_TON](AX_FB_TON.svg)

## Interface Structure

### **Event Inputs**
- **REQ** (Event): Normal Execution Request (takes the value from PT); Calls the function block (must be called cyclically)

### **Event Outputs**
- No direct event outputs available (control via adapter)

### **Data Inputs**
- **PT** (TIME): Process time - defines the delay duration

### **Data Outputs**
- **ET** (TIME): Elapsed time

### **Adapters**
- **IN** (Socket): Receives input events and data (Type: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sends output events and data (Type: `adapter::types::unidirectional::AX`)

## Functionality
The AX_FB_TON block functions as a power-on delay timer. The internal timer starts when a signal is received via the IN adapter.

1. When the input on the IN adapter becomes TRUE, the timer starts running.

2. After the set process time (PT) has elapsed, the output on the Q adapter becomes TRUE.

3. The data output ET indicates the time elapsed since the timer started until PT is reached.

4. If the input on the IN adapter becomes FALSE, the timer is reset, and the output on the Q adapter also becomes FALSE.

## Technical Features
- Implemented based on the IEC 61131-3 TON standard
- Uses unidirectional adapters for integration into adapter-based architectures
- Provides an ET output for monitoring the time progression
- Compatible with IEC 61131-3 and IEC 61499

## State Overview
1. **Idle State**: IN is FALSE, timer inactive, Q is FALSE, ET is 0.

2. **Timing State**: IN is TRUE, timer running, ET is increasing, Q is FALSE.

3. **Triggered**: IN is TRUE, ET has reached PT, Q is TRUE.

4. **Reset**: IN becomes FALSE, timer stops, Q becomes FALSE, ET becomes 0.

## Application Scenarios
- Classic power-on delays in PLC programming
- Monitoring of process times with visualization of remaining runtime (via ET)
- Cascading of time sequences in adapter-based systems

## ⚖️ Comparison with similar function blocks
Compared to [AX_TON](../../events/unidirectional/BOOL/timers/AX_TON.md)], AX_FB_TON additionally offers the **ET** output for the elapsed time and strictly follows the behavior of the IEC 61131-3 TON block, while AX_TON is optimized more for the IEC 61499 E_TON.

## 🛠️ Related Exercises
* [Exercise_020c3_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c3_AX.md)

## Conclusion
AX_FB_TON combines the proven behavior of the IEC 61131-3 TON timer with the flexibility of adapter interfaces, thus enabling precise time control with feedback of the current time status.