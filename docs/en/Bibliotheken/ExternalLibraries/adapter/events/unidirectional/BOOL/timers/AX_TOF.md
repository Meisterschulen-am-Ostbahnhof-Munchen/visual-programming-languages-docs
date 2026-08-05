# AX_TOF

<img width="962" height="255" alt="image" src="https://github.com/user-attachments/assets/b86d8399-ca0b-492c-b20c-52dde7069371" />

* * * * * * * * * *

## Introduction
**Important note: This function block requires only one event and no cyclic calls. It has no output ET and does not display the elapsed time.**

The AX_TOF function block is a standard timer function block for off-delay timing. It implements a time delay when a signal is switched off and is controlled via adapter interfaces.


![AX_TOF](AX_TOF.svg)

## Interface Structure

### **Event Inputs**
- **R**: Reset event to reset the timer

### **Event Outputs**
*No direct event outputs available*

### **Data Inputs**
- **PT**: TIME - Process time for the delay

### **Data Outputs**
*No direct data outputs available*

### **Adapters**
- **IN** (Socket): Input adapter of type `adapter::types::unidirectional::AX`

- Event: E1

- Data: D1
- **Q** (Plug): Output adapter of type `adapter::types::unidirectional::AX`

- Event: E1

- Data: D1

## Functionality
The AX_TOF block implements an off-delay. When an incoming signal is received via the IN adapter, the output is activated immediately. When the input signal is switched off, the timer starts and keeps the output active for the set time PT before it is deactivated.
... ## Technical Features
- Internally uses the E_TOF standard timer block
- Unidirectional adapter interfaces for input and output
- Reset functionality for immediate timer reset
- Time base in TIME data type

## State Overview
1. **Idle State**: No active signal
2. **Enabled**: Input signal present, output active
3. **Delay**: Input signal switched off, timer running, output remains active
4. **Expired**: Timer expired, output disabled

## Application Scenarios
- Control of switch-off delays in industrial processes
- Safety functions with overrun times
- Delayed shutdown of motors or actuators
- Process control with defined shutdown sequences

## ⚖️ Comparison with Similar Blocks
Compared to other timer blocks, AX_TOF offers:

- Specialized in switch-off delays
- Adapter-based interface for modular design
- Integrated reset functionality
- Standardized TIME Data Types

Comparison with [E_TOF](../../../../../../StandardLibraries/events/timers/E_TOF.md)]

## 🛠️ Related Exercises

* [Exercise_020e_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020e_AX.md)]

## Conclusion
The AX_TOF function block offers a reliable and standardized solution for turn-off delays in 4diac-based control systems. Through the use of adapter interfaces, it enables flexible integration into more complex function block networks.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)]


```