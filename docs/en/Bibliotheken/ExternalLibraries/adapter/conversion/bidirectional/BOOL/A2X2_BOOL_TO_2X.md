# A2X2_BOOL_TO_2X

![A2X2_BOOL_TO_2X](A2X2_BOOL_TO_2X.svg)

* * * * * * * * * *

## Introduction

The A2X2_BOOL_TO_2X function block is a composite function block that translates two plain BOOL channels (UP and DOWN) into the bidirectional [A2X2](../../../types/bidirectional/BOOL/A2X2.md) adapter format. It exposes an A2X2 plug and maps each of the two channels independently through its own request/confirmation event pair.

## Interface Structure

### **Event Inputs**

- **REQ_UP**: request event for the UP channel, delivers `OUT_UP`
- **REQ_DOWN**: request event for the DOWN channel, delivers `OUT_DOWN`

### **Event Outputs**

- **CNF_UP**: confirmation event for the UP channel, delivers `IN_UP`
- **CNF_DOWN**: confirmation event for the DOWN channel, delivers `IN_DOWN`

### **Data Inputs**

- **OUT_UP**: BOOL, TRUE = forward, up, right, clockwise
- **OUT_DOWN**: BOOL, TRUE = backward, down, left, counter-clockwise

### **Data Outputs**

- **IN_UP**: BOOL, UP data from the adapter
- **IN_DOWN**: BOOL, DOWN data from the adapter

### **Adapters**

- **A2X2_OUT** (Plug): output adapter of type `adapter::types::bidirectional::A2X2`

## Functionality

When a `REQ_UP` event arrives, the current value of `OUT_UP` is sent out via `A2X2_OUT.EO_UP`/`A2X2_OUT.DO_UP`; the same happens for `REQ_DOWN`/`OUT_DOWN` via `EO_DOWN`/`DO_DOWN`. Conversely, whatever the adapter receives on its request side (`A2X2_OUT.EI_UP`/`A2X2_OUT.EI_DOWN` with `DI_UP`/`DI_DOWN`) is forwarded unchanged as `CNF_UP`/`IN_UP` and `CNF_DOWN`/`IN_DOWN` respectively. Both channels operate completely independently of each other.

## Technical Details

- Pure 1:1 pass-through, no internal state, no gates or logic blocks needed
- Each channel (UP/DOWN) has its own event pair — there is no shared variable that two sources would need to write at once
- Uses the A2X2 plug, i.e. this block acts as the "endpoint" that an A2X2 socket connects to

## State Overview

The block is stateless; every connection acts immediately and directly:

- REQ_UP → A2X2_OUT.EO_UP, OUT_UP → A2X2_OUT.DO_UP
- REQ_DOWN → A2X2_OUT.EO_DOWN, OUT_DOWN → A2X2_OUT.DO_DOWN
- A2X2_OUT.EI_UP → CNF_UP, A2X2_OUT.DI_UP → IN_UP
- A2X2_OUT.EI_DOWN → CNF_DOWN, A2X2_OUT.DI_DOWN → IN_DOWN

## Application Scenarios

- Connecting two plain BOOL signals (e.g. two buttons or limit switches for UP/DOWN) to an A2X2 bus system
- Test blocks that simulate A2X2 traffic without real hardware
- Bridging classic BOOL wiring and adapter-based subnetworks

## ⚖️ Comparison with Similar Blocks

The socket counterpart [A2X2_2X_TO_BOOL](A2X2_2X_TO_BOOL.md) has the same interface but uses an A2X2 socket instead of a plug. For the unidirectional case, [A2X_BOOL_TO_2X](../../unidirectional/BOOL/A2X_BOOL_TO_2X.md) implements the same basic idea but without a request side (only `E_UP`/`E_DOWN`). The single-channel bidirectional predecessor is [AX2_BOOL_TO_X](AX2_BOOL_TO_X.md), whose pattern this block doubles onto two independent channels.

## Conclusion

A2X2_BOOL_TO_2X is the simplest way to connect plain BOOL signals to an A2X2 adapter — no state, no logic, a direct 1:1 pass-through per channel.
