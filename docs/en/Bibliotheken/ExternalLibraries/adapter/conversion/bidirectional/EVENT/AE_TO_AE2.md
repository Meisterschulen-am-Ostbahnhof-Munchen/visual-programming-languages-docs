# AE_TO_AE2

![AE_TO_AE2](AE_TO_AE2.svg)

* * * * * * * * * *

## Introduction

The AE_TO_AE2 function block inserts a bidirectional [AE2](../../../types/bidirectional/EVENT/AE2.md) tap into a unidirectional [AE](../../../types/unidirectional/EVENT/AE.md) event chain. Rather than a simple 1:1 conversion, it uses **three** adapters: an incoming unidirectional AE event is both published onto the bidirectional AE2 interface and — whatever AE2 returns on its request side — output again as a standalone unidirectional AE event.

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

- **AE_IN** (Socket): unidirectional EVENT source, of type `adapter::types::unidirectional::AE`
- **AE2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `AE_IN` and whose incoming side is forwarded to `AE_OUT`, of type `adapter::types::bidirectional::AE2`
- **AE_OUT** (Plug): mirrors the incoming (request) side of `AE2_BIDIR` as a unidirectional event, of type `adapter::types::unidirectional::AE`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `AE_IN` (`E1`) is published directly onto the outgoing side of `AE2_BIDIR` (`EO1`) — so AE2_BIDIR reports outward the same event coming in via AE_IN. Conversely, whatever `AE2_BIDIR` receives on its request side (`EI1` — i.e. whatever a bidirectional peer attached to AE2_BIDIR "sends back") is output unchanged as a standalone unidirectional event via the plug `AE_OUT`. Since AE/AE2 are pure event adapters with no payload data, there are no DataConnections at all.

## Technical Details

- Three adapters instead of two: the incoming event direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- No data transport: AE/AE2 carry only events, so this block has no DataConnections
- `AE_OUT` only reflects what comes back via `AE2_BIDIR` from an attached bidirectional peer — without such a peer, `AE_OUT` stays idle

## State Overview

The block is stateless:

- AE_IN.E1 → AE2_BIDIR.EO1
- AE2_BIDIR.EI1 → AE_OUT.E1

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional AE event chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display a unidirectional event and send an event back
- Bridging a unidirectional AE zone and a bidirectional AE2 zone

## ⚖️ Comparison with Similar Blocks

[AE2_TO_AE](AE2_TO_AE.md) is the mirror image of this block — there, `AE2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between a plain EVENT signal and AE2, see [AE2_EVENT_TO_E](AE2_EVENT_TO_E.md)/[AE2_E_TO_EVENT](AE2_E_TO_EVENT.md). For two coupled events (SET/RESET), see [ASR_TO_ASR2](ASR_TO_ASR2.md).

## Conclusion

AE_TO_AE2 is not a simple converter but a tap point: it makes a unidirectional AE event visible at a bidirectional AE2 point without breaking the original unidirectional event chain, while forwarding the request event received there as a standalone AE event.
