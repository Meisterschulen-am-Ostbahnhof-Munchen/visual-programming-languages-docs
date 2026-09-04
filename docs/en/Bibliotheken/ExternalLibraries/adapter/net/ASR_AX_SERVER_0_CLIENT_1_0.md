# ASR_AX_SERVER_0_CLIENT_1_0

![ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.svg)

* * * * * * * * * *

## Introduction

The **ASR_AX_SERVER_0_CLIENT_1_0** function block is a composite function block that receives two independent remote OPC UA **method calls** (Set and Reset), each via its own `SERVER_0` block, and writes the resulting state back to a remote node via `CLIENT_1_0` – all behind a single bidirectional **ASR_AX adapter plug**. It is the server-side counterpart to [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md).

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_SET`, `STATUS_RESET`, and `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` updated, associated with the same variables

### **Data Inputs**

- **QI** (BOOL): Qualifier input for all three internal connections
- **ID_SET** (WSTRING): Local method address (ACTION=CREATE_METHOD) for the Set method call
- **ID_RESET** (WSTRING): Local method address (ACTION=CREATE_METHOD) for the Reset method call
- **ID_STATE** (WSTRING): Remote target address (ACTION=WRITE) for the state

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SET_SERVER`, `RESET_SERVER`, and `STATE_CLIENT` currently all report `QO = TRUE`
- **STATUS_SET** (WSTRING): Status information from `SET_SERVER`
- **STATUS_RESET** (WSTRING): Status information from `RESET_SERVER`
- **STATUS_STATE** (WSTRING): Status information from `STATE_CLIENT`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| S_R | adapter::types::bidirectional::ASR_AX | Plug – Set/Reset (input), state (output) | Received Set/Reset, state out |

## Functionality

1. Via the `INIT` event, `SET_SERVER`, `RESET_SERVER`, and `STATE_CLIENT` are initialized one after another. After all three have confirmed, `INITO` is reported externally.
2. A remote Set call on `SET_SERVER` triggers `S_R.SET`, and a remote Reset call on `RESET_SERVER` triggers `S_R.RESET` – both are thus reported inward via the adapter.
3. As soon as the downstream logic delivers a feedback event `S_R.EI1` with data `S_R.DI1` via the adapter, this clocks the internal **E_D_FF** flip-flop, which captures and holds the value stably.
4. The flip-flop's output `EO` triggers `STATE_CLIENT.REQ`; the buffered value is sent as an OPC UA write to the remote node configured in `ID_STATE`.
5. `AND_QO` (AND_BOOL_3) ANDs the `QO` outputs of all three internal blocks; every confirmation additionally triggers `CNF` externally.

## Technical Features

- **Three network connections behind one adapter**: Two `SERVER_0` instances (Set, Reset) and one `CLIENT_1_0` (state) are combined into a single bidirectional ASR_AX interface.
- **Buffering with D flip-flop**: The feedback value reported via the adapter is stabilized via an internal `iec61499::events::E_D_FF` before being sent via `CLIENT_1_0`.
- **Sequential initialization**: `SET_SERVER` → `RESET_SERVER` → `STATE_CLIENT` (composite FBTypes chain `INIT`/`INITO` serially through each instance).
- **Encapsulation**: Only the ASR_AX adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: All three connections (Set server, Reset server, state client) are established.
3. **Receive Active**: A remote Set or Reset call is reported to the internal logic via the adapter.
4. **State Write**: A feedback value from the internal logic is buffered and sent via remote write to the configured target node.

## Application Scenarios

- Receiving remote Set/Reset calls while simultaneously writing the resulting state back to a different remote node over a single adapter connection
- Server-side counterpart to [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md) in distributed control architectures

## Comparison with Similar Function Blocks

- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: The client/calling counterpart.
- **[AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.md)**: The same pattern with only one receiving server instead of two.
- **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: Extends the same pattern with a third receiving server (Toggle).

## Conclusion

**ASR_AX_SERVER_0_CLIENT_1_0** bundles two receiving servers (Set/Reset) and a state-writing client behind a single bidirectional ASR_AX adapter, forming the server-side counterpart to [ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md).
