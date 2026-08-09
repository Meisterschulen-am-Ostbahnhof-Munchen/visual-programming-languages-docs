# CAN_MSG

* * * * * * * * * *
## Introduction

The data type `CAN_MSG` is a structured type definition (struct) for representing a classic CAN message frame (without a transport protocol, TP). It serves as a container for the essential attributes of a CAN message, including priority, payload length, and the actual data buffer. This type is intended for use in function blocks that implement CAN communication in an IEC 61499 system.
## Interface Structure

Since `CAN_MSG` is a data type and not a function block, there are no event or adapter interfaces. The structure is defined exclusively by its data members.
### **Data Inputs**

*(Not applicable – Data Type)*

### **Data Outputs**

*(Not applicable – Data Type)*

### **Event Inputs**

*(Not applicable – Data Type)*

### **Event Outputs**

*(Not applicable – Data Type)*

### **Adapters**

*(Not applicable – Data Type)*

## Functionality

The `CAN_MSG` type is a passive data structure. It encapsulates the information relevant for a CAN message:

1. **Priority (`u8Priority`)**: Defines the arbitration priority on the CAN bus. A lower numerical value corresponds to a higher priority.
2. **Data Length (`u16DaSize`)**: Specifies the actual number of bytes used in the data buffer (0 to 8). 3. **Data Buffer (`data`)**: An 8-byte array that stores the message payload. Unused bytes are initialized with a default value.

This structure can be used as an input or output data type for function blocks that send, receive, process, or log CAN messages.

## Technical Features

* **Fixed Buffer Size**: The data array is statically dimensioned to a length of 8 bytes, which corresponds to the maximum payload length of a standard CAN frame.
* **Initialization**: By default, the data array is pre-populated with the hexadecimal value `16#FF` (decimal 255) in all 8 positions. The data length `u16DaSize` defaults to `0`, and the priority `u8Priority` defaults to `7` (lowest priority).
* **Type Safety**: Using a structured type instead of individual variables improves maintainability and clarity in the function block connection view.

## State Overview

*(Not applicable – the data type has no behavior or state machine.)*

## Application Scenarios

The `CAN_MSG` type is fundamental for:

* **CAN Sender FBs**: An FB that receives a `CAN_MSG` type as an input and sends its contents as a physical CAN frame to the bus.
* **CAN Receiver FBs**: An FB that packs received CAN frames into a variable of type `CAN_MSG` and forwards them to downstream logic.
* **Message Construction**: FBs that construct a valid `CAN_MSG` structure for later transmission from individual values (e.g., from sensor FBs).
* **Message Filtering/Processing**: FBs that analyze and process incoming `CAN_MSG` structures based on priority, data content, or length.

## ⚖️ Comparison with similar building blocks

As a data type, `CAN_MSG` is comparable to other structured types in 4diac that represent communication protocols (e.g., `UDP_PACKET`, `MODBUS_MSG`). Its specific characteristic is its close mapping to the hardware properties of the CAN bus protocol (priority, 8-byte limit). Unlike a TP-based message type (e.g., for ISO 11783 or CANopen), it lacks fields for packetization, sequence numbers, or specific protocol headers.

## Conclusion

The `CAN_MSG` data type provides an essential and well-structured foundation for implementing CAN bus communication in 4diac-based control systems. By consolidating priority, length, and data into a single type, the handling of CAN messages in function block networks is significantly simplified and standardized. Its use is recommended for all applications requiring direct access to CAN frames.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
