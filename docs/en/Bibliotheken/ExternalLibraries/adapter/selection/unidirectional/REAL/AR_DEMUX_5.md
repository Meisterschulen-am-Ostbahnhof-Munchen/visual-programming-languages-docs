# AR_DEMUX_5

![AR_DEMUX_5](./AR_DEMUX_5.svg)

* * * * * * * * * *
## Introduction

The AR_DEMUX_5 function block is a generic demultiplexer for the unidirectional AR adapter. It allows an incoming AR data stream to be routed to one of five output adapters. The target output is selected via an index input. The block is specified according to IEC 61499-2 and is provided as a generic FB with the class name `GEN_AR_DEMUX`.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |
|------|-----|------------|
| REQ | Event | Sets the index K and triggers the demultiplexing. (With data input K) |

### **Event Outputs**

| Name | Type | Comment |
|------|-----|-----------|
| CNF | Event | Confirmation that index K has been processed and the input value has been passed to the corresponding output. |

### **Data Inputs**

| Name | Type | Comment |
|------|-----|-----------|
| K | UINT | Index (1 to 5) for selecting the destination output. |

### **Data Outputs**

– None –

### **Adapters**

| Type | Name | Direction | Comment |
|-----|------|----------|-----------|
| adapter::types::unidirectional::AR | IN | Socket | Input adapter that provides the data to be demultiplexed. |
| adapter::types::unidirectional::AR | OUT1…OUT5 | Plug | Five output adapters to which the data is forwarded. |

## Functionality

The function block operates in an event-driven manner: When an event occurs at input `REQ`, the current value of index `K` is evaluated. The AR data stream provided via socket `IN` is then routed to the plug designated by `K` (`OUT1` for `K=1`, `OUT2` for `K=2`, etc.). After a successful switchover, an event is output at `CNF`. If `K` is not within the valid range (1…5), presumably no output is used and demultiplexing is omitted – depending on the implementation, this can lead to an error. The function block is declared as a generic function block and can be parameterized with various AR adapter types depending on the application.

## Technical Features

- **Generic Type**: The function block has the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AR_DEMUX'`, which means that it can be instantiated in the 4diac IDE as a specialized function block for a specific number of outputs (here, 5).
- **Unidirectional Adapters**: Both the input socket and the output plugs use the type `adatper::types::unidirectional::AR`. This assumes that data flows in only one direction (from the socket to one of the plugs).
- **No Internal State Machine**: The function block (FB) does not have an Execution Control Chart (ECC) in its XML description, so its functionality is based purely on event-driven index mapping.

## State Overview

Since the FB has no defined states, its behavior is deterministic: Every `REQ` event triggers an immediate switchover. There are no delays or wait states.

## Application Scenarios

- **Distribution of Sensor Data**: A central AR data stream (e.g., from a fieldbus or controller) should be selectively sent to different consumers (machine modules, actuators).
- **Test and Simulation Environments**: Selective injection of data into different test paths.
- **Agricultural Control Systems**: Switching between multiple device connections (e.g., valves, PTO shafts) based on an index.

## Comparison with Similar Function Blocks

- **AR_MUX_5**: The corresponding multiplexer, which combines data from five inputs into one output.
- **Demultiplexers with Other Adapter Types**: Similar function blocks exist for other unidirectional or bidirectional adapters (e.g., `DAT_DEMUX` for simple data types). The advantage of the AR adapter lies in the structured transmission of complex data.
- **Generic N-Demultiplexers**: Corresponding generic variants (`AR_DEMUX_3`, `AR_DEMUX_8`, etc.) are available for other numbers of outputs.

## Conclusion

The **AR_DEMUX_5** is a simple yet effective function block for selectively routing an AR data stream to five different outputs. Thanks to its generic design and clean event handling, it is ideally suited for modular automation systems, especially in the context of agricultural machinery control. The clear interface and the avoidance of internal states simplify integration and maintenance.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
