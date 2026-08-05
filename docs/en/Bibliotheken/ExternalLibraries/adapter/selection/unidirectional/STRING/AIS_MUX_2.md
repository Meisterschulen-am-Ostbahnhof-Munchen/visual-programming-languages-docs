# AIS_MUX_2
![AIS_MUX_2](./AIS_MUX_2.svg)
* * * * * * * * * *
## Introduction
The function block `AIS_MUX_2` implements a generic multiplexer for the adapter type `adapter::types::unidirectional::AIS`. It selects one of two input adapters (IN1, IN2) based on an index (K) and forwards its signals to the output adapter (OUT). The block is designed for use in IEC 61499.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| `REQ` | Event | Sets the index K and triggers the switching. |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| `CNF` | Event | Confirms the adoption of the new index K. |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| `K` | UINT | Index for selecting the active input (0 = IN1, 1 = IN2). |

### **Data Outputs**
No data outputs are available. Adapter signals are forwarded via the adapter interfaces.

### **Adapters**

| Direction | Name | Type | Comment |

### **Adapters** |----------|------|-----|-----------|

| Plug (Output) | `OUT` | `adapter::types::unidirectional::AIS` | Output adapter that reflects the selected input. |

| Socket (Input) | `IN1` | `adapter::types::unidirectional::AIS` | First input adapter (switched on when K = 0). |

| Socket (Input) | `IN2` | `adapter::types::unidirectional::AIS` | Second input adapter (switched on when K = 1). |

## Functionality
The component operates as a simple 2-to-1 multiplexer at the adapter level. As soon as the event `REQ` occurs, the value of `K` is evaluated:

- If `K = 0` is present, the signals from adapter `IN1` are routed to output adapter `OUT`.
- If `K = 1` is present, the signals from `IN2` are routed to `OUT`.

After a successful switchover, the event `CNF` is output.

The switchover process takes place within a single execution sequence, so no intermediate states occur.
... ## Technical Features

- **Generic Function Block**: The function block is declared as a generic type (`GenericClassName = 'GEN_AIS_MUX'`) and can be used for any instance of the `AIS` adapter type.
- **No Data Outputs**: All data is transmitted via the adapter interfaces; no separate values (e.g., as `ANY`) are output.
- **Type Hash**: An attribute `TypeHash` is present but is left empty by default. It enables cryptographic checksums for runtime identification, if needed.
- **Event-Driven**: Switching occurs only on an explicit `REQ` signal; without this signal, the last active output remains active.

## State Overview

The function block implicitly has two states, which are traversed by the event `REQ`:

| State | Description |

|---------|--------------|

| **IDLE** | Waiting for a `REQ` event. The output `OUT` is connected to the last selected input. |

| **SWITCH** | Upon arrival of `REQ`, the index `K` is read, a connection to `IN1` or `IN2` is established, and `CNF` is output. The component then returns to the **IDLE** state.

A graphical state machine is not part of the XML definition; its behavior is represented by the event logic of the execution environment.

## Application Scenarios
- **Source Switching**: Switching between two AIS data sources, e.g., different sensors or communication channels.
- **Redundancy**: Switching to a backup input if the primary channel fails (controlled by higher-level logic).
- **Testing & Diagnostics**: Temporary connection of a test adapter instead of the normal data stream.

## Comparison with Similar Components
- **Standard Multiplexers (e.g., MUX)**: These usually operate on simple data types (INT, BOOL) and output a single data value. In contrast, the `AIS_MUX_2` operates on the entire adapter interface, allowing multiple related signals to be switched simultaneously.
- **Adapter Selectors (e.g., SELECT)**: Comparable function blocks exist for other adapter types; this one is specifically tailored to the `AIS` type.

## Conclusion
The `AIS_MUX_2` is a compact and efficient function block for selecting between two AIS adapter inputs. Its generic declaration allows its use in various contexts, while the pure adapter interface simplifies integration into existing IEC 61499 systems. Its simple event-driven control makes it highly predictable and easily integrated into higher-level control logic.