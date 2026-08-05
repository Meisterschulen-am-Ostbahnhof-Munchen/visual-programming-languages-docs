# Button_IX

<img width="1352" height="285" alt="image" src="https://github.com/user-attachments/assets/6e6968e4-bc91-448b-abea-62a909edce06" />

* * * * * * * * * *

## Introduction
Button_IX is a service interface function block for Boolean input data, specifically designed for processing key presses in 4diac systems. This block serves as an interface between the application logic and physical input devices such as pushbuttons or switches.


![Button_IX](Button_IX.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Request
- **IND**: Indication from Resource Interface

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **u16ObjId** (UINT): Object ID with Initial Value ID_NULL

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status Information
- **IN** (BOOL): Input Data from the Resource

### **Adapter**
None Adapter interfaces are available.

## Functionality
The Button_IX function block manages the entire lifecycle of a keystroke. During initialization (INIT event), the service parameters are configured and the system is prepared for operation. The REQ event triggers a current query of the input state, while the IND event signals asynchronous state changes of the keystroke.


## Technical Features
- Supports ISOBUS-compliant communication
- Uses specific TypeHash identification for 4diac
- Integrates object ID management for device identification
- Provides comprehensive status feedback via the STATUS output

## State Overview
The function block goes through the following main states:

1. **Not Initialized**: Waiting for an INIT event

2. **Initialized**: Ready for REQ and IND events

3. **Active**: Processing input requests and indications
4. **Error**: In case of invalid parameters or communication problems

## Application Scenarios
- Operator panels in industrial control systems
- Machine control with push-button inputs
- ISOBUS-compatible agricultural machinery control systems
- Safety-critical input systems with status monitoring

## ⚖️ Comparison with Similar Blocks
Compared to simple digital input blocks, Button_IX offers extended functionalities such as:

- Configurable service configuration
- Detailed Status Feedback
- ISOBUS Integration
- Asynchronous Event Handling

## 🛠️ Related Exercises

* [Exercise_010a2](../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010a2.md)
* [Exercise_010a3](../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010a3.md)

## Conclusion
The Button_IX function block provides a robust and flexible solution for integrating keystrokes into 4diac-based control systems. Its comprehensive interface and status management make it particularly suitable for demanding industrial applications that require reliable and monitorable input processing.

--

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```