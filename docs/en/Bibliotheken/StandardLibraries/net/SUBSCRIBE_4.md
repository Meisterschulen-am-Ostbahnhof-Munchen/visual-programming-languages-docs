# SUBSCRIBE_4

<img width="1291" height="393" alt="image" src="https://github.com/user-attachments/assets/64c5b7ee-a7e0-4217-a6d8-5b4904bf79d4" />

* * * * * * * * * *
## Introduction
The SUBSCRIBE_4 function block is used to subscribe to data from a PUBLISH_4 block. It allows the receipt of up to four different data points via a communication link and makes them available when they become available.


``` ![SUBSCRIBE_4](SUBSCRIBE_4.svg)

## Interface Structure

### **Event Inputs**

- **INIT** (Type: EInit) - Initialization Event

- Linked to: QI, ID

- **RSP** (Type: Event) - Response Event

- Linked to: QI

### **Event Outputs**

- **INITO** (Type: EInit) - Initialization Acknowledgement

- Linked to: QO, STATUS

- **IND** (Type: Event) - Data Availability Message

- Linked to: QO, STATUS, RD_1, RD_3, RD_2, RD_4

### **Data Inputs**

- **QI** (BOOL) - Qualified Input (Activation/Deactivation)

- **ID** (WSTRING) - Identifier for the Communication Connection

### **Data Outputs**

- **QO** (BOOL) - Qualified Output (Status Feedback)

- **STATUS** (WSTRING) - Status Information

- **RD_1** (ANY) - Received Data 1

- **RD_2** (ANY) - Received Data 2

- **RD_3** (ANY) - Received Data 3
- **RD_4** (ANY) - Received Data 4

### **Adapters**
No adapter interfaces are available.

## Functionality
Upon receiving the INIT event, the SUBSCRIBE_4 block initializes a subscription connection to a PUBLISH_4 block using the specified ID. After successful initialization, it confirms this with INITO. When new data is available from the publisher, the IND event is triggered, and the received data is made available via the RD_1 to RD_4 outputs.


### ## Technical Features
- Supports receiving up to four different data types (ANY type)
- Uses WSTRING for status and identification information
- Generic implementation via the GEN_SUBSCRIBE base class
- Robust error handling via STATUS output

## State Overview
1. **Inactive**: Block is not initialized
2. **Initialized**: Subscription active, waiting for data
3. **Data Receiving**: Processes incoming data and outputs an IND event

## Application Scenarios
- Distributed automation systems
- Data distribution in decentralized controllers
- Communication between different control components
- Monitoring systems with data subscription

## ⚖️ Comparison with Similar Blocks
Compared to simpler SUBSCRIBE blocks, SUBSCRIBE_4 offers the ability to receive up to four different data points simultaneously. This enhanced functionality makes it particularly suitable for more complex communication scenarios where multiple data sources need to be consolidated.

## Conclusion
The SUBSCRIBE_4 function block represents a powerful solution for subscription-based communication in IEC 61499 systems. Its ability to manage multiple data points in parallel makes it a flexible choice for demanding automation applications with distributed data communication.