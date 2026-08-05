# CLIENT_0
* * * * * * * * * *
## Introduction
The CLIENT_0 function block is used to communicate with a SERVER_0 block via a network connection. It enables the establishment and closure of connections. Unlike CLIENT_1, there is no explicit data exchange via data inputs/outputs; synchronization occurs primarily through events.

* ![CLIENT_0](CLIENT_0.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Opens a new connection (QI = TRUE) or closes an existing connection (QI = FALSE)
- **REQ**: Requests interaction with the server

### **Event Outputs**
- **INITO**: Confirms that a new connection has been established (QI = TRUE) or that a connection has been closed (QI = FALSE)
- **CNF**: Confirms that the request has been executed

### **Data Inputs**
- **QI** (BOOL): Controls the connection status (TRUE = open connection, FALSE = close connection)
- **ID** (WSTRING): Identifier for the connection

### **Data Outputs**
- **QO** (BOOL): Connection status (TRUE = connected, FALSE = disconnected)
- **STATUS** (WSTRING): Status information about The Connection

### **Adapter**
No adapter interfaces are available.

## Functionality
The CLIENT_0 block initializes a network connection to the SERVER_0 block via the INIT event. Upon successful connection, the INITO event is triggered with QO=TRUE. Interaction with the server can be initiated via the REQ event, the completion of which is confirmed by CNF.

## Technical Features
- No data inputs/outputs (SD_x, RD_x) available
- WSTRING data type for ID and STATUS
- Generic implementation via GEN_CLIENT class name

## State Overview
1. **Not connected**: Initial state, QO = FALSE

2. **Connection Established**: INIT processed with QI = TRUE

3. **Connected**: INITO confirmed with QO = TRUE

4. **Interaction**: REQ/CNF cycle

5. **Connection Disconnected**: INIT processed with QI = FALSE

## Application Scenarios
- Pure event synchronization between systems
- "Heartbeat" monitoring without user data
- Trigger signals over network

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | (c) 2025 Monika Wenger |

| License | EPL-2.0 |

Version | 3.0 (December 5, 2025, Monika Wenger) |

4diac Package | iec61499::net |

--

### 🌐 Related subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
