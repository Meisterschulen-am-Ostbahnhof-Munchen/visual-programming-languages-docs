# SERVER_0
* * * * * * * * * *
## Introduction
The SERVER_0 function block serves as the counterpart to a CLIENT_0 block. It enables the establishment of a server-client connection without exchanging user data via data inputs/outputs.
``` ![SERVER_0](SERVER_0.svg)
## Interface Structure

### **Event Inputs**
- **INIT** (Type: Event) - Enables the server for a client connection (QI = TRUE) or shuts down the server (QI = FALSE)
- **RSP** (Type: Event) - Sends a response/acknowledgment to the client

### **Event Outputs**
- **INITO** (Type: Event) - Signals readiness for a client connection (QI = TRUE) or a closed state (QI = FALSE)
- **IND** (Type: Event) - Indicates that a request has been received from the client

### **Data Inputs**
- **QI** (BOOL) - Qualifier for the INIT operation
- **ID** (WSTRING) - Identifier for the server instance

### **Data Outputs**
- **QO** (BOOL) - Qualifier for status output
- **STATUS** (WSTRING) - Status Information

## Functionality
The SERVER_0 block manages the connection.

1. **Initialization**: Activation via INIT.

2. **Synchronization**:

- When the client sends a request (REQ), the IND event is triggered on the server.
- The server can then respond with RSP, which triggers the CNF event on the client.

No user data (SD_x, RD_x) is transmitted during this process.

## Technical Features
- No data inputs/outputs available
- WSTRING type for ID and STATUS
- Generic implementation via the 'GEN_SERVER' class attribute

## State Overview
- **Not Initialized**: Server inactive
- **Initialized**: Server ready
- **Indication (IND)**: Client has requested
- **Response (RSP)**: Server responding

## Application Scenarios
- Event synchronization
- Signaling of states without data content

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | (c) 2025 Monika Wenger |

| License | EPL-2.0 |

| Version | 3.0 (2025-12-05, Monika Wenger) |

| 4diac package | iec61499::net |

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
