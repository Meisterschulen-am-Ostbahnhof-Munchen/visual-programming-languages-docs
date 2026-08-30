# EBMaster

<img width="1420" height="292" alt="image" src="https://github.com/user-attachments/assets/699321b3-f59e-49ad-8e4c-2d0a94a6fccc" />
* * * * * * * * * *
## Introduction

The EBMaster function block is a Service Interface Function Block for communication with EtherBrick modules via SPI (Serial Peripheral Interface). It serves as the master component for controlling and configuring SPI bus communication with connected slave modules.
![EBMaster](EBMaster.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service Initialization - Initializes the SPI bus and configures the communication parameters

### **Event Outputs**

- **INITO**: Initialization Acknowledgement - Confirms successful completion of initialization
- **IND**: Resource Indication - Signals status changes or events from the connected modules

### **Data Inputs**

- **QI** (BOOL): Event Input Qualifier - Enables/Disables the function block
- **BusInterface** (UINT): ID of the SPI interface (initial value: 1)
- **BusSelectPin** (UINT): SPI Slave Select Pin (initial value: 49)
- **BusInitSpeed** (UDINT): SPI speed during initialization in Hz (initial value: 300000)
- **BusLoopSpeed** (UDINT): SPI speed during operation in Hz (initial value: 700000)
- **SlaveUpdateInterval** (UINT): Global update interval of the slave modules in Hz (initial value: 25)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier - status of the event output
- **STATUS** (WSTRING): Service Status - detailed status information

### **Adapters**

- **BusAdapterOut**: Adapter for communication with the EtherBrick bus system

## Functionality

The EBMaster manages SPI communication as the master component. During initialization (INIT event), it configures the SPI interface with the specified parameters. During operation, it controls the data transmission to the connected slave modules at the configured update interval. The block allows for different speeds during the initialization and operation phases.

## Technical Features

- Support for various SPI speeds for initialization and operation
- Configurable slave select pins
- Adjustable global update interval for slave modules
- WSTRING-based status feedback for detailed fault diagnosis

## State Overview

The function block goes through the following states:

1. **Not Initialized**: Waits for INIT event
2. **Initialization**: Configures SPI parameters upon INIT event
3. **Ready**: Sends INITO upon successful initialization
4. **Active**: Communicates with slaves according to the configured interval
5. **Fault**: Sends an IND event with STATUS information in case of problems

## Application Scenarios

- Control of EtherBrick I/O modules in automation systems
- SPI-based communication in embedded systems
- Industrial controllers with modular I/O expansions
- Real-time data acquisition with configurable Update Rates

## ⚖️ Comparison with Similar Blocks

Compared to generic SPI master blocks, EBMaster offers specific optimizations for EtherBrick modules, including pre-configured parameter values and specialized bus adapter interfaces.

## Conclusion

The EBMaster function block provides a robust and configurable solution for SPI master communication with EtherBrick modules. By separating initialization and operating speeds and offering a configurable update interval, it enables optimal adaptation to various application requirements.
