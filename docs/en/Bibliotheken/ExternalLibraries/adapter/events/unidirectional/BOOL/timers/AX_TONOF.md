# AX_TONOF

<img width="1154" height="290" alt="image" src="https://github.com/user-attachments/assets/eecdf987-773b-4d5a-9da7-7ba858235b94" />
* * * * * * * * * *
## Introduction

**Important note: This function block requires only one event and no cyclic calls. It has no output ET and does not display the elapsed time.**
AX_TONOF is a standardized timer function block that implements both on and off delays. This function block combines the functionalities of an on-delay and an off-delay timer in a compact solution.

![AX_TONOF](AX_TONOF.svg)

## Interface Structure

### **Event Inputs**

- **R**: Reset event to reset the timer

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

- **PT_ON**: TIME - Process time for the power-on delay
- **PT_OFF**: TIME - Process time for the power-off delay

### **Data Outputs**

*No direct data outputs available*

### **Adapters**

- **IN**: Input adapter (socket) for control signals
- **Q**: Output adapter (plug) for status outputs

## Functionality

The AX_TONOF function block processes input signals via the IN adapter and applies the configured delay times depending on the signal state. When an input signal is active, the PT_ON delay is taken into account; when the signal is inactive, the PT_OFF delay is used. The result is output via the Q-adapter.

...)`) ) ) ) ``) ``) ``)`) is taken into account. The `PT_ON` delay is taken into account when an

## Technical Features

- Supports bidirectional time delays (on and off delay)
- Integrated reset functionality
- Uses adapters for inputs and outputs instead of direct interfaces
- Based on the E_TONOF core function block

## State Overview

The function block can assume the following states:

- **Idle State**: No active time measurement
- **On Delay**: Time measurement for PT_ON active
- **Off Delay**: Time measurement for PT_OFF active
- **Reset State**: All active time measurements are canceled

## Application Scenarios

- Motor controls with start and stop delays
- Lighting control with on/off delays
- Process controls with staggered switching operations
- Safety-related applications with delayed responses

## ⚖️ Comparison with Similar Function Blocks

Compared to simple timer function blocks like TON or TOF, AX_TONOF offers the combined functionality of both timer types in a single block. The use of adapters instead of direct inputs/outputs allows for more flexible integration into complex control structures.

Comparison with [E_TONOF](../../../../../../StandardLibraries/events/timers/E_TONOF.md)

## 🛠️ Related Exercises

- [Exercise_020g_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020g_AX.md)

## Conclusion

The AX_TONOF is a versatile timer module that, thanks to its combined on/off delay functionality and adapter-based interface design, is particularly well-suited for modular control architectures. The integrated reset function increases flexibility in practical applications.
