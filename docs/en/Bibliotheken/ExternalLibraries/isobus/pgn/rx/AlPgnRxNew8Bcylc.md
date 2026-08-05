# AlPgnRxNew8Bcylc

<img width="1277" height="291" alt="image" src="https://github.com/user-attachments/assets/5d409e8c-eb17-45a5-a2af-fcaedc21d048" />

* * * * * * * * * *
## Introduction
The function block `AlPgnRxNew8Bcylc` is used for the cyclical reception of data via an ISOBUS network according to the Parameter Group Number (PGN) protocol. It enables the configuration and monitoring of receive channels for specific PGNs, including the handling of timeouts and error conditions. The block is designed for use in control systems that require reliable and monitored communication with other ISOBUS devices.

![AlPgnRxNew8Bcylc](AlPgnRxNew8Bcylc.svg)

## Interface Structure

### **Event Inputs**

* **INIT**: Initializes the function block.

* **install**: Installs a new receive channel for a specific PGN. Triggers the configuration with the associated data inputs.


### **Event Outputs**

* **INITO**: Confirms successful initialization.

* **installO**: Signals completion of an installation request. Returns the assigned `PGN_handle`.

* **IND**: Triggered when new data is received for the configured PGN.

* **TIMEOUT**: Signals that a timeout has occurred for the configured PGN.

* **dataERR**: Indicates an error in the received data.

* **pgnERR**: Indicates an error related to the PGN configuration or processing.

### **Data Inputs**

* **u32Pgn** (UDINT): The parameter group number (PGN) to be received. Valid range: 0 to 0x3FFFF.

* **NmSource** (isobus::pgn::ISONETEVENT_T): Defines the communication partner (network management source).

* **u16DaSize** (UINT): The expected data size of the PGN in bytes (0..8).

* **u8Priority** (USINT): The default priority of this PGN (0..7, where 0 is the highest priority). Initial value: 7.

* **u16CtrlTime** (UINT): The control time (timeout time) for receiving this PGN in milliseconds (0 ... 0xFDFF ms). A value of 0 disables timeout monitoring.

### **Data Outputs**

* **PGN_handle** (INT): A handle that identifies the successfully installed receive channel. In case of an error, `HANDLE_UNVALID` is output.

* **dataERRC** (INT): Error code set when the `dataERR` event is triggered.

* **pgnERRC** (INT): Error code set when the `pgnERR` event is triggered.

* **bTimeout** (BOOL): Indicates whether a timeout occurred (`TRUE` = timeout, `FALSE` = no timeout). Initial value: `FALSE`.

* **s32TimeStamp_timeout** (DINT): Timestamp of the timeout in milliseconds.

* **s32TimeStamp** (DINT): Timestamp of the last received message in milliseconds. Initial value: -1.

* **Data** (isobus::pgn::CAN_MSG): Buffer containing the received user data.

### **Adapters**
This function block does not use adapters.

## Operation

1. **Initialization**: The `INIT` event makes the function block operational. Confirmation is provided by `INITO`.

2. **Channel Configuration**: A receive channel is configured by the `install` event. The associated parameters (`u32Pgn`, `NmSource`, `u16DaSize`, `u8Priority`, `u16CtrlTime`) define the desired data stream. On successful completion, a unique `PGN_handle` event (`installO`) is returned. On failures, `pgnERR` or `dataERR` is triggered.

3. **Cyclic Reception**: Once a channel is installed, the block listens for messages from the configured PGN at the specified source. Upon receiving a valid message, the data is made available in the `Data` output, and the `IND` event is triggered. The `s32TimeStamp` event is then updated.

4. **Timeout Monitoring**: If `u16CtrlTime` > 0, the block monitors the time between received messages. If no new message is received within this time window, the `TIMEOUT` event is triggered, `bTimeout` is set to `TRUE`, and `s32TimeStamp_timeout` is updated.

5. **Error Handling**: Protocol errors or invalid configurations trigger the corresponding error events (`dataERR`, `pgnERR`) with their associated error codes.

## Technical Features
* The block supports the specific data types `isobus::pgn::CAN_MSG` and `isobus::pgn::ISONETEVENT_T` from the ISOBUS PGN library.

* Timeout monitoring is optional and can be disabled by setting `u16CtrlTime` to 0.

* The `PGN_handle` serves as a reference for the installed channel and may be necessary for later management operations (e.g., uninstallation).

## Status Overview

1. **Not Initialized**: After startup. Waiting for `INIT`.

2. **Ready**: After successful initialization (`INITO`). Can receive `install` requests.

3. **Ready to Receive (Channel Active)**: After successful installation of a channel (`installO`). Monitors the bus for the configured PGN and triggers `IND` upon receipt or `TIMEOUT` if the monitoring time is exceeded.

4. **Error State**: Signaled by the events `pgnERR` or `dataERR`. The exact error can be found in the respective error code. The block can usually be used again after the cause has been resolved.

## Application Scenarios
* **Agricultural Machinery Control**: Receiving implement data (e.g., seed drill status) from an implement on the ISOBUS.

* **Vehicle Diagnostics**: Cyclic reception of engine data (RPM, temperature) for display and monitoring in the terminal.

* **Implement Control**: Receiving setpoint values (e.g., setpoint depth) from an operator console for a hydraulic lower link.

## ⚖️ Comparison with Similar Blocks
Unlike generic CAN receive blocks, `AlPgnRxNew8Bcylc` is specifically tailored to the ISOBUS PGN protocol. It offers higher abstraction through direct PGN addressing, integrated partner identification (`NmSource`), and automatic timeout management. Simple receive blocks would not provide this protocol layer and management functionality.

## 🛠️ Related Exercises

* [Exercise_131](../../../../../Uebungen/test_B/Uebungen_doc/Uebung_131.md)]

## Conclusion
The `AlPgnRxNew8Bcylc` is an essential building block for robust ISOBUS applications that need to receive cyclic data from other network participants. Its integrated channel management, timing, and error detection features significantly simplify the development of reliable communication interfaces and relieve application developers of the burden of dealing with low-level protocol details.