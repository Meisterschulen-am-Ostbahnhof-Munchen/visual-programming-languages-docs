# A2X_TO_A2X2

![A2X_TO_A2X2](A2X_TO_A2X2.svg)

* * * * * * * * * *

## Introduction

The A2X_TO_A2X2 function block inserts a bidirectional [A2X2](../../../types/bidirectional/BOOL/A2X2.md) tap into a unidirectional [A2X](../../../types/unidirectional/BOOL/A2X.md) chain. Rather than a simple 1:1 conversion, it uses **three** adapters: an incoming unidirectional A2X signal is both published onto the bidirectional A2X2 interface and — whatever A2X2 returns on its request side — output again as a standalone unidirectional A2X signal.

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

- **A2X_IN** (Socket): unidirectional UP/DOWN source, of type `adapter::types::unidirectional::A2X`
- **A2X2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `A2X_IN` and whose incoming side is forwarded to `A2X_OUT`, of type `adapter::types::bidirectional::A2X2`
- **A2X_OUT** (Plug): mirrors the incoming (request) side of `A2X2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::A2X`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `A2X_IN` (`E_UP`/`UP`, `E_DOWN`/`DOWN`) is published directly onto the outgoing side of `A2X2_BIDIR` (`EO_UP`/`DO_UP`, `EO_DOWN`/`DO_DOWN`) — so A2X2_BIDIR reports outward the same UP/DOWN signal coming in via A2X_IN. Conversely, whatever `A2X2_BIDIR` receives on its request side (`EI_UP`/`DI_UP`, `EI_DOWN`/`DI_DOWN` — i.e. whatever a bidirectional peer attached to A2X2_BIDIR "sends back") is output unchanged as a standalone unidirectional signal via the plug `A2X_OUT`. A2X2_BIDIR thus acts as a tap point that doesn't break the unidirectional chain but extends it with a bidirectional observation/injection point.

## Technical Details

- Three adapters instead of two: the incoming signal direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `A2X_OUT` only reflects what comes back via `A2X2_BIDIR` from an attached bidirectional peer — without such a peer, `A2X_OUT` stays idle

## State Overview

The block is stateless:

- A2X_IN.E_UP → A2X2_BIDIR.EO_UP, A2X_IN.UP → A2X2_BIDIR.DO_UP
- A2X_IN.E_DOWN → A2X2_BIDIR.EO_DOWN, A2X_IN.DOWN → A2X2_BIDIR.DO_DOWN
- A2X2_BIDIR.EI_UP → A2X_OUT.E_UP, A2X2_BIDIR.DI_UP → A2X_OUT.UP
- A2X2_BIDIR.EI_DOWN → A2X_OUT.E_DOWN, A2X2_BIDIR.DI_DOWN → A2X_OUT.DOWN

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional A2X signal chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display the status of a unidirectional signal source and send commands back
- Bridging a unidirectional A2X zone and a bidirectional A2X2 zone

## ⚖️ Comparison with Similar Blocks

[A2X2_TO_A2X](A2X2_TO_A2X.md) is the mirror image of this block — there, `A2X2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between the single-channel adapters, see the conversion blocks between [AX](../../../types/unidirectional/BOOL/AX.md) and [AX2](../../../types/bidirectional/BOOL/AX2.md) in the same library.

## Conclusion

A2X_TO_A2X2 is not a simple converter but a tap point: it makes a unidirectional A2X signal visible at a bidirectional A2X2 point without breaking the original unidirectional signal chain, while forwarding the request signal received there as a standalone A2X signal.
