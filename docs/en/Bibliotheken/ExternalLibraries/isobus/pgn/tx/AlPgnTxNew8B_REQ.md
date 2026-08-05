# AlPgnTxNew8B_REQ

<img width="1308" height="254" alt="image" src="https://github.com/user-attachments/assets/09f85519-8068-47fc-af54-0c2422fe947f" />

* * * * * * * * * *
## Introduction
The function block `AlPgnTxNew8B_REQ` is used to configure and control the transmission of parameter group numbers (PGNs) in an ISOBUS network (J1939). Its main purpose is to install a new transmit PGN (TX-PGN) in the network. The block responds to a REQ event (J1939 network event) and provides a callback interface for asynchronous feedback on the data transmission status. It is part of a specialized library for ISOBUS communication.

![AlPgnTxNew8B_REQ](AlPgnTxNew8B_REQ.svg)

## Interface Structure

### **Event Inputs**

* **INIT**: Initializes the function block. Must be triggered before first use.

* **install**: Triggers the installation of a new Transmit PGN (TX). The installation is configured with the data parameters bound to this event (`u32Pgn`, `NmDestin`, `u16DaSize`, `u8Priority`).

### **Event Outputs**

* **INITO**: Confirms successful initialization of the function block.

* **installO**: Signals completion of the installation request. Returns the assigned `PGN_handle` or, in case of an error, an invalid handle.

* **CNF**: Confirms that data was successfully sent. Typically triggered via the callback adapter.

* **dataERR**: Indicates an error related to the data being sent. Returns an error code via `dataERRC`.

* **pgnERR**: Indicates an error related to PGN configuration or management. Returns an error code via `pgnERRC`.

### **Data Inputs**

* **u32Pgn** (UDINT): The parameter group number (PGN) to be installed. Valid range: 0 to 0x3FFFF (decimal 262143).

* **NmDestin** (isobus::pgn::ISONETEVENT_T): Defines the communication partner (destination address) for the PGN. The exact type is defined by the ISOBUS library.

* **u16DaSize** (UINT): The length of the payload for this PGN in bytes. Valid range: 0 to 8.

* **u8Priority** (USINT): The default priority for this PGN. Valid range: 0 (highest) to 7 (lowest). Initial value: 7.

### **Data Outputs**

* **PGN_handle** (INT): A handle (identifier) for the installed PGN. If the installation is successful, it contains a valid, positive value. In case of an error, an invalid handle (e.g., `HANDLE_UNVALID`) is output.

* **dataERRC** (INT): The specific error code when a `dataERR` event occurs.

* **pgnERRC** (INT): The specific error code when a `pgnERR` event occurs.


### **Adapter**

* **CB** (Type: `isobus::pgn::tx::Callback`): A socket adapter that provides a callback interface. Asynchronous feedback (such as the `CNF` event) is reported from the underlying ISOBUS driver system to the function block via this adapter. The function block must be connected to a corresponding plug adapter to receive the feedback.

## Operation

1. **Initialization**: First, the `INIT` event must be triggered to make the function block operational. This results in the output of `INITO`.

2. **PGN Installation**: The `install` event starts the configuration process. The function block passes the parameters `u32Pgn`, `NmDestin`, `u16DaSize`, and `u8Priority` to the ISOBUS protocol stack to register a new transmit PGN.

3. **Feedback**: After processing the installation request, the function block responds with the `installO` event and returns `PGN_handle`. This handle must be used for subsequent transmit operations (e.g., with a separate transmit function block).

4. **Asynchronous Operational Feedback**: During operation, when data is sent for the configured PGN, the acknowledgment (`CNF`) or error message (`dataERR`, `pgnERR`) is sent asynchronously via the respective event outputs. The triggering of the `CNF` event is typically controlled by the callback adapter (`CB`).

## Technical Features
* This module is specific to ISOBUS/J1939 networks and uses type-safe data structures (`isobus::pgn::ISONETEVENT_T`).


* Error handling is divided into `dataERR` (data error) and `pgnERR` (PGN configuration error), enabling precise error diagnosis.

* Communication with the actual network stack occurs via a callback interface (`CB` adapter), which allows for loose coupling and asynchronous notification.

* `PGN_handle` serves as an abstract reference to the internally managed PGN instance.

## State Overview
The component implicitly passes through the following main states:

1. **Not Initialized**: Before the first `INIT` event.

2. **Ready**: After successful initialization (`INITO` received). The function block can now receive `install` requests.

3. **Installation in progress**: After triggering `install`, the function block waits for a response from the protocol stack.

4. **Operational**: After successful `installO`, the PGN is registered in the stack and can be used for transmission. Asynchronous events (`CNF`, `dataERR`, `pgnERR`) can now occur.

## Application Scenarios

* **Agricultural Machinery Control**: Integrating a new control unit into an ISOBUS network that needs to regularly send operating data (e.g., engine speed, temperature).


* **Implements**: Dynamic configuration of communication between a tractor and a specific implement that requires an individual PGN for its data.

* **Diagnostic Tools**: A diagnostic tool that temporarily installs a PGN on the network to request specific data or send commands.

## ⚖️ Comparison with Similar Blocks

* **`E_SEND` / `E_RCV` (Standard 61499)**: These generic communication blocks are protocol-independent. In contrast, `AlPgnTxNew8B_REQ` is specialized for ISOBUS/J1939 and handles the protocol-specific configuration (PGN, priority, destination address) that would have to be manually defined in the data parameters of the standard blocks.

* **Simple TX Blocks**: Other ISOBUS transmit blocks often expect a pre-configured `PGN_handle`. `AlPgnTxNew8B_REQ` is the upstream component that provides precisely this handle by installing a new PGN.

## 🛠️ Related Exercises

* [Exercise_125](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_125.md)]

## Conclusion
The `AlPgnTxNew8B_REQ` is an essential configuration component for ISOBUS communication in 4diac. It abstracts the complex setup of a transmitting PGN in a J1939 network behind a clear, event-driven interface. It separates installation (`install`/`installO`) from operation (`CNF`/`*ERR`).The use of a callback adapter makes it robust and easily integrated into larger control applications for mobile machine communication.


These features, along with the ability to use a callback adapter, make it robust and well-suited for integration into larger control applications for mobile machine communication.---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]