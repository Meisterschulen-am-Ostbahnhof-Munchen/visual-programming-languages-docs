# eIW

<img width="1434" height="296" alt="image" src="https://github.com/user-attachments/assets/4b045e96-1325-4fca-9291-53d4d39a6161" />

* * * * * * * * * *

## Introduction
The eIW function block is an input service interface for word input data (WORD) with event-based triggering. It serves as an interface between the control application and physical input devices and enables the querying of 16-bit data words.


![eIW](eIW.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization - initializes the function block and configures the hardware parameters
- **REQ**: Service Request - triggers a query for the input data

### **Event Outputs**
- **INITO**: Initialization Acknowledgement - confirms successful initialization
- **CNF**: Acknowledge of Requested Service Request - provides the requested input data
- **IND**: Indication from Resource - signals asynchronous state changes of the input data

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier - controls the execution of service requests

- **PARAMS** (STRING): Service Parameters - configuration parameters for the hardware interface

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - indicates success or failure Operation at

- **STATUS** (STRING): Service status - detailed status information about the executed operation

- **IN** (WORD): Input data from the resource - the read 16-bit data

### **Adapter**

- **eCONF** (eclipse4diac::io::eio::eGenAdapter): Configuration of event-based triggering - allows customization of the trigger behavior

## Functionality
The eIW function block acts as an intermediary between the control application and physical input devices. During initialization (INIT), the hardware parameters are configured. Subsequently, input data can be selectively queried via REQ events. The block supports both synchronous queries (CNF) and asynchronous notifications for state changes (IND).


## Technical Features
- Processes 16-bit word data (WORD data type)
- Supports event-based and polling-based query modes
- Provides detailed status feedback via the STATUS output
- Enables flexible hardware configuration via the PARAMS input
- Integrates an adapter interface for advanced trigger configuration

## State Overview
The function block goes through the following states:

1. **Not Initialized**: Block is operational but not configured

2. **Initialized**: Hardware parameters are configured, block is operational
3. **Query Active**: Service request is being processed

4. **Data Available**: Input data is available and is being output

## Application Scenarios

- Querying digital input groups (16-bit)
- Reading encoder values
- Monitoring status registers
- Acquiring sensor data words
- Interface to I/O modules with word access

## ⚖️ Comparison with Similar Devices Function Blocks
Compared to simple digital input blocks, eIW offers:

- Advanced 16-bit data processing
- Detailed status feedback
- Flexible configuration options
- Support for event-based and polling-based operating modes
- Adapter interface for extended functionality

## Conclusion
The eIW function block provides a powerful and flexible interface for processing word input data in IEC 61499 control systems. Its combined support for synchronous queries and asynchronous notifications makes it particularly suitable for applications requiring both deterministic queries and time-critical state changes.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

