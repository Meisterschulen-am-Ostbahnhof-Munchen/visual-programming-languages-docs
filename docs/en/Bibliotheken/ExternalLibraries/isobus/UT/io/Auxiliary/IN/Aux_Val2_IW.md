# Aux_Val2_IW

<img width="1351" height="292" alt="image" src="https://github.com/user-attachments/assets/3d049160-0f3d-47ee-99f9-04a4361361bc" />
* * * * * * * * * *
## Introduction

The Aux_Val2_IW is an input service interface function block for word input data. This block serves as an interface for communication with resources and enables the processing of 16-bit word input data in distributed automation systems.
![Aux_Val2_IW](Aux_Val2_IW.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block with parameters
- **REQ**: Service Request - Triggers a service request

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Confirmation of Requested Service - Acknowledges a service request
- **IND**: Indication from Resource - Signals incoming data from the resource

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Enables/disables processing
- **PARAMS** (STRING): Service Parameters - Configuration parameters for the service
- **u16ObjId** (UINT): Object ID - Identifier for the data object (initial value: ID_NULL)

### **Data Outputs**

- **QO** (BOOL): Event output qualifier - Output processing status
- **STATUS** (STRING): Service status - Service status feedback
- **IN** (WORD): Input data from the resource - The received 16-bit word data

### **Adapters**

No adapter interfaces are available.

## Functionality

This function block acts as a service interface for word input data. During INIT initialization, the service parameters and object ID are configured. Service requests can be made via REQ events, which are acknowledged with CNF events. When data is received from the resource, an IND event is issued containing the received word data.

## Technical Features

- Processes 16-bit Word data types (WORD)
- Supports configurable object IDs for data identification
- Provides comprehensive status feedback on the SERVICE status
- Enables parameterizable service configuration

## State Overview

The function block goes through the following states:

1. **Not Initialized**: Before INIT initialization
2. **Initialized**: After successful INIT processing with INITO confirmation
3. **Ready**: For REQ requests and IND indications
4. **Service Active**: During the processing of service requests

## Application Scenarios

- Reading 16-bit sensor data in distributed systems
- Communication with ISOBUS-compatible devices
- Input of Word data in automation applications
- Interface to external resources for data acquisition

## ⚖️ Comparison with Similar Blocks

Compared to simpler input blocks, it offers Aux_Val2_IW offers extended service functionality with configurable settings, status feedback, and object identification. It is specifically designed for processing 16-bit word data.

## Conclusion

The Aux_Val2_IW function block provides a powerful service interface for processing word input data in industrial automation systems. Its extensive configurability and status feedback make it particularly suitable for demanding applications with high requirements for reliability and diagnostic capabilities.
