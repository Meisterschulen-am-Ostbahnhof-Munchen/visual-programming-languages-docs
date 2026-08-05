# Aux_QXA

<img width="1474" height="164" alt="image" src="https://github.com/user-attachments/assets/d340aff6-bc76-425a-b4a7-5e628255f4a6" />

* * * * * * * * * *

## Introduction
The Aux_QXA is a composite function block for outputting Boolean data. It serves as an interface for auxiliary outputs in ISOBUS-compatible systems and enables the control of Boolean output signals via standardized interfaces.


![Aux_QXA](Aux_QXA.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization Event

- Linked to: QI, PARAMS, iInpNr

### **Event Outputs**

- **INITO**: Initialization Acknowledgement

- Linked to: QO, STATUS

- **CNF**: Acknowledgement of Requested Service

- Linked to: QO, STATUS

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier
- **PARAMS** (STRING): Service Parameter
- **iInpNr** (INT): Auxiliary Output Array Number (corresponds to the order in the pool, where the first auxiliary input has iInpNr = 0)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (STRING): Service Status

### **Adapter**

- **OUT**: Unidirectional adapter of type AX

- Position: x="-400", y="1000"

## Functionality
The Aux_QXA function block acts as a wrapper for the internal Aux_QX block. Upon initialization (INIT event), the configuration parameters are passed and the internal block is initialized. Output requests can be sent via the OUT adapter, which are then processed by the internal block. Acknowledgement is provided via the CNF and INITO output events.


## Technical Features
- Uses a unidirectional adapter for output communication
- Supports configurable service configuration via STRING parameters
- Allows addressing of multiple auxiliary outputs via the iInpNr parameter
- Implements standardized initialization and acknowledgment protocols

## State Overview
The function block goes through the following states:

1. **Not Initialized**: Before the INIT event
2. **Initialization**: During INIT processing
3. **Ready**: After successful initialization (INITO)
4. **Active**: During output processing (CNF)

## Application Scenarios
- Control of Boolean actuators in agricultural machinery
- ISOBUS-compatible auxiliary outputs in tractors and implements
- Automated control systems in agricultural technology
- Networked control of peripheral devices

## ⚖️ Comparison with Similar Blocks
Compared to simple Boolean output blocks, this offers Aux_QXA:

- Extended parameterization via STRING parameters

- ISOBUS compatibility
- Standardized initialization procedures

- Adapter-based interface for extended communication

## 🛠️ Related Exercises

* [Exercise_003c_sub_AX](../../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_003c_sub_AX.md)

## Conclusion
The Aux_QXA function block provides a robust and standards-compliant solution for controlling Boolean auxiliary outputs in ISOBUS systems. Its modular architecture and extended parameterization options make it particularly suitable for complex control tasks in modern agricultural technology.