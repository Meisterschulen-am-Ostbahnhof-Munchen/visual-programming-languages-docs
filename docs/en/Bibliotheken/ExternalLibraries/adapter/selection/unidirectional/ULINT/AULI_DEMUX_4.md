# AULI_DEMUX_4

![AULI_DEMUX_4](./AULI_DEMUX_4.svg)

* * * * * * * * * *
## Introduction

The **AULI_DEMUX_4** is a generic demultiplexer that forwards an incoming AULI adapter data stream to one of four possible output adapters. Selection is made via a numeric index (K), which is evaluated when the REQ event is set. The function block is designed for use in agricultural automation (AULI) and allows for flexible signal distribution.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| REQ | Event | Sets the index K and triggers the demultiplexing operation. |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirms successful forwarding to the selected adapter. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index (value range 0–3 for OUT1…OUT4) |

### **Data Outputs**

*None*

### **Adapters**

| Name | Type | Direction | Comment |
|------|-----|----------|-----------|
| IN | AULI | Socket (Input) | Input adapter containing the data to be distributed |
| OUT1 | AULI | Plug (Output) | First output (when K=0) |
OUT2 | AULI | Plug (output) | Second output (when K=1) |
OUT3 | AULI | Plug (output) | Third output (when K=2) |
OUT4 | AULI | Plug (output) | Fourth output (when K=3) |

## Functionality

The module operates in an event-driven manner:

1. A REQ event is received.
2. The current value of the data input **K** is read.
3. The state of the socket adapter **IN** is copied to the plug adapter **OUT1**, **OUT2**, **OUT3**, or **OUT4**, depending on the value of K (e.g., K=0 → OUT1, K=1 → OUT2, …).
4. After successful transmission, the **CNF** event is output.

The function block is generic (GenericClassName `'GEN_AULI_DEMUX'`) and can be adapted to various AULI subtypes through parameterization.

## Technical Features

- **Adapter-based**: Input and output are handled exclusively via AULI adapters, enabling loose coupling and modular reuse.
- **Unidirectional**: Data flows only from socket **IN** to one of the plugs; feedback is not supported.
- **Generic**: The function block is defined as a template (Generic FB), allowing it to be used with different AULI data types.
- **Simple Indexing**: Index K is implemented as a UINT (values 0 to 3). For invalid values, the behavior is undefined (no range check in the FB interface).

## State Overview

The function block does not have an explicit state machine (ECC) in the XML. Its functionality is reduced to a pure event-data transaction:

- **IDLE**: Waiting for REQ.
- **ACTIVE**: Copying the IN adapter value to the OUT adapter determined by K.
- **DONE**: Outputting CNF and returning to IDLE.

A detailed state graph is not required because the function block operates atomically.

## Application Scenarios

- **Distribution of Sensor Data**: An AULI sensor (e.g., soil moisture) is sequentially forwarded to various actuator units.
- **Channel Switching**: Controlling four different loads (valves, motors) via a common data source.
- **Test and Simulation Environments**: Targeted addressing of individual components in an AULI-based test platform.

## Comparison with Similar Components

| Component | Type | Difference |
|----------|-----|-------------|
| AULI_MUX_4 | Multiplexer | Combines multiple AULI inputs into one output (reverse direction). |
| AULI_DEMUX_2 | Dual Demultiplexer | Same functionality, but only two outputs. |
| AULI_SWITCH | Switch | Enables dynamic connection between multiple inputs and outputs (matrix topology). |

## Change Detection

The selected output plug is only written and its adapter event only sent if the incoming value differs from the value currently held on that plug. If the value is unchanged, no adapter event is sent, avoiding redundant updates on unrelated peers.


## Conclusion

The **AULI_DEMUX_4** is a compact, generic demultiplexer for AULI adapters, ideally suited for the targeted distribution of data streams in agricultural technology. Thanks to its simple event control and adapter interface, it can be easily integrated into existing 4diac process chains. Its generic nature allows for customization without changing the block logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
