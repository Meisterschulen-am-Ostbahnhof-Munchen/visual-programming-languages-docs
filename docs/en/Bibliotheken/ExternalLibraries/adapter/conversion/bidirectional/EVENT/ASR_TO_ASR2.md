# ASR_TO_ASR2

![ASR_TO_ASR2](ASR_TO_ASR2.svg)

* * * * * * * * * *

## Introduction

The ASR_TO_ASR2 function block inserts a bidirectional [ASR2](../../../types/bidirectional/EVENT/ASR2.md) tap into a unidirectional [ASR](../../../types/unidirectional/EVENT/ASR.md) chain. ASR/ASR2 carry two coupled events, SET and RESET, rather than a single E1. Like the other bridge blocks, ASR_TO_ASR2 uses **three** adapters: incoming unidirectional SET/RESET events are both published onto the bidirectional ASR2 interface and — whatever ASR2 returns on its request side — output again as standalone unidirectional SET/RESET events.

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs — communication happens exclusively through the adapters.

### **Event Outputs**

The function block has no direct event outputs.

### **Data Inputs**

The function block has no data inputs or outputs at all — ASR and ASR2 carry only the SET/RESET events, never payload data.

### **Data Outputs**

The function block has no data inputs or outputs at all — ASR and ASR2 carry only the SET/RESET events, never payload data.

### **Adapters**

- **ASR_IN** (Socket): unidirectional SET/RESET source, of type `adapter::types::unidirectional::ASR`
- **ASR2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `ASR_IN` and whose incoming side is forwarded to `ASR_OUT`, of type `adapter::types::bidirectional::ASR2`
- **ASR_OUT** (Plug): mirrors the incoming (request) side of `ASR2_BIDIR` as unidirectional SET/RESET events, of type `adapter::types::unidirectional::ASR`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `ASR_IN` (`SET`/`RESET`) is published directly onto the outgoing side of `ASR2_BIDIR` (`EO_SET`/`EO_RESET`) — so ASR2_BIDIR reports outward the same events coming in via ASR_IN. Conversely, whatever `ASR2_BIDIR` receives on its request side (`EI_SET`/`EI_RESET` — i.e. whatever a bidirectional peer attached to ASR2_BIDIR "sends back") is output unchanged as standalone unidirectional events via the plug `ASR_OUT` (`SET`/`RESET`). Since ASR/ASR2 are pure event adapters with no payload data, there are no DataConnections at all.

## Technical Details

- Three adapters instead of two: the incoming event direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Two parallel but independently routed event pairs (SET and RESET), never merged or combined
- Pure wiring, no logic or state, every destination variable has exactly one writer
- No data transport: ASR/ASR2 carry only SET/RESET events, so this block has no DataConnections
- `ASR_OUT` only reflects what comes back via `ASR2_BIDIR` from an attached bidirectional peer — without such a peer, `ASR_OUT` stays idle

## State Overview

The block is stateless:

- ASR_IN.SET → ASR2_BIDIR.EO_SET, ASR_IN.RESET → ASR2_BIDIR.EO_RESET
- ASR2_BIDIR.EI_SET → ASR_OUT.SET, ASR2_BIDIR.EI_RESET → ASR_OUT.RESET

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional ASR SET/RESET chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display SET/RESET state and send SET/RESET events back
- Bridging a unidirectional ASR zone and a bidirectional ASR2 zone

## ⚖️ Comparison with Similar Blocks

[ASR2_TO_ASR](ASR2_TO_ASR.md) is the mirror image of this block — there, `ASR2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between two plain EVENT signals and ASR2, see [ASR2_4EVENTS_TO_SR2](ASR2_4EVENTS_TO_SR2.md)/[ASR2_SR2_TO_4EVENTS](ASR2_SR2_TO_4EVENTS.md). For a single event without SET/RESET coupling, see [AE_TO_AE2](AE_TO_AE2.md).

## Conclusion

ASR_TO_ASR2 is not a simple converter but a tap point: it makes a unidirectional ASR SET/RESET pair visible at a bidirectional ASR2 point without breaking the original unidirectional chain, while forwarding the request SET/RESET pair received there as a standalone ASR signal.
