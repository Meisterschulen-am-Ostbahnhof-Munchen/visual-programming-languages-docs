# AIWS_SPLIT_4

![AIWS_SPLIT_4](./AIWS_SPLIT_4.svg)

* * * * * * * * * *
## Introduction

The function block `AIWS_SPLIT_4` is used to split an incoming unidirectional **AIWS** adapter connection into four parallel outputs. It acts as a passive splitter, forwarding the values received via the socket to all four plugs without processing events or data itself.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapter**

| Type | Direction | Name | Description |
|-----|----------|------|--------------|
| `adapter::types::unidirectional::AIWS` | Socket | **IN** | Input adapter for the AIWS connection to be distributed |
| `adapter::types::unidirectional::AIWS` | Plug | **OUT1** | First output adapter |
| `adapter::types::unidirectional::AIWS` | Plug | **OUT2** | Second output adapter |
| `adapter::types::unidirectional::AIWS** | Plug | **OUT3** | Third output adapter |
| `adapter::types::unidirectional::AIWS` | Plug | **OUT4** | Fourth output adapter |

## Functionality

This component is a simple "splitter" for the unidirectional data type **AIWS**. It has no internal logic, no states, and no events of its own. All values arriving via the input adapter `IN` are copied identically to the four output adapters `OUT1` through `OUT4`. This allows multiple subsequent function blocks (FBs) to be supplied with the same data in parallel.

Since the FB is designed generically (`GenericClassName = 'GEN_AIWS_SPLIT'`), the specific data type **AIWS** must be defined when inserting it into a project.

## Technical Features

- **Generic Implementation**: The FB is marked as a generic splitter via the attribute `eclipse4diac::core::GenericClassName`. The actual type is only determined during instantiation.
- **No Active Control**: The FB does not require any events to trigger – distribution occurs passively via the adapter connections.
- **Complete Transparency**: Changes to the adapter data are passed on to all outputs without delay.

## State Overview

The function block (FB) has no states or sequences of its own. It uses purely combinatorial routing.

## Application Scenarios

- **Distribution of Sensor Data** – A sensor value (e.g., temperature, pressure) is to be made available to multiple processing blocks simultaneously.
- **Redundant Data Backup** – A data stream is to be sent in parallel to two or more independent logic units.
- **Test and Simulation Setups** – A signal is split across multiple paths to test different response patterns.

## Comparison with Similar Function Blocks

- **Manual Wiring**: Without a splitter, each subsequent FB would have its own connection to the source FB, which reduces clarity.
- **Event-Based Splitters**: Some splitters use event outputs (e.g., `SPLIT` for arbitrary events). `AIWS_SPLIT_4` is specifically designed for the unidirectional **AIWS** adapter and requires no events.
- **Multiple Outputs**: Variants with two (e.g., `AIWS_SPLIT_2`) or more outputs are available; `AIWS_SPLIT_4` provides four outputs by default.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The `AIWS_SPLIT_4` is a simple yet essential component for distributing unidirectional **AIWS** adapter connections. It reduces wiring complexity, ensures clear structures, and enables the parallel use of a data stream by multiple function blocks without additional logic.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
