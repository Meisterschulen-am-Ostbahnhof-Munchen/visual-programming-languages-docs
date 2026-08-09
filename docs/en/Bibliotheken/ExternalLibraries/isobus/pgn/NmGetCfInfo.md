# NmGetCfInfo

<img width="1465" height="241" alt="image" src="https://github.com/user-attachments/assets/3ea313ab-46a3-4f18-9a72-53f679663551" />
* * * * * * * * * *
## Introduction

The function block `NmGetCfInfo` is used within an ISOBUS network to retrieve information about connected communication partners (Connected CFs). It allows both internal and external participants in the network to be identified and their details to be recorded. This block is part of ISOBUS PGN communication and is typically used for network management tasks.
![NmGetCfInfo](NmGetCfInfo.svg)
## Interface Structure

### **Event Inputs**

* **INIT (Type: EInit)**: Initializes the service. When triggered, the configured data inputs are accepted and the initialization process is started.
* **RSP (Type: Event)**: Acknowledges receipt of an indication (`IND`). This event signals to the module that a previously sent indication has been processed.

### **Event Outputs**

* **INITO (Type: EInit)**: Confirms successful completion of initialization.
* **IND (Type: Event)**: Triggered to forward a received network indication (e.g., detected communication partners) to the application.

### **Data Inputs**

* **u8CanIdx (Type: USINT, Initial Value: ISO_CAN_NODE::INVALID)**: Identifies the CAN node used (CAN controller index).
* **member (Type: SINT, Initial Value: ISOUSERHOME_e::notdef)**: Defines the membership or role of the requesting participant in the network.
* **address (Type: isobus::pgn::NAMEFIELD_T)**: The address of the other network participant for whom information is to be retrieved.
* **mask (Type: isobus::pgn::NAMEFIELD_T)**: A bitmask that specifies which parts of the address should be considered during the search. Only set bits (1) are evaluated.

### **Data Outputs**

* **bwaitingForRSP (Type: BOOL)**: Indicates whether the function block is currently waiting for a response (`RSP`) to a sent indication.
* **sNetEv (Type: isobus::pgn::ISONETEVENT_T)**: Contains details of the network event that occurred (e.g., error or status).
* **sCfInfo (Type: isobus::pgn::CF_INFO_T)**: The retrieved information about the found communication partner (CF = Communication Function).
* **sNameField (Type: isobus::pgn::NAMEFIELD_T)**: The ISOBUS name of the detected communication partner.

### **Adapter**

This function block does not use any adapter interfaces.

## Functionality

1. **Initialization**: The block is configured by triggering the `INIT` event. The passed parameters (`u8CanIdx`, `member`, `address`, `mask`) define the context and target of the query. After successful initialization, `INITO` is output.
2. **Query and Indication**: After initialization, the module begins searching for suitable communication partners in the network based on the `address` and `mask` events. If a participant is found, the module triggers the `IND` event and makes the found information available in the data outputs `sCfInfo` and `sNameField`. Simultaneously, `bwaitingForRSP` is set to `TRUE`.
3. **Response Processing**: The higher-level application acknowledges receipt of the indication by sending the `RSP` event. The function block then reverts from `bwaitingForRSP` to `FALSE`. This handshake mechanism ensures secure transmission.

## Technical Features

* The function block implements a request-response protocol (`IND`/`RSP`) for reliable communication.
* The use of a bit-based `mask` enables flexible search queries, e.g., for participants of a specific device class.
* The data types (`ISONETEVENT_T`, `CF_INFO_T`, `NAMEFIELD_T`) are specific to ISOBUS PGN communication and contain structured information according to the ISO 11783 standard.
*
## Status Overview

1. **Inactive**: Before initialization.
2. **Initialized**: After `INITO`. The function block is ready for operation and can process requests.
3. **Waiting for RSP**: After `IND` is triggered. The function block waits for confirmation (`RSP`) from the application before performing further actions.

## Application Scenarios

* **Network Discovery**: When a device starts up, to identify all active participants in the ISOBUS network.
* **Diagnostics and Monitoring**: To monitor whether specific expected control units (e.g., of an implement) are connected and reachable.
* **Dynamic Configuration**: To obtain information about newly added devices and adapt the application accordingly.

## ⚖️ Comparison with Similar Modules

Unlike simple read or query modules, `NmGetCfInfo` is specifically designed for querying ISOBUS-specific network information. It offers more context (through `member`, `address`, `mask`) and structured result data (`CF_INFO_T`) than a generic communication module. Modules like `E_SWITCH` or `E_DEMUX` only forward events, while `NmGetCfInfo` performs active network communication and protocol handling.

Modules like `E_SWITCH` or `E_DEMUX` only forward events, while `NmGetCfInfo` performs active network communication and protocol execution.
## 🛠️ Related exercises

* [Uebung_120](../../../../Uebungen/test_B/Uebungen_doc/Uebung_120.md)
* [Uebung_121](../../../../Uebungen/test_B/Uebungen_doc/Uebung_121.md)
* [Uebung_122](../../../../Uebungen/test_B/Uebungen_doc/Uebung_122.md)
* [Uebung_122b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_122b.md)
* [Uebung_123](../../../../Uebungen/test_B/Uebungen_doc/Uebung_123.md)
* [Uebung_124](../../../../Uebungen/test_B/Uebungen_doc/Uebung_124.md)
* [Uebung_125](../../../../Uebungen/test_B/Uebungen_doc/Uebung_125.md)
* [Uebung_126](../../../../Uebungen/test_B/Uebungen_doc/Uebung_126.md)
* [Uebung_126b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b.md)
* [Uebung_126b2](../../../../Uebungen/test_B/Uebungen_doc/Uebung_126b2.md)
* [Uebung_127](../../../../Uebungen/test_B/Uebungen_doc/Uebung_127.md)
* [Uebung_128](../../../../Uebungen/test_B/Uebungen_doc/Uebung_128.md)
* [Uebung_128b](../../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)
* [Uebung_130](../../../../Uebungen/test_B/Uebungen_doc/Uebung_130.md)
* [Uebung_131](../../../../Uebungen/test_B/Uebungen_doc/Uebung_131.md)
* [Uebung_132](../../../../Uebungen/test_B/Uebungen_doc/Uebung_132.md)
* [Uebung_133](../../../../Uebungen/test_B/Uebungen_doc/Uebung_133.md)
* [Uebung_134](../../../../Uebungen/test_B/Uebungen_doc/Uebung_134.md)

## Conclusion

The `NmGetCfInfo` function block is a An essential tool for managing ISOBUS networks, it abstracts the complex protocol communication required to detect network participants into an easy-to-use, event-driven interface. Its ability to search for participants and return detailed information makes it valuable for robust and intelligent agricultural control systems.
