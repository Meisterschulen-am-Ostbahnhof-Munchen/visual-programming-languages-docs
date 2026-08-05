# AX_TON
<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />
* * * * * * * * * *
## Introduction
**Important note: This function block requires only one event and no cyclic calls. It has no output ET and does not display the elapsed time.**
AX_TON is a standardized timer function block that implements on-delay timing. After activation, the block waits a defined time before setting the output signal.

![AX_TON](AX_TON.svg)

## Interface Structure

### **Event Inputs**
- No direct event inputs available

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **PT** (TIME): Process time - defines the delay duration

### **Data Outputs**
- No direct data outputs available

### **Adapters**
- **IN** (Input Adapter): Receives input events and data
- **Q** (Output Adapter): Sends output events and data

## Functionality
The AX_TON block functions as a power-on delay timer. When an input event is received via the IN adapter, the internal timer starts. After the set process time (PT) has elapsed, an output event with the status TRUE is sent via the Q adapter. If the input is deactivated during the time monitoring period, the timer is reset.

## Technical Features
- Implemented based on the E_TON standard timer block
- Uses unidirectional adapters for inputs and outputs
- Supports TIME data type for precise timing control
- Compatible with IEC 61499-2 standard

## State Overview
1. **Idle State**: No active timer, output FALSE
2. **Activation State**: Timer runs after input signal
3. **Delay State**: Timer counts down, output remains FALSE
4. **Trigger State**: After time elapses, output becomes TRUE

## Application Scenarios
- Control of time-delayed process starts
- Monitoring of minimum runtimes
- Delayed activation of machine components
- Safety-relevant time monitoring

## ⚖️ Comparison with Similar Blocks
Compared to other timer blocks, AX_TON offers a standardized interface via adapters, which facilitates reusability and modular integration into larger control systems.

Comparison with [E_TON](../../../../../../StandardLibraries/events/timers/E_TON.md)]

## 🛠️ Related Exercises
* [Exercise_020c_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020c_AX.md)]
* [Exercise_160b2_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_160b2_AX.md)]

## Conclusion
AX_TON is a robust and reliable timer module for power-on delays, which, thanks to its standardized adapter-based interface, enables flexible integration into various automation systems.