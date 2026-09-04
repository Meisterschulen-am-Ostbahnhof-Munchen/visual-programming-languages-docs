# ASRT_AX_CLIENT_0_SUBSCRIBE_1

![ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Introduction

The **ASRT_AX_CLIENT_0_SUBSCRIBE_1** function block is a composite function block that triggers three independent remote OPC UA **method calls** (Set, Reset, and Toggle), each via its own `CLIENT_0` block, and reads the corresponding state back via `SUBSCRIBE_1` – all behind a single bidirectional **ASRT_AX adapter socket**. It is the variant of [ASRT_CLIENT_0](ASRT_CLIENT_0.md) extended with a state channel.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_SET`, `STATUS_RESET`, `STATUS_TOGGLE`, and `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` updated, associated with the same variables

### **Data Inputs**

- **QI** (BOOL): Qualifier input for all four internal connections
- **ID_SET** (WSTRING): Remote method address for the Set call
- **ID_RESET** (WSTRING): Remote method address for the Reset call
- **ID_TOGGLE** (WSTRING): Remote method address for the Toggle call
- **ID_STATE** (WSTRING): Locally monitored state node (ACTION=READ)

### **Data Outputs**

- **QO** (BOOL): TRUE only if `SET_CLIENT`, `RESET_CLIENT`, `TOGGLE_CLIENT`, and `STATE_SUBSCRIBE` currently all report `QO = TRUE`
- **STATUS_SET** (WSTRING): Status information from `SET_CLIENT`
- **STATUS_RESET** (WSTRING): Status information from `RESET_CLIENT`
- **STATUS_TOGGLE** (WSTRING): Status information from `TOGGLE_CLIENT`
- **STATUS_STATE** (WSTRING): Status information from `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| S_R_T | adapter::types::bidirectional::ASRT_AX | Socket – Set/Reset/Toggle (output), state (input) | Set/Reset/Toggle out, state back |

## Functionality

1. Via the `INIT` event, `SET_CLIENT`, `RESET_CLIENT`, `TOGGLE_CLIENT`, and `STATE_SUBSCRIBE` are initialized one after another. After all four have confirmed, `INITO` is reported externally.
2. `S_R_T.SET`, `S_R_T.RESET`, and `S_R_T.TOGGLE` directly trigger the corresponding `CLIENT_0` method calls.
3. As soon as `STATE_SUBSCRIBE` delivers a new state value via `IND`, this clocks the internal **E_D_FF** flip-flop, which captures and holds the value stably.
4. The flip-flop's output `EO` fires `S_R_T.EI1` with the buffered value at `S_R_T.DI1` – the state is reported back over the same adapter used to trigger Set/Reset/Toggle.
5. `AND_QO` (AND_BOOL_4) ANDs the `QO` outputs of all four internal blocks; every confirmation additionally triggers `CNF` externally.

## Technical Features

- **Four network connections behind one adapter**: Three `CLIENT_0` instances (Set, Reset, Toggle) and one `SUBSCRIBE_1` (state) are combined into a single bidirectional ASRT_AX interface.
- **Buffering with D flip-flop**: The state received via `SUBSCRIBE_1` is stabilized via an internal `iec61499::events::E_D_FF` before being reported back over the adapter.
- **Sequential initialization**: `SET_CLIENT` → `RESET_CLIENT` → `TOGGLE_CLIENT` → `STATE_SUBSCRIBE` (composite FBTypes chain `INIT`/`INITO` serially through each instance).
- **Encapsulation**: Only the ASRT_AX adapter interface is visible externally.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: All four connections (Set, Reset, Toggle, state subscription) are established.
3. **Send Active**: A Set, Reset, or Toggle event arriving at the adapter triggers the corresponding remote method call.
4. **State Update**: A new value from the subscription is buffered and reported back over the same adapter.

## Application Scenarios

- Remotely triggering Set/Reset/Toggle on a remote actuator while simultaneously reading back the resulting state over a single adapter connection
- Reducing manual CLIENT_0/SUBSCRIBE_1 wiring to a single reusable building block

## Comparison with Similar Function Blocks

- **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: The same three triggers, but without reading the state back.
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)**: The same pattern with only two triggers (no Toggle).
- **[ASRT_AX_SERVER_0_CLIENT_1_0](ASRT_AX_SERVER_0_CLIENT_1_0.md)**: The server-side counterpart.

## Conclusion

**ASRT_AX_CLIENT_0_SUBSCRIBE_1** bundles three remote triggers (Set/Reset/Toggle) and a state subscription behind a single bidirectional ASRT_AX adapter, turning a hand-wired combination into a single reusable building block.
