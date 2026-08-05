# SUBSCRIBE_7
<img width="1108" height="417" alt="image" src="https://github.com/user-attachments/assets/ac515d80-1f79-40e2-ae6f-0236e0a0ec3b" />
* * * * * * * * * *
## Introduction
The SUBSCRIBE_7 function block acts as a subscriber for data from a PUBLISH_7 block. It enables the reception of up to seven different data points over a single communication link. This block is part of the IEC 61499 network communication functionality and is used in distributed automation systems.
![SUBSCRIBE_7](SUBSCRIBE_7.svg)

## Interface Structure

### **Event Inputs**
- **INIT**: Initialization event with associated data QI and ID
- **RSP**: Response event with associated data QI

### **Event Outputs**
- **INITO**: Initialization confirmation with associated data QO and STATUS
- **IND**: Indication event when new data is available with associated data QO, STATUS, and RD_1 to RD_7

### **Data Inputs**
- **QI** (BOOL): Qualifier for initialization
- **ID** (WSTRING): Identifier for the connection

### **Data Outputs**
- **QO** (BOOL): Qualifier for output state
- **STATUS** (WSTRING): Connection status information
- **RD_1** to **RD_7** (ANY): Received data points 1 to 7

### **Adapter**
No adapter interfaces available.

## Functionality
The SUBSCRIBE_7 block initializes itself via the INIT event and establishes a connection to a corresponding PUBLISH_7 block. After successful initialization, it confirms this via INITO. When data is received from the publisher, the IND event is triggered, and the received data is output via RD_1 to RD_7. The RSP input allows for the handling of reply messages.

## Technical Features
- Supports up to seven different data points simultaneously
- Uses WSTRING for status and identification information
- ANY data type for received data enables flexible data types
- Generic implementation via the GEN_SUBSCRIBE base class

## State Overview
1. **Not Initialized**: Block waits for INIT event

2. **Initialization**: Processing the INIT request
3. **Ready**: Successfully connected, waiting for data
4. **Data Receiving**: Processing incoming data with IND trigger

## Application Scenarios
- Distributed automation system with data distribution
- Machine networking in Industry 4.0 environments
- Data exchange between different control components
- Monitoring systems with centralized data collection

## ⚖️ Comparison with Similar Blocks
Compared to simpler SUBSCRIBE blocks, SUBSCRIBE_7 offers the ability to receive up to seven data points in parallel. Compared to individual communication solutions, it offers standardized IEC 61499 interfaces and simplified configuration.

## Conclusion
The SUBSCRIBE_7 block is a powerful communication module for distributed automation systems. Its flexible data transmission and standardized interfaces provide a reliable foundation for industrial communication applications.