# ASR2_TO_ASR

![ASR2_TO_ASR](ASR2_TO_ASR.svg)

* * * * * * * * * *

## Introduction

The ASR2_TO_ASR function block is the mirror image of [ASR_TO_ASR2](ASR_TO_ASR2.md): here the bidirectional [ASR2](../../../types/bidirectional/EVENT/ASR2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [ASR](../../../types/unidirectional/EVENT/ASR.md) socket and a unidirectional ASR plug.

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

- **ASR2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `ASR_OUT` and whose outgoing side is fed by `ASR_IN`, of type `adapter::types::bidirectional::ASR2`
- **ASR_IN** (Socket): unidirectional SET/RESET source, of type `adapter::types::unidirectional::ASR`
- **ASR_OUT** (Plug): mirrors the incoming (indication) side of `ASR2_BIDIR` as unidirectional SET/RESET events, of type `adapter::types::unidirectional::ASR`

## Functionality

The block operates in two directions at once: whatever the socket `ASR2_BIDIR` receives on its indication side (`EO_SET`/`EO_RESET` — i.e. whatever a bidirectional peer attached to ASR2_BIDIR reports) is output unchanged as standalone unidirectional events via the plug `ASR_OUT` (`SET`/`RESET`). Conversely, whatever arrives at the socket `ASR_IN` (`SET`/`RESET`) is published onto the request side of `ASR2_BIDIR` (`EI_SET`/`EI_RESET`) — so ASR2_BIDIR forwards the same events to the attached bidirectional peer. Since ASR/ASR2 are pure event adapters with no payload data, there are no DataConnections at all.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Two parallel but independently routed event pairs (SET and RESET), never merged or combined
- Pure wiring, no logic or state, every destination variable has exactly one writer
- No data transport: ASR/ASR2 carry only SET/RESET events, so this block has no DataConnections
- `ASR_OUT` only reflects what is reported via `ASR2_BIDIR` by an attached bidirectional peer — without such a peer, `ASR_OUT` stays idle

## State Overview

The block is stateless:

- ASR2_BIDIR.EO_SET → ASR_OUT.SET, ASR2_BIDIR.EO_RESET → ASR_OUT.RESET
- ASR_IN.SET → ASR2_BIDIR.EI_SET, ASR_IN.RESET → ASR2_BIDIR.EI_RESET

## Application Scenarios

- Reading a bidirectional ASR2 peer as a plain unidirectional SET/RESET pair, combined with injecting a separate unidirectional SET/RESET pair
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to ASR2
- Bridging a bidirectional ASR2 zone and a unidirectional ASR zone

## ⚖️ Comparison with Similar Blocks

[ASR_TO_ASR2](ASR_TO_ASR2.md) is the mirror image of this block — there, `ASR2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between ASR2 and two plain EVENT signals, see [ASR2_SR2_TO_4EVENTS](ASR2_SR2_TO_4EVENTS.md)/[ASR2_4EVENTS_TO_SR2](ASR2_4EVENTS_TO_SR2.md). For a single event without SET/RESET coupling, see [AE2_TO_AE](AE2_TO_AE.md).

## Conclusion

ASR2_TO_ASR is not a simple converter but a tap point: it makes the state of a bidirectional ASR2 peer visible as a standalone unidirectional SET/RESET pair while simultaneously injecting a separate unidirectional SET/RESET pair into the bidirectional side.
