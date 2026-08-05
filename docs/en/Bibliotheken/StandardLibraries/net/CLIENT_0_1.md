# CLIENT_0_1

* * * * * * * * * *

## Introduction
The CLIENT_0_1 function block is used to communicate with a corresponding server block (e.g., SERVER_1_0) via a network connection. It is specifically designed to **receive** data from the server without sending any data itself (Receive Only Client).


![CLIENT_0_1](CLIENT_0_1.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Opens a new connection (QI = TRUE) or closes an existing connection (QI = FALSE)

- **REQ**: Requests data from the server

### **Event Outputs**

- **INITO**: Confirms that a new connection has been established (QI = TRUE) or that a connection has been closed (QI = FALSE)

- **CNF**: Signals that new data has been received from the server and is available at RD_1

### **Data Inputs**

- **QI** (BOOL): Controls the connection status (TRUE = open connection, FALSE = close connection)

- **ID** (WSTRING): Identifier for the connection

### **Data Outputs**

- **QO** (BOOL): Connection status (TRUE = connected, FALSE = disconnected)

- **STATUS** (WSTRING): Connection status information

- **RD_1** (ANY): Data received from the server

### **Adapter**
No adapter interfaces are available.

## Functionality
The CLIENT_0_1 block establishes a connection via INIT. It requests data from the server using the REQ event. When the server responds, the data is provided at output RD_1, and the CNF event is triggered. There is no data input for sending user data.

## Technical Features
- Unidirectional data transmission (receive)
- Use of the ANY data type for RD_1 enables flexible data types
- WSTRING data type for ID and STATUS

## Application Scenarios

- Querying sensor values or status information from a remote system

- Monitoring systems that only read data

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | © 2017, 2025 fortiss GmbH, JKU Linz |

License | EPL-2.0 |

Version | 3.0 (2025-19-26, Alois Zoitl) |

4diac Package | iec61499::net |

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]