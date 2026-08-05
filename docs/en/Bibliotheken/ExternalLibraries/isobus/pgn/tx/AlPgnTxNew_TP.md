# AlPgnTxNew_TP

* * * * * * * * * *

## Introduction
The function block **AlPgnTxNew_TP** is used to transmit data over the ISOBUS/CAN bus based on Parameter Group Numbers (PGN). It enables the registration of a specific PGN and the subsequent transmission of data packets whenever a local request event (REQ) occurs. The block is part of the `isobus::pgn::tx` package and is specifically designed for handling transport protocols or generic PGN transmissions.

![AlPgnTxNew_TP](AlPgnTxNew_TP.svg)

## Interface Structure

### **Event Inputs**

* **INIT** (Type: `EInit`): Initializes the service. Sets the block to its initial state.

* **install** (Type: `Event`): Installs or registers a transmit PGN. Parameters such as PGN number, destination, data size, and priority are adopted.

* **REQ** (Type: `Event`): Requests data transmission (unacknowledged transmission). Uses the buffer provided in input `Data`.

### **Event Outputs**

* **INITO** (Type: `EInit`): Acknowledges initialization.

* **installO** (Type: `Event`): Acknowledges that the installation process has completed. Returns `PGN_handle`.

* **CNF** (Type: `Event`): Confirmation that the data was sent successfully.

* **dataERR** (Type: `Event`): Signals an error during data transmission or access to the data.

* **pgnERR** (Type: `Event`): Signals an error regarding the PGN configuration or registration.

### **Data Inputs**

* **u32Pgn** (Type: `UDINT`): The parameter group number (PGN) to be sent. The range is between 0 and 0x3FFFF.

* **NmDestin** (Type: `isobus::pgn::ISONETEVENT_T`): Defines the communication partner or the destination in the network (Network Management Destination).

* **u16DaSize** (Type: `UINT`): The length of the data for this PGN in bytes (typically 0 to 8 for standard CAN, but can vary depending on the protocol).

* **u8Priority** (Type: `USINT`): The default priority of this PGN (0 to 7), where 0 is the highest priority. The default value is 7.

### **Data Outputs**

* **PGN_handle** (Type: `INT`): Return value after installation. A valid handle on success, or `HANDLE_UNVALID` in case of failure.

* **dataERRC** (Type: `INT`): Error code output when the event `dataERR` is triggered. * **pgnERRC** (Type: `INT`): Error code output when the event `pgnERR` is triggered.

### **InOut Variables**

* **Data** (Type: `BYTE`, ArraySize: `*`): A pointer to the data buffer (variable-size byte array). The payload data to be sent is stored here. Declaring it as `InOut` enables efficient memory management without unnecessary copy operations.

### **Adapters**

* This function block does not use any explicit adapter interfaces.


### ## Functionality

The module operates in two main phases:

1. **Configuration (Installation):**

* First, the module must be initialized via `INIT`.

* Then, the PGN is configured via the event `install`. This process defines the PGN ID (`u32Pgn`), the target (`NmDestin`), the size (`u16DaSize`), and the priority (`u8Priority`).

* After successful installation, the event `installO` is triggered, and a `PGN_handle` handle is provided. This handle represents the registered PGN in the system.


2. **Data Transfer:**

* Data must be provided in the `Data` array before it can be sent.

* The `REQ` event triggers the sending process.

* `CNF` is triggered upon successful transmission.

* If problems occur (e.g., invalid data length or bus error), `dataERR` is triggered with the corresponding error code `dataERRC`.

## Technical Specifications
* **Variable Array Size:** The `Data` input is defined as the `InOut` variable with `ArraySize="*"`. This means that the function block can work with data buffers of varying sizes, making it flexible for different PGN types.

* **Error Separation:** The function block explicitly distinguishes between errors during PGN setup (`pgnERR`) and errors during runtime data transmission (`dataERR`). This significantly simplifies debugging.

* **ISOBUS Types:** The function block imports specific ISOBUS data types (`isobus::pgn::ISONETEVENT_T`), which requires tight integration into corresponding ISOBUS stacks.

## State Overview
The function block has internally implicit states defined by the availability of a valid `PGN_handle`:

* **Not Initialized:** Before `INIT`.

* **Initialized, Not Installed:** After `INIT`, but before successful `install`. Send requests (`REQ`) would fail here.

* **Installed / Ready for Operation:** A valid handle has been created. Data can be sent via `REQ`.

## Application Scenarios

* **ISOBUS Device Development:** Implementation of virtual terminals or task controllers that need to send specific PGNs.

* **Sensor Data Transmission:** A sensor module sends measured values to the CAN bus cyclically or based on events.

* **Control Commands:** Sending control messages to actuators in the network (e.g., valves or motors) with a defined priority.


## ⚖️ Comparison with Similar Function Blocks

* **AlPgnTx vs. AlPgnTxNew_TP:** While older or simpler versions may only support static PGNs, the "New_TP" suffix indicates a revised version that may offer better support for transport protocols (TP) or utilize more modern memory management (via `InOut` variables).

* **Standard CAN_WRITE:** Compared to a generic `CAN_WRITE` function block, `AlPgnTxNew_TP` abstracts the complexity of PGN management (priority, data length, handle management) and is more specifically tailored to the J1939/ISOBUS protocol.


* **Standard CAN_WRITE:** Compared to a generic `CAN_WRITE` function block, `AlPgnTxNew_TP` abstracts the complexity of PGN management (priority, data length, handle management) and is more specifically tailored to the J1939/ISOBUS protocol.

* ## 🛠️ Related Exercises

* [Exercise_128b](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_128b.md)]

## Conclusion
The **AlPgnTxNew_TP** is a specialized and robust function block for sending messages in ISOBUS networks. By separating configuration (`install`) and transmission (`REQ`) and utilizing reference data buffers (`InOut`), it is ideally suited for resource-efficient control applications that require precise control over PGN parameters.