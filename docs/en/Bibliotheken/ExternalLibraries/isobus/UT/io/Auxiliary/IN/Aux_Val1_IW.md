# Aux_Val1_IW

<img width="1351" height="292" alt="image" src="https://github.com/user-attachments/assets/c88e5ead-0835-4374-be47-397bd18dd315" />

* * * * * * * * * *

## Introduction
The Aux_Val1_IW function block is an input service interface function block for word input data. It serves as an interface between the control logic and external resources for processing 16-bit word input data in an ISOBUS context.


![Aux_Val1_IW](Aux_Val1_IW.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization

- Linked to: QI, PARAMS, u16ObjId
- **REQ**: Service Request

- Linked to: QI

### **Event Outputs**

- **INITO**: Initialization Acknowledgement

- Linked to: QO, STATUS

- **CNF**: Acknowledgement of Requested Service Request

- Linked to: QO, STATUS, IN

- **IND**: Resource Indication

- Linked to: QO, STATUS, IN

### **Data Inputs**

- **QI**: Event Input Qualifier (BOOL)

- **PARAMS**: Service Parameters (STRING)

- **u16ObjId**: Object ID (UINT) Initial value: ID_NULL

### **Data Outputs**

- **QO**: Event output qualifier (BOOL)

- **STATUS**: Service status (STRING)

- **IN**: Input data from the resource (WORD)

### **Adapter**
No adapter interfaces are available.

## Functionality
This function block enables communication with external resources for capturing Word input data. The INIT initialization configures the service parameters and the object ID. The REQ request triggers data collection, while IND events signal asynchronous data updates from the resource.


## Technical Features
- Uses WORD data type for 16-bit data acquisition
- ISOBUS-compatible interface
- Supports asynchronous data indications
- Initialization with configurable parameters
- Error status feedback via STATUS output

## State Overview
The function block goes through the following main states:

1. **Not Initialized**: Waiting for INIT event

2. **Initialized**: Ready for REQ requests
3. **Active**: Processing data requests and indications
4. **Error**: Status message in case of problems

## Application Scenarios
- ISOBUS-based agricultural machinery control
- Acquisition of 16-bit sensor data
- Communication with external I/O modules
- Automation systems in agricultural technology

## ⚖️ Comparison with Similar Blocks
Compared to simple input blocks, Aux_Val1_IW offers extended ISOBUS functionality with configurable initialization, status feedback, and asynchronous Indication mechanisms.

## Conclusion
The Aux_Val1_IW function block provides a robust and flexible solution for capturing word input data in ISOBUS environments, with comprehensive error handling and configurable service parameters.