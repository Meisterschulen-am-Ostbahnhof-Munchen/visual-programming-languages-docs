# ATM_DEMUX_3

![ATM_DEMUX_3](./ATM_DEMUX_3.svg)

* * * * * * * * * *

## Introduction

The function block **ATM_DEMUX_3** is a generic demultiplexer for unidirectional ATM data streams. It routes an incoming data stream to one of three outputs based on its index. The block is event-driven and suitable for on-demand data distribution in automation or communication systems.

## Interface Structure

### **Event Inputs**

| Event | Type | Comment |

|----------|--------|----------------------------|

| REQ | Event | Sets the index K and triggers the forwarding |

### **Event Outputs**

| Event | Type | Comment |

|----------|--------|----------------------------------|

| CNF | Event | Confirmation of index setting and forwarding |

### **Data Inputs**

| Variable | Type | Comment |

|----------|-------|-----------|

| K | UINT | Index for selecting output (1, 2, or 3) |

### **Data Outputs**
No direct data outputs are available; data is passed through the adapters.

### **Adapters**
**Plugs (Outputs):**

| Name | Type | Comment |

|------|------------------------------------|-----------|

| OUT1 | adapter::types::unidirectional::ATM | First output |

| OUT2 | adapter::types::unidirectional::ATM | Second Output |

| OUT3 | adapter::types::unidirectional::ATM | Third Output |

**Sockets (Inputs):**

| Name | Type | Comment |

|------|------------------------------------|---------------------------|

| IN | adapter::types::unidirectional::ATM | Input data stream for demultiplexing |

## Functionality

This function block operates in an event-driven manner. When an event occurs at the **REQ** input, the current value of the **K** (Index) data input is read. The data present at the **IN** socket (ATM adapter) is then forwarded to the corresponding output adapter:

- **K = 1** → Data flows to **OUT1**
- **K = 2** → Data flows to **OUT2**
- **K = 3** → Data flows to **OUT3**

After successful forwarding, the **CNF** event is triggered. No behavior is specified for other values of **K**; in practice, the index should be limited to the valid range (1–3).

## Technical Features

- **Generic Function Block**: The function block is defined as a generic type (`GEN_ATM_DEMUX`) and can be configured for different target platforms using `eclipse4diac::core::GenericClassName` and `TypeHash`.

- **Unidirectional Adapters**: All adapters are of type `adapter::types::unidirectional::ATM`, which defines a clear direction of data flow.

- **No State Storage**: The module is stateless – its behavior is determined solely by the REQ event and the current index K.

## State Overview

The **ATM_DEMUX_3** has no internal states. It reacts directly to each REQ event by forwarding the data and logging a CNF event (provided the index is valid). There are no time dependencies or sequential processes.

## Application Scenarios

- **Data Distribution in Fieldbus Systems**: An incoming data stream (e.g., from a sensor) is forwarded to different actuators depending on the addressing.

- **Control of Multiple Outputs**: In a machine controller, a signal can be selectively routed to three different output channels.

- **Prototype for n-way demultiplexer**: This component can be used as a basis for extended demultiplexers with more outputs (by adjusting the number of adapters).

## Comparison with similar components

| Component | Description | Difference |

|--------------------|--------------|-------------|

| MUX (Multiplexer) | Combines multiple inputs into one output | Opposite function |

| DEMUX_2 / DEMUX_4 | Demultiplexer with 2 or 4 outputs | **ATM_DEMUX_3** offers exactly three outputs and is specialized for unidirectional ATM adapters |

| SELECT | Selects one of several data paths (often without adapters) | Usually works directly with data variables instead of adapters |

## Conclusion

The **ATM_DEMUX_3** is a compact and clearly defined demultiplexer for unidirectional ATM adapters. Its generic design allows for flexible integration into various automation projects, while its event-driven operation ensures deterministic data distribution. With its three outputs, it is particularly well-suited for typical 1-out-of-3 switching tasks in control engineering.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]