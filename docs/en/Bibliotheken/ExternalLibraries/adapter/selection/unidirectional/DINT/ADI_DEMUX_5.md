# ADI_DEMUX_5

![ADI_DEMUX_5](./ADI_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The function block **ADI_DEMUX_5** is a generic demultiplexer for adapter-based data transport (ADI). It forwards a value present at its socket IN to one of five output adapters (OUT1 to OUT5). The destination port is selected using the integer index K.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| `REQ` | Starts the demultiplex operation. The current value of K determines the destination output. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Sent as soon as the value is transferred to the selected output. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| `K` | UINT | Index of the target output (1-based: 1 → OUT1, …, 5 → OUT5). |

### **Data Outputs**

No direct data outputs are available. Output is exclusively via the adapters.

### **Adapters**

| Role | Name | Type (Adapter) | Description |
|-------|-------|---------------|--------------|
Socket | `IN` | ADI (unidirectional) | Input value to be demultiplexed. |
Plug | `OUT1` | ADI (unidirectional) | First output destination adapter. |
Plug | `OUT2` | ADI (unidirectional) | Second output destination adapter. |
Plug | `OUT3` | ADI (unidirectional) | Third output destination adapter. |
Plug | `OUT4` | ADI (unidirectional) | Fourth output destination adapter. |
Plug | `OUT5` | ADI (unidirectional) | Fifth output destination adapter. |

## Functionality

When an event arrives at input `REQ`, the current value of index `K` is evaluated. The function block copies the ADI value present at socket `IN` to the plug whose number corresponds to the value of `K` (OUT1 for K=1, OUT2 for K=2, … OUT5 for K=5). After successful transmission, an acknowledgment event is sent at output `CNF`. For K values outside the range 1-5, no output is activated, but a `CNF` is still sent to complete the protocol.

Function block
## Technical Features

- **Generic Base Block**: The function block is implemented as a generic type `GEN_ADI_DEMUX`, which is parameterized at runtime with the specific adapter interface.
- **Unidirectional**: Both inputs and outputs use the unidirectional ADI adapter, meaning that data is only forwarded from the socket to a plug; no feedback is provided.
- **No Dedicated Data Outputs**: Output is exclusively via the adapter interfaces, enabling close coupling with other ADI-enabled function blocks.

## State Overview

The function block does not have an explicit internal state machine. It is stateless: Each call to the event `REQ` results in the described demultiplexing operation, regardless of previous calls. The behavior is deterministic and determined solely by the current values of `K` and `IN`.

## Application Scenarios

- **Signal Forwarding in Modular Controllers**: A sensor value (e.g., via ADI bus) is to be distributed to different control units depending on the operating mode.
- **Channel Selection in Measurement Systems**: Several sensors are accessed via a common ADI path; switching is performed using the index K.
- **Prototype Extension**: Due to its generic nature, the function block can be used in adapter-based frameworks for flexible data paths.

## Comparison with Similar Function Blocks

- **ADI_MUX_5** (Multiplexer): Performs the reverse operation – selects one of five inputs and forwards it to a common output.
- **STATIC_ROUTER**: Always forwards data to a fixed, predefined port without a dynamic index.
- **CASE_Selector**: Implements logical branching with multiple outputs, but often using Boolean conditions rather than a numerical index.

In contrast to these components, the ADI_DEMUX_5 is characterized by its direct adapter connection and simple index-driven distribution.

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **ADI_DEMUX_5** is a specialized demultiplexer for ADI adapters that enables clean, index-based signal distribution to up to five outputs with minimal effort. Its generic implementation and clear event handling make it a versatile tool in modular automation systems based on the Eclipse 4diac framework.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
