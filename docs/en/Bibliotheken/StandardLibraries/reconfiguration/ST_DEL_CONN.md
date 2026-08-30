# ST_DEL_CONN

![ST_DEL_CONN](https://user-images.githubusercontent.com/116869307/214154770-816b11aa-c17e-4fad-93d5-e43f10015347.png)

* * * * * * * * * *
## Introduction

The ST_DEL_CONN function block is used to delete event or data connections between two function block instances within a 4diac system. It enables the dynamic reconfiguration of connections at runtime and belongs to the category of structural services according to IEC 61499-1.
![ST_DEL_CONN](ST_DEL_CONN.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Event to request the deletion of a connection

### **Event Outputs**

- **CNF**: Event confirming that the connection has been deleted

### **Data Inputs**

- **QI** (BOOL): Event input qualifier
- **SRC_FB** (WSTRING): Reference to the source FB instance
- **SRC_FB_OUT** (WSTRING): Reference to the event/data output of the source FB instance
- **DST_FB** (WSTRING): Reference to the target FB instance
- **DST_FB_IN** (WSTRING): Reference to the event/data input of the target FB instance
- **DST** (WSTRING): Destination where the connection must be deleted (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (WSTRING): Service Status: RDY, NO_SUCH_OBJECT

### **Adapters**

No adapter interfaces are available.

## Functionality

When the REQ event is triggered, the specified connection between the indicated function block instances is deleted. The block expects complete references for both the source and target function block instances, including their inputs and outputs. After successful processing, the CNF event is output with the corresponding status.

## Technical Features

- Supports the deletion of both event and data connections
- Works with wide-string data types for all reference parameters
- Provides status feedback on successful or failed operations
- Implemented according to the IEC 61499-1 standard for structured services

## State Overview

The function block supports various service sequences:

- Normal initialization (INIT+ → INITO+)
- Failed initialization (INIT+ → INITO-)
- Successful request (REQ+ → CNF+)
- Suppressed request (REQ- → CNF-)
- Failed request (REQ+ → CNF-)
- Application- and resource-side termination

## Application Scenarios

- Dynamic reconfiguration of control systems
- Removal of connections at runtime
- Error handling for connection problems
- Adaptive systems that need to adjust to changing requirements

## ⚖️ Comparison with Similar Blocks

Specialized compared to other reconfiguration blocks ST_DEL_CONN focuses exclusively on deleting connections, while other function blocks may support creating or modifying connections.

## Conclusion

ST_DEL_CONN is an essential function block for systems requiring dynamic reconfiguration. Its clear interface definition and reliable status feedback make it a dependable tool for managing connections in IEC 61499-based control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
