# Aux_IX
<img width="1351" height="286" alt="image" src="https://github.com/user-attachments/assets/490e8389-ce94-4dd0-b554-b7010a05fdde" />
* * * * * * * * * *
## Introduction
The Aux_IX function block is a service interface function block for Boolean input data. It serves as an interface for input services and enables communication with resources for querying digital input signals.
![Aux_IX](Aux_IX.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization - Initializes the function block with the parameters QI, PARAMS, and u16ObjId
- **REQ**: Service Request - Triggers a service request with the qualifier QI

### **Event Outputs**
- **INITO**: Initialization Acknowledgement - Confirms the initialization with QO and STATUS
- **CNF**: Acknowledgement of Requested Service Request - Returns QO, STATUS, and IN data
- **IND**: Resource Indication - Signals data availability with QO, STATUS, and IN data

### **Data Inputs**
- **QI**: BOOL - Event Input Qualifier
- **PARAMS**: STRING - Service Parameter
- **u16ObjId**: UINT - Object ID with initial value ID_NULL

### **Data Outputs**
- **QO**: BOOL - Event Output Qualifier
- **STATUS**: STRING - Service Status
- **IN**: BOOL - Input data from the resource

### **Adapter**
No adapter interfaces are available.

## Functionality
The Aux_IX function block operates as an input service interface for Boolean data. During initialization (INIT), the service parameters and the object ID are configured. Service requests (REQ) trigger the querying of input data from the associated resource. The data is returned via the CNF and IND events, with the STATUS output providing information about the success or failure of the operation.

## Technical Features
- Uses specific TypeHash identification for 4diac
- Initializes the object ID with a default value (ID_NULL)
- Supports configurable service configuration via STRING parameters
- Provides both request-based (CNF) and event-based (IND) data output

## State Overview
The function block goes through the following states:

1. **Not Initialized**: Before INIT processing
2. **Initialized**: After successful INIT processing with INITO confirmation
3. **Ready**: Can process REQ requests
4. **Active**: During data retrieval from the resource

## Application Scenarios
- Querying digital input signals in control systems
- Integrating hardware inputs into IEC 61499 applications
- Monitoring switch states and sensors
- Implementing standardized input interfaces in distributed systems

## ⚖️ Comparison with Similar Function Blocks
In Compared to simple digital input blocks, Aux_IX offers enhanced service functionality with configurable settings, status feedback, and both request-driven and event-driven data provisioning.

## 🛠️ Related Exercises
* [Exercise_010b1](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_010b1.md)

## Conclusion
The Aux_IX function block provides a robust and flexible solution for integrating Boolean input data into IEC 61499-based control systems. Its service-oriented architecture and comprehensive status feedback make it particularly suitable for demanding industrial applications with high requirements for reliability and diagnostic capabilities.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

