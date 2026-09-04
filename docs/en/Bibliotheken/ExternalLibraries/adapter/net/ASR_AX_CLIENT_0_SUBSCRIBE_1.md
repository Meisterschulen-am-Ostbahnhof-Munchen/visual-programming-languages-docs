# ASR_AX_CLIENT_0_SUBSCRIBE_1

![ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Introduction

The **ASR_AX_CLIENT_0_SUBSCRIBE_1** function block is a composite function block that triggers two independent remote OPC UA **method calls** (Set and Reset), each via its own `CLIENT_0` block, and reads the corresponding state back via `SUBSCRIBE_1` – all behind a single bidirectional **ASR_AX adapter socket**. It is the variant of [ASR_CLIENT_0](ASR_CLIENT_0.md) extended with a state channel.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_SET`, `STATUS_RESET`, and `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` updated, associated with the same variables

### **Data Inputs**

- **QI** (BOOL): Qualifier input for all three internal connections
- **ID_SET** (WSTRING): Remote method address for the Set call
- **ID_RESET** (WSTRING): Remote method address for the Reset call
- **ID_STATE** (WSTRING): Locally monitored state node (ACTION=READ)

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SET_CLIENT`, `RESET_CLIENT`, and `STATE_SUBSCRIBE` currently all report `QO = TRUE`
- **STATUS_SET** (WSTRING): Status information from `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Status information from `RESET_CLIENT`
- **STATUS_STATE** (WSTRING): Status information from `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| S_R | adapter::types::bidirectional::ASR_AX | Socket – Set/Reset (output), state (input) | Set/Reset out, state back |

## Functionality

1. Via the `INIT` event, `STATE_SUBSCRIBE` is initialized first, followed one after another by `SET_CLIENT` and `RESET_CLIENT`. After all have confirmed, `INITO` is reported externally.
2. `S_R.SET` and `S_R.RESET` directly trigger the method calls `SET_CLIENT.REQ` and `RESET_CLIENT.REQ` respectively.
3. As soon as `STATE_SUBSCRIBE` delivers a new state value via `IND`, this clocks the internal **E_D_FF** flip-flop, which captures and holds the value stably.
4. The flip-flop's output `EO` fires `S_R.EI1` with the buffered value at `S_R.DI1` – the state is reported back over the same adapter used to trigger Set/Reset.
5. `AND_QO` (AND_BOOL_3) ANDs the `QO` outputs of all three internal blocks; every confirmation additionally triggers `CNF` externally.

## Technical Features

- **Three network connections behind one adapter**: Two `CLIENT_0` instances (Set, Reset) and one `SUBSCRIBE_1` (state) are combined into a single bidirectional ASR_AX interface.
- **Buffering with D flip-flop**: The state received via `SUBSCRIBE_1` is stabilized via an internal `iec61499::events::E_D_FF` before being reported back over the adapter.
- **Sequential initialization**: `STATE_SUBSCRIBE` → `SET_CLIENT` → `RESET_CLIENT` (composite FBTypes chain `INIT`/`INITO` serially through each instance).
- **Encapsulation**: Only the ASR_AX adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: All three connections (Set, Reset, state subscription) are established.
3. **Send Active**: A Set or Reset event arriving at the adapter triggers the corresponding remote method call.
4. **State Update**: A new value from the subscription is buffered and reported back over the same adapter.

## Application Scenarios

- Remotely triggering Set/Reset on a remote actuator while simultaneously reading back the resulting state over a single adapter connection
- Reducing manual CLIENT_0/SUBSCRIBE_1 wiring to a single reusable building block

## Comparison with Similar Function Blocks

- **[ASR_CLIENT_0](ASR_CLIENT_0.md)**: The same two triggers, but without reading the state back.
- **[AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.md)**: The same pattern with only one trigger instead of two.
- **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Extends the same pattern with a third trigger (Toggle).
- **[ASR_AX_SERVER_0_CLIENT_1_0](ASR_AX_SERVER_0_CLIENT_1_0.md)**: The server-side counterpart.

## Conclusion

**ASR_AX_CLIENT_0_SUBSCRIBE_1** bundles two remote triggers (Set/Reset) and a state subscription behind a single bidirectional ASR_AX adapter, turning a hand-wired combination into a single reusable building block.
