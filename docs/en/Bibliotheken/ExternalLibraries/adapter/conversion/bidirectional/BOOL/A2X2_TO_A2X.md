# A2X2_TO_A2X

![A2X2_TO_A2X](A2X2_TO_A2X.svg)

* * * * * * * * * *

## Introduction

The A2X2_TO_A2X function block is the mirror image of [A2X_TO_A2X2](A2X_TO_A2X2.md): here the bidirectional [A2X2](../../../types/bidirectional/BOOL/A2X2.md) tap sits as a socket on the left (input) side, complemented by a second unidirectional [A2X](../../../types/unidirectional/BOOL/A2X.md) socket and a unidirectional A2X plug.

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

- **A2X2_BIDIR** (Socket): bidirectional tap whose incoming side is forwarded to `A2X_OUT` and whose outgoing side is fed by `A2X_IN`, of type `adapter::types::bidirectional::A2X2`
- **A2X_IN** (Socket): unidirectional UP/DOWN source, of type `adapter::types::unidirectional::A2X`
- **A2X_OUT** (Plug): mirrors the incoming (indication) side of `A2X2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::A2X`

## Functionality

The block operates in two directions at once: whatever the socket `A2X2_BIDIR` receives on its indication side (`EO_UP`/`DO_UP`, `EO_DOWN`/`DO_DOWN` — i.e. whatever a bidirectional peer attached to A2X2_BIDIR reports) is output unchanged as a standalone unidirectional signal via the plug `A2X_OUT`. Conversely, whatever arrives at the socket `A2X_IN` (`E_UP`/`UP`, `E_DOWN`/`DOWN`) is published onto the request side of `A2X2_BIDIR` (`EI_UP`/`DI_UP`, `EI_DOWN`/`DI_DOWN`) — so A2X2_BIDIR forwards the same UP/DOWN signal to the attached bidirectional peer.

## Technical Details

- Three adapters instead of two: the direction received from the tap and the separately injected direction are deliberately kept apart rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `A2X_OUT` only reflects what is reported via `A2X2_BIDIR` by an attached bidirectional peer — without such a peer, `A2X_OUT` stays idle

## State Overview

The block is stateless:

- A2X2_BIDIR.EO_UP → A2X_OUT.E_UP, A2X2_BIDIR.DO_UP → A2X_OUT.UP
- A2X2_BIDIR.EO_DOWN → A2X_OUT.E_DOWN, A2X2_BIDIR.DO_DOWN → A2X_OUT.DOWN
- A2X_IN.E_UP → A2X2_BIDIR.EI_UP, A2X_IN.UP → A2X2_BIDIR.DI_UP
- A2X_IN.E_DOWN → A2X2_BIDIR.EI_DOWN, A2X_IN.DOWN → A2X2_BIDIR.DI_DOWN

## Application Scenarios

- Reading the status of a bidirectional A2X2 peer as a plain unidirectional A2X signal, combined with injecting a separate unidirectional command signal
- Systems where a bidirectional peer needs to be monitored without converting the rest of the control logic to A2X2
- Bridging a bidirectional A2X2 zone and a unidirectional A2X zone

## ⚖️ Comparison with Similar Blocks

[A2X_TO_A2X2](A2X_TO_A2X2.md) is the mirror image of this block — there, `A2X2_BIDIR` sits as a plug on the right side. For a pure, non-tapping 1:1 conversion between the single-channel adapters, see the conversion blocks between [AX](../../../types/unidirectional/BOOL/AX.md) and [AX2](../../../types/bidirectional/BOOL/AX2.md) in the same library.

## Conclusion

A2X2_TO_A2X is not a simple converter but a tap point: it makes the state of a bidirectional A2X2 peer visible as a standalone unidirectional A2X signal while simultaneously injecting a separate unidirectional signal into the bidirectional side.
