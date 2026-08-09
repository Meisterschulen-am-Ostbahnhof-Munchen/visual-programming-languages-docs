# EBSlave2301

<img width="1529" height="334" alt="image" src="https://github.com/user-attachments/assets/8995d004-b357-48c9-b1d3-cc1fdc00c9e3" />
* * * * * * * * * *
## Introduction

The EBSlave2301 is a Service Interface Function Block for communication with an EtherBrick slave module. This function block serves as an interface for configuring and controlling up to six relay outputs via an EtherBrick bus system.
![EBSlave2301](EBSlave2301.svg)

## Interface Structure

### **Event Inputs**

- **MAP**: Triggered to configure the pin assignments. Accompanied by the data variables Relay_1 to Relay_6 and QI.

### **Event Outputs**

- **MAPO**: Confirms successful pin assignment. Outputs with QO.
- **IND**: Message from the resource interface. Outputs with QO and STATUS.

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Enables/disables the function block
- **Relay_1** to **Relay_6** (WSTRING): Relay pin configuration
- **UpdateInterval** (UINT): Slave module update interval in Hz (inherited from the master)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - Operation status
- **STATUS** (WSTRING): Service status information

### **Adapters**

- **BusAdapterOut** (Plug): Outgoing bus adapter of type EBBusAdapter
- **BusAdapterIn** (Socket): Incoming bus adapter of type EBBusAdapter

## Functionality

The EBSlave2301 allows the configuration of up to six relay outputs via the MAP event. When activated by QI, the relay parameters are transmitted to the EtherBrick system via the bus adapters. The MAPO event confirms successful configuration, while IND events provide status information from the resource interface.

## Technical Features

- Supports WSTRING data types for relay configuration
- Uses an adapter-based bus system for communication
- UpdateInterval is inherited from the master system
- Provides qualified event control via QI and QO

## State Overview

The function block toggles between the following states:

- Inactive: QI = FALSE
- Configuration mode: On MAP event with QI = TRUE
- Ready for operation: After successful MAPO acknowledgment
- Fault state: On IND event with status information

## Application Scenarios

- Control of relay-based actuators in automation systems
- Integration into EtherBrick-based I/O systems
- Distributed control system with master-slave architecture
- Applications with configurable relay assignments

## ⚖️ Comparison with Similar Devices

Compared to simple digital output devices, the EBSlave2301 offers:

- Configurable pin assignments for Runtime
- Adapter-based bus communication
- Qualified event control
- Status feedback from the resource interface

## Conclusion

The EBSlave2301 is a specialized function block for the flexible control of relay outputs in EtherBrick systems. Its configurable interfaces and adapter-based architecture make it particularly suitable for demanding automation applications with dynamic I/O configurations.
