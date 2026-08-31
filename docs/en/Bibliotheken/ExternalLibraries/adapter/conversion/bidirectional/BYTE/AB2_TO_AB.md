# AB2_TO_AB

![AB2_TO_AB](AB2_TO_AB.svg)

* * * * * * * * * *

## Introduction

The AB2_TO_AB function block is the mirror image of [AB_TO_AB2](AB_TO_AB2.md): here the bidirectional [AB2](../../../types/bidirectional/BYTE/AB2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [AB](../../../types/unidirectional/BYTE/AB.md) socket and a unidirectional AB plug.

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

- **AB2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `AB_OUT` and whose outgoing side is fed by `AB_IN`, of type `adapter::types::bidirectional::AB2`
- **AB_IN** (Socket): unidirectional BYTE source, of type `adapter::types::unidirectional::AB`
- **AB_OUT** (Plug): mirrors the incoming (indication) side of `AB2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AB`

## Functionality

The block operates in two directions at once: whatever the socket `AB2_BIDIR` receives on its indication side (`EO1`/`DO1` — i.e. whatever a bidirectional peer attached to AB2_BIDIR reports) is output unchanged as a standalone unidirectional signal via the plug `AB_OUT`. Conversely, whatever arrives at the socket `AB_IN` (`E1`/`D1`) is published onto the request side of `AB2_BIDIR` (`EI1`/`DI1`) — so AB2_BIDIR forwards the same signal to the attached bidirectional peer.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AB_OUT` only reflects what is reported via `AB2_BIDIR` by an attached bidirectional peer — without such a peer, `AB_OUT` stays idle

## State Overview

The block is stateless:

- AB2_BIDIR.EO1 → AB_OUT.E1, AB2_BIDIR.DO1 → AB_OUT.D1
- AB_IN.E1 → AB2_BIDIR.EI1, AB_IN.D1 → AB2_BIDIR.DI1

## Application Scenarios

- Reading the status of a bidirectional AB2 peer as a plain unidirectional AB signal, combined with injecting a separate unidirectional command signal
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to AB2
- Bridging a bidirectional AB2 zone and a unidirectional AB zone

## ⚖️ Comparison with Similar Blocks

[AB_TO_AB2](AB_TO_AB2.md) is the mirror image of this block — there, `AB2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between AB2 and a plain BYTE signal, see [AB2_BYTE_TO_B](AB2_BYTE_TO_B.md)/[AB2_B_TO_BYTE](AB2_B_TO_BYTE.md).

## Conclusion

AB2_TO_AB is not a simple converter but a tap point: it makes the state of a bidirectional AB2 peer visible as a standalone unidirectional AB signal while simultaneously injecting a separate unidirectional signal into the bidirectional side.
