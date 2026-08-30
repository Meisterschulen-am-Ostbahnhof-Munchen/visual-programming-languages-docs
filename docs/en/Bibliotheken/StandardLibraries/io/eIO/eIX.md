# eIX

<img width="1435" height="298" alt="image" src="https://github.com/user-attachments/assets/cae6a064-563d-41dd-9f8e-9cb9bb401bc6" />
* * * * * * * * * *
## Introduction

The eIX function block is an input service interface for Boolean input data with event-based triggering. It serves as an interface between the control logic and physical input devices and enables the querying of digital input signals.
![eIX](eIX.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the function block with parameters
- **REQ**: Service Request - Triggers a query of the input signal

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful initialization
- **CNF**: Service Acknowledgement - Confirms the processed service request
- **IND**: Resource Indication - Signals a status change of the input

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Enables/disables processing
- **PARAMS** (STRING): Service Parameters - Configuration parameters for the service

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - Processing status
- **STATUS** (STRING): Service status - Error or status information
- **IN** (BOOL): Input data from the resource - Current value of the digital input

### **Adapter**

- **eCONF**: Configuration of event-based triggering - Adapter for trigger configuration

## Functionality

The eIX block acts as a service interface for digital inputs. During initialization (INIT), the service parameters are configured. Targeted queries of the input signal can be triggered via REQ events. The block returns the current input values via CNF and can report asynchronous status changes via IND.

## Technical Features

- Event-based query mechanisms
- Separate initialization and operating modes
- String-based status feedback
- Adapter-based configuration of trigger logic
- Support for both requested and indexed operations

## State Overview

1. **Not Initialized**: Block waits for INIT event
2. **Initialized**: Block is ready for operation and can process REQ events
3. **Active**: Processing service requests and providing feedback of input values
4. **Error**: In case of problems, STATUS is populated with error information

## Application Scenarios

- Querying digital sensors (limit switches, proximity switches)
- Monitoring switching states
- Integration of pushbuttons and control elements
- Signal processing in automation systems
- Condition monitoring of machines and systems

## ⚖️ Comparison with Similar Blocks

Compared to simple digital input blocks, eIX offers extended functionality:

- Event-based instead of cyclic querying
- Detailed Status feedback
- Configurable trigger mechanisms
- Separate initialization and operating phases

## Conclusion

The eIX function block represents a flexible and robust solution for integrating digital inputs into IEC 61499-based control systems. Its event-based architecture and comprehensive status feedback make it particularly suitable for applications requiring reliable and configurable input processing.
