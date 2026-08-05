# ADI_DEMUX_4
![ADI_DEMUX_4](./ADI_DEMUX_4.svg)

* * * * * * * * * *
## Introduction
The function block `ADI_DEMUX_4` is a generic demultiplexer that distributes an incoming data value via a unidirectional adapter (socket) to one of four output adapters (plugs). The destination output is selected via an index input. This block is typically used in industrial automation to dynamically switch signal paths or route data to different consumers.
## Interface Structure

### **Event Inputs**

| Name | Type | Description |
|------|-----|--------------|
| REQ | Event | Event to execute the demultiplex operation; triggers the processing of the index `K` |

### **Event Outputs**

| Name | Type | Description |
|------|-----|-------------|
| CNF | Event | Confirmation that the demultiplexing operation is complete |

### **Data Inputs**

| Name | Type | Description |
|------|-----|-------------|
| K | UINT | Index (1-based) for selecting the destination output (1→OUT1, 2→OUT2, 3→OUT3, 4→OUT4) |

### **Data Outputs**
_None_

### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|-------------|
Socket | IN | ADI (unidirectional) | Input adapter through which the data value to be distributed is present |
Plug | OUT1 | ADI (unidirectional) | First output adapter |
Plug | OUT2 | ADI (unidirectional) | Second output adapter |
Plug | OUT3 | ADI (unidirectional) | Third output adapter |
Plug | OUT4 | ADI (unidirectional) | Fourth output adapter |

## Functionality

1. The function block waits for an event at input `REQ`.

2. Upon receipt of `REQ`, the current value of index `K` is read.

3. The data value provided via socket `IN` (e.g., `INT`, `REAL`, or a user-defined type – depending on the specific adapter instantiation) is forwarded to the output adapter addressed by `K` (`OUT1`, `OUT2`, `OUT3`, or `OUT4`).

4. The event `CNF` is then issued to signal successful completion.

> **Note:** The index `K` is interpreted as an unsigned integer. Values outside the range 1…4 lead to undefined behavior – in a robust implementation, the calling function block should ensure valid indices.

## Technical Features
- **Generic Type:** The function block is designed as a generic function block (`eclipse4diac::core::GenericClassName = 'GEN_ADI_DEMUX'`). It can be parameterized in conjunction with various data adapters (e.g., for `INT`, `REAL`, `BOOL`) without requiring modifications to the logic itself.
- **Unidirectional Adapters:** All adapters are unidirectional – data flows only from socket `IN` to one of the plugs. This enables loose coupling and easy exchange of data sources and sinks.
- **Event-driven execution:** The demultiplex operation is triggered only by the `REQ` event. There is no continuous data stream; the function block operates strictly according to the event-driven paradigm of IEC 61499.

## State overview

The function block has no explicit states. Its behavior can be described as a simple sequence:

- **Start:** Wait for `REQ`.
- **REQ received:** Read `K`, forward the `IN` value to the corresponding `OUTn` plug, and output `CNF`.
- **Return to Standby State.**

## Application Scenarios
- **Signal Distribution:** A sensor delivers measured values via an ADI adapter. Depending on the operating mode (index `K`), the values are forwarded to various actuators or control logics.
- **Process Switching:** In a multi-process system, the same data input can be selectively routed to different processing stations.
- **Diagnostics & Testing:** A central data stream is switched to different test or monitoring blocks without requiring any changes to the wiring.

## Comparison with Similar Components

| Component | Description | Difference |
|----------|---------------|-------------|
| `ADI_MUX_4` | Multiplexer – collects data from four inputs and forwards it via one output | Reverse direction (multiple inputs → one output) |
| `DEMUX_2` / `DEMUX_8` | Demultiplexer with a different number of channels | `ADI_DEMUX_4` offers exactly four outputs; other variants can be adapted using custom adapters or generic parameters |
| `SELECT` (IEC standard) | Selection between two values (Boolean control) | Works with simple data types, not with adapters; less flexible with regard to different data sources |

## Conclusion

The `ADI_DEMUX_4` is a compact, generic demultiplexer for event-driven distribution of adapter data. Thanks to its unidirectional adapter interface and generic design, it is ideally suited for modular automation solutions where data flows need to be switched dynamically. The simple interface—one event, one index, and five adapters—enables straightforward integration into larger control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
