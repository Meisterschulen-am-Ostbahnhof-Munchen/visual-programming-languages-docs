# AE_AX_CLIENT_0_SUBSCRIBE_1

![AE_AX_CLIENT_0_SUBSCRIBE_1](AE_AX_CLIENT_0_SUBSCRIBE_1.svg)

* * * * * * * * * *

## Introduction

The **AE_AX_CLIENT_0_SUBSCRIBE_1** function block is a composite function block that triggers a remote OPC UA **method call** via `CLIENT_0` and reads the corresponding state back via `SUBSCRIBE_1` – both behind a single bidirectional **AE_AX adapter socket**. It collapses the pattern of "one hand-wired `CLIENT_0` plus one `SUBSCRIBE_1`" into a single building block with one adapter port.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO`, `STATUS_TRIGGER`, and `STATUS_STATE`
- **CNF** (Event): `QO`/`STATUS` updated, associated with `QO`, `STATUS_TRIGGER`, and `STATUS_STATE`

### **Data Inputs**

- **QI** (BOOL): Qualifier input for both internal connections
- **ID** (WSTRING): Remote method address for the trigger call (`CLIENT_0_1`)
- **ID_STATE** (WSTRING): Locally monitored state node for `SUBSCRIBE_1` (ACTION=READ)

### **Data Outputs**

- **QO** (BOOL): TRUE only if `CLIENT_0_1` and `STATE_SUBSCRIBE` currently both report `QO = TRUE`
- **STATUS_TRIGGER** (WSTRING): Status information from `CLIENT_0_1`
- **STATUS_STATE** (WSTRING): Status information from `STATE_SUBSCRIBE`

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| TRIGGER | adapter::types::bidirectional::AE_AX | Socket – trigger (output), state (input) | Triggering event out, state back |

## Functionality

1. Via the `INIT` event, `STATE_SUBSCRIBE` (`SUBSCRIBE_1`) is initialized first with `QI` and `ID_STATE`; after its `INITO`, `CLIENT_0_1` is initialized with `QI` and `ID`. After both have confirmed, `INITO` is reported externally.
2. An event arriving at the adapter socket `TRIGGER.E1` directly triggers the method call `CLIENT_0_1.REQ`.
3. As soon as `STATE_SUBSCRIBE` delivers a new state value at `RD_1` via `IND`, this event clocks the internal **E_D_FF** flip-flop, which captures and holds the value stably.
4. The flip-flop's output `EO` fires `TRIGGER.EI1` with the buffered value at `TRIGGER.DI1` – so the state is reported back over the same adapter used to send the trigger out.
5. `AND_QO` (AND_BOOL_2) ANDs the `QO` outputs of `CLIENT_0_1` and `STATE_SUBSCRIBE`; every confirmation (`CLIENT_0_1.CNF` or `STATE_SUBSCRIBE.IND`) additionally triggers `CNF` externally.

## Technical Features

- **Two network connections behind one adapter**: `CLIENT_0` (trigger, write direction) and `SUBSCRIBE_1` (state, read direction) are combined into a single bidirectional AE_AX interface.
- **Buffering with D flip-flop**: The state received via `SUBSCRIBE_1` is stabilized via an internal `iec61499::events::E_D_FF` before being reported back over the adapter.
- **Sequential initialization**: `STATE_SUBSCRIBE` is initialized before `CLIENT_0_1` (composite FBTypes chain `INIT`/`INITO` serially through each instance).
- **Encapsulation**: Only the AE_AX adapter interface is visible externally; `CLIENT_0`'s `REQ` and `SUBSCRIBE_1`'s `IND`/`RD_1` remain internal.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: Both connections (trigger and state subscription) are established.
3. **Send Active**: A trigger event arriving at the adapter triggers the remote method call.
4. **State Update**: A new value from the subscription is buffered and reported back over the same adapter.

## Application Scenarios

- Remotely triggering a remote action while simultaneously reading back the resulting state over a single adapter connection, e.g. for a control element that immediately shows the actual state of the remote actuator
- Reducing manual CLIENT_0/SUBSCRIBE_1 wiring to a single reusable building block

## Comparison with Similar Function Blocks

- **[AE_CLIENT_0](AE_CLIENT_0.md)**: A pure trigger without reading the state back.
- **[AI_SUBSCRIBE_1](AI_SUBSCRIBE_1.md)**: A pure state subscription without trigger functionality.
- **[ASR_AX_CLIENT_0_SUBSCRIBE_1](ASR_AX_CLIENT_0_SUBSCRIBE_1.md)** / **[ASRT_AX_CLIENT_0_SUBSCRIBE_1](ASRT_AX_CLIENT_0_SUBSCRIBE_1.md)**: Extend the same pattern to 2 and 3 parallel triggers.
- **[AE_AX_SERVER_0_CLIENT_1_0](AE_AX_SERVER_0_CLIENT_1_0.md)**: The server-side counterpart – receives instead of triggering, and writes instead of subscribing.

## Conclusion

**AE_AX_CLIENT_0_SUBSCRIBE_1** bundles a remote trigger and a state subscription behind a single bidirectional AE_AX adapter, turning a hand-wired CLIENT_0/SUBSCRIBE_1 combination into a single reusable building block.
