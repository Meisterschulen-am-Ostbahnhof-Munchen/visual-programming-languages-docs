# AX2_TO_AX

![AX2_TO_AX](AX2_TO_AX.svg)

* * * * * * * * * *

## Introduction

The AX2_TO_AX function block is the mirror image of [AX_TO_AX2](AX_TO_AX2.md): here the bidirectional [AX2](../../../types/bidirectional/BOOL/AX2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [AX](../../../types/unidirectional/BOOL/AX.md) socket and a unidirectional AX plug.

## Interface Structure

### **Event Inputs**

The function block has no direct event inputs — communication happens exclusively through the adapters.

### **Event Outputs**

The function block has no direct event outputs.

### **Data Inputs**

The function block has no direct data inputs.

### **Data Outputs**

The function block has no direct data outputs.

### **Adapters**

- **AX2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `AX_OUT` and whose outgoing side is fed by `AX_IN`, of type `adapter::types::bidirectional::AX2`
- **AX_IN** (Socket): unidirectional BOOL source, of type `adapter::types::unidirectional::AX`
- **AX_OUT** (Plug): mirrors the incoming (indication) side of `AX2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AX`

## Functionality

The block operates in two directions at once: whatever the socket `AX2_BIDIR` receives on its indication side (`EO1`/`DO1` — i.e. whatever a bidirectional peer attached to AX2_BIDIR reports) is output unchanged as a standalone unidirectional signal via the plug `AX_OUT`. Conversely, whatever arrives at the socket `AX_IN` (`E1`/`D1`) is published onto the request side of `AX2_BIDIR` (`EI1`/`DI1`) — so AX2_BIDIR forwards the same signal to the attached bidirectional peer.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AX_OUT` only reflects what is reported via `AX2_BIDIR` by an attached bidirectional peer — without such a peer, `AX_OUT` stays idle

## State Overview

The block is stateless:

- AX2_BIDIR.EO1 → AX_OUT.E1, AX2_BIDIR.DO1 → AX_OUT.D1
- AX_IN.E1 → AX2_BIDIR.EI1, AX_IN.D1 → AX2_BIDIR.DI1

## Application Scenarios

- Reading the status of a bidirectional AX2 peer as a plain unidirectional AX signal, combined with injecting a separate unidirectional command signal
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to AX2
- Bridging a bidirectional AX2 zone and a unidirectional AX zone

## ⚖️ Comparison with Similar Blocks

[AX_TO_AX2](AX_TO_AX2.md) is the mirror image of this block — there, `AX2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between AX2 and a plain BOOL signal, see [AX2_X_TO_BOOL](AX2_X_TO_BOOL.md)/[AX2_BOOL_TO_X](AX2_BOOL_TO_X.md). The 2-channel A2X2/A2X counterpart is [A2X2_TO_A2X](A2X2_TO_A2X.md).

## Conclusion

AX2_TO_AX is not a simple converter but a tap point: it makes the state of a bidirectional AX2 peer visible as a standalone unidirectional AX signal while simultaneously injecting a separate unidirectional signal into the bidirectional side.
