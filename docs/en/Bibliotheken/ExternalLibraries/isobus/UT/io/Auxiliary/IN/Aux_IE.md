# Aux_IE
<img width="1335" height="214" alt="image" src="https://github.com/user-attachments/assets/96c43b99-3ad6-4ea1-835a-f1ca01902622" />
* * * * * * * * * *
## Introduction
The Aux_IE function block is an input service interface function block for event input data. It is used to process auxiliary inputs and enables the recognition of various input events such as pressing, releasing, single-clicking, double-clicking, etc.
![Aux_IE](Aux_IE.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization
- Linked to: QI, PARAMS, u16ObjId, InputEvent
- **REQ**: Service Request
- Linked to: QI

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- Linked to: QO, STATUS
- **CNF**: Acknowledgement of Requested Service Request
- Linked to: QO, STATUS
- **IND**: Display of Resource
- Linked to: QO, STATUS

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service parameters
- **u16ObjId** (UINT): Object ID, initial value: ID_NULL
- **InputEvent** (AuxiliaryState_S): Identifies the event (Down, Up, Single-Click, Double-Click, etc.), initial value: Invalid

### **Data Outputs**
- **QO** (BOOL): Event output qualifier
- **STATUS** (STRING): Service status

### **Adapters**
No adapter interfaces are available.

## Functionality
The Aux_IE block processes auxiliary input events and provides a standardized interface for communication with input devices. During initialization (INIT), the service parameters and object ID are configured. Service requests can be made via REQ events, while IND events indicate incoming signals from the resource.

## Technical Features
- Uses specific ISOBUS data types for agricultural machinery
- Supports various input event types via the AuxiliaryState structure
- Initialization with standardized NULL values (ID_NULL)
- String-based status feedback

## State Overview
The block has an initialization state (INIT/INITO) and operational states for service requests (REQ/CNF) as well as resource indicators (IND).

## Application Scenarios
- Control of agricultural machinery via auxiliary inputs
- Processing of user interactions in ISOBUS systems
- Recognition of complex input patterns (single click, double click)
- Integration into control systems for agricultural machinery

## ⚖️ Comparison with Similar Blocks
Compared to simple digital input blocks, Aux_IE offers enhanced functionality for recognizing more complex input events and is specifically optimized for ISOBUS environments.

## 🛠️ Related exercises
* [Uebung_010b3](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010b3.md)
* [Uebung_010b3_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b3_AX.md)
* [Uebung_010bA2](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA2.md)
* [Uebung_010bA2_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA2_AX.md)
* [Uebung_010bA3](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA3.md)
* [Uebung_010bA3_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA3_AX.md)
* [Uebung_010bA4](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010bA4.md)
* [Uebung_010bA4_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010bA4_AX.md)

## Conclusion
The The Aux_IE function block provides a powerful interface for processing auxiliary input events in ISOBUS-based control systems and enables the reliable detection of various user interactions.