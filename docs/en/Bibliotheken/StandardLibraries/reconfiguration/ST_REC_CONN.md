# ST_REC_CONN

![ST_REC_CONN](https://user-images.githubusercontent.com/116869307/214155169-b982c961-19de-4e7e-876a-55ba47f27411.png)

* * * * * * * * * *
## Introduction

The ST_REC_CONN function block is used for the dynamic reconfiguration of connections between function blocks in 4diac systems. It enables the redirection of event or data connections from existing source and target function blocks to new instances during runtime.

![ST_REC_CONN](ST_REC_CONN.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Starts the reconfiguration process for a connection

### **Event Outputs**

- **CNF**: Confirms whether the connection reconfiguration was successful or failed

### **Data Inputs**

- **QI** (BOOL): Qualifies the event input
- **OLD_SRC_FB** (WSTRING): Reference to the old source FB instance
- **OLD_SRC_FB_OUT** (WSTRING): Reference to the old source FB output (event/data)
- **OLD_DST_FB** (WSTRING): Reference to the old target FB instance
- **OLD_DST_FB_IN** (WSTRING): Reference to the old target FB input (event/data)
- **NEW_SRC_FB** (WSTRING): Reference to the new Source FB Instance
- **NEW_SRC_FB_OUT** (WSTRING): Reference to the new source FB output (event/data)
- **NEW_DST_FB** (WSTRING): Reference to the new target FB instance
- **NEW_DST_FB_IN** (WSTRING): Reference to the new target FB input (event/data)
- **DST** (WSTRING): Destination for reconfiguration (Syntax: ResourceName)

### **Data Outputs**

- **QO** (BOOL): Qualifies the event output
- **STATUS** (WSTRING): Service status (RDY, NO_SUCH_OBJECT, INVALID_STATE)

### **Adapters**

No adapter interfaces are available.

## Functionality

Upon arrival of the REQ event, the function block analyzes the passed parameters and performs the following steps:

1. Identifies the existing connection between OLD_SRC_FB and OLD_DST_FB
2. Disconnects the existing connection
3. Establishes a new connection between NEW_SRC_FB and NEW_DST_FB
4. Provides feedback on the operation status via the CNF event

The QI input controls the execution: If FALSE, the operation is not performed.

## Technical Features

- Supports both event and data connections
- Uses WSTRING data types for all reference parameters
- Works with resource-specific target specifications
- Provides detailed status feedback
- Implemented according to the IEC 61499-1 standard for reconfiguration

## State Overview

The function block operates according to a simple request-acknowledgment principle:

- Waiting state: No active operation
- Execution state: Processing the REQ request
- Completion state: Sending the CNF acknowledgment

## Application Scenarios

- Dynamic system reconfiguration during operation
- Hot-swapping of function blocks
- Load balancing through connection redirection
- Fault-tolerant systems with redundant components
- Adaptive control systems with changing operating modes

## ⚖️ Comparison with similar blocks

Unlike static connections in 4diac, ST_REC_CONN enables:

- Dynamic adjustment of connections at runtime
- Greater flexibility in Adaptive Systems
- More complex reconfiguration scenarios compared to simple connection blocks

## Conclusion

ST_REC_CONN is an essential component for flexible and adaptive automation systems that require dynamic reconfiguration during operation. Its comprehensive parameterization enables precise control of connection changes, while status feedback ensures reliable monitoring of the reconfiguration processes.

--

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
