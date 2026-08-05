# AUDI_DEMUX_4
![AUDI_DEMUX_4](./AUDI_DEMUX_4.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_DEMUX_4** implements a generic 1:4 demultiplexer for the unidirectional **AUDI** adapter type. It routes a signal present at its input (socket) to one of four outputs (plugs). The active output is selected via an index parameter and is triggered by an event at input `REQ`. After successful switching, an acknowledgment event is sent at output `CNF`.
The block is implemented as a generic function block (Generic FB) and can therefore be used in various projects with the corresponding adapter type.

## Interface Structure

### **Event Inputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `REQ` | Event | Sets the index `K` and triggers the demultiplexing action. |

### **Event Outputs**

| Name | Data Type | Comment |

|------|----------|-----------|

| `CNF` | Event | Confirmation of successful index setting and switching. |

### **Data Inputs**

| Name | Data Type | Initial Value | Comment |

|--------|----------|-------------|-----------|
| `K` | UINT | – | Index of the desired output (1..4). |

### **Data Outputs**

No data outputs available.

### **Adapters**

| Type | Name | Direction | Comment |

|-----|------|----------|-----------|

| `adapter::types::unidirectional::AUDI` | `IN` | Socket (Input) | Input signal that is passed to the selected output. |

| `adapter::types::unidirectional::AUDI` | `OUT1` | Plug (Output) | First output (Index 1). |

| `adapter::types::unidirectional::AUDI` | `OUT2` | Plug (Output) | Second Output (Index 2). |

| `adapter::types::unidirectional::AUDI` | `OUT3` | Plug (Output) | Third Output (Index 3). |

| `adapter::types::unidirectional::AUDI` | `OUT4` | Plug (Output) | Fourth Output (Index 4). |

## Functionality

The function block operates strictly event-driven:

1. A valid event at input `REQ` takes the current value of data input `K` as the selection index.

2. The function block connects the adapter data stream present at `IN` to the output adapter referenced by `K` (`OUT1` … `OUT4`).

3. After a successful switchover, the event `CNF` is output.

Unused outputs remain unchanged (e.g., disconnected from the source). The index `K` expects values in the range 1 to 4; other values do not result in a valid switchover. The behavior with invalid indices is undefined and should be avoided by higher-level logic.

## Technical Features
- **Generic Function Block**: The function block is declared as a generic type (`GEN_AUDI_DEMUX`). It can be instantiated with any adapter that follows the scheme `adapter::types::unidirectional::AUDI`. The actual adapter definition is determined at compile time.
- **Unidirectional Adapters**: All adapters used are unidirectional. Signal flow occurs only from the socket (`IN`) to the plugs (`OUT1` … `OUT4`).
- **No Internal States**: The function block does not have an explicit state machine. Processing is purely event-driven without intermediate data storage, except for the index `K`.

## State Overview

The function block does not have a defined ECC (Execution Control Chart). Its behavior can be reduced to two phases:

| Phase | Description |

|-------|--------------|

| **Waiting** | The function block (FB) is awaiting an event at `REQ`. |

| **Processing** | Upon receiving `REQ`, the index is updated, the routing is revised, and `CNF` is sent. The FB then immediately returns to the wait state. |

Parallel processing of multiple events is not supported; the FB is designed for strictly sequential operation.

## Application Scenarios
- **Signal forwarding** in modular automation systems where a sensor value or control variable must be selectively forwarded to various consumers (e.g., actuators, visualizations).
- **Channel switching** in communication interfaces based on the AUDI adapter protocol.
- **Test and simulation environments** where a data stream needs to be selectively switched to different analysis or logging paths.

## Comparison with Similar Function Blocks

Unlike conventional demultiplexers (e.g., `MUX`/`DEMUX` at the signal level), **AUDI_DEMUX_4** operates at the **adapter connection** level. Instead of switching individual bits or values, the entire data structure defined by the adapter is switched. This simplifies the handling of complex data types and improves clarity in application design.

Conversely, a **generic MUX function block** for the same adapter type would combine multiple inputs into a single output. This function block fulfills the opposite function – distributing one input to multiple outputs.

## Conclusion

The **AUDI_DEMUX_4** is a compact, generic function block for the unidirectional demultiplexing of AUDI adapter connections. Due to its pure event-driven control, simple index selection, and clear separation of event and data paths, it is particularly suitable for application-neutral distribution tasks in IEC 61499-2 compliant systems. Integration as a generic function block increases reusability across different projects.
