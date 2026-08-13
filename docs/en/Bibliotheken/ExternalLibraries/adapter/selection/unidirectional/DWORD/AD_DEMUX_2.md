# AD_DEMUX_2

![AD_DEMUX_2](./AD_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

The function block `AD_DEMUX_2` is a generic AD demultiplexer. It distributes an incoming AD adapter data stream to one of two possible output adapters, controlled by an index value. The block operates in an event-driven manner, thus enabling flexible channel selection in industrial automation.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Sets the index `K` and triggers the forwarding of the AD input to the corresponding output. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirms successful completion of the demultiplex operation. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|-----------------------------|
| `K` | UINT | Index (0-based) for selecting the output (0 → OUT1, 1 → OUT2) |

### **Data Outputs**

No data outputs available.

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----------------------------------|-------------------------------------|
Socket | `IN` | `adapter::types::unidirectional::AD` | Input Adapter (signal to be distributed) |
Plug | `OUT1` | `adapter::types::unidirectional::AD` | First Output Adapter (Index 0) |
Plug | `OUT2` | `adapter::types::unidirectional::AD` | Second Output Adapter (Index 1) |

## Functionality

When the event `REQ` is triggered, the AD adapter connected to socket `IN` is forwarded to one of the two plugs according to the current value of `K`:

- `K = 0` → Connection from `IN` to `OUT1`
- `K = 1` → Connection from `IN` to `OUT2`

After the switchover is complete, the event `CNF` is output. The function block operates without internal states and executes the switchover within a single event cycle.

...
## Technical Features

- **Generic Type:** The function block (FB) is declared as a generic AD demultiplexer (`GEN_AD_DEMUX`). It can be used for any `adapter::types::unidirectional::AD` adapter, as long as the specific type is passed at runtime.
- **Eclipse 4diac Specific:** The attributes `GenericClassName` and `TypeHash` are used for type checking and the runtime environment of the Eclipse 4diac IDE.
- **No State Machine:** Processing is purely event-driven without sequential states; therefore, the response time is minimal.

## State Overview

The FB does not have an explicit state machine (ECC). All logic is limited to event processing at `REQ` and the immediate forwarding of the adapter data. There are no wait or operating states.

## Application Scenarios

- **Channel Selection:** In a controller, an analog or digital value (via AD adapter) is to be passed on to different devices depending on a condition.
- **Redundancy Switching:** A sensor value can be switched to two different evaluation units if required.
- **Test and Simulation Environments:** Switching between real and simulated adapters during commissioning.

## Comparison with Similar Function Blocks

- **AD_MUX (Multiplexer):** Works in reverse – selects one from several input adapters and passes it on to a single output.
- **AD_DEMUX with More Outputs:** For more than two outputs, function blocks such as `AD_DEMUX_4` or a more generic variant with a configurable number of channels are available.
- **Manual Switching via Logic:** An alternative could be a simple selector block, which, however, does not offer adapter interfaces and requires separate data and event connections.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The `AD_DEMUX_2` is a compact, generic function block for the simple demultiplexing of AD adapters. Its clear interface, purely event-driven operation, and support for generic types make it a flexible tool for many automation tasks where a signal needs to be selectively switched to one of two paths.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
