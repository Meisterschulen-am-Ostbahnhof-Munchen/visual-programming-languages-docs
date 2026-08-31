# A2X2_4AX_TO_2X

![A2X2_4AX_TO_2X](A2X2_4AX_TO_2X.svg)

* * * * * * * * * *

## Introduction

The A2X2_4AX_TO_2X function block is the inverse of [A2X2_2X_TO_4AX](A2X2_2X_TO_4AX.md): it composes an [A2X2](../../../types/bidirectional/BOOL/A2X2.md) plug from **four** unidirectional [AX](../../../types/unidirectional/BOOL/AX.md) adapters. Two channels (UP/DOWN) × two directions (indication/request) = four AX.

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

- **A2X2_OUT** (Plug): composed output of type `adapter::types::bidirectional::A2X2`
- **REQ_UP** (Plug): UP request, published outward from `A2X2_OUT.EI_UP`, of type `adapter::types::unidirectional::AX`
- **REQ_DOWN** (Plug): DOWN request, published outward from `A2X2_OUT.EI_DOWN`, of type `adapter::types::unidirectional::AX`
- **IND_UP** (Socket): UP indication, received from outside and forwarded to `A2X2_OUT.EO_UP`, of type `adapter::types::unidirectional::AX`
- **IND_DOWN** (Socket): DOWN indication, received from outside and forwarded to `A2X2_OUT.EO_DOWN`, of type `adapter::types::unidirectional::AX`

## Functionality

Whatever arrives from outside at the unidirectional sockets `IND_UP`/`IND_DOWN` is passed through to the indication side of the A2X2 plug (`EO_UP`/`DO_UP` or `EO_DOWN`/`DO_DOWN`). Conversely, whatever the A2X2 plug receives on its request side (`EI_UP`/`DI_UP` or `EI_DOWN`/`DI_DOWN`) is published via the unidirectional plugs `REQ_UP`/`REQ_DOWN`.

## Technical Details

- Four separate AX adapters instead of two AX2, because AX does not combine an `EventInputs`/`EventOutputs` pair in one adapter — each direction needs its own adapter
- Pure wiring, no logic or state
- Every destination variable has exactly one writer, no fan-in on data connections

## State Overview

The block is stateless:

- IND_UP.E1 → A2X2_OUT.EO_UP, IND_UP.D1 → A2X2_OUT.DO_UP
- IND_DOWN.E1 → A2X2_OUT.EO_DOWN, IND_DOWN.D1 → A2X2_OUT.DO_DOWN
- A2X2_OUT.EI_UP → REQ_UP.E1, A2X2_OUT.DI_UP → REQ_UP.D1
- A2X2_OUT.EI_DOWN → REQ_DOWN.E1, A2X2_OUT.DI_DOWN → REQ_DOWN.D1

## Application Scenarios

- Building an A2X2 endpoint from four already existing unidirectional AX signals
- Migration scenarios where an existing AX infrastructure is gradually converted to A2X2
- Systems where bidirectional AX2 adapters are unavailable or undesired

## ⚖️ Comparison with Similar Blocks

For the same task (composing A2X2), [A2X2_2AX2_TO_2X](A2X2_2AX2_TO_2X.md) offers a simpler alternative that only needs two bidirectional [AX2](../../../types/bidirectional/BOOL/AX2.md) instead of four unidirectional AX — where AX2 infrastructure is available, that is the leaner solution. The counterpart to this block is [A2X2_2X_TO_4AX](A2X2_2X_TO_4AX.md), which decomposes an A2X2 back into four AX.

## Conclusion

A2X2_4AX_TO_2X is the right choice when an A2X2 endpoint must be built from purely unidirectional AX infrastructure — at the cost of twice as many adapters as the AX2-based alternative.
