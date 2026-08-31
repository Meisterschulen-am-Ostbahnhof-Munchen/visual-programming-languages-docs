# AB_AUI_DEMUX_2

![AB_AUI_DEMUX_2](AB_AUI_DEMUX_2.svg)

* * * * * * * * * *

## Introduction

`AB_AUI_DEMUX_2` is the adapter-based variant of the generic demultiplexer for data type `BYTE`. Unlike `AB_DEMUX_2`, it does not receive the selection index through a REQ event with an associated K data input, but through its own adapter socket **K** of type `AUI` ("Adapter Unidirectional Interface"). This lets the index be fed directly from another block with a matching `AUI` plug, without wiring a separate event and data line for it.

## Interface Structure

### **Event Inputs**

- No explicit event inputs on the block itself. The index is received exclusively through the adapter socket **K**: as soon as the `AUI` plug connected there fires its internal event `E1` carrying the data value `D1`, `AB_AUI_DEMUX_2` evaluates the index internally and triggers processing.

### **Event Outputs**

- **CNF**: Always sent once an event from the selector adapter `K` has been processed -- regardless of whether the selected output changed.

### **Data Inputs**

- No direct data inputs. The index (`UINT`, 0-based) arrives exclusively as the `D1` value of the `AUI` adapter connected to socket **K**.

### **Data Outputs**

- No direct data outputs.

### **Adapters**

- **K** (Socket, type `AUI`): index input -- selects the active input/output through the adapter's own `E1`/`D1` event.
- **IN** (Socket): input adapter carrying the byte value (8-bit bit pattern) to forward, routed to exactly one of the outputs (AB adapter type).
- **OUT1** (Plug): output adapter 1 of 2 (AB adapter type).
- **OUT2** (Plug): output adapter 2 of 2 (AB adapter type).

## Functionality

The function block re-evaluates the current value of **K** on every incoming event -- both on an event from the selector adapter `K` (type `AUI`) and on an event from the input adapter `IN`:

1. The current value of `K.D1` determines which of the 2 output adapters (`OUT1` … `OUT2`) is currently selected.
2. The data value of `IN` is compared against the value currently held on the selected output. Only on an actual change is that output rewritten and its adapter event sent (see "Change Detection" below).
3. If the triggering event comes from the selector adapter `K`, the `CNF` event is additionally always sent -- regardless of whether the selected output changed -- to confirm that the index update was processed.

As a result, a pure change of `K` alone also propagates the current value of `IN` to the newly selected output immediately, even if `IN` hasn't changed since its own last event.

## Technical Details

- Adapter-based index input instead of the classic REQ/K input pair -- reduces wiring when the index is already available as an `AUI` adapter.
- Generic implementation (`GEN_AB_AUI_DEMUX`) -- shared across all port counts of this block family (AB_AUI_DEMUX_2 … AB_AUI_DEMUX_5).
- **Change detection**: the written output plug is only updated -- and its adapter event only sent -- when the new value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates for downstream peers.

## State Overview

The function block has no explicit state machine; instead it re-evaluates the current value of `K.D1` on every incoming event:

- **Any event** (selector adapter `K` or `IN`) → determine the currently selected output, update it with the current `IN` value on a change and send its adapter event.
- **Additionally on an event from `K`** → `CNF` is always sent, regardless of whether the selected output changed.

## Application Scenarios

- Distributing a byte value (8-bit bit pattern) to up to 2 downstream consumers, selected via an adapter-carried index
- Routing in modules that already receive the selection index as an AUI adapter link from an upstream block (no separate REQ/K pair needed)
- Building cascadable distributor networks where the index itself originates from another AUI-based block

## ⚖️ Comparison with Similar Blocks

Compare with `AB_DEMUX_2` (same distribution logic, but the index arrives through a classic **REQ** event plus **K** data input instead of an adapter).

Compare with [E_DEMUX](../../../../../StandardLibraries/events/E_DEMUX.md), which demultiplexes purely on events without any adapter concept.

- **[`AB_AUI_DEMUX_2_UNGATED`](AB_AUI_DEMUX_2_UNGATED.md)**: Ungated variant – updates the output on every run, even without a value change.

## Conclusion

`AB_AUI_DEMUX_2` carries the demultiplexer logic of the `AB_DEMUX_2` family over to a purely adapter-based index supply. This makes it the right choice whenever the selection index is already available as an `AUI` adapter from another block and no additional event/data wiring for the index is wanted.
