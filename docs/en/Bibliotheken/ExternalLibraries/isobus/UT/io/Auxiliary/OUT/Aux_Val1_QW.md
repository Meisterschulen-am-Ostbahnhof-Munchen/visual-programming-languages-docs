# Aux_Val1_QW
<img width="1496" height="174" alt="image" src="https://github.com/user-attachments/assets/06793149-2165-45d1-91f2-b47c071b9248" />
* * * * * * * * * *
## Introduction
The Aux_Val1_QW is an output service interface function block for word output data. This block serves as an interface to auxiliary output resources and enables the output of 16-bit data words to external peripheral devices.
![Aux_Val1_QW](Aux_Val1_QW.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Service Initialization Event
- **REQ**: Service Request Event

### **Event Outputs**
- **INITO**: Initialization Acknowledgement
- **CNF**: Acknowledgement of Requested Service Execution

### **Data Inputs**
- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameters
- **OUT** (WORD): Output Data for the Resource
- **iInpNr** (INT): Auxiliary Array Number - corresponds to the order in the pool (the first aux input in the pool has iInpNr = 0, etc.)

### **Data Outputs**
- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapter**
No adapter interfaces available.

## Functionality
This function block initializes and controls auxiliary output devices via the ISOBUS UT protocol stack. During initialization (INIT event), the service parameters are configured and the auxiliary device is set up accordingly. Upon service requests (REQ event), the WORD data is sent to the configured output device. The block supports various auxiliary device types and provides status feedback on the success or failure of operations.

## Technical Features
- Supports Auxiliary Types: 0, 1, 2, 3, 4, 6, 11, 12, 13
- Uses WORD data type (16-bit) for output data
- Implements ISOBUS UT protocol for auxiliary I/O
- Provides detailed status information via STRING output
- Allows configuration of multiple auxiliary devices via iInpNr parameters

## State Overview
The function block has two main operating states:

1. **Initialization State**: Processes the INIT request and configures the auxiliary device

2. **Service State**: Processes REQ requests and outputs data to the configured device

## Application Scenarios
- Control of auxiliary output devices in mobile machinery
- ISOBUS-compliant peripheral control
- Agricultural and construction machinery applications
- Connectivity of Word-based output devices via the UT protocol

## ⚖️ Comparison with Similar Function Blocks

Compared to simple digital output blocks, Aux_Val1_QW offers advanced functionality for ISOBUS environments, including parameterization, status feedback, and support for various auxiliary device types. The WORD data width enables the control of more complex peripheral devices compared to simple BOOL output blocks.

## Conclusion
The Aux_Val1_QW function block represents a robust and standards-compliant solution for controlling auxiliary WORD output devices in ISOBUS environments. Its flexible configurability and comprehensive status feedback make it particularly suitable for demanding industrial and mobile applications.
