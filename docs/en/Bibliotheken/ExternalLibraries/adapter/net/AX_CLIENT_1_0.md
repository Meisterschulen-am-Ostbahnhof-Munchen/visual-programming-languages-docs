# AX_CLIENT_1_0

![AX_CLIENT_1_0](./AX_CLIENT_1_0.svg)

* * * * * * * * * *

## Introduction

The **AX_CLIENT_1_0** function block is a composite function block that encapsulates the network-based `CLIENT_1_0` function block from the IEC 61499 standard library and maps its interface to a unidirectional **AX adapter**. A **BOOL** value present at the adapter socket `IN` is buffered via an internal D flip-flop (E_D_FF) and then sent via `CLIENT_1_0` as an OPC UA **write** to the remote node configured in `ID`.

The generic `CLIENT_1_0` network client writes to a **remote** server identified by an `ID` that corresponds to a connection on the server block. For OPC UA, an `ID` such as `opc_ua[WRITE;opc.tcp://192.168.1.12:4840#;...]` is a transport-specific example, not a requirement; unlike **AX_PUBLISH_1** (local publish/subscribe), `CLIENT_1_0` can write to a remote server.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI` and `ID`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO` and `STATUS`
- **CNF** (Event): Confirmation that data has been sent, associated with `QO` and `STATUS`

### **Data Inputs**

- **QI** (BOOL): Qualifier input, opens (TRUE) or closes (FALSE) the connection to the server
- **ID** (WSTRING): Connection identifier (OPC UA address of the target node, e.g. `opc_ua[WRITE;opc.tcp://192.168.1.12:4840#;...]`)

### **Data Outputs**

- **QO** (BOOL): Qualifier output, connection status
- **STATUS** (WSTRING): Status information as a Unicode string

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------------------------------|-----------|---------------------------------|
| IN | adapter::types::unidirectional::AX | Socket (Input) | BOOL value to be sent |

## Functionality

1. The internal `CLIENT_1_0` block is initialized with `QI` and `ID` via the `INIT` event; it establishes the connection to the remote server. Upon success, it returns `INITO`.
2. As soon as the AX socket `IN` sends an event to `IN.E1`, the BOOL value simultaneously present at `IN.D1` is transferred to the internal **E_D_FF** flip-flop (`CLK` or `D`).
3. The flip-flop holds the value stably at its output `Q` and generates the event `EO` when the value changes.
4. `EO` triggers the send event `REQ` of the internal `CLIENT_1_0` block. The buffered value `Q` is transmitted over the data connection as `SD_1` and sent to the server as an OPC UA write.
5. After successful transmission, the `CLIENT_1_0` block confirms with `CNF`, which is then sent out.

## Technical Features

- **Buffering with D-Flip-Flop**: The BOOL value to be sent is buffered via an internal `iec61499::events::E_D_FF`. This prevents a changing input value during processing from interfering with the transmission.
- **Remote write instead of local publish**: `CLIENT_1_0` addresses a remote OPC UA server directly (ACTION=WRITE with a full ENDPOINT in `ID`), unlike `PUBLISH_1`/`SUBSCRIBE_1`, which only work locally on the same FORTE node.
- **Encapsulation**: The original event/data interface of `CLIENT_1_0` (including `REQ`/`SD_1`) is moved internally; only the AX adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: The connection to the remote server is established, the block is ready to send.
3. **Send Active**: An event arriving at the AX socket buffers the value and triggers the remote write via the internal `CLIENT_1_0` block.

## Application Scenarios

- **Remote control of other modules**: A VT button press on a module with its own ISOBUS/VT connection triggers an OPC UA write to a different, remote control module (e.g. STG1 switches an output on STG2–STG5).
- **Network coupling in AX applications**: Sending Boolean signals (switching commands) from adapter-based logic directly to a remote OPC UA server.
- **Modular control architectures**: Integration of distributed remote control into libraries that consistently rely on AX adapters.

## Comparison with Similar Function Blocks

- **CLIENT_1_0**: The standard function block exposes its interface as events/variables (`REQ`, `SD_1`, ...). **AX_CLIENT_1_0** encapsulates this function block, buffers the value with a D flip-flop, and only provides the AX adapter.
- **AX_PUBLISH_1**: Structurally identical (same events/variables/adapter), but encapsulates `PUBLISH_1` instead of `CLIENT_1_0` – so it only publishes locally instead of actively writing to a remote node.

## Conclusion

**AX_CLIENT_1_0** combines the connection-oriented remote-write communication of the standard function block `CLIENT_1_0` with adapter-based Boolean processing. Internal D flip-flop buffering stabilizes the transmitted value; the simplified AX interface makes the function block ideal for writing directly to a remote OPC UA server in fully adapter-based IEC 61499 applications.
