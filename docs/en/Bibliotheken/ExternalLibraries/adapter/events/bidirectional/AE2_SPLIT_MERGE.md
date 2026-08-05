# AE2_SPLIT_MERGE

<img width="1100" height="217" alt="image" src="https://github.com/user-attachments/assets/2e9417e6-db5d-41ea-95a9-b176f5538af4" />

* * * * * * * * * *

## Introduction
The AE2_SPLIT_MERGE is a bidirectional splitter and merge function block that can process events in both directions. The block enables the distribution and merging of events via adapter interfaces, without direct routing between the SOCKET and PLUG.


![AE2_SPLIT_MERGE](AE2_SPLIT_MERGE.svg)

## Interface Structure

### **Event Inputs**

- **EI**: Main event input for incoming events

### **Event Outputs**

- **EO**: Main event output for outgoing events

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

### **Adapters**

- **PLUG**: Adapter interface of type "adapter::types::bidirectional::AE2"

- **SOCKET**: Adapter interface of type "adapter::types::bidirectional::AE2"

## Functionality
The function block operates according to the following principles:

1. **Event Distribution**: Events at input EI are simultaneously forwarded to both adapter interfaces (PLUG and SOCKET).

2. **Event Merging**: Events from both adapter interfaces are combined. (PLUG.EI1 and SOCKET.EO1) are combined at output EO.

3. **Bidirectional Isolation**: There is no direct communication between the PLUG and SOCKET adapter interfaces.

## Technical Features
- Pure event processing without data transfer
- Symmetrical handling of both adapter directions
- Isolated signal paths between the adapter interfaces
- Real-time event distribution

## State Overview

The functional block has no internal state and operates stateless. All incoming events are processed and forwarded immediately.


## Application Scenarios

- Distribution of control events to multiple subsystems
- Merging of status events from various sources
- Bidirectional communication in distributed control systems
- Event-based architectures with adapter patterns

## ⚖️ Comparison with similar building blocks
Compared to simple splitter or merger blocks, AE2_SPLIT_MERGE offers:

- Bidirectional functionality in a single block
- Adapter-based interfaces for standardized communication
- Isolated signal paths between different adapter directions

## Conclusion
AE2_SPLIT_MERGE is a specialized function block for complex event distribution and merging scenarios in bidirectional communication architectures. Its adapter-based structure enables flexible and standardized integration into larger control systems.