# CLIENT_1_0

* * * * * * * * * *
## Introduction

The CLIENT_1_0 function block is used to communicate with a corresponding server block (e.g., SERVER_0_1) via a network connection. It is specifically designed for **sending** data to the server without receiving any data (Send Only Client).
![CLIENT_1_0](CLIENT_1_0.svg)
## Interface Structure

### **Event Inputs**

- **INIT**: Opens a new connection (QI = TRUE) or closes an existing connection (QI = FALSE)
- **REQ**: Sends the data present at SD_1 to the server

### **Event Outputs**

- **INITO**: Confirms that a new connection has been established (QI = TRUE) or that a connection has been closed (QI = FALSE)
- **CNF**: Confirms that the data was sent successfully

### **Data Inputs**

- **QI** (BOOL): Controls the connection status (TRUE = open connection, FALSE = close connection)
- **ID** (WSTRING): Identifier for the connection
- **SD_1** (ANY): Data to be sent to the server

### **Data Outputs**

- **QO** (BOOL): Connection status (TRUE = connected, FALSE = disconnected)
- **STATUS** (WSTRING): Status information about the connection

### **Adapter**

No adapter interfaces are available.

## Functionality

The CLIENT_1_0 block establishes a connection via INIT. When the REQ event is triggered, the block sends the value of SD_1 to the server. Successful transmission is confirmed by the CNF event. There is no data output for received data.

## Technical Features

- Unidirectional data transmission (sending)
- Use of the ANY data type for SD_1 enables flexible data types
- WSTRING data type for ID and STATUS

## Application Scenarios

- Sending control commands or setpoints to a remote system (without a direct response as data)
- Logging clients that push data to a central server

## Metadata

| Attribute | Value |
| :--- | :--- |
| Copyright | (c) 2017, 2025 fortiss GmbH, JKU Linz |
| License | EPL-2.0 |
| Version | 3.0 (2025-19-26, Alois Zoitl) |
| 4diac Package | iec61499::net |

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
