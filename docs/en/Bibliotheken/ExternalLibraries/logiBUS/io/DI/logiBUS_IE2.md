# logiBUS_IE2

<img width="1746" height="283" alt="image" src="https://github.com/user-attachments/assets/ac2845b6-9709-446e-9377-bd61a000862d" />
* * * * * * * * * *
## Introduction

The logiBUS_IE2 is an input service interface function block for event input data. It serves as an interface for processing input events in logiBUS systems and enables the processing of various input event types such as key presses, clicks, and time-based events.
![logiBUS_IE2](logiBUS_IE2.svg)

## Interface Structure

### **Event Inputs**

- **INIT** (Service Initialization) - Initializes the service with the following data:
- QI
- PARAMS
- Input
- InputEvent
- arg
- **REQ** (Service Request) - Requests a service with:
- QI

### **Event Outputs**

- **INITO** (Initialization Confirm) - Confirms the initialization with:
- QO
- STATUS
- **CNF** (Confirmation of Requested Service) - Confirms the requested service with:
- QO
- STATUS
- **IND** (Indication from Resource) - Message from the resource with:
- QO
- STATUS

### **Data Inputs**

- **QI** (BOOL) - Event Input Qualifier
- **PARAMS** (STRING) - Service Parameters
- **Input** (logiBUS_DI_S) - Identifies input Input_I1..I8 (Initial value: Invalid)
- **InputEvent** (logiBUS_DI_Events_S) - Identifies the event (Down, Up, Single-Click, Double-Click, etc.) (Initial value: Invalid)
- **arg** (UINT) - Long-press time event data OR multi-click event data (depending on the input event) (Initial value: 65535)

### **Data Outputs**

- **QO** (BOOL) - Event Output Qualifier
- **STATUS** (STRING) - Service Status

### **Adapter**

No adapter interfaces available.

## Functionality

The logiBUS_IE2 function block processes input events from logiBUS inputs and converts them into standardized event messages. It supports various event types such as key presses (down/up), single clicks, double clicks, and time-based events like long presses. The block can be configured via the INIT input and returns status information and acknowledgments via its outputs.

## Technical Features

- Supports multiple inputs (I1 to I8)
- Processes various event types via the InputEvent variable
- Can process time-based events (long press) and count-based events (multiple clicks)
- Initialization with specific parameters via the PARAMS input
- Provides detailed status information via the STATUS output

## State Overview

The function block has an initialization state (INIT/INITO) and operational states for service requests (REQ/CNF) as well as asynchronous event messages (IND). The exact state engine depends on the implementation.

## Application Scenarios

- Operator panel controls with keypad input
- Machine control with event-based input
- Systems with complex keypad input sequences
- Applications with long-press and multi-click detection

## ⚖️ Comparison with similar modules

Compared to simple digital input modules, logiBUS_IE2 offers enhanced functionality for complex event detection and supports various input event types with configurable parameters.

## 🛠️ Related Exercises

- [Exercise_004c6](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c6.md)
- [Exercise_004c6_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c6_AX.md)
- [Exercise_004c7](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_004c7.md)
- [Exercise_004c7_AX](../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_004c7_AX.md)

## Conclusion

The logiBUS_IE2 is a powerful function block for processing event input data in logiBUS systems. Its flexibility in event detection and extensive configuration options make it suitable for demanding control applications.
