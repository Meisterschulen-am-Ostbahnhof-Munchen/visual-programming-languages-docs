# A2X2_2X_TO_BOOL

![A2X2_2X_TO_BOOL](A2X2_2X_TO_BOOL.svg)

* * * * * * * * * *

## Introduction

The A2X2_2X_TO_BOOL function block is the socket counterpart of [A2X2_BOOL_TO_2X](A2X2_BOOL_TO_2X.md): it translates the bidirectional [A2X2](../../../types/bidirectional/BOOL/A2X2.md) adapter format back into two plain BOOL channels (UP and DOWN) by exposing an A2X2 socket.

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

- **A2X2_IN** (Socket): input adapter of type `adapter::types::bidirectional::A2X2`

## Functionality

When the socket `A2X2_IN` receives events on its indication side (`EO_UP`/`DO_UP` or `EO_DOWN`/`DO_DOWN`), they are immediately reported outward as `CNF_UP`/`IN_UP` or `CNF_DOWN`/`IN_DOWN`. Conversely, when a `REQ_UP` or `REQ_DOWN` event arrives, the corresponding `OUT_UP`/`OUT_DOWN` value is sent out via the socket (`EI_UP`/`DI_UP` or `EI_DOWN`/`DI_DOWN`). Both channels operate completely independently of each other.

## Technical Details

- Pure 1:1 pass-through, no internal state, no gates or logic blocks needed
- Uses an A2X2 socket, i.e. this block is the counterpart that an A2X2 plug connects to
- Identical interface to [A2X2_BOOL_TO_2X](A2X2_BOOL_TO_2X.md), only the adapter role (socket instead of plug) differs

## State Overview

The block is stateless; every connection acts immediately and directly:

- A2X2_IN.EO_UP → CNF_UP, A2X2_IN.DO_UP → IN_UP
- A2X2_IN.EO_DOWN → CNF_DOWN, A2X2_IN.DO_DOWN → IN_DOWN
- REQ_UP → A2X2_IN.EI_UP, OUT_UP → A2X2_IN.DI_UP
- REQ_DOWN → A2X2_IN.EI_DOWN, OUT_DOWN → A2X2_IN.DI_DOWN

## Application Scenarios

- Reading the UP/DOWN channels of an A2X2 bus participant as plain BOOL signals
- Integrating an A2X2 endpoint into a classically wired controller
- Test blocks acting as the counterpart of A2X2_BOOL_TO_2X

## ⚖️ Comparison with Similar Blocks

The plug counterpart is [A2X2_BOOL_TO_2X](A2X2_BOOL_TO_2X.md). For the unidirectional case, see [A2X_2X_TO_BOOL](../../unidirectional/BOOL/A2X_2X_TO_BOOL.md). The single-channel bidirectional predecessor is [AX2_X_TO_BOOL](AX2_X_TO_BOOL.md).

## Conclusion

A2X2_2X_TO_BOOL is the direct counterpart of A2X2_BOOL_TO_2X and makes an A2X2 bus signal usable as two plain BOOL channels for the rest of the application.
