# AB_DEMUX_2

![AB_DEMUX_2](./AB_DEMUX_2.svg)

* * * * * * * * * *
## Introduction

The function block **AB_DEMUX_2** is a generic demultiplexer (branch) for a unidirectional AB adapter. It allows an incoming data stream (via socket **IN**) to be selectively routed to one of two output adapters (**OUT1** or **OUT2**). The destination output is selected via the parameter **K** for each REQ event. This function block is specifically designed for control applications where signal distribution to different paths is required.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|-------|--------|--------------------------|
| REQ | Event | Request for switching; requires parameter K. |

### **Event Outputs**

| Name | Type | Comment |
|-------|--------|------------------------------------|
| CNF | Event | Confirmation of successful switching. |

### **Data Inputs**

| Name | Type | Comment |
|------|-------|-------------------------|
| K | UINT | Index (0 or 1) that determines which output is activated. |

### **Data Outputs**

No direct data outputs – output is exclusively via the adapter interfaces.

### **Adapters**

| Name | Type | Direction | Comment |
|-------------|--------------------------------------|----------|------------------------------------------|
| IN | adapter::types::unidirectional::AB | Socket | Receives the data to be distributed. |
OUT1 | adapter::types::unidirectional::AB | Plug | First output for the demultiplexed data stream. |
OUT2 | adapter::types::unidirectional::AB | Plug | Second output for the demultiplexed data stream. |

## Functionality

The module operates on the principle of a 1-to-2 demultiplexer:

1. An incoming **REQ** event triggers processing.
2. The value of the data input **K** is read. It must be **0** or **1**.
3. If **K = 0**, the data stream is redirected from the **IN** adapter to the adapter **OUT1**.

If **K = 1**, it is forwarded to **OUT2**.

4. After a successful switchover, the **CNF** event is sent.

During processing, the data from the **IN** adapter is completely transferred to the selected output adapter. The unselected output interface remains inactive (no data is passed).

## Technical Features

- **Generic Nature**: The function block is declared as a generic function block (`GEN_AB_DEMUX`), meaning it can, in principle, be instantiated with various adapter types. In this implementation, the adapter `adapter::types::unidirectional::AB` is used.
- **No Buffering**: The demultiplexer operates strictly event-driven and does not buffer any data. A subsequent request immediately overwrites previous switches.
- **Easy Extensibility**: The architecture allows for easy adaptation to multiple outputs, although the current version has exactly two outputs.

## State Overview

The function block does not have explicit states in the sense of a state machine – it reacts immediately to every **REQ** event. Its behavior can be described as follows:

- **Idle State**: No REQ is active. Outputs are inactive (no data on **OUT1** or **OUT2**).
- **Switching Process**: Upon arrival of **REQ**, **K** is evaluated, the data connection is established to the corresponding output, and **CNF** is immediately returned. The block then returns to its idle state.

## Application Scenarios

- **Routing of Sensor Values**: A sensor continuously provides data (e.g., via an AB adapter). Depending on the operating mode (K = 0 or K = 1), the data is forwarded to different control units.
- **Switching Between Two Actuator Paths**: In a redundant control setup, the data stream can be selectively switched to either a primary or a secondary actuator.
- **Test/Normal Operation**: In test mode (K=1), the data is redirected to an analysis device, while in normal operation (K=0), it supplies the production control system.

## Comparison with Similar Function Blocks

| Function Block | Properties |
|-------------------------|-------------------------------------------------------------------------------|
| **AB_DEMUX_2** | Specifically for unidirectional AB adapters; two outputs; index-controlled. |
| **AB_DEMUX_4** | Analog demultiplexer with four outputs, expects a larger index range. |
| **AB_SWITCH** | Bidirectional switching (switch) between two paths, usually for data adapters. |
| **E_DEMUX** (Event) | Demultiplexes events, not data adapters – event-only control. |

The **AB_DEMUX_2** is characterized by its ease of use with only two outputs and direct adapter coupling. In contrast to an event-driven demultiplexer, it forwards complete adapter signals (including all embedded data).

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AB_DEMUX_2** is a compact, event-driven demultiplexer for unidirectional AB adapters. Its clear separation of event control and data forwarding makes it ideal for modular automation solutions where a data stream needs to be switched between two destinations. Its generic design allows for use in various contexts, while the simple interface ensures reliable integration into existing 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
