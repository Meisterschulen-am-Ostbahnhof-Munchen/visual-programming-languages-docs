# AE_DEMUX_4

![AE_DEMUX_4](./AE_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The function block **AE_DEMUX_4** is a generic demultiplexer for adapters of type `AE`. It forwards an adapter value present at its input to one of four outputs. The target output is selected via an index parameter.
## Interface Structure

### **Event Inputs**

| Event | Description | With Data |
|----------|--------------|-----------|
| `REQ` | Sets the index K and triggers the forwarding | `K` |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirms execution of the demultiplexing operation |

### **Data Inputs**

| Name | Type | Description |
|------|-------|--------------------|
| `K` | UINT | Target output index (1..4) |

### **Data Outputs**

No data outputs available.

### **Adapters**

- **Plugs (Outputs)**
- `OUT1` (Type `AE`) – Adapter Output 1
- `OUT2` (Type `AE`) – Adapter Output 2
- `OUT3` (Type `AE`) – Adapter Output 3
- `OUT4` (Type `AE`) – Adapter Output 4
- **Socket (Input)**
- `IN` (Type `AE`) – Input adapter that connects to a The outputs are redirected

## Functionality

The module operates as a **1-to-4 demultiplexer** at the adapter level. Upon an event at input `REQ`, the adapter value currently present at socket `IN` (i.e., the adapter's entire data and event interface) is routed to the output adapter specified by data input `K` (`OUT1` … `OUT4`). The remaining outputs remain inactive. After successful routing, the output event `CNF` is sent.

The index `K` must have a valid value between 1 and 4; invalid values result in undefined behavior.

## Technical Features

- The function block is designed as a **generic type** (`GenericClassName = 'GEN_AE_DEMUX'`) and can be reused in various contexts.
- The adapter interfaces are of type `adapter::types::unidirectional::AE`, meaning they are unidirectional event/data adapters.
- The function block includes a type hash (`TypeHash`) that supports identification in distributed systems.
- Copyright protected (Eclipse Public License 2.0).

## State Overview

The function block has no explicit states; its functionality is purely combinatorial and event-driven. A demultiplexing operation is performed within a single event call.

## Application Scenarios

- **Signal distribution** in automation technology, e.g., forwarding a measured value to different processing stations.
- **Control logics** where a control command must be sent to different actuators.
- **Routing of adapter-connected components** in modular 4diac applications.

## Comparison with similar function blocks

- **`AE_SELECT`** – A multiplexer that selects one input from several. The demultiplexer function is its dual function.
- **`E_DEMUX`** – A pure event demultiplexer without data (only event forwarding). In contrast, `AE_DEMUX_4` works with full adapters and transmits both events and data.
- **`DATA_DEMUX_4`** – Demultiplexer for simple data types (e.g., INT, BOOL). The function block described here is specialized for the complex adapter type `AE`.

## Conclusion

The `AE_DEMUX_4` is a compact and generic demultiplexer for adapter-based communication. It enables the dynamic routing of an entire adapter interface to one of four outputs and is particularly suitable for modular and reusable automation solutions in the 4diac IDE.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
