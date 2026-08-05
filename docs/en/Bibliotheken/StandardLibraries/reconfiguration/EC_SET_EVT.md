# EC_SET_EVT

![EC_SET_EVT](https://user-images.githubusercontent.com/116869307/214154604-e4081ae0-85d5-496e-a037-2b8bf39eba7d.png)

* * * * * * * * * *

## Introduction

The EC_SET_EVT function block is used to set event inputs or outputs of a function block instance. It enables the targeted triggering of events in other function blocks and can be used, for example, as an event sniffer. This function block belongs to the category of reconfiguration services according to the IEC 61499-1 standard.


![EC_SET_EVT](EC_SET_EVT.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - triggers the execution of the setting operation

### **Event Outputs**

- **CNF**: Acknowledgement of the requested service operation

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - enables/disables the service

- **FB_NAME** (WSTRING): Name of the function block instance

- **FB_EVENT_IO** (WSTRING): Name of the event to be set

- **DST** (WSTRING): Destination where the event is to be set (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - indicates the status of the service execution

- **STATUS** (WSTRING): Service status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapter**

No adapter interfaces are available.

## Functionality

The EC_SET_EVT function block receives a request via the REQ event to set a specific event in another function block instance. The input data specifies the target function block instance (FB_NAME), the event to be set (FB_EVENT_IO), and the destination (DST). After successful execution, the CNF event is returned with the corresponding status.














... ## Technical Features

- Implementation in C++ for GCC compiler version 3.0 and later

- Supports wide-string data types for international character sets
- Provides detailed status feedback for troubleshooting
- Operates as a reconfiguration service between the application and the resource

## State Overview

The function block supports several service sequences:

- **normal_establishment**: Successful initialization
- **unsuccessful_establishment**: Failed initialization
- **request_confirm**: Successful service execution
- **request_inhibited**: Suppressed service request
- **request_error**: Failed service execution
- **application_initiated_termination**: Application-side termination
- **resource_initiated_termination**: Resource-side termination

## Application Scenarios

- Debugging and monitoring of event flows
- Automated test environments
- Dynamic reconfiguration of control systems
- Event-based diagnostic functions
- Simulation of external Events

## ⚖️ Comparison with Similar Function Blocks

Compared to standard function blocks, EC_SET_EVT offers special reconfiguration capabilities that go beyond normal event processing. It allows external access to events in other function blocks, which is particularly valuable for diagnostic and testing purposes.

## Conclusion

The EC_SET_EVT function block is a powerful tool for advanced control applications, especially for debugging, testing, and dynamic reconfiguration. Its ability to selectively set events in other function block instances makes it a valuable component for complex automation systems.