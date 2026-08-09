# CLIENT_1

<img width="1355" height="161" alt="image" src="https://github.com/user-attachments/assets/add0b8a4-197b-4733-b9d8-45407aae8979" />
* * * * * * * * * *
## Introduction

The CLIENT_1 function block is used to communicate with a SERVER_1 block via a network connection. It enables the establishment and closure of connections as well as data exchange between client and server.
![CLIENT_1](CLIENT_1.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Opens a new connection (QI = TRUE) or closes an existing connection (QI = FALSE)
- **REQ**: Sends data to the server and requests data from the server

### **Event Outputs**

- **INITO**: Confirms the establishment of a new connection (QI = TRUE) or the closing of a connection (QI = FALSE)
- **CNF**: Signals that new data is available from the server

### **Data Inputs**

- **QI** (BOOL): Controls the connection status (TRUE = open connection, FALSE = close connection)
- **ID** (WSTRING): Identifier for the connection
- **SD_1** (ANY): Data to be sent to the server

### **Data Outputs**

- **QO** (BOOL): Connection status (TRUE = connected, FALSE = disconnected)
- **STATUS** (WSTRING): Connection status information
- **RD_1** (ANY): Data received from the server

### **Adapter**

No adapter interfaces are present.

## Functionality

The CLIENT_1 block initializes a network connection to the SERVER_1 block via the INIT event. Upon successful connection, the INITO event is triggered with QO=TRUE. Data can be sent to and requested from the server via the REQ event. Received data is made available via the CNF event using the corresponding data outputs.

## Technical Features

- Use of the ANY data type for SD_1 and RD_1 enables flexible data types
- WSTRING data type for ID and STATUS supports Unicode characters
- Generic implementation through GEN_CLIENT class names

## State Overview

1. **Not connected**: Initial state, QO = FALSE
2. **Connection establishing**: INIT processed with QI = TRUE
3. **Connected**: INITO confirmed with QO = TRUE
4. **Data transmission**: REQ/CNF cycle for data exchange
5. **Connection disconnection**: INIT processed with QI = FALSE

## Application Scenarios

- Communication between distributed control systems
- Data exchange in Industry 4.0 applications
- Client-server architectures in automation systems
- Networked control components via TCP/IP or other protocols

## ⚖️ Comparison with similar modules

Compared to simpler communication modules, this offers CLIENT_1:

- Bidirectional data exchange in a single transaction
- Flexible data types through ANY type
- Explicit connection control
- Detailed status feedback

## Conclusion

The CLIENT_1 function block provides a robust solution for client-server communication in distributed automation systems. Its flexible interface and explicit connection control make it particularly suitable for demanding network applications in industrial environments.