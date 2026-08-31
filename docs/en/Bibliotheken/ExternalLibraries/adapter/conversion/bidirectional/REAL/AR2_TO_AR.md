# AR2_TO_AR

![AR2_TO_AR](AR2_TO_AR.svg)

* * * * * * * * * *

## Introduction

The AR2_TO_AR function block is the mirror image of [AR_TO_AR2](AR_TO_AR2.md): here the bidirectional [AR2](../../../types/bidirectional/REAL/AR2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [AR](../../../types/unidirectional/REAL/AR.md) socket and a unidirectional AR plug.

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

- **AR2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `AR_OUT` and whose outgoing side is fed by `AR_IN`, of type `adapter::types::bidirectional::AR2`
- **AR_IN** (Socket): unidirectional REAL source, of type `adapter::types::unidirectional::AR`
- **AR_OUT** (Plug): mirrors the incoming (indication) side of `AR2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AR`

## Functionality

The block operates in two directions at once: whatever the socket `AR2_BIDIR` receives on its indication side (`EO1`/`DO1` — i.e. whatever a bidirectional peer attached to AR2_BIDIR reports) is output unchanged as a standalone unidirectional signal via the plug `AR_OUT`. Conversely, whatever arrives at the socket `AR_IN` (`E1`/`D1`) is published onto the request side of `AR2_BIDIR` (`EI1`/`DI1`) — so AR2_BIDIR forwards the same signal to the attached bidirectional peer.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AR_OUT` only reflects what is reported via `AR2_BIDIR` by an attached bidirectional peer — without such a peer, `AR_OUT` stays idle

## State Overview

The block is stateless:

- AR2_BIDIR.EO1 → AR_OUT.E1, AR2_BIDIR.DO1 → AR_OUT.D1
- AR_IN.E1 → AR2_BIDIR.EI1, AR_IN.D1 → AR2_BIDIR.DI1

## Application Scenarios

- Reading the status of a bidirectional AR2 peer as a plain unidirectional AR signal, combined with injecting a separate unidirectional setpoint signal
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to AR2
- Bridging a bidirectional AR2 zone and a unidirectional AR zone

## ⚖️ Comparison with Similar Blocks

[AR_TO_AR2](AR_TO_AR2.md) is the mirror image of this block — there, `AR2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between AR2 and a plain REAL signal, see [AR2_REAL_TO_R](AR2_REAL_TO_R.md)/[AR2_R_TO_REAL](AR2_R_TO_REAL.md).

## Conclusion

AR2_TO_AR is not a simple converter but a tap point: it makes the state of a bidirectional AR2 peer visible as a standalone unidirectional AR signal while simultaneously injecting a separate unidirectional signal into the bidirectional side.
