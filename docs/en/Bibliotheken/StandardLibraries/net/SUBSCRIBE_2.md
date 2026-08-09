# SUBSCRIBE_2

<img width="1291" height="336" alt="image" src="https://github.com/user-attachments/assets/55eb6a91-e2ee-4848-813e-eb2568e1ed1c" />
* * * * * * * * * *
## Introduction

The SUBSCRIBE_2 function block acts as a subscriber for a PUBLISH_2 block and enables the receipt of data via a publish-subscribe communication pattern. The block can receive and process two different data values from a publisher.
![SUBSCRIBE_2](SUBSCRIBE_2.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initialization event with the associated data QI and ID
- **RSP**: Response event with the associated data value QI

### **Event Outputs**

- **INITO**: Initialization confirmation with the data QO and STATUS
- **IND**: Indication event when new data is available with QO, STATUS, RD_1, and RD_2

### **Data Inputs**

- **QI** (BOOL): Qualifier Input - Controls block activation
- **ID** (WSTRING): Identification string for assignment to the corresponding publisher

### **Data Outputs**

- **QO** (BOOL): Qualifier Output - Block operation status
- **STATUS** (WSTRING): Status information as a Unicode string
- **RD_1** (ANY): Received Data 1 (any data type)
- **RD_2** (ANY): Received Data 2 (any data type)

### **Adapter**

No adapter interfaces are available.

## Functionality

The SUBSCRIBE_2 block initializes itself via the INIT event and subscribes to a specific publisher using the ID identifier. After successful initialization, the block confirms this via INITO. When data is received from the publisher, the block triggers the IND event and makes the received data available via RD_1 and RD_2.

## Technical Features

- Supports receiving two different data values simultaneously
- Uses WSTRING for status and identification information
- Implements generic data types (ANY) for maximum flexibility
- Based on the GEN_SUBSCRIBE generic template

## State Overview

The block goes through the following main states:

1. **Not Initialized**: Block waits for the INIT event
2. **Initialized**: Block is ready to receive data
3. **Data Receipt**: Processing incoming data and triggering IND

## Application Scenarios

- Distributed control systems with data distribution
- IoT applications with publisher-subscriber architecture
- Industrial automation with decentralized data communication
- Systems with flexible data type requirements

## ⚖️ Comparison with Similar Blocks

Compared to simpler SUBSCRIBE blocks, SUBSCRIBE_2 offers the ability to receive two different data values in parallel. The use of ANY data types allows for greater flexibility compared to type-specific implementations.

## Conclusion

The SUBSCRIBE_2 block represents an enhanced solution for publish-subscribe communication in 4diac systems, offering exceptional flexibility through its support for two data channels and generic data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]