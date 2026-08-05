# ST_CREATE_CONN
![ST_CREATE_CONN](https://user-images.githubusercontent.com/116869307/214154724-8b937f3d-9158-4a65-8267-347c9eeaf763.png)

* * * * * * * * * *
## Introduction
The ST_CREATE_CONN function block is used to create event or data connections between two function block instances at runtime. This component enables the dynamic reconfiguration of connections in a 4diac system and is classified as a structural service.
![ST_CREATE_CONN](ST_CREATE_CONN.svg)

## Interface Structure

### **Event Inputs**
- **REQ**: Event requesting the creation of a connection

### **Event Outputs**
- **CNF**: Event confirming that the connection has been created

### **Data Inputs**
- **QI** (BOOL): Event input qualifier
- **SRC_FB** (WSTRING): Reference to the source FB instance
- **SRC_FB_OUT** (WSTRING): Reference to the event/data output of the source FB instance
- **DST_FB** (WSTRING): Reference to the target FB instance
- **DST_FB_IN** (WSTRING): Reference to the event/data input of the target FB instance
- **DST** (WSTRING): Destination where the connection must be created (Syntax: ResourceName)

### **Data Outputs**
- **QO** (BOOL): Event output qualifier
- **STATUS** (WSTRING): Service status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapter**
No adapter interfaces are available.

## Functionality
The function block establishes a connection between a source and a target function block instance upon request (REQ event). The connection can be used for both events and data streams. After successful processing, an acknowledgment (CNF event) is issued with the corresponding status.

## Technical Features
- Supports dynamic reconfiguration at runtime
- Uses wide-string data types for all references
- Provides detailed status feedback
- Implemented as a structured service according to IEC 61499-1

## State Overview
The function block supports several service sequences:

- Normal connection creation
- Failed connection creation
- Request acknowledgment cycle
- Request prevention
- Error handling
- Application- and resource-initiated termination

## Application Scenarios
- Dynamic system reconfiguration
- Runtime adaptation of control logic
- Flexible connection management in distributed systems
- Adaptive automation systems

## ⚖️ Comparison with Similar Function Blocks
Unlike statically configured connections, ST_CREATE_CONN enables the dynamic creation of connections at runtime. Other reconfiguration function blocks typically focus on creating or deleting FB instances, while this function block is specifically optimized for connection management.

## Conclusion

ST_CREATE_CONN is an essential building block for systems requiring dynamic reconfiguration. Its ability to create connections between function blocks at runtime makes it particularly valuable for adaptive and flexible automation solutions.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
