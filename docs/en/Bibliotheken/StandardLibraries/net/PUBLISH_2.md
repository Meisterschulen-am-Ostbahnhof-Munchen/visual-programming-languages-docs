# PUBLISH_2

<img width="1179" height="286" alt="image" src="https://github.com/user-attachments/assets/ae23ed15-e54c-43ad-8379-07e0e8126f56" />

* * * * * * * * * *

## Introduction
The PUBLISH_2 function block is used to send data to one or more SUBSCRIBE_2 blocks. It enables unacknowledged communication between different components in a distributed system.


![PUBLISH_2](PUBLISH_2.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization event with the associated data QI and ID

- **REQ**: Request event to send data with the associated data QI, SD_1, and SD_2

### **Event Outputs**

- **INITO**: Confirmation of initialization with the associated data QO and STATUS

- **CNF**: Confirmation that data has been sent, with the associated data QO and STATUS

### **Data Inputs**

- **QI** (BOOL): Qualifier for initialization and operation

- **ID** (WSTRING): Identifier for communication

- **SD_1** (ANY): First data value to be sent (any data type)

- **SD_2** (ANY): Second data value to be sent (any data type)

### **Data Outputs**

- **QO** (BOOL): Qualifier for the output state

- **STATUS** (WSTRING): Status information about the operating state

### **Adapters**
No adapters available.

## Functionality
The PUBLISH_2 block initializes itself via the INIT event and then sends data via the REQ event. The data SD_1 and SD_2 are distributed to all connected SUBSCRIBE_2 blocks. Communication is unacknowledged, meaning that no response is expected from the receivers.


## Technical Features
- Supports any data type for SD_1 and SD_2
- Uses WSTRING for ID and STATUS for international character support
- Unacknowledged communication mode (Publish/Subscribe pattern)
- Flexible data transmission with two separate data channels

## State Overview
1. **Not Initialized**: Block waits for INIT event

2. **Initialized**: Block is ready and can process REQ events
3. **Ready to Send**: Processes REQ events and sends data to the subscriber

## Application Scenarios
- Distributed systems with multiple data receivers
- Real-time data distribution without an acknowledgment mechanism
- Systems with variable data types
- Communication between different control components

## ⚖️ Comparison with Similar Blocks
Compared to acknowledged communication blocks, PUBLISH_2 offers higher performance but lower reliability. Its support for any data type makes it more flexible than type-specific communication blocks.


## Conclusion

The PUBLISH_2 block is an efficient tool for unacknowledged data distribution in distributed systems. Its flexibility in data type support and ease of use make it ideal for scenarios where performance is more important than guaranteed delivery.