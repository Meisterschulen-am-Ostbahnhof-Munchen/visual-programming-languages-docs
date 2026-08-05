# AS_DEMUX_4

![AS_DEMUX_4](./AS_DEMUX_4.svg)

* * * * * * * * * *

## Introduction

The function block **AS_DEMUX_4** serves as a demultiplexer for a unidirectional adapter of type `AS`. It routes the adapter input at a single input to one of four possible outputs. The target output is selected via a numeric index, which is specified when an event is requested. The block is implemented as a generic type (`GEN_AS_DEMUX`) and is suitable for use in modular control architectures where data flows need to be switched dynamically.

## Interface Structure

### **Event Inputs**

| Event | Description |

|----------|--------------|

| `REQ` | Request to forward the input adapter. The value of `K` specifies the destination output. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| `CNF` | Confirmation of successful switching. Indicates that the adapter is ready on the selected output. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|--------------|

| `K` | UINT | Index of the desired output (expected values 1 … 4). |


### **Data Outputs**

No standalone data outputs – output is exclusively via the adapter ports.

### **Adapters**

#### Socket (Input)

| Adapter | Type | Description |

|---------|-------------------------------------------|------------------------------------|

| `IN` | `adapter::types::unidirectional::AS` | Input value to be demultiplexed |

#### Plugs (Outputs)

| Adapter | Type | Description |

|---------|-------------------------------------------|----------------------------------------|

| `OUT1` | `adapter::types::unidirectional::AS` | First output (Index 1) |

| `OUT2` | `adapter::types::unidirectional::AS` | Second Output (Index 2) |

| `OUT3` | `adapter::types::unidirectional::AS` | Third Output (Index 3) |

| `OUT4` | `adapter::types::unidirectional::AS` | Fourth Output (Index 4) |

## Functionality

The module operates as a **1-to-4 demultiplexer** at the adapter level. As soon as an event arrives at input `REQ`, the adapter connected to socket `IN` (including its entire data and event interface) is switched to the output port (`OUT1` … `OUT4`) determined by the variable `K`.

The following applies:

- The value of `K` determines the target output (1-based).

- Only the selected output receives a connection to the input; all other outputs remain inactive or retain their last state (depending on the specific adapter implementation).

- After the switchover, the acknowledgment event `CNF` is triggered.



``` The link between the event and data paths is ensured via the ``With`` attribute of ``REQ``: ``K`` is evaluated together with the event.

## Technical Features

- **Generic Design**: The function block is defined as a generic type (``GEN_AS_DEMUX``). This allows it to be reused for any adapter instance of the unidirectional ``AS`` type without requiring any modifications to the source code.

- **Index Range**: If a value outside the valid range (1 … 4) is passed for ``K``, the behavior is undefined. The function block does not perform a range check. The user is responsible for validating the index.


- - **Event-driven operation**: Switching occurs exclusively via the `REQ` event. A static index change without an event has no effect.

## State overview

The function block does not have an explicit state machine in the XML model. Its behavior is purely reactive: Every `REQ` event is immediately followed by switching and the output of `CNF`. There is no internal state that persists beyond event execution.

| State / Phase | Description |

|----------------|--------------|

| **Waiting** | The function block is waiting for a `REQ` event. The last index, `K`, remains stored internally, but without effect. |

| **Switching** | Upon receipt of `REQ`, the value of `K` is read and the corresponding output is activated. |

**Confirming** | After the switching, `CNF` is sent, and the function block returns to standby mode. |

## Application Scenarios

- **Tool Changers in Manufacturing**: A central sensor or actuator adapter provides data that must be switched to one of four machine adapters, depending on the current machining station.

- **Modular Control Architectures**: A higher-level function block selects the subsystem to communicate with from several concurrently configured subsystems.

- **Test and Simulation Environments**: Switching between the real process adapter and a simulated backup adapter, e.g., for commissioning or troubleshooting.


## Comparison with Similar Function Blocks

- **`AS_MUX_4`** (Multiplexer): Performs the reverse operation – multiple inputs are switched to a single output. The AS_DEMUX_4 complements this function block to create a complete switching system.

- **`SELECT`-FB** (IEC 61499 Standard): Selects one of two data paths based on a Boolean input. The AS_DEMUX_4 operates at the adapter level and offers four paths instead of two, but is not limited to simple data types.

- **Generic Demultiplexers**: Other implementations often use single data-event pairs. The AS_DEMUX_4 uses adapters, enabling the switching of complex interfaces (events + data) in one operation.


## Conclusion

The **AS_DEMUX_4** is a compact, generic function block for dynamically distributing a unidirectional `AS` adapter to up to four outputs. Its event-driven selection via a numeric index makes it versatile for use in modular control systems. By using adapters, not only data but also the associated event paths are switched, enabling a clean and encapsulated interface structure. Index validation must be performed outside the function block.