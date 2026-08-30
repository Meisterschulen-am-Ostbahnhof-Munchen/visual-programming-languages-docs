# CLIENT_3_2

<img width="1368" height="191" alt="image" src="https://github.com/user-attachments/assets/bd26cabe-e445-4ad6-97b6-00579ab220c9" />
* * * * * * * * * *
## Introduction

The CLIENT_3_2 is a function block for HTTP communication, designed as a client with three inputs and two outputs. It enables communication with a server via the HTTP protocol and supports both opening and closing connections as well as sending requests and receiving responses.
![CLIENT_3_2](CLIENT_3_2.svg)

## Interface Structure

### **Event Inputs**

- **INIT** (Type: EInit) - Opens a new connection (QI = TRUE) or closes a connection (QI = FALSE)
- **REQ** (Type: Event) - Sends data to the server

### **Event Outputs**

- **INITO** (Type: EInit) - Signals that a new connection has been established (QI = TRUE) or a connection has been closed (QI = FALSE)
- **CNF** (Type: Event) - Response from the server

### **Data Inputs**

- **QI** (BOOL) - Quality indicator for INIT and REQ events
- **ID** (WSTRING) - Connection identifier
- **SD_1** (ANY) - Token for authentication with the server
- **SD_2** (ANY) - Parameter for the Message
- **SD_3** (ANY) - Message Body

### **Data Outputs**

- **QO** (BOOL) - Quality indicator for INITO and CNF events
- **STATUS** (WSTRING) - Status information
- **RD_1** (ANY) - Server response code
- **RD_2** (ANY) - Server response body

### **Adapter**

No adapter interfaces available.

## Functionality

The CLIENT_3_2 function block operates in two main phases: connection management and data transmission. The INIT event establishes or closes a connection to the server. After a successful connection, data can be sent to the server via the REQ event. The server response is reported back via the CNF event.

## Technical Features

- Use of WSTRING for ID and STATUS for international character set support
- ANY type for SD_1, SD_2, SD_3, RD_1, and RD_2 enables flexible data types
- Separate quality indicators for inputs (QI) and outputs (QO)
- Support for authentication tokens (SD_1)

## State Overview

1. **Initialization State**: Waiting for INIT event
2. **Connection Establishment**: Processing INIT with QI=TRUE
3. **Ready**: Connection established, waiting for REQ events
4. **Data Transfer**: Sending REQ and waiting for CNF
5. **Connection Termination**: Processing INIT with QI=FALSE

## Application Scenarios

- HTTP REST API communication in automation systems
- Web service integration in industrial controllers
- Data exchange with cloud services
- Authenticated communication with Backend Servers

## ⚖️ Comparison with Similar Modules

Compared to simpler client modules, CLIENT_3_2 offers enhanced functionality through three separate data inputs (SD_1-3) and two data outputs (RD_1-2), enabling structured transmission of authentication data, parameters, and message content.

## Conclusion

CLIENT_3_2 is a versatile HTTP client module that, thanks to its flexible data interface and comprehensive status feedback, enables robust communication with HTTP servers in industrial automation environments.
