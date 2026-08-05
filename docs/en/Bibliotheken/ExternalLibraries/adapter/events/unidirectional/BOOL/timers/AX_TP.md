# AX_TP
<img width="915" height="258" alt="image" src="https://github.com/user-attachments/assets/650ebf90-0b85-464b-a6bb-79536b7a5119" />
* * * * * * * * * *
## Introduction
**Important Note: This function block requires only one event and no cyclic calls. It has no output ET and does not display the elapsed time.**
The AX_TP is a standardized timer function block of type "Pulse" used in 4diac IDE applications. This function block generates a timed pulse output based on a configurable time interval.

![AX_TP](AX_TP.svg)

## Interface Structure

### **Event Inputs**
- **R**: Reset Event - Resets the timer

### **Event Outputs**
- No direct event outputs available

### **Data Inputs**
- **PT**: TIME - Pulse Time (Pulse Duration)

### **Data Outputs**
- No direct data outputs available

### **Adapters**
- **IN**: Input Adapter (Socket) - Receives input events and data
- **Q**: Output Adapter (Plug) - Sends output events and data

## Functionality
The AX_TP function block operates as a pulse timer. When an event is received via the IN adapter, a timed pulse is generated, the duration of which is defined by the PT input. The reset input (R) allows the timer to be reset prematurely. The internal E_TP function block handles the actual timer functionality.

``` ## Technical Features
- Uses the standardized E_TP timer block as its core component
- Implemented via adapter interfaces for modular connection
- Supports the TIME data type for pulse time configuration
- Provides separate reset functionality

## State Overview
The function block has the following operating states:

- **Inactive**: No active timer
- **Active**: Timer is running with configured pulse time
- **Reset**: Timer has been reset

## Application Scenarios
- Time-controlled sequences
- Pulse generation for actuators
- Delay circuits
- Process control with defined time intervals

## ⚖️ Comparison with Similar Blocks
Compared to other timer blocks, AX_TP offers:

- Adapter-based interface for improved modularity
- Explicit reset functionality
- Standardized pulse timer implementation

Comparison with [E_TP](../../../../../../StandardLibraries/events/timers/E_TP.md)]

## 🛠️ Related Exercises
* [Exercise_020f_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020f_AX.md)]
* [Exercise_020j2_AX_sub](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020j2_AX_sub.md)]
* [Exercise_020j_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_020j_AX.md)]
* [Exercise_177_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_177_AX.md)]
* [Exercise_178_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_178_AX.md)]

## Conclusion
The AX_TP is a robust and standards-compliant timer function block, ideally suited for time-controlled applications in distributed automation systems. Its adapter-based architecture enables flexible integration into more complex control structures.

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
