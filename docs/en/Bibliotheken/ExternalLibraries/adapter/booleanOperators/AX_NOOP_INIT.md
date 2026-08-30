# AX_NOOP_INIT

![AX_NOOP_INIT](./AX_NOOP_INIT.svg)

* * * * * * * * * *

## Introduction

The function block `AX_NOOP_INIT` is a no-operation block that forwards incoming events and data from an adapter interface unchanged to an output interface. It also has an initialization function that, upon arrival of the INIT event, triggers both the INITO acknowledgment and the adapter's output event. It serves as a simple pass-through or placeholder block in automation technology.

## Interface Structure

### **Event Inputs**

- **INIT** (Type: `EInit`): Initialization request. Upon arrival, it triggers the event outputs `INITO` and `OUT.E1`.

### **Event Outputs**

- **INITO** (Type: `EInit`): Initialization confirmation. Triggered directly by `INIT`.

### **Data Inputs**

This function block does not have separate data inputs at the top level. All data is transmitted via the incoming adapter (`IN`).

### **Data Outputs**

This function block does not have separate data outputs at the top level. All data is transmitted via the outgoing adapter (`OUT`).

### **Adapters**

- **IN** (Socket): Input adapter of type `adapter::types::unidirectional::AX`. Provides an event interface `E1` and a data interface `D1`.
- **OUT** (Plug): Output adapter of type `adapter::types::unidirectional::AX`. Provides an event interface `E1` and a data interface `D1`.

## Functionality

The function block operates as a simple pass-through module:

1. **Event Forwarding**:

- The INIT event is forwarded to `INITO` and to `OUT.E1`.
- The event `IN.E1` is passed directly to `OUT.E1`.
1. **Data Forwarding**:

- The value of `IN.D1` is copied unchanged to `OUT.D1`.

No processing or modification of the data takes place. The function block is stateless and simply combines the signal and data paths.

## Technical Features

- The function block combines the pure pass-through function of a no-operation function block with an initialization-controlled output to the output adapter.
- The use of adapters (plug/socket) enables clean encapsulation and reusability of the interface definition.
- There are no internal states or timing behaviors – the response occurs immediately upon event input.

## State Overview

The `AX_NOOP_INIT` has no states of its own. It reacts immediately to every incoming event and forwards it along with the associated data. A state machine is not present.

## Application Scenarios

- **Initialization Cascades**: When multiple components in a chain need to be initialized, `AX_NOOP_INIT` can serve as a link, both acknowledging an INIT request and passing it on to the subsequent component.
- **Test and Simulation Environments**: As a placeholder to bridge interfaces and test functionalities without actual logic.
- **Adapter Passthrough**: When an adapter signal needs to be passed unchanged from a source to a destination without additional processing.

## Comparison with Similar Components

A simple `AX_NOOP` (without INIT) would only pass through the IN/OUT events and data, but would not generate a separate initialization acknowledgment (`INITO`). The `AX_NOOP_INIT` extends this functionality with INIT handling, allowing it to be used directly in initialization processes.

## Conclusion

The `AX_NOOP_INIT` is a simple yet useful function block for passing events and data at the adapter level. Its INIT functionality makes it particularly valuable in initialization chains or as a replacement for a test block. Its stateless nature makes it easy to understand and resource-efficient.
