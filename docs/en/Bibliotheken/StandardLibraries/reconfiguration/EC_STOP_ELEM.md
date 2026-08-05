# EC_STOP_ELEM

![EC_STOP_ELEM](https://user-images.githubusercontent.com/116869307/214154650-cf730975-2179-4eb9-8312-7affc7c95a31.png)

* * * * * * * * * *

## Introduction
The EC_STOP_ELEM function block is used to stop instances according to the state machine of IEC 61499 function blocks. It can stop function block instances, connections (event/data), resources, or devices. This block belongs to the category of reconfiguration services and implements an execution control service according to IEC 61499-1.


![EC_STOP_ELEM](EC_STOP_ELEM.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Event to request that an element be stopped

### **Event Outputs**
- **CNF**: Event to confirm that the element has been stopped

### **Data Inputs**
- **QI** (BOOL): Event input qualifier
- **ELEM_NAME** (WSTRING): Element instance name
- **DST** (WSTRING): Destination where the element must be stopped (Syntax: ResourceName)

### **Data Outputs**
- **QO** (BOOL): Event output qualifier
- **STATUS** (WSTRING): Service status: RDY, NO_SUCH_OBJECT, INVALID_STATE

### **Adapters**
No adapter interfaces are available.


## Functionality

The EC_STOP_ELEM function block processes stop requests for various elements within an IEC 61499 system. Upon receipt of a REQ event with an enabled QI input, the stop process for the specified element is initiated. After completion of the stop process, a CNF event is output with the corresponding status.



``` ## Technical Features
- Supports stopping various element types: FBs, connections, resources, and devices
- Uses WSTRING data types for element names and targets
- Provides detailed status feedback on possible error states
- Implemented according to the IEC 61499-1 standard for execution control services

## State Overview
The function block has several service sequences:

- **normal_establishment**: Successful initialization
- **unsuccessful_establishment**: Failed initialization
- **request_confirm**: Successful stop request
- **request_inhibited**: Suppressed stop request
- **request_error**: Failed stop request
- **application_initiated_termination**: Application-initiated termination
- **resource_initiated_termination**: Resource-initiated termination

## Application Scenarios

- Dynamic reconfiguration of control systems
- Planned shutdown of system components
- Error handling Targeted stopping of faulty components

- Maintenance work on running systems

## ⚖️ Comparison with similar function blocks
Compared to other reconfiguration function blocks, EC_STOP_ELEM offers a specialized function for the targeted stopping of individual system components. While general reconfiguration function blocks often support more complex operations, this function block focuses on the specific task of controlled stopping.

## Conclusion
EC_STOP_ELEM is an essential function block for dynamic control systems that require runtime reconfiguration. Its clear interface and reliable status feedback make it a valuable tool for developing maintainable and flexible automation solutions according to IEC 61499.