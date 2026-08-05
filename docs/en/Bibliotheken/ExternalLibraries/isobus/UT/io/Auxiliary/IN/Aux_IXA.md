# Aux_IXA
<img width="1383" height="318" alt="image" src="https://github.com/user-attachments/assets/d064bd8f-6af0-4b04-9952-995892584e9a" />
* * * * * * * * * *
## Introduction
The Aux_IXA is a composite function block for processing Boolean input data. It serves as a wrapper for the basic function block Aux_IX and provides an extended interface for integration into ISOBUS-compatible systems.
![Aux_IXA](Aux_IXA.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service initialization with the associated data QI, PARAMS, and u16ObjId
- **REQ**: Service request with the associated data QI

### **Event Outputs**
- **INITO**: Initialization confirmation with the associated data QO and STATUS

### **Data Inputs**
- **QI**: Event Input Qualifier (BOOL) - Qualifier for event inputs
- **PARAMS**: Service Parameters (STRING) - Configuration parameters for the service
- **u16ObjId**: Object ID (UINT) - Object identifier with initial value ID_NULL

### **Data Outputs**
- **QO**: Event Output Qualifier (BOOL) - Qualifier for event outputs
- **STATUS**: Service Status (STRING) - Service status information

### **Adapter**
- **IN**: Unidirectional AX-type adapter for data communication

## Functionality
The Aux_IXA acts as a composite block that encapsulates the basic function block Aux_IX. Upon an INIT event, all parameters are forwarded to the internal IX block. REQ events trigger service requests, while INITO confirms successful initialization. The IN adapter enables bidirectional communication with external components.

**IN**
## Technical Features
- Integration into ISOBUS environments through a special package structure
- Use of TypeHash for type identification
- Unidirectional adapter for standardized interfaces
- Initialization with a NULL object ID as the default value

## State Overview
The block goes through the following states:

1. **Not Initialized**: Before the INIT event

2. **Initialization**: During INIT processing

3. **Ready**: After successful initialization (INITO)
4. **Service Mode**: During REQ event processing

## Application Scenarios
- ISOBUS-compatible agricultural machinery control
- Boolean signal processing in agricultural technology systems
- Wrapper implementation for existing I/O functionality
- Parameter configuration for auxiliary inputs

## ⚖️ Comparison with Similar Blocks
Compared to simple Boolean input blocks, Aux_IXA offers:

- Extended parameterization options
- ISOBUS specification
- Adapter-based interface
- Composite structure for improved reusability

## 🛠️ Related exercises
* [Exercise_010b1_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010b1_AX.md)

## Conclusion
The Aux_IXA represents a robust composite function block for Boolean input data processing in ISOBUS environments. Its clear interface definition and adapter integration enable flexible integration into complex agricultural control systems.
