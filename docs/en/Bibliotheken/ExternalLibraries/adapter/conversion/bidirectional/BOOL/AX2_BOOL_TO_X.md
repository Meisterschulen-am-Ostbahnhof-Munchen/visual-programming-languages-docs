# AX2_BOOL_TO_X

<img width="1186" height="196" alt="image" src="https://github.com/user-attachments/assets/ed299069-4248-4942-bdcb-3615f0044660" />
* * * * * * * * * *
## Introduction

The AX2_BOOL_TO_X function block serves as a composite function block for converting BOOL values into the AX2 adapter format. It enables bidirectional communication between simple BOOL data and the specific AX2 adapter interface.
![AX2_BOOL_TO_X](AX2_BOOL_TO_X.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Request event to activate the adapter
- Linked to data output OUT
- Y position: 46

### **Event Outputs**

- **CNF**: Acknowledge event from the adapter
- Linked to data input IN
- Y position: 46

### **Data Inputs**

- **OUT**: BOOL data input for output
- Y position: 31

### **Data Outputs**

- **IN**: BOOL data output for input
- Receives data from the adapter
- Y position: 47

### **Adapter**

- **AX2_OUT**: AX2 adapter for bidirectional communication
- Adapter type: adapter::types::bidirectional::AX2
- Position: x=-3900, y=-500

## Functionality

This function block acts as a bridge between BOOL data and the AX2 adapter. Upon receiving a REQ event, the OUT value is sent via the AX2_OUT adapter. Simultaneously, incoming data can be received via the same adapter and made available as an IN output with a CNF event.

## Technical Features

- Implemented as a composite function block
- Supports bidirectional data transmission
- Uses a specific AX2 adapter interface
- Automatic event and data forwarding between the main interface and the adapter

## State Overview

The function block operates statelessly and forwards events and data directly between the interfaces:

- REQ → AX2_OUT.EO1
- AX2_OUT.EI1 → CNF
- OUT → AX2_OUT.DO1
- AX2_OUT.DI1 → IN

## Application Scenarios

- Integration of BOOL signals into AX2-based systems
- Protocol translation between different automation levels
- Bidirectional data exchange scenarios
- Adapter-based system integration

## ⚖️ Comparison with Similar Blocks

Compared to simple conversion blocks, AX2_BOOL_TO_X offers:

- Bidirectional functionality
- Integrated adapter interface
- Complete event handling
- Higher level of abstraction Composite Design

## Conclusion

AX2_BOOL_TO_X is a specialized composite function block that efficiently bridges BOOL data and the AX2 adapter protocol. Its bidirectional architecture and integrated event handling make it ideal for systems requiring seamless integration between different protocol layers.
