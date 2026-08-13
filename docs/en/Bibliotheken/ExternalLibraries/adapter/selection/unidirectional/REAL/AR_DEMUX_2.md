# AR_DEMUX_2

![AR_DEMUX_2](./AR_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

The function block **AR_DEMUX_2** is a generic demultiplexer for unidirectional AR adapters. It forwards an incoming AR adapter value (via socket `IN`) to one of two possible output adapters (`OUT1` or `OUT2`). The target output is selected via an index `K`, which is set by an event `REQ`. This block is typically used to selectively route a data or signal path to different subsequent function blocks.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Requests the transfer of index `K` and triggers the demultiplex operation. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirms the successful execution of the demultiplex operation. |

### **Data Inputs**

| Name | Type | Description |
|------|-------|--------------------------|
| `K` | UINT | Integer index (1-based) for selecting the output (1 → OUT1, 2 → OUT2). |

### **Data Outputs**

No dedicated data outputs; output is exclusively via the adapters `OUT1` and `OUT2`.

### **Adapters**

| Type | Name | Direction | Description |
|--------|-------|----------|-------------------------------------------------|
| Socket | `IN` | Input | Unidirectional AR adapter that is demultiplexed. |
| Plug | `OUT1`| Output | First destination adapter for the demultiplexed value. |
| Plug | `OUT2`| Output | Second destination adapter for the demultiplexed value. |

## Functionality

1. The function block waits for an event at input `REQ`.
2. Upon receiving this event, the current value of data input `K` is read.
3. The value of the AR adapter connected to `IN` is transferred to the output adapter determined by `K`:
- `K = 1` → Output `OUT1`
- `K = 2` → Output `OUT2`
- For other values of `K` (e.g., 0 or >2), no action is performed (the output state remains unchanged).
4. After successful transfer, the event `CNF` is output.

The operation is event-driven and operates without an internal buffer – each `REQ` call immediately demultiplexes the current `IN` value.

## Technical Features

- The function block is declared as a **generic FB** (GenericClassName = `GEN_AR_DEMUX`), meaning it can be adapted to different AR adapter types through type-specific parameterization.
- The interface uses only unidirectional adapters, ensuring a clear separation of data flow direction.
- The index `K` is mapped as `UINT`; the count starts at 1 for the first output.
- The runtime environment must provide the adapter types (`adapter::types::unidirectional::AR`).

## State Overview

The function block does not have an explicit state diagram (ECC) in the provided definition. It behaves like a **combinatorial** function block with event-driven triggering:

- **IDLE** – Waiting for `REQ`
- **ACTIVE** – Processing the index and transferring the adapter (takes a single cycle)
- **DONE** – Outputting `CNF`, returning to IDLE

Since no internal state variables exist, the behavior is deterministic and concurrently safe.

## Application Scenarios

- **Route Switching**: In an industrial controller, AR_DEMUX_2 can be used to selectively route an incoming sensor or actuator adapter to two different processing logics.
- **Redundancy Switching**: In case of a fault, a primary signal is switched to a secondary path.
- **Test/Production Mode**: Depending on the operating mode, the same data stream is passed on to a test or production unit.

## Comparison with Similar Components

- **AR_MUX_2** (Multiplexer): A multiplexer selects one input adapter from several and routes it to a single output. The AR_DEMUX_2 works in exactly the opposite way: one input is distributed to multiple outputs.
- **AR_SELECTOR**: A simple switch that also selects between two paths, but often without an index event (e.g., via a Boolean input). The AR_DEMUX_2 offers extended selection options through the UINT index and is scalable to multiple outputs (here: two).
- **SWITCH function blocks (IEC 61499 standard)**: Many standard libraries contain generic demultiplexers for simple data types (e.g., ANY). The AR_DEMUX_2 abstracts the adapter type and is specifically optimized for unidirectional AR interfaces.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AR_DEMUX_2** is a compact, generic demultiplexer for unidirectional AR adapters. It is ideally suited for switching an incoming adapter path to up to two outputs in IEC 61499-based systems. The clearly defined interface with index input and acknowledgment event enables reliable and deterministic switching in automation and control applications. Due to its generic nature, the function block can be reused for different AR types without modifying its internal behavior.
