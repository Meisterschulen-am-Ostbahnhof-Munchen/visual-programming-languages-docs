# Button_IXA

<img width="1388" height="321" alt="image" src="https://github.com/user-attachments/assets/8f014f19-717a-4392-9d65-ba1fe63e1a6e" />
* * * * * * * * * *
## Introduction

Button_IXA is a composite function block for processing Boolean input data. The block serves as an interface for button inputs and provides standardized processing of switching states in automation systems.
`` ![Button_IXA](Button_IXA.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - triggered by QI, PARAMS, and u16ObjId
- **REQ**: Service Request - triggered by QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - triggered by QO and STATUS

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL)
- **PARAMS**: Service Parameters (STRING)
- **u16ObjId**: Object ID (UINT) - Initial Value: ID_NULL

### **Data Outputs**

- **QO**: Event Output Qualifier (BOOL)
- **STATUS**: Service Status (STRING)

### **Adapters**

- **IN**: Unidirectional Adapter from Type adapter::types::unidirectional::AX

## Functionality

The Button_IXA function block acts as a wrapper around the internal Button_IX block. During initialization (INIT), the configuration parameters are passed and the internal block is configured. Service requests (REQ) trigger the query of the button state. The IN adapter serves as the interface for the actual button input.

## Technical Features

- Uses ISOBUS-compliant types and adapters
- Supports object identification via u16ObjId
- Flexible parameterization via STRING parameters
- Unidirectional adapter interface for input data

## State Overview

The function block has the following main states:

- Not initialized: Waiting for an INIT event
- Initialized: Ready for REQ requests
- Active: Processing button inputs via the adapter

## Application Scenarios

- Button inputs in agricultural machinery
- ISOBUS-compatible control systems
- Boolean input processing in distributed automation systems
- Operator panels and control panels

## ⚖️ Comparison with Similar Function Blocks

Compared to simple Boolean input blocks, Button_IXA offers:

- ISOBUS compatibility
- Extended parameterization options
- Standardized status feedback
- Adapter-based architecture for improved reusability

## 🛠️ Related Exercises

* [Exercise_010a2_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010a2_AX.md)]
* [Exercise_010a3_AX](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_010a3_AX.md)]

## Conclusion

Button_IXA is a specialized function block for the reliable processing of button inputs in ISOBUS environments. Its modular architecture and standardized interfaces make it ideally suited for use in complex agricultural automation systems.
