# AlPgnRxNew8B_REQ
<img width="1324" height="281" alt="image" src="https://github.com/user-attachments/assets/692b1960-1bad-4a6d-89ca-c6daba8a85cd" />
* * * * * * * * * *
## Introduction
The function block `AlPgnRxNew8B_REQ` is used to request data via an ISOBUS network. It enables the installation of a receive parameter set (RX PGN) and the triggering of a one-time request for this parameter. The block is part of an ISOBUS-specific communication library and handles the interaction with the CAN network protocol according to ISO 11783.
![AlPgnRxNew8B_REQ](AlPgnRxNew8B_REQ.svg)
## Interface Structure

### **Event Inputs**
* **INIT**: Initializes the function block.
* **install**: Installs a receive parameter set (RX PGN) for subsequent data requests. Triggered with the data `u32Pgn`, `NmSource`, `u16DaSize`, and `u8Priority`.
* **REQ**: Triggers a one-time request for the previously installed RX PGN.

### **Event Outputs**
* **INITO**: Confirms successful initialization.
* **installO**: Confirms successful installation of a PGN. Returns the assigned `PGN_handle`.
* **CNF**: Confirms successful transmission of the request to the network.
* **IND**: Triggered when the requested data message is received. Returns `Data` and `s32TimeStamp`.
* **dataERR**: Signals a data processing error. Returns the error code `dataERRC`.
* **pgnERR**: Signals an error in PGN processing (e.g., during installation). Returns the error code `pgnERRC`.

### **Data Inputs**
* **u32Pgn** (UDINT): The parameter Group Number (PGN) in the range 0 to 0x3FFFF.
* **NmSource** (isobus::pgn::ISONETEVENT_T): Defines the communication partner in the network.
* **u16DaSize** (UINT): The expected data length of the PGN (0-8 bytes).
* **u8Priority** (USINT): The default priority of this PGN (0..7, where 0 is the highest priority). Initial value is 7.

### **Data Outputs**
* **PGN_handle** (INT): A handle to identify the successfully installed PGN. In case of an error, an invalid handle value (`HANDLE_UNVALID`) is returned.
* **dataERRC** (INT): Error code set when the `dataERR` event is triggered.
* **pgnERRC** (INT): Error code set when the `pgnERR` event is triggered.
* **s32TimeStamp** (DINT): Timestamp of the received message in milliseconds. Initial value is -1.
* **Data** (isobus::pgn::CAN_MSG): The buffer containing the received CAN message data.

### **Adapter**
This function block does not use any adapter interfaces.

## Operation
The function block operates in two main phases: installation and request.

1. **Installation**: The `install` event configures the parameters for a PGN to be received (number, source, size, priority). The block registers this request in the underlying ISOBUS stack and returns a `PGN_handle` via `installO`. This handle is needed for later references.

2. **Request**: The `REQ` event triggers a one-time request for the most recently installed PGN on the network. After successful transmission of the request, `CNF` is triggered. When the requested message arrives from the defined `NmSource`, it is stored in the `Data` buffer and output along with a timestamp via the `IND` event.

Errors during installation (e.g., invalid PGN) result in the `pgnERR` output. Errors during data reception or processing result in the `dataERR` output.

## Technical Specifications
* This block is designed to process PGNs with a data length of up to 8 bytes (`u16DaSize` 0..8).
* Priority management (`u8Priority`) follows the ISOBUS standard.
* Data is provided in a type-safe buffer (`CAN_MSG`).
* Error handling is structured via dedicated event outputs (`pgnERR`, `dataERR`).

## Status Overview

1. **Not Initialized**: Before the first `INIT` event.

2. **Initialized / Ready**: After `INITO`. The block can receive `install` events.

3. **PGN Installed**: After successful `installO`. The block is ready to process `REQ` events.

4. **Request Pending**: After `REQ` and before `CNF`. The network request has been sent.

5. **Ready to Receive Data**: After `CNF`. The block is waiting for the incoming message and will trigger `IND` upon receipt.

## Application Scenarios
Typical applications are in agricultural or mobile machinery control (ISO 11783 / ISOBUS):

* Querying machine parameters (e.g., speed, temperature) from an implement.
* Requesting configuration data once from a control unit on the network.
* Implementing diagnostic or service tools that need to query specific PGNs.

## ⚖️ Comparison with Similar Blocks

Compared to generic CAN receive blocks, `AlPgnRxNew8B_REQ` is specifically tailored to the ISOBUS protocol and its PGN concept. It abstracts the low-level CAN details (such as ID filtering) and provides a clean interface at the PGN level. Blocks like `E_CYCLE` or `E_DELAY` could be used to implement periodic requests, while `AlPgnRxNew8B_REQ` itself only handles single requests.

```
## 🛠️ Related Exercises

* [Exercise_132](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_132.md)

## Conclusion
The `AlPgnRxNew8B_REQ` is a specialized function block for on-demand communication in ISOBUS networks. By separating installation (`install`) and execution (`REQ`), it enables flexible and controlled data requests. Its integrated error handling and type-safe data interface make it a robust component for demanding embedded controllers in agricultural technology.
