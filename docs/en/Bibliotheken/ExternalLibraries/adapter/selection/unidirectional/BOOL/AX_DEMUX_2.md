# AX_DEMUX_2
<img width="1220" height="220" alt="image" src="https://github.com/user-attachments/assets/843be5c8-1e18-4cc5-81d1-922180394ad4" />
* * * * * * * * * *
## Introduction
The AX_DEMUX_2 is a generic demultiplexer function block that distributes input signals to different output channels based on an index value. This block is used for the targeted routing of data streams in distributed automation systems.
![AX_DEMUX_2](AX_DEMUX_2.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Sets the index K and initiates the demultiplexing process

### **Event Outputs**
- **CNF**: Confirms successful setting of index K

### **Data Inputs**
- **K** (UINT): Index value for controlling output selection

### **Data Outputs**
- No direct data outputs available

### **Adapters**
- **IN** (Socket): Input adapter for the value to be demultiplexed (unidirectional AX type)
- **OUT1** (Plug): First output adapter (unidirectional AX type)
- **OUT2** (Plug): Second output adapter (unidirectional AX type)

## Functionality
The AX_DEMUX_2 receives input data via the IN adapter and forwards it based on the Index value K is selectively passed to one of the two output adapters, OUT1 or OUT2. Upon activation of the REQ event, index K is set and the demultiplexing operation is performed. The CNF event signals the successful completion of the operation.

## Technical Features
- Generic implementation for flexible reuse
- Use of unidirectional AX adapters for clear signal flow direction
- UINT data type for index control enables extensible output selection
- Eclipse 4diac compatible according to IEC 61499-2 standard

## State Overview
The function block operates statelessly and reacts exclusively to incoming REQ events. Each REQ pulse leads to immediate processing and triggering of the CNF acknowledgment signal.

## Application Scenarios
- Distributing sensor data across different processing paths
- Selective activation of actuators in multi-channel systems
- Routing of control commands in modular systems
- Load balancing in parallel processing chains

## ⚖️ Comparison with similar components
Compared to simple switches or multiplexers, the AX_DEMUX_2 offers specialized demultiplexing functionality with an adapter-based interface. The use of standardized AX adapters ensures compatibility within the 4diac ecosystem.

Comparison with [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md)]

## Conclusion
The AX_DEMUX_2 represents an efficient and standards-compliant component for data distribution in IEC 61499-based automation systems. Its generic nature and adapter-based architecture make it a flexible solution for various demultiplexing applications.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]