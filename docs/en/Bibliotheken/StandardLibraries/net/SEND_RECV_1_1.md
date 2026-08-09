# SEND_RECV_1_1

<img width="1257" height="287" alt="image" src="https://github.com/user-attachments/assets/91b59d90-84f9-436c-93b0-702ec3b5def5" />
* * * * * * * * * *
## Introduction

The SEND_RECV_1_1 function block implements a duplex communication interface for bidirectional data exchange over communication channels. The block enables both sending and receiving data over a shared channel and supports generic data types for maximum flexibility.
![SEND_RECV_1_1](SEND_RECV_1_1.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Service initialization with associated data QI and ID
- **REQ**: Send request with associated data QI and SD_1
- **RSP**: Receive request with associated data QI and SD_1

### **Event Outputs**

- **INITO**: Initialization acknowledgment with QO and STATUS
- **CNF**: Send acknowledgment with QO, STATUS, and RD_1
- **IND**: Receive indication with QO, STATUS, and RD_1

### **Data Inputs**

- **QI** (BOOL): Event input qualifier
- **ID** (WSTRING): Channel identifier
- **SD_1** (ANY): Data to be sent (generic) Data Type)

### **Data Outputs**

- **QO** (BOOL): Event Output Qualifier
- **STATUS** (WSTRING): Channel Status Information
- **RD_1** (ANY): Received Data (generic data type)

### **Adapter**

No adapter interfaces are available.

## Functionality

The function block operates as a bidirectional communication interface, initialized via the INIT event input. After successful initialization, data can be sent via REQ and received via RSP. Communication occurs via a channel identified by its ID. The generic ANY data type allows the transmission of any data structure.

## Technical Features

- Support for generic data types (ANY) for maximum flexibility
- Bidirectional communication over a shared channel
- Unicode string support for channel IDs and status messages
- Separate qualifiers for input and output events
- Status feedback via WSTRING for detailed error information

## State Overview

The function block goes through the following states:

1. **Not Initialized**: Before INIT call
2. **Initialized**: After successful INIT/INITO sequence
3. **Send Operation**: During REQ/CNF operation
4. **Receive Operation**: During RSP/IND operation

## Application Scenarios

- Client-server communication in distributed systems
- Bidirectional data transmission between control components
- Protocol implementations with request-response patterns
- Network communication in industrial automation systems

## ⚖️ Comparison with Similar Blocks

Compared to simple SEND or SEND_RECV_1_1 offers RECV blocks the combined functionality of both operations in a single block. Its duplex capability distinguishes it from simplex communication blocks and enables more efficient communication patterns.

## Conclusion

The SEND_RECV_1_1 function block provides a versatile solution for bidirectional communication requirements in distributed automation systems. By supporting generic data types and offering combined send/receive functionality, it provides an efficient foundation for various communication scenarios.