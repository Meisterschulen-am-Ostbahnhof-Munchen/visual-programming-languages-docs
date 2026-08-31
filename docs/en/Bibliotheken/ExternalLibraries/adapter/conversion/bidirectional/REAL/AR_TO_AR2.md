# AR_TO_AR2

![AR_TO_AR2](AR_TO_AR2.svg)

* * * * * * * * * *

## Introduction

The AR_TO_AR2 function block inserts a bidirectional [AR2](../../../types/bidirectional/REAL/AR2.md) tap into a unidirectional [AR](../../../types/unidirectional/REAL/AR.md) chain. Rather than a simple 1:1 conversion, it uses **three** adapters: an incoming unidirectional AR signal is both published onto the bidirectional AR2 interface and — whatever AR2 returns on its request side — output again as a standalone unidirectional AR signal.

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

- **AR_IN** (Socket): unidirectional REAL source, of type `adapter::types::unidirectional::AR`
- **AR2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `AR_IN` and whose incoming side is forwarded to `AR_OUT`, of type `adapter::types::bidirectional::AR2`
- **AR_OUT** (Plug): mirrors the incoming (request) side of `AR2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AR`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `AR_IN` (`E1`/`D1`) is published directly onto the outgoing side of `AR2_BIDIR` (`EO1`/`DO1`) — so AR2_BIDIR reports outward the same signal coming in via AR_IN. Conversely, whatever `AR2_BIDIR` receives on its request side (`EI1`/`DI1` — i.e. whatever a bidirectional peer attached to AR2_BIDIR "sends back") is output unchanged as a standalone unidirectional signal via the plug `AR_OUT`. AR2_BIDIR thus acts as a tap point that doesn't break the unidirectional chain but extends it with a bidirectional observation/injection point.

## Technical Details

- Three adapters instead of two: the incoming signal direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AR_OUT` only reflects what comes back via `AR2_BIDIR` from an attached bidirectional peer — without such a peer, `AR_OUT` stays idle

## State Overview

The block is stateless:

- AR_IN.E1 → AR2_BIDIR.EO1, AR_IN.D1 → AR2_BIDIR.DO1
- AR2_BIDIR.EI1 → AR_OUT.E1, AR2_BIDIR.DI1 → AR_OUT.D1

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional AR signal chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display the status of a unidirectional measurement source and send setpoints back
- Bridging a unidirectional AR zone and a bidirectional AR2 zone

## ⚖️ Comparison with Similar Blocks

[AR2_TO_AR](AR2_TO_AR.md) is the mirror image of this block — there, `AR2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between a plain REAL signal and AR2, see [AR2_R_TO_REAL](AR2_R_TO_REAL.md)/[AR2_REAL_TO_R](AR2_REAL_TO_R.md).

## Conclusion

AR_TO_AR2 is not a simple converter but a tap point: it makes a unidirectional AR signal visible at a bidirectional AR2 point without breaking the original unidirectional signal chain, while forwarding the request signal received there as a standalone AR signal.
