# Aux_QX

<img width="1481" height="173" alt="image" src="https://github.com/user-attachments/assets/3597540d-b375-4ca0-849a-c2a22e4c0732" />
* * * * * * * * * *
## Introduction

The Aux_QX function block is an output service interface function block for Boolean output data. It serves as an interface to auxiliary output devices and enables the control of Boolean output signals via a defined service mechanism.
![Aux_QX](Aux_QX.svg)

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
- **OUT** (BOOL): Output Data for the Resource
- **iInpNr** (INT): Auxiliary Array Number - corresponds to the order in the pool (the first aux input in the pool has iInpNr = 0, etc.)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

## Functionality

The The Aux_QX function block implements a standardized service interface for Boolean output data. Upon receiving an INIT event, the service is initialized, using the PARAMS and iInpNr parameters for configuration. The REQ event triggers the output of the Boolean value to the specified auxiliary resource. Each operation is acknowledged by corresponding confirmation events (INITO, CNF).

## Technical Features

- Supports addressing auxiliary outputs via the iInpNr parameter
- Flexible parameter configuration via STRING parameters
- Complete status feedback via the STATUS output
- Qualified event handling via QI/QO signals

## State Overview

The function block follows a typical service interface pattern with initialization and operating states. After successful initialization (INIT → INITO), service requests (REQ → CNF) can be processed.

## Application Scenarios

- Control of auxiliary output devices in ISOBUS environments
- Connection of Boolean actuators in agricultural machinery
- Integration into control systems for auxiliary functions
- Universal Boolean output interface in distributed automation systems

## ⚖️ Comparison with similar blocks

Compared to simple Boolean output blocks, Aux_QX offers extended service functionality with initialization sequences, parameter configuration, and detailed status management. Specific addressing via iInpNr enables integration into complex device pools.
...
## 🛠️ Related Exercises

- [Exercise_003c_sub](../../../../../../../Uebungen/test_B/Uebungen_doc/Uebung_003c_sub.md)

## Conclusion

The Aux_QX function block represents a robust and standardized solution for controlling Boolean auxiliary outputs. Its comprehensive service interface and flexible configurability make it particularly suitable for use in professional automation environments with ISOBUS compatibility.
