# AX_TO_AX2

![AX_TO_AX2](AX_TO_AX2.svg)

* * * * * * * * * *

## Introduction

The AX_TO_AX2 function block inserts a bidirectional [AX2](../../../types/bidirectional/BOOL/AX2.md) tap into a unidirectional [AX](../../../types/unidirectional/BOOL/AX.md) chain. Rather than a simple 1:1 conversion, it uses **three** adapters: an incoming unidirectional AX signal is both published onto the bidirectional AX2 interface and — whatever AX2 returns on its request side — output again as a standalone unidirectional AX signal.

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

- **AX_IN** (Socket): unidirectional BOOL source, of type `adapter::types::unidirectional::AX`
- **AX2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `AX_IN` and whose incoming side is forwarded to `AX_OUT`, of type `adapter::types::bidirectional::AX2`
- **AX_OUT** (Plug): mirrors the incoming (request) side of `AX2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AX`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `AX_IN` (`E1`/`D1`) is published directly onto the outgoing side of `AX2_BIDIR` (`EO1`/`DO1`) — so AX2_BIDIR reports outward the same signal coming in via AX_IN. Conversely, whatever `AX2_BIDIR` receives on its request side (`EI1`/`DI1` — i.e. whatever a bidirectional peer attached to AX2_BIDIR "sends back") is output unchanged as a standalone unidirectional signal via the plug `AX_OUT`. AX2_BIDIR thus acts as a tap point that doesn't break the unidirectional chain but extends it with a bidirectional observation/injection point.

## Technical Details

- Three adapters instead of two: the incoming signal direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AX_OUT` only reflects what comes back via `AX2_BIDIR` from an attached bidirectional peer — without such a peer, `AX_OUT` stays idle

## State Overview

The block is stateless:

- AX_IN.E1 → AX2_BIDIR.EO1, AX_IN.D1 → AX2_BIDIR.DO1
- AX2_BIDIR.EI1 → AX_OUT.E1, AX2_BIDIR.DI1 → AX_OUT.D1

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional AX signal chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display the status of a unidirectional signal source and send commands back
- Bridging a unidirectional AX zone and a bidirectional AX2 zone

## ⚖️ Comparison with Similar Blocks

[AX2_TO_AX](AX2_TO_AX.md) is the mirror image of this block — there, `AX2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between a plain BOOL signal and AX2, see [AX2_BOOL_TO_X](AX2_BOOL_TO_X.md)/[AX2_X_TO_BOOL](AX2_X_TO_BOOL.md). The 2-channel A2X/A2X2 counterpart is [A2X_TO_A2X2](A2X_TO_A2X2.md).

## Conclusion

AX_TO_AX2 is not a simple converter but a tap point: it makes a unidirectional AX signal visible at a bidirectional AX2 point without breaking the original unidirectional signal chain, while forwarding the request signal received there as a standalone AX signal.
