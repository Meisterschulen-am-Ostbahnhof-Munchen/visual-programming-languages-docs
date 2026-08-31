# AB_TO_AB2

![AB_TO_AB2](AB_TO_AB2.svg)

* * * * * * * * * *

## Introduction

The AB_TO_AB2 function block inserts a bidirectional [AB2](../../../types/bidirectional/BYTE/AB2.md) tap into a unidirectional [AB](../../../types/unidirectional/BYTE/AB.md) chain. Rather than a simple 1:1 conversion, it uses **three** adapters: an incoming unidirectional AB signal is both published onto the bidirectional AB2 interface and — whatever AB2 returns on its request side — output again as a standalone unidirectional AB signal.

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

- **AB_IN** (Socket): unidirectional BYTE source, of type `adapter::types::unidirectional::AB`
- **AB2_BIDIR** (Plug): bidirectional tap whose outgoing side is fed by `AB_IN` and whose incoming side is forwarded to `AB_OUT`, of type `adapter::types::bidirectional::AB2`
- **AB_OUT** (Plug): mirrors the incoming (request) side of `AB2_BIDIR` as a unidirectional signal, of type `adapter::types::unidirectional::AB`

## Functionality

The block operates in two directions at once: whatever arrives at the socket `AB_IN` (`E1`/`D1`) is published directly onto the outgoing side of `AB2_BIDIR` (`EO1`/`DO1`) — so AB2_BIDIR reports outward the same signal coming in via AB_IN. Conversely, whatever `AB2_BIDIR` receives on its request side (`EI1`/`DI1` — i.e. whatever a bidirectional peer attached to AB2_BIDIR "sends back") is output unchanged as a standalone unidirectional signal via the plug `AB_OUT`. AB2_BIDIR thus acts as a tap point that doesn't break the unidirectional chain but extends it with a bidirectional observation/injection point.

## Technical Details

- Three adapters instead of two: the incoming signal direction and the direction coming back from the tap are deliberately kept separate rather than mixed
- Pure wiring, no logic or state, every destination variable has exactly one writer
- `AB_OUT` only reflects what comes back via `AB2_BIDIR` from an attached bidirectional peer — without such a peer, `AB_OUT` stays idle

## State Overview

The block is stateless:

- AB_IN.E1 → AB2_BIDIR.EO1, AB_IN.D1 → AB2_BIDIR.DO1
- AB2_BIDIR.EI1 → AB_OUT.E1, AB2_BIDIR.DI1 → AB_OUT.D1

## Application Scenarios

- Retrofitting a bidirectional diagnostic or control point into an existing unidirectional AB signal chain without breaking it
- Systems where a bidirectional peer (e.g. an operator panel) needs to both display the status of a unidirectional byte signal source and send commands back
- Bridging a unidirectional AB zone and a bidirectional AB2 zone

## ⚖️ Comparison with Similar Blocks

[AB2_TO_AB](AB2_TO_AB.md) is the mirror image of this block — there, `AB2_BIDIR` sits as a socket on the left side. For a pure, non-tapping 1:1 conversion between a plain BYTE signal and AB2, see [AB2_B_TO_BYTE](AB2_B_TO_BYTE.md)/[AB2_BYTE_TO_B](AB2_BYTE_TO_B.md).

## Conclusion

AB_TO_AB2 is not a simple converter but a tap point: it makes a unidirectional AB signal visible at a bidirectional AB2 point without breaking the original unidirectional signal chain, while forwarding the request signal received there as a standalone AB signal.
