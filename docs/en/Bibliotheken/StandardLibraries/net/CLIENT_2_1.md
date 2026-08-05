# CLIENT_2_1

<img width="1295" height="167" alt="image" src="https://github.com/user-attachments/assets/988495a6-1be4-41f0-9d85-c324b87e7290" />

* * * * * * * * * *

## Introduction
The CLIENT_2_1 function block is used to communicate with a SERVER_1_2 block via a network connection. It enables the establishment and termination of connections as well as data exchange between client and server.


![CLIENT_2_1](CLIENT_2_1.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization event to open (QI = TRUE) or close (QI = FALSE) a connection

- **REQ**: Request event to send data to the server and request data from the server

### **Event Outputs**

- **INITO**: Acknowledge event for connection establishment (QI = TRUE) or connection termination (QI = FALSE)

- **CNF**: Acknowledge event when new data is available from the server

### **Data Inputs**

- **QI** (BOOL): Quality indicator for the INIT event (TRUE = open connection, FALSE = close connection)

- **ID** (WSTRING): Identifier for the connection

- **SD_1** (ANY): First data transmission block to the server

- **SD_2** (ANY): Second data transmission block to the Server

### **Data Outputs**

- **QO** (BOOL): Quality indicator for output events

- **STATUS** (WSTRING): Status information about the connection or operation

- **RD_1** (ANY): Data block received from the server

### **Adapter**
No adapter interfaces available.

## Functionality
The CLIENT_2_1 block manages the entire client side of client-server communication. With INIT and QI=TRUE, a new connection to the specified server is established. With INIT and QI=FALSE, an existing connection is closed. The REQ event simultaneously triggers the sending of data SD_1 and SD_2 to the server and the request for data from the server. Upon successful operation, the received data is output via RD_1.


# ## Technical Features
- Supports the ANY data type for flexible data transfer
- Uses WSTRING for status messages and connection IDs
- Provides bidirectional data exchange in a single operation
- Implements complete connection management (establishment/disconnection)

## State Overview
The block can assume the following states:

- Not connected (initial state)
- Establishing connection
- Connected and ready for operation
- Disconnecting connection in progress

## Application Scenarios
- Industrial automation systems with distributed control
- IoT applications with client-server architecture
- Data exchange between different control levels
- Remote monitoring and control of devices

## ⚖️ Comparison with Similar Blocks
Compared to simpler client blocks, CLIENT_2_1 offers the ability to send two different data blocks simultaneously and receive one data block at a time. The integration of connection management and data exchange into a single block simplifies the application logic.


## Conclusion

The CLIENT_2_1 function block represents a powerful solution for client-server communication in distributed automation systems. By combining connection management and bidirectional data exchange in a single block, it enables efficient and transparent network applications.