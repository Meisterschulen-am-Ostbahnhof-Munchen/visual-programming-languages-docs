# ADI_DEMUX_3
![ADI_DEMUX_3](./ADI_DEMUX_3.svg)

* * * * * * * * * *
## Introduction
The function block **ADI_DEMUX_3** is a generic demultiplexer for adapter data (ADI). It forwards an incoming ADI value via the adapter socket **IN** to one of three output adapters, **OUT1**, **OUT2**, or **OUT3**, depending on the index **K**.
## Interface Structure
### **Event Inputs**

| Event | Description |
|----------|--------------|
| **REQ** | Sets the index **K** and triggers the forwarding of the incoming value to the corresponding output. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| **CNF** | Confirmation that the demultiplexing process is complete and the index **K** has been applied. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|--------------|
| **K** | UINT | Index (1-based) for selecting the output. Valid values: 1, 2, 3. Values outside this range do not result in an active output. |

### **Data Outputs**
No data outputs are available. Output is exclusively via the adapters.

### **Adapters**

| Direction | Label | Type | Description |
|----------|-------------|-----|--------------|
**Socket** (Input) | **IN** | `adapter::types::unidirectional::ADI` | Input adapter that provides the data value to be multiplexed. |
**Plug** (Output) | **OUT1** | `adapter::types::unidirectional::ADI` | First output (selected when K=1). |
**Plug** (Output) | **OUT2** | `adapter::types::unidirectional::ADI` | Second output (selected when K=2). |
**Plug** (Output) | **OUT3** | `adapter::types::unidirectional::ADI` | Third output (selected when K=3). |

## Functionality

The module operates as a 1-to-3 demultiplexer via the ADI adapters:

1. The value at socket **IN** is continuously received.

2. Upon arrival of an event **REQ**, the current value of index **K** is evaluated.

3. Depending on **K**, the incoming ADI value is passed on to the corresponding plug:

- **K = 1** → **OUT1** is supplied with the value from **IN**.
- **K = 2** → **OUT2** is activated.
- **K = 3** → **OUT3** is activated.

4. After successful forwarding, the event **CNF** is output.

5. For invalid values of **K** (e.g., 0 or >3), no output is activated, but **CNF** is still signaled to ensure consistent control flow.

## Technical Features
- **Generic Design**: The function block is declared as a generic FB with the class name `'GEN_ADI_DEMUX'`. It can be used as a template for other demultiplexer variants in the development environment via attributes such as `eclipse4diac::core::GenericClassName`.
- **Version Information**: Developed by **Franz Höpfinger** for **HR Agrartechnik GmbH**, version 1.0, released on **2026-05-28**.
- **License**: Released under the **Eclipse Public License 2.0** (EPL-2.0).
- **Compiler Import**: The function block imports `eclipse4diac::core::TypeHash` to support type checking.

## State Overview
The function block does not have any explicitly modeled states. The internal logic processes the index **K** with each **REQ** event and instantly updates the output adapters. A sequential state machine is not required because the demultiplexing process is event-driven and atomic.

## Application Scenarios
- **Signal Distribution in Adapter-Based Controllers**: A single sensor or data adapter (e.g., for temperature, pressure) is to be distributed across multiple parallel processing paths.
- **Channel Switching in Modular Automation Solutions**: Depending on the selection index, a connection is established to different actuators or subsystems.
- **Test and Simulation Environments**: A test signal can be dynamically routed to different functional blocks without changing the wiring.

## Comparison with Similar Components

| Component | Number of Outputs | Adapter Type | Special Features |
|----------|-----------------|------------|--------------|
| **ADI_DEMUX_3** (this FB) | 3 (OUT1-3) | Unidirectional ADI | Generic, event-driven switching |
| Other demultiplexers (e.g., `MUX` family) | Variable (2, 4, …) | ADI or standard data types | Often with enable input or multiple selection bits |
| Simple adapter splits (e.g., `ADAPTER_SPLIT`) | Usually a fixed number | Bidirectional or unidirectional | No selection option – all outputs receive the same signal |

The **ADI_DEMUX_3** is characterized by its explicit index selection (UINT), which enables flexible programming without the need for additional multiplexing logic. Unlike hard-wired splits, it allows for targeted channel selection at runtime.

## Conclusion
The **ADI_DEMUX_3** function block is a simple yet effective demultiplexer for ADI data streams. Thanks to its generic structure and clear event-driven operation, it is ideally suited for use in modular, adapter-based automation projects. Selecting one of three outputs via an index creates a clean separation of signal sources and sinks without requiring the implementation of complex, custom multiplexing logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
