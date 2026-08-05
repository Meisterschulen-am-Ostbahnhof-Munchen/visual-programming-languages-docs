# QD

![](https://user-images.githubusercontent.com/69573151/210781704-73d6a020-e7c0-430e-9797-2d0ef1cc6cc3.png)

* * * * * * * * * *
## Introduction
The QD function block is an output service interface component for outputting double-word (DWORD) data. It serves as an interface between the application logic and the physical output devices of a resource manager.


![QD](QD.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization - initializes the function block with the required parameters
- **REQ**: Service Request - triggers data output to the resource

### **Event Outputs**
- **INITO**: Initialization Acknowledgement - confirms completion of initialization
- **CNF**: Acknowledgement of Requested Service Execution - signals completion of data output

### **Data Inputs**
- **QI**: Event Input Qualifier (BOOL) - controls the execution of service requests

- **PARAMS**: Service Parameters (STRING) - configuration parameters for the service

- **OUT**: Output Data (DWORD) - the double-word data to be transmitted to the resource

### **Data Outputs**
- **QO**: Event Output Qualifier (BOOL) - status of the Service Execution

- **STATUS**: Service status (STRING) - detailed status information about service execution

### **Adapter**
No adapter interfaces are available.

## Functionality
The QD block operates as a cyclic service interface component. Upon receiving the INIT event, the block is initialized with the configuration data passed via PARAMS. The actual data output is triggered by the REQ event, whereby the DWORD data provided in the OUT input is transferred to the assigned resource. Each service request is acknowledged by corresponding confirmation events (INITO or CNF).


## Technical Features
- Processes 32-bit data (DWORD)
- Supports configurable service configuration
- Provides detailed status feedback
- Works with qualifier flags for reliable service control

## State Overview
The block goes through the following states:

1. **Not Initialized**: Block waits for an INIT event

2. **Initialized**: Block is ready for operation and waits for REQ events

3. **Service Execution**: Processing a REQ request

4. **Acknowledgement**: Feedback of the service result

## Application Scenarios

- Control of digital output modules with 32-bit data width
- Control of complex actuators with multiple parameter passing
- Integration into distributed control systems with resource management
- Applications with high output data integrity requirements

## ⚖️ Comparison with Similar Blocks
Compared to simpler output blocks, QD offers:

- Enhanced parameterization through STRING parameters

- DWORD data width instead of simple BOOL or BYTE values

- Detailed status feedback for fault diagnosis

- Complete service interface characteristics with initialization procedure

## 🛠️ Related Exercises

* [Exercise_060](../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion
The QD function block represents a powerful and flexible solution for outputting double-word data in IEC 61499 systems. Its comprehensive parameterization and detailed status feedback make it particularly suitable for demanding automation applications that require reliable and configurable output services.