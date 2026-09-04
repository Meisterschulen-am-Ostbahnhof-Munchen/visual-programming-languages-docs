# AE_CLIENT_0

![AE_CLIENT_0](AE_CLIENT_0.svg)

* * * * * * * * * *

## Introduction

The **AE_CLIENT_0** function block is a composite function block that encapsulates the network-based `CLIENT_0` function block from the IEC 61499 standard library and maps its interface to a unidirectional **AE adapter**. Every event arriving at the adapter socket `TRIGGER` triggers a remote OPC UA **method call** via `CLIENT_0` at the address configured in `ID`.

Unlike `CLIENT_1_0` (a remote write of a data value), `CLIENT_0` calls a remote **method without payload data** – the appropriate building block for event-driven trigger actions such as "Set", "Reset", or "Toggle" on a remote node.

## Interface Structure

### **Event Inputs**

- **INIT** (EInit): Initialization event, associated with `QI` and `ID`

### **Event Outputs**

- **INITO** (EInit): Initialization confirmation, associated with `QO` and `STATUS`
- **CNF** (Event): Confirmation that the method call has been sent, associated with `QO` and `STATUS`

### **Data Inputs**

- **QI** (BOOL): Qualifier input, opens (TRUE) or closes (FALSE) the connection to the server
- **ID** (WSTRING): Remote method address for the call

### **Data Outputs**

- **QO** (BOOL): Qualifier output, connection status (identical to `CLIENT_0_1.QO`)
- **STATUS** (WSTRING): Status information as a Unicode string (identical to `CLIENT_0_1.STATUS`)

### **Adapter**

| Adapter | Type | Direction | Description |
|---------|------|-----------|--------------|
| TRIGGER | adapter::types::unidirectional::AE | Socket (Input) | Triggering event for the method call |

## Functionality

1. The internal `CLIENT_0_1` block is initialized with `QI` and `ID` via the `INIT` event; it establishes the connection to the remote server. Upon success, it returns `INITO`.
2. Every event arriving at the adapter socket `TRIGGER` (`TRIGGER.E1`) directly triggers the send event `REQ` of the internal `CLIENT_0_1` block.
3. `CLIENT_0_1` then calls the remote method configured in `ID` and confirms with `CNF`, which is sent out.

## Technical Features

- **Pure trigger, no payload**: Unlike `AX_CLIENT_1_0`, `AE_CLIENT_0` transfers no data value – the adapter only supplies the triggering event.
- **Encapsulation**: The original event/data interface of `CLIENT_0` (including `REQ`) is moved internally; only the AE adapter interface is visible externally.
- The base building block from which [ASR_CLIENT_0](ASR_CLIENT_0.md) (2 triggers) and [ASRT_CLIENT_0](ASRT_CLIENT_0.md) (3 triggers) are derived by wiring multiple `CLIENT_0` instances in parallel.

## State Overview

1. **Not Initialized**: The block is waiting for the `INIT` event.
2. **Initialized**: The connection to the remote server is established, the block is ready to trigger method calls.
3. **Send Active**: An event arriving at the AE socket triggers the remote method call via the internal `CLIENT_0` block.

## Application Scenarios

- Remotely triggering a single remote action (e.g. "Start", "Trigger") without an associated data value
- Building block for composed multi-trigger blocks such as [ASR_CLIENT_0](ASR_CLIENT_0.md) and [ASRT_CLIENT_0](ASRT_CLIENT_0.md)
- Network coupling in AE-adapter-based applications

## Comparison with Similar Function Blocks

- **CLIENT_0**: The standard building block exposes its interface as events/variables (`REQ`, ...). **AE_CLIENT_0** encapsulates this building block and only provides the AE adapter.
- **AX_CLIENT_1_0**: Structurally similar, but encapsulates `CLIENT_1_0` (remote write of a data value) instead of `CLIENT_0` (pure method call without data).
- **[ASR_CLIENT_0](ASR_CLIENT_0.md)** / **[ASRT_CLIENT_0](ASRT_CLIENT_0.md)**: Extend the same pattern to 2 and 3 parallel triggers (Set/Reset and Set/Reset/Toggle, respectively).

## Conclusion

**AE_CLIENT_0** combines the trigger semantics of the standard function block `CLIENT_0` with adapter-based event processing. The simplified AE interface makes the function block ideal for directly triggering a remote OPC UA method call in fully adapter-based IEC 61499 applications.
