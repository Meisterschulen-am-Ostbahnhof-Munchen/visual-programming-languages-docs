# A2X2_2X_TO_4AX

![A2X2_2X_TO_4AX](A2X2_2X_TO_4AX.svg)

* * * * * * * * * *

## Introduction

The A2X2_2X_TO_4AX function block decomposes an [A2X2](../../../types/bidirectional/BOOL/A2X2.md) socket into **four** unidirectional [AX](../../../types/unidirectional/BOOL/AX.md) adapters. Since A2X2 has two channels (UP/DOWN) and each of them is itself bidirectional, representing it with unidirectional AX needs two AX per channel to cover both directions — one for the indication direction, one for the request direction. 2 channels × 2 directions = 4 AX.

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

- **A2X2_IN** (Socket): input to be decomposed, of type `adapter::types::bidirectional::A2X2`
- **REQ_UP** (Socket): UP request, received from outside and forwarded to `A2X2_IN.EI_UP`, of type `adapter::types::unidirectional::AX`
- **REQ_DOWN** (Socket): DOWN request, received from outside and forwarded to `A2X2_IN.EI_DOWN`, of type `adapter::types::unidirectional::AX`
- **IND_UP** (Plug): UP indication, published outward from `A2X2_IN.EO_UP`, of type `adapter::types::unidirectional::AX`
- **IND_DOWN** (Plug): DOWN indication, published outward from `A2X2_IN.EO_DOWN`, of type `adapter::types::unidirectional::AX`

## Functionality

Whatever the A2X2 socket receives on its indication side (`EO_UP`/`DO_UP` or `EO_DOWN`/`DO_DOWN`) is published unchanged via the unidirectional plugs `IND_UP`/`IND_DOWN`. Conversely, whatever arrives from outside at the unidirectional sockets `REQ_UP`/`REQ_DOWN` is forwarded to the request side of the A2X2 socket (`EI_UP`/`DI_UP` or `EI_DOWN`/`DI_DOWN`). This makes both directions of each channel available as their own plain unidirectional AX adapter.

## Technical Details

- Four separate AX adapters instead of two AX2, because AX does not combine an `EventInputs`/`EventOutputs` pair in one adapter — each direction needs its own adapter
- Pure wiring, no logic or state
- Every destination variable has exactly one writer, no fan-in on data connections

## State Overview

The block is stateless:

- A2X2_IN.EO_UP → IND_UP.E1, A2X2_IN.DO_UP → IND_UP.D1
- A2X2_IN.EO_DOWN → IND_DOWN.E1, A2X2_IN.DO_DOWN → IND_DOWN.D1
- REQ_UP.E1 → A2X2_IN.EI_UP, REQ_UP.D1 → A2X2_IN.DI_UP
- REQ_DOWN.E1 → A2X2_IN.EI_DOWN, REQ_DOWN.D1 → A2X2_IN.DI_DOWN

## Application Scenarios

- Connecting an A2X2 signal to infrastructure that only knows unidirectional AX adapters (e.g. older subsystems)
- Processing the request and indication directions separately, e.g. for independent logging or filtering
- Systems where bidirectional AX2 adapters are unavailable or undesired

## ⚖️ Comparison with Similar Blocks

For the same task (decomposing A2X2), [A2X2_2X_TO_2AX2](A2X2_2X_TO_2AX2.md) offers a simpler alternative that only needs two bidirectional [AX2](../../../types/bidirectional/BOOL/AX2.md) instead of four unidirectional AX — where AX2 infrastructure is available, that is the leaner solution. The counterpart to this block is [A2X2_4AX_TO_2X](A2X2_4AX_TO_2X.md), which recomposes an A2X2 from four AX.

## Conclusion

A2X2_2X_TO_4AX is the right choice when an A2X2 signal must be integrated into a purely unidirectional AX landscape — at the cost of twice as many adapters as the AX2-based alternative.
