# AL_DEMUX_5

![AL_DEMUX_5](./AL_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The function block **AL_DEMUX_5** is a generic demultiplexer for the universal data type `AL` (adapter of type `adapter::types::unidirectional::AL`). It forwards an incoming data value from its input adapter **IN** to any one of five output adapters (**OUT1…OUT5**). The destination output is selected via the index **K**, which is evaluated on a rising edge at the event input **REQ**. After successful forwarding, the event **CNF** is output.
## Interface Structure

### **Event Inputs**

| Event | Description |
|---|---|
| `REQ` | Sets the index **K** and triggers the demultiplexing of the current input value. |

### **Event Outputs**

| Event | Description |
|---|---|
| `CNF` | Confirms successful index setting and routing to the corresponding output. |

### **Data Inputs**

| Variable | Type | Description |
|---|---|---|
| `K` | `UINT` | Index (1-based) of the target output: `1`→OUT1, `2`→OUT2, …, `5`→OUT5. Values outside this range are ignored or result in no output signal (depending on the implementation). |

### **Data Outputs**

None.

### **Adapters**

| Direction | Name | Type | Description |
|---|---|---|---|
| **Socket** (Input) | `IN` | `adapter::types::unidirectional::AL` | Input adapter that provides the data value to be demultiplexed. |
| **Plug** (Output 1) | `OUT1` | `adapter::types::unidirectional::AL` | First output adapter. |
| **Plug** (Output 2) | `OUT2` | `adapter::types::unidirectional::AL` | Second output adapter. |
| **Plug** (Output 3) | `OUT3` | `adapter::types::unidirectional::AL` | Third output adapter. |
**Plug** (Output 4) | `OUT4` | `adapter::types::unidirectional::AL` | Fourth output adapter. |
**Plug** (Output 5) | `OUT5` | `adapter::types::unidirectional::AL` | Fifth output adapter. |

## Functionality

1. The function block waits for a `REQ` event. This event is used to read the current value of **K**.

**Plug** (Output 5) | `OUT5` | `adapter::types::unidirectional::AL` | Fifth output adapter. 2. The current value of the input adapter `IN` is copied to the output adapter (`OUT1`…`OUT5`) specified by **K**.

3. After successful transfer, the acknowledgment event `CNF` is sent.

The function block (FB) operates statelessly – every `REQ` call immediately triggers the described action. If an index outside the range 1…5 is specified, no forwarding occurs, but `CNF` is still sent (depending on the specific implementation; see technical details).

## Technical Details

- **Generic Block**: The FB is declared as generic `GEN_AL_DEMUX`. This allows for later specialization in other adapter types, provided the interface is compatible.
- **Adapter-based**: The use of adapters (sockets/plugs) enables loose coupling between data sources and sinks. The input `IN` and the outputs `OUT1`…`OUT5` are each of type `adapter::types::unidirectional::AL`.
- **Index handling**: The index **K** is defined as `UINT`. In the common implementation, only the value range 1…5 is considered valid. A value of 0 or >5 does not result in any data transmission, but still triggers `CNF`.
- **License**: This module is licensed under the **Eclipse Public License 2.0** (EPL-2.0), which permits free use and modification.
- **Version**: Version 1.0, provided for the 4diac IDE.

## State Overview

The **AL_DEMUX_5** module has no explicit states (ECC diagram). It is a purely combinatorial/event-driven module: Each `REQ` pulse immediately triggers index evaluation and forwarding, without intermediate states.

## Application Scenarios

- **Data Routing**: A sensor delivers a universal value via `IN`, which is to be forwarded to one of five processing stations (OUT1…OUT5) depending on the context. The index **K** is set by a higher-level controller.
- **Demand-driven distribution**: In a production line, a workpiece can be routed to different processing stations. The demultiplexer selects the target adapter based on an identification code (`K`).
- **Test environments**: Simulated switching between different test adapters without changing the wiring.

## Comparison with similar modules

| Module | Number of outputs | Data type | Special feature |
|---|---|---|---|
| `AL_DEMUX_5` | 5 | Adapter `AL` | Generic, adapter-based, event-driven |
| `E_DEMUX` (4diac standard) | 2/4/8 | Events | Event forwarding only, no data |
| `MUX` (Multiplexer) | – | Any | Inverted function (multiple inputs to one output) – not available by default in 4diac |

The `AL_DEMUX_5` fills a gap for the demultiplexing of adapter data (e.g., for complex data types such as structures), while pure event demultiplexers like `E_DEMUX` do not transport data.

## Conclusion

The **AL_DEMUX_5** is a simple yet useful generic demultiplexer for adapters of type `AL`. Its clear structure with one input and five output adapters makes it ideal for routing applications in IEC 61499 systems. EPL licensing and its generic design promote reusability and adaptability. This component adds the important capability of selectively distributing structured data adapters to existing standard demultiplexers.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
