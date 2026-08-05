# AX_DEMUX_4
<img width="1220" height="274" alt="image" src="https://github.com/user-attachments/assets/b2301b38-e22d-4369-99f4-29de847e9d20" />
* * * * * * * * * *
## Introduction
The AX_DEMUX_4 is a generic demultiplexer function block that receives incoming data via an adapter input and selectively forwards it to one of four output adapters based on an index value. This function block is used to distribute data streams in distributed automation systems.
![AX_DEMUX_4](AX_DEMUX_4.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Sets the index K and initiates the demultiplexing operation

### **Event Outputs**
- **CNF**: Confirms index setting and successful demultiplexing operation

### **Data Inputs**
- **K** (UINT): Index value for selecting the target output (0-3)

### **Data Outputs**
*No direct data outputs available*

### **Adapters**
- **IN** (Socket): Unidirectional AX adapter for the input value for demultiplexing
- **OUT1** (Plug): Unidirectional AX adapter for output 1
- **OUT2** (Plug): Unidirectional AX adapter for output 2
- **OUT3** (Plug): Unidirectional AX adapter for output 3
- **OUT4** (Plug): Unidirectional AX adapter for output 4

## Functionality
The AX_DEMUX_4 operates as a 4-way demultiplexer. Upon receiving a REQ event, the current value of index K is evaluated. Based on this index value, the incoming data stream is selectively routed from the IN adapter to one of the four OUT adapters. After successful distribution, the CNF event is triggered.

## Technical Features
- Generic function block with type-hash support
- Uses unidirectional AX adapters for robust data communication
- Index-based selection with UINT data type
- Four fixed output adapters

## State Overview
The function block has a simple state machine:

1. **Wait State**: Ready for REQ event
2. **Process State**: Evaluation of K and data distribution
3. **Acknowledge State**: Triggering of CNF after successful operation

## Application Scenarios
- Distribution of sensor data to different processing units
- Load balancing in distributed control systems
- Selective data forwarding based on priorities or target groups
- Routing of communication data in network architectures

## ⚖️ Comparison with Similar Components
Compared to simple multiplexers, AX_DEMUX_4 offers four fixed outputs with an adapter-based interface, enabling greater flexibility in distributed systems. The use of standard AX adapters ensures compatibility with other 4diac components.

Comparison with [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md)]

## Conclusion
The AX_DEMUX_4 is a robust and easy-to-configure demultiplexer for industrial automation systems. Its adapter-based architecture enables flexible integration into existing control structures, while index-driven selection ensures precise data distribution.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)]
