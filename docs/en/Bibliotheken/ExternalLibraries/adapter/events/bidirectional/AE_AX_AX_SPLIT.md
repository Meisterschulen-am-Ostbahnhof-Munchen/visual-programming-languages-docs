# AE_AX_AX_SPLIT

![AE_AX_AX_SPLIT](AE_AX_AX_SPLIT.svg)

* * * * * * * * * *

## Introduction

The AE_AX_AX_SPLIT is a composite function block that passes an incoming AE_AX event unchanged from its socket `IN` to the plug `OUT`, and additionally mirrors the state (event + bool) reported on the backward channel of `OUT` to the outside via a third, unidirectional `AX_OUT` plug. This allows the state of a downstream chain to be tapped in parallel at a second point without interrupting the actual AE_AX connection.

## Interface Structure

### **Event Inputs**

*No direct event inputs available – events arrive via the adapter sockets/plugs*

### **Event Outputs**

*No direct event outputs available*

### **Data Inputs**

*No data inputs available*

### **Data Outputs**

*No data outputs available*

### **Adapters**

- **IN**: Bidirectional adapter socket of type `adapter::types::bidirectional::AE_AX` (input)
- **OUT**: Bidirectional adapter plug of type `adapter::types::bidirectional::AE_AX` (output)
- **AX_OUT**: Unidirectional adapter plug of type `adapter::types::unidirectional::AX`, mirrors the AE_AX backward channel (state)

## Functionality

1. Every event arriving at `IN.E1` is forwarded unchanged to `OUT.E1` – the forward direction is passed through 1:1.
2. The backward-channel event `OUT.EI1` (together with its associated datum `OUT.DI1`) is relayed back to `IN.EI1`/`IN.DI1` and, at the same time, forwarded to `AX_OUT.E1`/`AX_OUT.D1`.
3. As a result, the state reported via `OUT` is visible at two points: at the original socket `IN` (as a pure passthrough would also provide) and additionally, in isolation, at the `AX_OUT` plug.

## Technical Features

- Pure event/data connections (`FBNetwork`), no own logic or state management
- The forward direction (socket → plug) is a simple 1:1 passthrough
- The backward channel is duplicated rather than split: both destinations (`IN` and `AX_OUT`) receive the same information

## State Overview

The function block has no internal state and operates statelessly. Every incoming event is immediately forwarded or mirrored.

## Application Scenarios

- Additional, isolated tapping of the AE_AX backward channel (e.g. for a separate display or logging) without altering the actual connection between `IN` and `OUT`
- Building diagnostic/monitoring paths in AE_AX-based control networks

## ⚖️ Comparison with similar building blocks

Compared to [AE2_SPLIT_MERGE](AE2_SPLIT_MERGE.md), which distributes/merges the forward and backward directions between two separate, isolated adapters, AE_AX_AX_SPLIT is a pure passthrough between `IN` and `OUT` with an additional mirror output for the backward channel – the ASR_AX and ASRT_AX variants [ASR_AX_AX_SPLIT](ASR_AX_AX_SPLIT.md) and [ASRT_AX_AX_SPLIT](ASRT_AX_AX_SPLIT.md) follow the same pattern with two and three forward events, respectively.

## Conclusion

AE_AX_AX_SPLIT makes the AX backward channel of an AE_AX adapter pair additionally available at a second point in the network, without interrupting or altering the actual signal chain.
