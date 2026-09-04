# AE_AX_SERVER_0_CLIENT_1_0

![AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.svg)

* * * * * * * * * *

## Introduction

The **AE_AX_SERVER_0_CLIENT_1_0** function block is a composite function block that receives a remote OPC UA **method call** via `SERVER_0` and writes the resulting state back to a remote node via `CLIENT_1_0` – both behind a single bidirectional **AE_AX adapter plug**. It is the server-side counterpart to [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md).

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_TRIGGER`, and `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` updated, associated with `QO`, `STATUS_TRIGGER`, and `STATUS_STATE`

### **Data Inputs**

- **QI** (BOOL): Qualifier input for both internal connections
- **ID** (WSTRING): Local method address (ACTION=CREATE_METHOD) for the trigger method call (`SERVER_0_1`)
- **ID_STATE** (WSTRING): Remote target address (ACTION=WRITE) for the state (`STATE_CLIENT`)

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SERVER_0_1` and `STATE_CLIENT` currently both report `QO = TRUE`
- **STATUS_TRIGGER** (WSTRING): Status information from `SERVER_0_1`
- **STATUS_STATE** (WSTRING): Status information from `STATE_CLIENT`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| TRIGGER | adapter::types::bidirectional::AE_AX | Plug – trigger (input), state (output) | Received event, state out |

## Functionality

1. Via the `INIT` event, `SERVER_0_1` is initialized first with `QI` and `ID`; after its `INITO`, `STATE_CLIENT` is initialized with `QI` and `ID_STATE`. After both have confirmed, `INITO` is reported externally.
2. A remote method call on `SERVER_0_1` generates the indication event `IND`, which is placed directly on `TRIGGER.E1` – the adapter thus reports the call inward to the downstream logic.
3. As soon as the downstream logic delivers a feedback event `TRIGGER.EI1` with data `TRIGGER.DI1` via the adapter, this clocks the internal **E_D_FF** flip-flop, which captures and holds the value stably.
4. The flip-flop's output `EO` triggers `STATE_CLIENT.REQ`; the buffered value is passed as `SD_1` and sent as an OPC UA write to the remote node configured in `ID_STATE`.
5. `AND_QO` (AND_BOOL_2) ANDs the `QO` outputs of `SERVER_0_1` and `STATE_CLIENT`; every confirmation additionally triggers `CNF` externally.

## Technical Features

- **Two network connections behind one adapter**: `SERVER_0` (receiving, server role) and `CLIENT_1_0` (state, remote write) are combined into a single bidirectional AE_AX interface.
- **Buffering with D flip-flop**: The feedback value reported via the adapter is stabilized via an internal `iec61499::events::E_D_FF` before being sent via `CLIENT_1_0`.
- **Sequential initialization**: `SERVER_0_1` is initialized before `STATE_CLIENT` (composite FBTypes chain `INIT`/`INITO` serially through each instance).
- **Encapsulation**: Only the AE_AX adapter interface is visible externally; `SERVER_0`'s `IND` and `CLIENT_1_0`'s `REQ`/`SD_1` remain internal.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: Both connections (server and state client) are established.
3. **Receive Active**: A remote method call is reported to the internal logic via the adapter.
4. **State Write**: A feedback value from the internal logic is buffered and sent via remote write to the configured target node.

## Application Scenarios

- Receiving a remote trigger call while simultaneously writing the resulting state back to a different remote node over a single adapter connection
- Server-side counterpart to [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md) in distributed control architectures

## Comparison with Similar Function Blocks

- **[AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md)**: The client/calling counterpart – actively triggers instead of receiving, subscribes instead of writing.
- **[AX_CLIENT_1_0](AX_CLIENT_1_0.md)**: A pure remote write without a receiving side.
- **[ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.md)** / **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: Extend the same pattern to 2 and 3 parallel receiving servers.

## Conclusion

**AE_AX_SERVER_0_CLIENT_1_0** bundles a receiving server and a state-writing client behind a single bidirectional AE_AX adapter, forming the server-side counterpart to [AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md).
