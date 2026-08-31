# AE2_TO_AE

![AE2_TO_AE](AE2_TO_AE.svg)

* * * * * * * * * *

## Introduction

The AE2_TO_AE function block is the mirror image of [AE_TO_AE2](AE_TO_AE2.md): here the bidirectional [AE2](../../../types/bidirectional/EVENT/AE2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [AE](../../../types/unidirectional/EVENT/AE.md) socket and a unidirectional AE plug.

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs — communication happens exclusively through the adapters.

### **Event Outputs**

The function block has no direct event outputs.

### **Data Inputs**

The function block has no data inputs or outputs at all — AE and AE2 carry only events, never payload data.

### **Data Outputs**

The function block has no data inputs or outputs at all — AE and AE2 carry only events, never payload data.

### **Adapters**

- **AE2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `AE_OUT` and whose outgoing side is fed by `AE_IN`, of type `adapter::types::bidirectional::AE2`
- **AE_IN** (Socket): unidirectional EVENT source, of type `adapter::types::unidirectional::AE`
- **AE_OUT** (Plug): mirrors the incoming (indication) side of `AE2_BIDIR` as a unidirectional event, of type `adapter::types::unidirectional::AE`

## Functionality

The block operates in two directions at once: whatever the socket `AE2_BIDIR` receives on its indication side (`EO1` — i.e. whatever a bidirectional peer attached to AE2_BIDIR reports) is output unchanged as a standalone unidirectional event via the plug `AE_OUT`. Conversely, whatever arrives at the socket `AE_IN` (`E1`) is published onto the request side of `AE2_BIDIR` (`EI1`) — so AE2_BIDIR forwards the same event to the attached bidirectional peer. Since AE/AE2 are pure event adapters with no payload data, there are no DataConnections at all.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- No data transport: AE/AE2 carry only events, so this block has no DataConnections
- `AE_OUT` only reflects what is reported via `AE2_BIDIR` by an attached bidirectional peer — without such a peer, `AE_OUT` stays idle

## State Overview

The block is stateless:

- AE2_BIDIR.EO1 → AE_OUT.E1
- AE_IN.E1 → AE2_BIDIR.EI1

## Application Scenarios

- Reading a bidirectional AE2 peer as a plain unidirectional AE event, combined with injecting a separate unidirectional event
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to AE2
- Bridging a bidirectional AE2 zone and a unidirectional AE zone

## ⚖️ Comparison with Similar Blocks

[AE_TO_AE2](AE_TO_AE2.md) is the mirror image of this block — there, `AE2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between AE2 and a plain EVENT signal, see [AE2_E_TO_EVENT](AE2_E_TO_EVENT.md)/[AE2_EVENT_TO_E](AE2_EVENT_TO_E.md). For two coupled events (SET/RESET), see [ASR2_TO_ASR](ASR2_TO_ASR.md).

## Conclusion

AE2_TO_AE is not a simple converter but a tap point: it makes the state of a bidirectional AE2 peer visible as a standalone unidirectional AE event while simultaneously injecting a separate unidirectional event into the bidirectional side.
