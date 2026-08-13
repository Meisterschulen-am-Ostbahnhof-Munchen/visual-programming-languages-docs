# ALI_AUI_DEMUX_2

![ALI_AUI_DEMUX_2](ALI_AUI_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

`ALI_AUI_DEMUX_2` is the adapter-based variant of the generic demultiplexer for data type `LINT`. Unlike [ALI_DEMUX_2](ALI_DEMUX_2.md), it does not receive the selection index through a REQ event with an associated K data input, but through its own adapter socket **K** of type `AUI` ("Adapter Unidirectional Interface"). This lets the index be fed directly from another block with a matching `AUI` plug, without wiring a separate event and data line for it.

## Interface Structure

### **Event Inputs**

- No explicit event inputs on the block itself. The index is received exclusively through the adapter socket **K**: as soon as the `AUI` plug connected there fires its internal event `E1` carrying the data value `D1`, `ALI_AUI_DEMUX_2` evaluates the index internally and triggers processing.

### **Event Outputs**

- **CNF**: confirms that the index received via K has been evaluated and the target plug updated accordingly.

### **Data Inputs**

- No direct data inputs. The index (`UINT`, 0-based) arrives exclusively as the `D1` value of the `AUI` adapter connected to socket **K**.

### **Data Outputs**

- No direct data outputs.

### **Adapters**

- **K** (Socket, type `AUI`): index input -- selects the active input/output through the adapter's own `E1`/`D1` event.
- **IN** (Socket): input adapter carrying the 64-bit signed integer to forward, routed to exactly one of the outputs (ALI adapter type).
- **OUT1** (Plug): output adapter 1 of 2 (ALI adapter type).
- **OUT2** (Plug): output adapter 2 of 2 (ALI adapter type).

## Functionality

`ALI_AUI_DEMUX_2` receives a value on socket **IN** and forwards it to exactly one of the 2 output plugs `OUT1` … `OUT2`. Which output is written is decided by the index arriving on the adapter socket **K** (type `AUI`): as soon as the `AUI` plug connected to K fires its internal `E1` event carrying the data value `D1`, `ALI_AUI_DEMUX_2` interprets that value as a 0-based index (`0` … `1`), writes the input value to the corresponding `OUT` plug and triggers that plug's adapter event. `ALI_AUI_DEMUX_2` then confirms completion via the **CNF** event.

## Technical Details

- Adapter-based index input instead of the classic REQ/K input pair -- reduces wiring when the index is already available as an `AUI` adapter.
- Generic implementation (`GEN_ALI_AUI_DEMUX`) -- shared across all port counts of this block family (ALI_AUI_DEMUX_2 … ALI_AUI_DEMUX_5).
- **Change detection**: the written output plug is only updated -- and its adapter event only sent -- when the new value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates for downstream peers.

## State Overview

The block is stateless with respect to any sequencing logic: it waits for the `E1` event on socket **K**, evaluates the index carried with it once it arrives, updates the affected adapter plug and reports completion via **CNF**. No state beyond the most recently written adapter value is kept between calls.

## Application Scenarios

- Distributing a 64-bit signed integer to up to 2 downstream consumers, selected via an adapter-carried index
- Routing in modules that already receive the selection index as an AUI adapter link from an upstream block (no separate REQ/K pair needed)
- Building cascadable distributor networks where the index itself originates from another AUI-based block

## ⚖️ Comparison with Similar Blocks

Compare with [ALI_DEMUX_2](ALI_DEMUX_2.md) (same distribution logic, but the index arrives through a classic **REQ** event plus **K** data input instead of an adapter).

Compare with [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md), which demultiplexes purely on events without any adapter concept.

## Conclusion

`ALI_AUI_DEMUX_2` carries the demultiplexer logic of the `ALI_DEMUX_2` family over to a purely adapter-based index supply. This makes it the right choice whenever the selection index is already available as an `AUI` adapter from another block and no additional event/data wiring for the index is wanted.
