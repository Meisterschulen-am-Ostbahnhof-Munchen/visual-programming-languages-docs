# AIWS_DEMUX_3

![AIWS_DEMUX_3](./AIWS_DEMUX_3.svg)

* * * * * * * * * *
## Introduction

The function block **AIWS_DEMUX_3** is a generic demultiplexer for data of the type **AIWS** (Agricultural Information and Workflow System). It distributes an incoming AIWS value to one of three outputs, depending on a passed index. Designed for use in agricultural technology, it enables the targeted routing of information within a control system.
## Interface Structure

### **Event Inputs**

| Event | Comment | with Variable |
|----------|------------|--------------|
| REQ | Set Index K | K |

### **Event Outputs**

| Event | Comment |
|----------|---------------------------------|
| CNF | Confirmation of Set Index K |

### **Data Inputs**

| Name | Type | Comment |
|------|-------|-----------|
| K | UINT | Index |

### **Data Outputs**

None (passed via adapter outputs).

### **Adapters**

| Type | Name | Direction |
|-------------------|-------|----------|
| AIWS (unidirectional) | IN | Socket |
| AIWS (unidirectional) | OUT1 | Plug |
| AIWS (unidirectional) | OUT2 | Plug |
| AIWS (unidirectional) | OUT3 | Plug |

## Functionality

The function block operates as a **1-to-3 demultiplexer**. As soon as a **REQ** event arrives, the current value of the data input **K** (index) is read. Depending on **K** (value range 1, 2, or 3 – other values are ignored or result in no output), the AIWS value present at socket **IN** is forwarded to the corresponding plug **OUT1**, **OUT2**, or **OUT3**. After successful transmission, the **CNF** event is issued to confirm the completion of the operation.

## Technical Features

- **Generic Structure**: The function block is marked with the attribute `GenericClassName` as `'GEN_AIWS_DEMUX'` and can therefore be used in generic instances.
- **Unidirectional Adapters**: All AIWS adapters are designed to be unidirectional, which defines a clear data flow direction.
- **Manufacturer-Specific**: Developed by HR Agrartechnik GmbH, optimized for agricultural automation solutions.
- **Package Structure**: This function block belongs to the package `adapter::selection::unidirectional` and uses a type-hash check from `eclipse4diac::core`.

## State Overview

This function block does not have an explicitly modeled state machine. However, its behavior can be reduced to two basic states:

1. **Idle** – Waiting for a REQ event.
2. **Forwarding Active** – Upon receipt of the REQ, the block switches to the selected output and transmits the data. CNF is then immediately sent, and the function block returns to the idle state.

## Application Scenarios

- **Distribution of Sensor Data**: A single AIWS sensor provides data that is forwarded to various actuators (e.g., valves, drives) depending on the index.
- **Routing in agricultural control systems**: In a field sprayer, different working widths or segments can be controlled via the three outputs.
- **Switching between multiple metering units**: Depending on the selected program (index), the metering command is routed to the corresponding unit.

## Comparison with similar modules

| Module | Function | Difference |
|----------|----------|-------------|
| **AIWS_DEMUX_3** | 1-to-3 demultiplexer for AIWS data | Specifically for the AIWS data type, three outputs |
| **Generic DEMUX** (e.g., IEC 61499 standard) | Demultiplexer for any data type | Not limited to AIWS, often multiple outputs freely configurable |
| **AIWS_SELECT** | 1-of-n selector (multiplexer) | Works in reverse: selects one of several inputs |

The **AIWS_DEMUX_3** offers a ready-to-use solution tailored to agricultural technology, requiring no additional configuration.

## Conclusion

The **AIWS_DEMUX_3** is a simple yet crucial function block for the targeted distribution of AIWS information to three outputs. Thanks to its clear interface and generic design, it integrates seamlessly into agricultural automation projects. It reduces programming effort and improves the clarity of data flow diagrams.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
