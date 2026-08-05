# AW_DEMUX_4
![AW_DEMUX_4](./AW_DEMUX_4.svg)
* * * * * * * * * *
## Introduction
The function block **AW_DEMUX_4** is a generic demultiplexer for adapters of type `adapter::types::unidirectional::AW`. It distributes an incoming adapter signal (via socket `IN`) to one of four output adapters (`OUT1` to `OUT4`). The target output is selected via the integer index `K`, which is set via the event input `REQ`. This function block is suitable for the dynamic routing of data streams in automation applications.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-------|------------------------------|

| REQ | Event | Sets the index `K` |

The event input `REQ` triggers processing: The current value of `K` is taken, and the input signal is forwarded to the corresponding output.

### **Event Outputs**

| Name | Type | Comment |

|------|-------|-----------------------------------------|

| CNF | Event | Confirmation of the takeover of `K` |

After successful switching, the event `CNF` is sent.

### **Data Inputs**

| Name | Type | Comment |

|------|-------|------------------|

| K | UINT | Index (typically 1-based) |

The value of `K` determines which output adapter is activated. Valid values are typically 1 to 4.

### **Data Outputs**
None.

### **Adapters**

| Direction | Name | Type | Comment |

|----------|-------|----------------------------------------|---------------------------------|

| Socket | IN | `adapter::types::unidirectional::AW` | Input Signal (Source) |

| Plug | OUT1 | `adapter::types::unidirectional::AW` | Output 1 |

| Plug | OUT2 | `adapter::types::unidirectional::AW` | Output 2 |

| Plug | OUT3 | `adapter::types::unidirectional::AW` | Output 3 |

| Plug | OUT4 | `adapter::types::unidirectional::AW` | Output 4 |

The adapters are unidirectional and of type `AW` (e.g., for analog or value forwarding).

## Functionality

1. The module waits for an event at input `REQ`.

2. Upon receiving `REQ`, the current value of data input `K` is recorded.

3. Depending on `K`, the adapter signal present at `IN` is switched to the corresponding output adapter (`OUT1` … `OUT4`).

4. After the switchover, the event `CNF` is output.

The function block operates in an event-driven manner and only changes the signal routing upon a new `REQ`.

## Technical Features
- **Generic Function Block:** The function block is provided as a generic template (`GEN_AW_DEMUX`) and can be customized for other adapter types if required.
- **Index Range:** The index `K` is declared as `UINT`. If a value outside the range 1…4 is passed, the switch remains undefined or the function block ignores the value (depending on the implementation).
- **EPL 2.0 License:** This function block is licensed under the Eclipse Public License 2.0 and may be used and modified in your own projects.

## State Overview
Since this is a basic demultiplexer, the function block has only one implicit state:

- **IDLE:** Waiting for `REQ`.
- **PROCESSING:** When `REQ` is passed, `K` is evaluated and the switch is executed. Then, `CNF` is sent, and the function block returns to the IDLE state.

An explicit state machine is not defined in the XML, but the described behavior is typical for such function blocks.

## Application Scenarios
- **Signal Distribution:** In a controller, an analog measured value should be sent to various consumers (e.g., display, logging, control).
- **Switching Communication Paths:** A data stream from a source is forwarded to different downstream function blocks depending on the operating mode.
- **Test and Simulation Environments:** A signal generator can be flexibly connected to multiple test objects via the index `K`.

## Comparison with Similar Function Blocks

| Function Block | Function | Outputs |

|----------------|--------------------------------------------|----------|

| **AW_DEMUX_4** | Demultiplexer for AW adapters (1→4) | 4 |

| AW_MUX_4 | Multiplexer for AW adapters (4→1) | 1 |

| AW_DEMUX_2 | Demultiplexer with two outputs | 2 |

The AW_DEMUX_4 is the extension to four outputs. It offers a higher number of destinations but requires a clearly defined index.

## Conclusion
The **AW_DEMUX_4** is a simple yet useful generic demultiplexer for unidirectional adapters. It allows the flexible routing of an input signal to one of four outputs, controlled by an index. Thanks to its generic structure and EPL 2.0 license, it integrates well into IEC 61499-based automation systems.