# AE_DEMUX_3
![AE_DEMUX_3](./AE_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **AE_DEMUX_3** is a generic AE demultiplexer.
It forwards an AE value received at the adapter input `IN` to one of three adapter outputs (`OUT1` to `OUT3`). The output is selected using the index `K`, which is evaluated when an event occurs at the input `REQ`.

`` The function block is implemented as a generic function block (GenericClassName `GEN_AE_DEMUX`) and is only specialized for the specific number of outputs at compile time or during instantiation.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Takes over the index `K` and forwards the adapter input to one of the three outputs |

### **Event Outputs**

| Event | Description |
|----------|---------------|
| `CNF` | Acknowledges the completed forwarding |

### **Data Inputs**

| Name | Type | Description |
|------|-------|--------------|
| `K` | UINT | Index of the selected output (valid values: 1, 2, or 3) |

### **Data Outputs**

*No direct data outputs are available. Output data is provided via the adapter outputs.*

### **Adapters**

| Adapter | Direction | Type | Description |
|---------|----------|--------------------------------------|--------------|
| `IN` | Socket | `adapter::types::unidirectional::AE` | Input AE Signal |
| `OUT1` | Plug | `adapter::types::unidirectional::AE` | First Output |
| `OUT2` | Plug | `adapter::types::unidirectional::AE` | Second Output |
| `OUT3` | Plug | `adapter::types::unidirectional::AE` | Third Output |

## Functionality

1. The function block waits for an event at input `REQ`.

2. The event triggers the reading of the integer value from data input `K`.

`` 3. Depending on the value of `K`, the AE value present at adapter socket `IN` is forwarded to one of the three adapter plugs:

- `K = 1` → Forwarding to `OUT1`
- `K = 2` → Forwarding to `OUT2`
- `K = 3` → Forwarding to `OUT3`

4. After successful forwarding, the event `CNF` is output.

If `K` is outside the valid range, the forwarding fails (`CNF` is still sent – depending on the implementation).

## Technical Features
- **Generic Function Block:** The function block is declared as generic (`GenericClassName = 'GEN_AE_DEMUX'`) and can be extended to other output numbers in the 4diac IDE.
- **Adapter-Based Interface:** Inputs and outputs are defined as adapters of type `adapter::types::unidirectional::AE`, enabling flexible coupling with other AE-compatible function blocks.
- **License and Origin:** The function block is provided under the Eclipse Public License 2.0 (Copyright 2026 HR Agrartechnik GmbH). The version information shows the author Franz Höpfinger and the date 2026-05-28.

## State Overview

An explicit state machine (ECC) is not defined in the present XML. Therefore, the behavior is assumed to be purely functional without internal states:

- For every `REQ` event, index evaluation and forwarding occur immediately.
- After the action, `CNF` is sent immediately.

## Application Scenarios
- **Signal Distribution in Automation Systems:** An incoming AE signal can be selectively forwarded to one of three downstream stations or subsystems.
- **Channel Selection:** In a communication chain, the data path is dynamically switched via `K`.
- **Test and Debugging Environments:** A test signal can be routed to various analyzers.

## Comparison with Similar Components
- **AE_DEMUX_2:** A demultiplexer with two outputs – same functionality, but fewer options.
- **AE_MUX_3 (Multiplexer):** The reverse component, combining multiple AE inputs into a single output.
- **Non-generic Demultiplexers:** These components have a fixed number of outputs and cannot be adapted to other configurations. The AE_DEMUX_3 offers greater flexibility due to its generic approach.

## Conclusion

The **AE_DEMUX_3** is a compact, generic demultiplexer for AE signals that allows targeted signal routing to three outputs with minimal effort. Its use of adapters and generic architecture make it well-suited for modular and reusable automation solutions. The clear event interface (REQ/CNF) facilitates integration into event-driven control sequences.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
