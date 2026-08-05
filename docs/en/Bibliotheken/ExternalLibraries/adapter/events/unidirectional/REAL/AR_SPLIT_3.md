# AR_SPLIT_3
![AR_SPLIT_3](./AR_SPLIT_3.svg)
* * * * * * * * * *
## Introduction
The function block **AR_SPLIT_3** serves as a generic splitter for adapter connections. It distributes an incoming data and event stream (via a `AR` adapter) to three separate, identically structured output adapters. This enables efficient reuse of information in automation processes without duplicating the logic.
## Interface Structure

### **Event Inputs**

None – the block has only adapter interfaces. Events are transmitted implicitly via the socket `IN` (of type `AR`).

### **Event Outputs**

None – Events are passed via the plugs `OUT1`, `OUT2`, and `OUT3` (type `AR`).

### **Data Inputs**
None – All data is provided via the adapter `IN`.

### **Data Outputs**
None – All data is output via the three output adapters (`OUT1`, `OUT2`, `OUT3`).

### **Adapters**

| Direction | Name | Type | Description |

|----------|-------|----------------------------|-------------------------------------------------|

Socket | `IN` | `adapter::types::unidirectional::AR` | Incoming adapter as the source of the data/events. |

Plug | `OUT1`| `adapter::types::unidirectional::AR` | First outgoing adapter (Destination 1). |

Plug | `OUT2`| `adapter::types::unidirectional::AR` | Second outgoing adapter (Destination 2). |

Plug | `OUT3`| `adapter::types::unidirectional::AR` | Third outgoing adapter (Destination 3). |

## Functionality

This function block implements a **1:3 distribution** at the adapter level. A `AR` adapter (unidirectional) connected to `IN` is internally routed to the three output adapters `OUT1`, `OUT2`, and `OUT3`.

Every event or data packet received at `IN` is simultaneously forwarded to all three outputs. The distribution occurs without delay and without data modification. The function block is generic and can be used with any `AR` adapter profile – its internal logic automatically adapts to the structure of the adapter type used.

...
## Technical Features

- **Generic Type**: The function block (FB) is designed as a generic block (`GEN_AR_SPLIT`) and can be used with different `AR` adapter definitions (unidirectional), provided the interfaces are compatible.
- **Unidirectional Adapters**: Both inputs and outputs are unidirectional, meaning the data/event direction is fixed (from sender to receiver). Feedback is not possible with this block.
- **Easy Scaling**: The outputs are split without additional configuration. For different numbers of outputs, variants such as `AR_SPLIT_2` or a configurable splitter (`AR_SPLIT_N`) can be used.
- **No State Change**: The block has no internal memory and no state machine – every event is replicated immediately and completely.

## State Overview

The function block is **stateless** (combinatorial). There are no internal states or sequential processes. Distribution occurs purely through the connection of the adapter signals.

## Application Scenarios
- **Distributing sensor data** to multiple parallel processing logics (e.g., evaluation, visualization, logging).
- **Controlling multiple actuator groups** with an identical control signal (e.g., parallel valve or motor control).
- **Splitting a control event** into different function blocks without copying the source logic.
- **Debugging and Monitoring**: A signal can be routed to a physical receiver and, in parallel, to a monitoring component.

## Comparison with Similar Function Blocks

| Function Block | Description |

|----------------|-----------------------------------------------------------------------------|

| **AR_SPLIT_2** | Distribution to two outputs – more compact for smaller applications. |

**AR_SPLIT_N** | Distribution to a configurable number of outputs (generic). |

**AR_CONNECT** | Simple 1:1 connection (no distribution). |

Unlike dedicated splitters with data or event inputs/outputs, the `AR_SPLIT_3` operates exclusively via adapters, making it particularly flexible and type-independent.

## Conclusion

**AR_SPLIT_3** is a simple yet useful generic function block for distributing adapter signals to multiple outputs. It reduces the effort required for signal duplication in IEC 61499 applications and, due to its generic nature, contributes to the reusability and clarity of control logic. Thanks to its pure adapter approach, it can be integrated into a wide variety of environments without modification.
