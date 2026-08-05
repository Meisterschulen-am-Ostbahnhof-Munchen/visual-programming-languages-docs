# EC_START_ELEM
![EC_START_ELEM](https://user-images.githubusercontent.com/116869307/214154626-dbd925bc-19c1-4bbf-98f5-db588d7cefec.png)

* * * * * * * * * *
## Introduction
The EC_START_ELEM function block is used to start instances according to the state machine definition of IEC 61499 function blocks. It enables the targeted starting of function block instances, connections (event/data), resources, or devices within a distributed automation system.
![EC_START_ELEM](EC_START_ELEM.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Event to request the start of an element. Associated with the data ELEM_NAME, DST, and QI.

### **Event Outputs**
- **CNF**: Event to confirm that the element has been started. Associated with the data STATUS and QO.

### **Data Inputs**
- **QI** (BOOL): Event input qualifier for controlling the request
- **ELEM_NAME** (WSTRING): Name of the element instance to be started
- **DST** (WSTRING): Destination where the element must be started (Syntax: ResourceName)

### **Data Outputs**
- **QO** (BOOL): Event output qualifier for status feedback
- **STATUS** (WSTRING): Service status with possible values: RDY, NO_SUCH_OBJECT, INVALID_STATE

### **Adapters**

No adapter interfaces are available.

## Operation

The function block responds to the REQ event and attempts to start the specified element (function block, connection, resource, or device) at the specified destination. The start process follows the IEC 61499 state machine. Upon successful startup, the CNF event is returned with the status "RDY". In case of errors, corresponding status messages such as "NO_SUCH_OBJECT" or "INVALID_STATE" are returned.

## Technical Features

- Supports wide-string data types for element names and destinations
- Implements a qualifier system to control execution logic
- Provides detailed status feedback for various error states
- Complies with the IEC 61499 standard for execution control services

## State Overview

The function block has several service sequences:

- **normal_establishment**: Successful initialization
- **unsuccessful_establishment**: Failed initialization
- **request_confirm**: Successful request processing
- **request_inhibited**: Suppressed request
- **request_error**: Failed request processing
- **application_initiated_termination**: Application-side termination
- **resource_initiated_termination**: Resource-side termination

## Application Scenarios
- Dynamically starting function blocks in running systems
- Reconfiguring automation systems at runtime
- Distributed management of resources and devices
- Fault-tolerant systems with restart functionality

## ⚖️ Comparison with similar function blocks

Compared to simple start function blocks, EC_START_ELEM offers extended functionality for distributed systems with specific destination specification and detailed status feedback. It is part of the reconfiguration services and supports various element types beyond those of simple function blocks.

## Conclusion

EC_START_ELEM is a powerful function block for the dynamic control of automation system components. Its ability to start various element types at specific destinations makes it particularly valuable for reconfigurable and adaptive control systems according to IEC 61499.
