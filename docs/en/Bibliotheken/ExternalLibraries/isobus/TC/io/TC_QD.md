# TC_QD

<img width="1355" height="263" alt="image" src="https://github.com/user-attachments/assets/9eac6074-381e-43b4-a37b-11784ad4fd72" />
* * * * * * * * * *
## Introduction

The TC_QD function block is an output service interface function block for double-word output data. It serves as an interface for communication with external resources and enables the output of 32-bit data values via specified device elements.
![TC_QD](TC_QD.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**

- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Operation

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **OUT** (DWORD): Output Data for the Resource
- **wDevElementNumb** (UINT): Requested TC Element Number for Output
- **wDDI** (UINT): Output Data Dictionary Identifier

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapter**

No adapter interfaces are available.

## Functionality

The TC_QD function block initializes and manages communication with external output devices. Upon activating the INIT event, the service is initialized, configuring the parameters PARAMS, wDevElementNumb, and wDDI. The REQ event triggers the actual data output, sending the double-word value provided in the OUT input to the specified resource.

## Technical Features

- Processes 32-bit data values (DWORD)
- Supports Data Dictionary Identifiers (DDI) for standardized data referencing
- Provides device element number specification for precise device control
- Delivers detailed status information via the STRING output STATUS

## State Overview

The function block has two main operating states:

1. **Initialization State**: Activated by the INIT event and confirmed by INITO
2. **Service Operating State**: Activated by the REQ event and completed by CNF

## Application Scenarios

- Control of ISOBUS-compatible agricultural machinery
- Output of control commands to industrial actuators
- Communication with TC (Tractor Controller) output devices
- Applications in agricultural technology and mobile machinery

## ⚖️ Comparison with Similar Function Blocks

Compared to simpler output blocks, TC_QD offers enhanced functionality through:

- DDI-based data identification
- Configurable device element numbers
- ISOBUS specification compatibility
- Comprehensive status feedback

## 🛠️ Related exercises

* [Exercise_060](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_060.md)

## Conclusion

The TC_QD function block represents a powerful and flexible solution for outputting double-word data in ISOBUS environments. Its structured interface and extensive parameterization options make it particularly suitable for demanding control applications in mobile automation.